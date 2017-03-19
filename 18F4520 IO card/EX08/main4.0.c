/* Compile options:  -ml (Large code model) */

//#include <stdio.h>
#include <p18f4520.h>
#include <adc.h>
#include <timers.h>
#include "typedefs.h"
#include <math.h>
// #pragma config WDT = ON
	
/*
 *  IO_card.h
 *  Test
 *
 *  Created by Pelle Gunnerfeldt on 2011-04-12.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *

	v3.1
		2014-10-14
		Automan Efforts
	v4.0
		2014-11-14
		Fix groups
 */

// allocate some resources in ACCESS RAM for speedy access in interrupt routines
// all locations in this section are volatile



#define SWITCH_DATA  			PORTCbits.RC0		// originally RC0. First card changed to RC4. Why didn't RC0 work?
#define SWITCH_LOAD  			LATCbits.LATC1
#define CLOCK_PIN  				LATCbits.LATC2
#define LED_DATA  				LATCbits.LATC5
#define MUTE_DATA  				LATAbits.LATA5
#define MF_REG_DATA  			LATCbits.LATC5
#define LED_LOAD  				LATCbits.LATC6
#define MUTE_LOAD  				LATCbits.LATC7

#define DAC_PIN_9  				LATBbits.LATB3
#define DAC_PIN_7  				LATBbits.LATB4

#define DAC_DATA  				LATBbits.LATB3
#define DAC_LOAD  				LATBbits.LATB4

#define MUTE_IN	  				PORTCbits.RC3		// originally RA1. First card changed to RC3. Why didn't RA1 work?
#define LED	  					PORTAbits.RA1	

#define SSP_en          		!PORTBbits.RB0
#define SSP_clk          		PORTBbits.RB1
#define STROBE          		PORTBbits.RB2
#define SSP_write()         	TRISD = 0;
#define SSP_read()         		TRISD = 255;

#define STATUS_MASK				0x0C;
#define MUTE_MASK				0x10;

#define IO_CARD_ID				0x01				// bits 0b00110000 is free for check bits. 00 or 11 could be scrap data.
											// 01 or 10 is suitable

#define STOP_TMR_0				INTCONbits.TMR0IE=0
#define START_TMR_0				INTCONbits.TMR0IF=0;INTCONbits.TMR0IE=1

#define bit_set(var,bitno) ((var) |= 1 << (bitno))
#define bit_clr(var,bitno) ((var) &= ~(1 << (bitno)))
#define testbit_on(data,bitno) ((data>>bitno)&0x01)
#define testbitmask(data,bitmask) ((data&bitmask)==bitmask)

#define bits_on(var,mask) var |= mask
#define bits_off(var,mask) var &= ~0 ^ mask

#define hibyte(x)       (unsigned char)(x>>8)
#define lobyte(x)        (unsigned char)(x & 0xFF)

#define EX08_ID			0x12;
#define EX08MF_ID			0x22;
#define MAJOR				0;
#define MINOR				9;




#pragma udata access volatile_access

union dacUnion {
	struct {
		unsigned fill:2;
		unsigned vca_lo:8;
		unsigned vca_hi:2;
		unsigned address:4;
	}channel[8];
	unsigned int data[8];
};

ram near struct shiftDataStruct {
	unsigned char trimLed;
	unsigned char absLed;
	unsigned char mute;
}shiftData;

union INdataUnion {
	unsigned char data[16];
	unsigned int word[8];
	struct{
		unsigned vca_lo:8;
		unsigned vca_hi:2;
		unsigned status:2;
		unsigned id_change_flag:1;
		unsigned blink_flag:1;
		unsigned touchsense:1;
		unsigned mute:1;
		}channel[8];
	struct{
		unsigned :8;
		unsigned cmd:4;
		unsigned flag:1;
		unsigned :3;
		}cmd[8];
};
union OUTdataUnion {
	unsigned char data[16];
	unsigned int word[8];
	struct{
		unsigned vca_lo:8;
		unsigned vca_hi:2;
		unsigned status_press:1;
		unsigned status_release:1;
		unsigned card_id:2;
		unsigned mute_press:1;
		unsigned mute_release:1;
		}channel[8];
	struct{
		unsigned vca_lo:8;
		unsigned vca_hi:2;
		unsigned status:2;
		unsigned touch_press:1;
		unsigned touch_release:1;
		unsigned mute_press:1;
		unsigned mute_release:1;
		}mf[8];
};

ram near union INdataUnion INdata;
ram near union INdataUnion INbuffer;
ram near union OUTdataUnion OUTdata;
ram near unsigned char tempOUTdata[16];
ram near unsigned int VCAout[8];
ram near unsigned int VCAoutOld[8];

#pragma udata

unsigned char MOTORFADERS = 0;
unsigned char HANDSHAKE = 0;
unsigned char LocalMuteBits = 0; 				// 8 mute bits.
unsigned char SwitchBits = 0; 					// 8 switch bits.
unsigned char StoredSwitchBits = 0; 			// 8 accumulated switch bits.

int VCAoutStep[8];
unsigned int VCAinOld[8];
unsigned int VCAinOldest[24];
unsigned int BlinkCnt = 0;
unsigned int status_bits;
unsigned int VCAPassThru[8];
unsigned char VCAgroup=0;
//unsigned int VCAgroupValue[8];

 union VCAgroupLinUnion {
	unsigned int word[8];
	unsigned char bytes [16];
}VCAgroupLin;

byte BlinkLED = 1;
byte LEDtoggle = 1;
unsigned int testCV=0;
unsigned char VCAyes=0;

unsigned char CARD_ID = 1;

unsigned char hardwareReportState = 0;
unsigned char totalRecallState = 0;
unsigned char ledTRblink;
unsigned int ledTRcntr;

int adc;				// ADC int
byte adcMSB;			// ADC byte
byte adcLSB;			// ADC byte
byte adcchn = 0;
byte error;

const byte MANUAL =	0x00;
const byte AUTO = 0x04;
const byte TOUCH = 0x08;
const byte WRITE = 0x0C;

const unsigned char TICK_RATE = 8;

byte ShiftOut[5];		// Shift reg data out. LEDs and Motor Disable
						// byte 0 = MOTOR DISABLE
						// bytes 1-4:
						// bit 0 = AUTO LED	channel 7,5,3,1
						// bit 1 = TOUCH LED
						// bit 2 = WRITE LED
						// bit 3 = MUTE LED (inverted)
						// bit 4 = AUTO LED	channel 8,6,4,2
						// bit 5 = TOUCH LED
						// bit 6 = WRITE LED
						// bit 7 = MUTE LED (inverted)
byte ShiftIn;		// Shift reg data in. Switches



BOOL clk_flg = FALSE;

	unsigned long Ltimer;
	unsigned char clk_flag = 0; 
	unsigned char sw[8]; 
	unsigned char MUX[16];
//	unsigned char swbuf[40]; 
	unsigned long blinkcnt; 
	unsigned long cnt; 
	unsigned long Wcnt; 
	unsigned long wCntr; 
	unsigned long cnt1; 
	unsigned long cnt2;
	unsigned long cnt3; 
	unsigned int DACcnt;
	byte LEDword;
	unsigned int LEDcnt;
	unsigned int SWcnt;	
	short long DAClog;
	unsigned int DACval;
	unsigned int DACword;
	unsigned int DACaddr;
	unsigned char doOnce=0;
	unsigned char MFtimerTick;
	unsigned char muxCntr = 0;


	unsigned int vca_in;
	unsigned int lo_adc;
	unsigned int hi_adc;
	byte LED_byte;
	unsigned char test=0;

	unsigned int TEST2=0;

	unsigned char WriteToDACflag = 0;
	unsigned char ParallelPortflag = 0;
	unsigned char Q_Frame = 0;
	unsigned char Q_Frame_Flag = 1;
	unsigned char Timer_Flag = 1;
	unsigned char MFtimer = 0;

// *********************************** Prototypes ****************************************
void Init(void);
void Read_ADC(byte);
void Read_Mute(byte);
void Set_Get_VCA(unsigned char);
void Set_VCA(unsigned char);
void Read_Switches(void);
void Set_Mutes(void);
void Set_Leds(void);
void Motor_Faders(unsigned char);
void LEDaction(void);

int PGtoVCA(int);
int VCAtoPG(int);

#pragma code


// *********************************** Interrupts ****************************************

#pragma interrupt YourHighPriorityISRCode

	void YourHighPriorityISRCode()
	{
		unsigned char n, chn, i;
		unsigned char last_clk=0;
		unsigned char clk=0;
		static unsigned int ADval = 0;
		unsigned char inCmd = 0;

//		OUTdata.data[0]	= 0xff;
//		OUTdata.data[1]	= 0x13;


		if (INTCONbits.INT0IF)									// Interrupt flag for RB0
		{	
//			ClrWdt();											// Is this bad?


			cnt=0;	
			if(HANDSHAKE)
			{
				SSP_write();
			}										// First send the 16 bytes



			if(!hardwareReportState && !totalRecallState)
			{
				if (!ParallelPortflag)								// Interrupt flag for RB0
				{
					LATD = OUTdata.data[0];							// start with first byte on parallel port
					while(cnt<16)
					{
						while(SSP_clk==0){;}						// Wait for fisrt clock
						cnt++;										// count index
						LATD = OUTdata.data[(cnt)];					// Put byte on parallel port
						while(SSP_clk==1){;}						// Data must remain on the port until clock falls
						if(!SSP_en)break;							// if CS pin releases, abort
					}												// loop 16 times
					SSP_read();										// Then read
					while(cnt<32)
					{
						while(SSP_clk==0){;}						// Wait until clock rises
						INbuffer.data[cnt-16]=PORTD;					// read and store port in a buffer
						cnt++;										// count index
						while(SSP_clk==1){;}						// hold until clock falls
						if(!SSP_en)break;							// if CS pin releases, abort
					}		
					if(cnt==32)ParallelPortflag=1;					// Flag for new data in

				}
			}

			if(hardwareReportState)
			{	
				OUTdata.data[0] = CARD_ID;
				OUTdata.data[1] = MAJOR;
				OUTdata.data[2] = MINOR;
				OUTdata.data[3] = 0;
				cnt=0;

				LATD = OUTdata.data[0];							// start with first byte on parallel port
				while(cnt<4)
				{
					while(SSP_clk==0){;}						// Wait for fisrt clock
					cnt++;										// count index
					LATD = OUTdata.data[(cnt)];					// Put byte on parallel port
					while(SSP_clk==1){;}						// Data must remain on the port until clock falls
					if(!SSP_en){break;}							// if CS pin releases, abort
				}												// loop 4 times
				SSP_read();										// Then read
				while(cnt<8)
				{
					while(SSP_clk==0){;}						// Wait until clock rises
					// INbuffer.data[cnt-4]=PORTD;					// read and store port in a buffer
					cnt++;										// count index
					while(SSP_clk==1){;}						// hold until clock falls
					if(!SSP_en){break;}						// if CS pin releases, abort
				}	
				hardwareReportState=0;

			}							


			if(totalRecallState==1)
			{				
//				if(totalRecallState==1)totalRecallState=2;
				cnt=0;
				while(cnt<9)
				{
					LATD = ADval;								// Put byte on parallel port
					while(SSP_clk==0){;}						// Data must remain on the port until clock falls
					while(SSP_clk==1){;}
				//	if(!SSP_en)break;							// if CS pin releases, abort
						while( ADCON0bits.GO );
						ADval = ADRESH<<6;	
						ADval = ADval+(ADRESL>>2);				// put the word together
						LATE = MUX[cnt+1];
						ADCON0bits.GO = 1;								// Wait til ready
				//	ADCON0bits.GO = 0;
					cnt++;
				}		
				SSP_read();	
				while(SSP_clk==0){;}						// hold until clock falls
				inCmd=PORTD;								// read and store port in a buffer
				while(SSP_clk==1){;}
				
//	TRISAbits.TRISA0 = 1;							// Channel !!!
//	ConvertADC();
				if(inCmd==0xFF)
				{
					ADCON2bits.ACQT = 0x6;
					totalRecallState=0;
					ParallelPortflag=0;

				}
			}




			INTCONbits.INT0IF=0;								// clear int flag			
		}
		if (INTCON3bits.INT2IF)									// Interrupt flag for RB1
		{
			Q_Frame_Flag = 1;									// Strobe every Q frame
			INTCON3bits.INT2IF = 0;								// Clear interrupt on port RB1	
		}

	if (INTCONbits.TMR0IF)										// Timer base for creating slots in between transfers
		{			
			Timer_Flag = 1;										// Strobe DAC / ADC timer
			MFtimer++;
			if(MFtimer==2)MFtimerTick=1;						// Motorfader serial data. Second byte 
			ledTRcntr--;
			if(!ledTRcntr)
			{
				ledTRblink=!ledTRblink;
				ledTRcntr=192;
			}
			INTCONbits.TMR0IF = 0;
		}

	}
	#pragma interruptlow YourLowPriorityISRCode
	void YourLowPriorityISRCode()
	{
	
	}	//This return will be a "retfie", since this is in a #pragma interruptlow section 


#pragma code

// *********************************** Init ****************************************
void Init(void)
{
	int n;
	ADCON1 = 0b00111110;
	T1CONbits.T1OSCEN=0; 			// Turn off OSC Timer 1 thing. Didn't effect anything after all.ö
	TRISA = 0x0C;					// Port A: RA0=ADC, RA1=LED, RA2=VREF-, RA3=VREF+, RA5=MUTE_DATA, RA6=OSC;
	TRISB = 0x07;					// Port B: RB0, RB1, RB2=P.Port
	TRISC = 0x09; 					// Port C: RC0=SW_DATA, RC1=SW_LOAD, RC2=Clock, RC3=MUTE_IN
	TRISD = 0xFF;
	TRISE = 0x00;
	
	
    OpenADC(	ADC_FOSC_32     &
				ADC_RIGHT_JUST	&
				ADC_16_TAD,
				ADC_CH0		&
				ADC_INT_OFF		&
				ADC_VREFPLUS_EXT &
				ADC_VREFMINUS_EXT
				, 15 );


	CMCON = 0x07; /* Disable Comparator */

	// Set buffers to zero. Just in case
	for(n=0;n<16;n++)
	{
		OUTdata.data[n]=0;
		INdata.data[n]=0;
	}

	INTCONbits.GIE = 1;	// Enables Low Prio interrupts
	INTCONbits.PEIE = 1;		// Enables High Prio 
//	RCONbits.IPEN = 1;		// Enables Priorites
	INTCONbits.GIEL = 1;	// Enables Low Prio interrupts
	INTCONbits.GIEH = 1;		// Enables High Prio 

	INTCON2bits.INTEDG0 = 0; // Chip Select is inverted
	INTCON2bits.INTEDG2 = 0; // Strobe too
	INTCONbits.INT0IE = 1; // Bank Select RB0 interrupt - Bank Select
	INTCON3bits.INT2IE = 1; ; // Clock RB2 interrupt - Strobe


	OpenTimer0( TIMER_INT_ON &
	T0_8BIT &
	T0_SOURCE_INT &
	T0_PS_1_128 );		// Frequency for writing to ADC/DAC



	MUX[0]=0x0;
	MUX[1]=0x1;
	MUX[2]=0x3;		// Fader 1
	MUX[3]=0x5;		// Fader 2
	MUX[4]=0x6;		// Fader 3
	MUX[5]=0x7;		// Fader 4
	MUX[6]=0x4;		// Fader 5
	MUX[7]=0x2;		// Fader 6
	MUX[8]=0x1;		// Fader 7
	MUX[9]=0x3;		// Fader 8
	MUX[10]=0x5;
	MUX[11]=0x6;
	MUX[12]=0x7;
	MUX[13]=0x4;
	MUX[14]=0x2;
	MUX[15]=0x0;
}

// *********************************** MAIN ****************************************
void main (void)
{
	unsigned int loopCnt = 0;
	unsigned int addr;
	unsigned int word;
	unsigned char chn,n, i;
	unsigned char mux_cnt = 0;
	unsigned int ADC_value;
	static unsigned int testDAC=0;
	Init();
	SSP_read();
	DAC_LOAD=0;											// Clear all regs
	LED_LOAD=0;											// Clear all regs
	MUTE_LOAD=0;                              
	for(i=0;i<16;i++) 	// SCK (ABS LED)	
	{
		MF_REG_DATA = 0;
		CLOCK_PIN=1;
		CLOCK_PIN=0;	
	}
	LED_LOAD=1;										
	LED_LOAD=0;										
 	for(wCntr=0;wCntr<100000;wCntr++)
		{
		;
		}
	LED=0;
	// Try to shake hands with the motor faders (or other units) first
	// handShake();
	// Don't start collect data until receptor unit is defined!
	
//	HANDSHAKE=MOTORFADERS=1;
	while(1)
	{
		LEDaction();
		if(ParallelPortflag)							// New Data arrived
		{
			LEDtoggle=!LEDtoggle;
			for(n=0;n<8;n++)							// loop thru channels
			{
				if(MOTORFADERS)
				{
					INdata.word[n]=INbuffer.word[n];		// Copy buffer
				}
				else
				{
					if((INbuffer.cmd[n].flag==0) && !hardwareReportState)				// same as id change flag
					{
						INdata.word[n]=INbuffer.word[n];		// Copy buffer
					}
					else
					{
	//LED=!LED;
						if(INbuffer.channel[n].blink_flag)			// Blink Command
						{
							INdata.word[n]=INbuffer.word[n];		// Copy buffer
						}
						else
						{
							if(INbuffer.cmd[n].cmd == 1)			// HW Report
							{
								hardwareReportState=1;
							}
							if(INbuffer.cmd[n].cmd == 2)
							{
								totalRecallState=1;
								ADCON2bits.ACQT = 0;
								TRISAbits.TRISA0 = 1;							// Channel !!!
								ADCON0bits.ADON=1;
							}
						}
					}
				}
			}
			// testCV=(testCV++)&0x3FF;


            // **** Motorfaders only
            if(MOTORFADERS || !HANDSHAKE)
            {
                Motor_Faders(0);		// Q frame 0
            }

			MFtimer=0;

            // **** SSL only
            if(!MOTORFADERS && HANDSHAKE && !totalRecallState)
            {
				for(chn=0;chn<8;chn++)						// loop thru channels
				{
					LEDaction();
					VCAout[chn]=1023-(PGtoVCA(INdata.word[chn]&0x3FF));
					ADC_value = VCAtoPG(VCAinOld[chn]);			// convert to linear scale. Why Old?
					// try to hold interrupt here
					INTCONbits.INT0IE = 0; // Bank Select RB0 interrupt - Bank Select
				// To keep software from reading fader pos when mute
				// We need to delay the ouput one frame
				// only when muted. So no latency is added
				if(!testbit_on(LocalMuteBits,chn))
				{
					OUTdata.channel[chn].vca_lo = ADC_value&0xFF;	// split the WORD
					OUTdata.channel[chn].vca_hi = ADC_value>>8;
					VCAinOldest[chn]=VCAinOldest[chn+8];
				//	VCAinOldest[chn+8]=VCAinOldest[chn+16];
					VCAinOldest[chn+8]=ADC_value;
				}
				else
				{
					OUTdata.channel[chn].vca_lo = VCAinOldest[chn]&0xFF;	// split the WORD
					OUTdata.channel[chn].vca_hi = VCAinOldest[chn]>>8;
				}
//					OUTdata.channel[chn].card_id=IO_CARD_ID;
					// release interrupt
					INTCONbits.INT0IE = 1; // Bank Select RB0 interrupt - Bank Select
				}
	
			}
			doOnce=1;									// flag for mute switch reads
/*
            if(VCAgroup)								// When motor faders are in VCA group the DAC is updated with incomming value
            {
				for(chn=0;chn<8;chn++)						// loop thru channels
				{
				//	VCAout[chn]=testDAC++;
				//	if(testDAC>1023)testDAC=0;
					VCAout[chn]=1023-(PGtoVCA(VCAgroupValue[chn]));
				}
	
			}
*/
			ParallelPortflag=0;							// Clear transfer flag. Buffer is safe to write to
            // **** SSL only
            if(!MOTORFADERS && HANDSHAKE)
            {
				Read_Switches();
			}
			
		}

		if(totalRecallState)
		{	
			LEDaction();
		}
		else
		{
			if(Timer_Flag)						// Frequency?
		//	if(Q_Frame_Flag)						// Subframe (Frame X 4)
			{
				Timer_Flag = 0;
				Q_Frame_Flag = 0;
				if(HANDSHAKE)
				{
		            // **** SSL only
		            if(!MOTORFADERS)
		            {
						for(n=0;n<8;n++)						// loop thru channels
						{	
							LEDaction();
							Set_Get_VCA(n);							// Read fader and write to DAC
						}
						Set_Leds();								// write mute and leds
					}
					else
					{
			            // **** SSL VCAgroup
			        //    if(VCAgroup && VCAyes)
			            {
							for(n=0;n<8;n++)						// loop thru channels
							{	
							//	Read_ADC(n);
								Read_Mute(n);								// Read the Mute only
								Set_VCA(n);							// write to DAC
							}
						}
					}
					Set_Mutes();								// write mute and leds
				}
	
				BlinkCnt++;
				if(BlinkCnt>30)
				{
					BlinkLED=!BlinkLED;
					BlinkCnt=0;
				}
			}
	
	        // **** Motorfaders only
	        if(MOTORFADERS || !HANDSHAKE)
	        {
	            if(MFtimerTick)						// New Data arrived
	            {
					Motor_Faders(1);		// Q frame 1
	                MFtimerTick=0;
					for(chn=0;chn<8;chn++)						// loop thru channels
					{
						VCAout[chn]=1023-(PGtoVCA(VCAgroupLin.word[chn]));
					}
					
	            }
	        }
		}	


	}
}

// *********************************** Motor Fader Communication ****************************************

void Motor_Faders(unsigned char byteSwitch)
{
	unsigned char i,n,m;
	unsigned char OutByte;
	unsigned char debugByte;
	unsigned int VCAGroupValueTemp =0;
	static unsigned int handshakeTmr = 0x6F;
	static unsigned char fakeChnNo = 1;
	static unsigned char VCAgroupFlag = 0;
	static unsigned int fakeCnt = 1;
	static unsigned char SendFaderIDs=0;
	static unsigned int VCAsetCntr=0;

if(totalRecallState || hardwareReportState) return;
	
//	DAC_LOAD=1;											// This is probably not neccesary
	LED_LOAD=0;											// Clear all regs
	MUTE_LOAD=0;                                        // This is probably not neccesary
/*	
	if(SendFaderIDs==1)				// new Fader ID after handshake
	{
		for(i=0;i<8;i++)
		{
			INdata.data[i*2]=i;	
			INdata.data[(i*2)+1]=0x10;	// 0x1X is only used for commands. 0xX1 is handshake.
		}
		SendFaderIDs++;
	}	
	if(SendFaderIDs==2)				// Next phase -> Wave
	{
		for(i=0;i<8;i++)
		{
			INdata.data[i*2]=i;	
			INdata.data[(i*2)+1]=0x14;	// 0x1X is only used for commands. 0xX4 is wave
		}
		SendFaderIDs=0; 		// or. Continue with something else?
	}
*/

	if(!HANDSHAKE)
	{
		for(i=0;i<8;i++)
		{
			INdata.data[i*2]=0x02;	
			INdata.data[(i*2)+1]=0x11;	// 0x1X is only used for commands. 0xX1 is handshake.
		}
	}

	if(VCAgroupFlag)		// flag is set for toggling fader mode
	{
		if(!byteSwitch) VCAgroup=!VCAgroup;	// only on the first byte, toggle mode
		else VCAgroupFlag=0;				// when last byte, clear flag

		for(i=0;i<8;i++)
		{
			INdata.data[i*2]=0x01+VCAgroup;		// 1 for standard mode, 2 for vca group
			INdata.data[(i*2)+1]=0x12;			// 0x1X is only used for commands. 0xX2 is fader mode
		}
	}
    // This loop is running thru all the bits of the 8 bytes. 
     
	for(n=0;n<8;n++)
	{		
	
	// Clock bit "n" from all the 8 bytes
	
		for(i=0;i<8;i++)	// SDO (TRIM LED)
		{
			
	// Msb out first. "byteSwitch" determines if it's byte 0 or 1
	
			OutByte=(INdata.data[((7-i)*2)+byteSwitch]>>(7-n));
	 		MF_REG_DATA=~(OutByte & 1);

    // Clock it
    
			CLOCK_PIN=1;
			CLOCK_PIN=0;	
		}
			
	// Next 8 bits is for preparing clock rise to all the MF MCUs
	
		for(i=0;i<8;i++) 	// SCK (ABS LED)	
		{
			MF_REG_DATA = 0;
			CLOCK_PIN=1;
			CLOCK_PIN=0;	
		}
	
	// When 8 data bits and 8 clock bits are set. Load to clock the bit into the MF MCU.
	
		LED_LOAD=1;
		LED_LOAD=0;
		
	// Maintain the data bits for the falling SPI clock
		
		for(i=0;i<8;i++)	// SDO (TRIM LED)
		{
			OutByte=(INdata.data[((7-i)*2)+byteSwitch]>>(7-n));
	 		MF_REG_DATA=~(OutByte & 1);
			CLOCK_PIN=1;
			CLOCK_PIN=0;	
		}
	
	// This is a good time to capture the returning data. So strobe the Switch Reg to latch the current pins.
	
		SWITCH_LOAD = 0;
		SWITCH_LOAD = 1;
		
	// Now the Switch register outputs the serial data. So, catch when clocking out the clock-low bits
	
		for(i=0;i<8;i++) 	// SCK (ABS LED)	
		{
		
	// Shift the data left. Msb first.	


	// ====================================== NEW NEW NEW =========================================
	//		OUTdata.data[((7-i)*2)+byteSwitch] <<= 1;
			tempOUTdata[((7-i)*2)+byteSwitch] <<= 1;

			if(SWITCH_DATA) tempOUTdata[((7-i)*2)+byteSwitch]+=0x01;
	
			MF_REG_DATA = 1;
			CLOCK_PIN=1;
			CLOCK_PIN=0;	
		}
		
	// Strobe LED chip again to trigger clock-low
	
		LED_LOAD=1;
		LED_LOAD=0;
		
	}
	if(!HANDSHAKE)			// if init sequence
	{
		handshakeTmr--;
		if(!handshakeTmr)HANDSHAKE=1;
		if(byteSwitch)
		{
			for(i=0;i<16;i++)
			{
				if(tempOUTdata[i]==0xF0)		// Normally forbidden so it means MF wants to handshake
				{
					MOTORFADERS=1;
					HANDSHAKE=1;
					SendFaderIDs=1;
					CARD_ID = EX08MF_ID;
				}
				OUTdata.data[i]=0;			// Must clear this before sending to host
			}
		}
	}
	else											// not init sequence
	{
		if(byteSwitch)								// only after second byte has been read
		{
			if(!VCAgroup)							// if not in VCA group mode
			{
				VCAyes=0;VCAsetCntr=0;
				for(i=0;i<16;i++)
				{
					OUTdata.data[i]=tempOUTdata[i];		// copy buffer
				}
			}			
			else
			{
				// must wait some frames to update DAC
				VCAsetCntr++;
				if(VCAsetCntr>2){VCAsetCntr=10;VCAyes=1;}
				for(i=0;i<8;i++)						// 
				{
					OUTdata.data[(i*2)+1]&=0x03;			// make sure any "write drop out" event clears
/*
					VCAGroupValueTemp=tempOUTdata[(i*2)+1]&0x03;
					VCAGroupValueTemp<<=8;
					VCAGroupValueTemp+=tempOUTdata[(i*2)];
*/
				//	VCAout[i]=1023-(PGtoVCA(VCAGroupValueTemp));

					VCAgroupLin.bytes[(i*2)]=tempOUTdata[(i*2)];
					VCAgroupLin.bytes[(i*2)+1]=tempOUTdata[(i*2)+1]&0x03;
		
					if(INdata.channel[i].blink_flag) VCAgroup = 0;	// reset fader mode locally
				}	
			}
			for(i=0;i<8;i++)						// check for vca mode
			{
				if((tempOUTdata[(i*2)+1]&0x30)==0x30)		// Normally forbidden.MF sends a fader mode switch command
				{
				//	VCAgroup = !VCAgroup;			// toggle VCA group mode. NOT YET. MUST SEND CMD TO THE FADERS FIRST
					tempOUTdata[(i*2)+1]&=0x03;			// clear this before sending to host
					OUTdata.data[(i*2)+1]&=0x03;			// clear this before sending to host

					VCAgroupFlag=1;					// flag for sending out fader mode next loop
				}
			}
			if(VCAgroupFlag==1)
			{
				for(i=0;i<8;i++)						// check for vca mode
				{
					OUTdata.data[(i*2)+1]&=0x03;			// clear this before sending to host
					if(INdata.channel[i].status==0x03)		// Clear Write Status when jumping to Group Mode
					{
						OUTdata.data[(i*2)+1]+=0x0C;			// clear this before sending to host
					}
				}
			}			
		}
	}
}

// *********************************** DAC only ****************************************
void Set_VCA(unsigned char ch){
	unsigned int loopCnt = 0;
	unsigned int word;
	unsigned int addr;
	unsigned int DACvalue;

	DACvalue = ((VCAout[ch]+(VCAoutOld[ch]))/2);	// VCA data from computer

//	DACvalue += VCAPassThru[ch];
//	DACvalue =0;

	if(MUTE_DATA=testbit_on(LocalMuteBits,ch))DACvalue=1023;

	VCAoutOld[ch]=DACvalue;


	addr = ch+1;								// address for the DAC ( 1 of 8)
	word = (addr<<12)+(DACvalue<<2);			// align the data right

	CLOCK_PIN = 0;								// prepare DAC chip
	DAC_LOAD = 0;
	for(loopCnt=0;loopCnt<16;loopCnt++){		// shift the DATA out
  		DAC_DATA=testbit_on(word,15-loopCnt);
		CLOCK_PIN = 1;
		CLOCK_PIN = 0;
	}
	DAC_LOAD = 1;								// Release the DAC chip

//	}
}
// *********************************** Mute out register ****************************************

void Set_Mutes(void)
	{
	unsigned char i;
	MUTE_LOAD=0;
	for(i=0;i<8;i++)								// First send Mute data
	{
//		Always do hard mute for SSL mutes
//		if(INdata.channel[i].status==0) {			// if Fader is in Manual Input MUTE > Output MUTE
			MF_REG_DATA=testbit_on(LocalMuteBits,i);
//			MF_REG_DATA=0;
//		}
//		else {										// Else. System is in control. Latching
//			MUTE_DATA=INdata.channel[i].mute;
//		}
//		if(i==1)MUTE_DATA=1;
//		else MUTE_DATA=0;
		CLOCK_PIN=1;
		CLOCK_PIN=0;
	}
	for(i=0;i<16;i++)								// First send Mute data
	{
		MF_REG_DATA=1;
		CLOCK_PIN=1;
		CLOCK_PIN=0;
	}


	MUTE_LOAD=1;																						// Strobe chips
	MUTE_LOAD=0;
	}
// *********************************** Mute & Led out registers ****************************************

void Set_Leds(void)
	{
	unsigned char i;

	DAC_LOAD=1;										// Clear all regs
	LED_LOAD=0;

	for(i=0;i<8;i++) 	// ABS LED							// Send LED data
	{
		LED_DATA=(INdata.channel[7-i].status!=0);		// TRIM LED should lit for all states except manual
		CLOCK_PIN=1;
		CLOCK_PIN=0;	
	}
	for(i=0;i<8;i++)	// TRIM LED						
	{
		LED_DATA=(INdata.channel[7-i].status==3);													// Write is lit only in WRITE STATE
		if(INdata.channel[7-i].touchsense)LED_DATA=(BlinkLED&(INdata.channel[7-i].status!=0));		// Write blink when Touch sense is set and not in Manual
		CLOCK_PIN=1;
		CLOCK_PIN=0;	
	}

	LED_LOAD=1;
	LED_LOAD=0;
	}

// *********************************** ADC and DAC ****************************************
void Set_Get_VCA(unsigned char ch){
	unsigned int loopCnt = 0;
	unsigned int word;
	unsigned int addr;
	unsigned int DACvalue;
	Read_ADC(ch);								// Read the ADC

//	INdata.channel[ch].status=1;				// !!!!!!!!!!!!!!

	if(INdata.channel[ch].status==0) {			// if Fader is in Manual state DAC should copy ADC
		DACvalue = VCAPassThru[ch];				// VCA data still in log form
	}
	else {
		DACvalue = (VCAout[ch]+(VCAoutOld[ch]))/2;	// VCA data from computer
		VCAoutOld[ch]=DACvalue;
	}


	addr = ch+1;								// address for the DAC ( 1 of 8)
	word = (addr<<12)+(DACvalue<<2);			// align the data right

	CLOCK_PIN = 0;								// prepare DAC chip
	DAC_LOAD = 0;
	for(loopCnt=0;loopCnt<16;loopCnt++){		// shift the DATA out
  		DAC_DATA=testbit_on(word,15-loopCnt);
		CLOCK_PIN = 1;
		CLOCK_PIN = 0;
	}
	DAC_LOAD = 1;								// Release the DAC chip

//	}
}

// *********************************** Read Status Switches ****************************************
void Read_Switches(void)
	{
	unsigned char n,m,SwitchXOR,PresSwitches,RelSwitches;
	SwitchBits=0;
	SWITCH_LOAD = 0;
	SWITCH_LOAD = 1;

	for (n=0;n<8;n++){
		OUTdata.channel[n].status_press = 0;					// clear event flag instead of waitloop
		if(SWITCH_DATA)bit_set(SwitchBits,n);					// Set a 1 if pin is 1
		CLOCK_PIN = 1;
		OUTdata.channel[n].status_release = 0;				// clear event flag instead of waitloop
		CLOCK_PIN = 0;
	}

	if(SwitchBits!=StoredSwitchBits) {							// If previous 8 bits are NOT equal with the current 8 bits:
		SwitchXOR=SwitchBits^StoredSwitchBits;					// Create a mask with all changed bits
		PresSwitches=SwitchBits&SwitchXOR;						// Mask out all Pressed switches
		RelSwitches=StoredSwitchBits&SwitchXOR;					// Mask out all Released Switches

		for (n=0;n<8;n++){
			OUTdata.channel[7-n].status_press	= PresSwitches & 1;		// Pack pressed switches in the Struct
			OUTdata.channel[7-n].status_release	= RelSwitches & 1;		// Pack released switches in the Struct
			PresSwitches>>=1;											// Shift right
			RelSwitches>>=1;											// Shift right
//			OUTdata.channel[7-n].card_id=CARD_ID;						// If we're reading  switches card ID is 0x01;
		}
	}
	StoredSwitchBits=SwitchBits;								// Copy Switch pins til next read		
}

//********************************************************************
//
//	P&G to VCA
//	input: int PG
//	output: int VCA
//
//********************************************************************

int PGtoVCA(int PG)
	 {
	unsigned int VCA;				//VCA fader value
	unsigned long groundlevel;		//VCA fader value as long
	unsigned long val;				//VCA fader value as long

	if(PG<157)
		{
		val=PG;
		groundlevel=0;
		val=val*3677;
		val=val/1000;
		}
	else
		{
		val=PG-157;
		groundlevel=577;
		val=val*515;
		val=val/1000;
		}
	VCA=val+groundlevel;
	return VCA;
	}

//********************************************************************
//
//	VCA to P&G
//	input: int VCA
//	output: int PG
//
//********************************************************************


int VCAtoPG(int VCA)
	{
	unsigned int PG=0;			//P&G fader value
	unsigned long groundlevel;		//VCA fader value as long
	unsigned long val;		//VCA fader value as long

	if(VCA<577)
		{
		val=VCA;
		groundlevel=0;
		val=val*271;
		val=val/1000;
		}
	else
		{
		val=VCA-577;
		groundlevel=157;
		val=val*1942;
		val=val/1000;
		}
	PG=val+groundlevel;
	return PG;
	}

// *********************************** Start ADC ****************************************
void Start_ADC(void)
	{
	ConvertADC();
	}

// ****************************** Read ADC & Mute Pin************************************


void Read_ADC(unsigned char chn)
	{
	unsigned int ADC_value;											// Start conversion
	if(doOnce)														// This can only be run once each frame
	{
		if(((LocalMuteBits>>chn)&1) != MUTE_IN)						// Check for MUTE change
		{
			if(MUTE_IN) 
			{
				OUTdata.channel[chn].mute_press = 1;				// Event flag for mute press
				OUTdata.channel[chn].mute_release = 0;					// clear event flag
				bit_set(LocalMuteBits,chn);							// Set bit in a storage byte

			}
			else
			{
				OUTdata.channel[chn].mute_press = 0;				// clear event flag
				OUTdata.channel[chn].mute_release = 1;				// Event flag for mute release
				bit_clr(LocalMuteBits,chn);							// Clear bit in a storage byte
			}
		}
		else
		{
			OUTdata.channel[chn].mute_press = 0;					// clear event flag
			OUTdata.channel[chn].mute_release = 0;					// clear event flag
		}

//		doOnce=0;  Must read 8 times for all chns
		if(chn==7)doOnce=0; 
	}
	
	ADCON0bits.ADON=0;
	TRISAbits.TRISA0 = 0;

	if(!MUTE_IN)
	{
		while( BusyADC() );								// Wait til ready
	
		ADC_value = ADRESH;	
		ADC_value = (ADC_value<<8)+ADRESL;				// put the word together
	
	
		VCAPassThru[chn] = ADC_value;					// Untouched value for manual fader state
		ADC_value = 1023-ADC_value;						// reverse scale
		ADC_value = (ADC_value + (VCAinOld[chn]*1))/2;	// this use to be 4 to 1
		VCAinOld[chn] = ADC_value;
	}

	LATE = MUX[chn];
	TRISAbits.TRISA0 = 1;							// Channel !!!
	ADCON0bits.ADON=1;
	ConvertADC();

	}
// ****************************** Read ADC & Mute Pin************************************


void Read_Mute(unsigned char chn)
	{
	if(doOnce)														// This can only be run once each frame
	{
//		if(((LocalMuteBits>>chn)&1) != MUTE_IN)						// Check for MUTE change
		{
			if(MUTE_IN) 
			{
			//	OUTdata.channel[chn].mute_press = 1;				// Event flag for mute press
			//	OUTdata.channel[chn].mute_release = 0;					// clear event flag
				bit_set(LocalMuteBits,chn);							// Set bit in a storage byte
			}
			else
			{
			//	OUTdata.channel[chn].mute_press = 0;				// clear event flag
			//	OUTdata.channel[chn].mute_release = 1;				// Event flag for mute release
				bit_clr(LocalMuteBits,chn);							// Clear bit in a storage byte
			}
		}
//		else
		{
		//	OUTdata.channel[chn].mute_press = 0;					// clear event flag
		//	OUTdata.channel[chn].mute_release = 0;					// clear event flag
		} 
	}
	if(chn==7)doOnce=0;
	LATE = MUX[chn];

	}

// ****************************** LED action************************************


void LEDaction(void)
{
	static unsigned int LEDcntr=0x8000;
	static unsigned int LEDdim=0xFFFF;
	static unsigned int LEDcntr2=0x0;
	
/*
	if(INdata.channel[0].status)LED=0;
	else LED=1;
*/

	if(HANDSHAKE)
	{
		if(totalRecallState)
		{
			LED=ledTRblink;return;
		}
		if(!MOTORFADERS && !totalRecallState)
		{
		//	LED=0;
		//
			LEDcntr>>=1;
			if(!(LEDcntr&LEDdim))LED=0;
			else LED=1;
	
			if(LEDcntr==0)
			{
				LEDcntr=0x8000;
				LEDcntr2++;
				if(LEDcntr2>0x2FF)
				{
					LEDcntr2=0x0;
					LEDdim>>=1;
					if(LEDdim==0)LEDdim=0xFFFF;
				}
			}	
		}
		else
		{
			LED=LEDtoggle;
		}
	}
	else
	{
		LEDcntr2++;
		if(LEDcntr2==0xFFFF)
		{
			LEDcntr2=0x0;
			LED=!LED;
		}
	}
}

