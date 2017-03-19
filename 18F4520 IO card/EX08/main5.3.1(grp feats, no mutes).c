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
	v3.2
		2014-11-12
		+ Add Group snapshot data
	v5.1
		2014-11-19
		+ Try 3 byte SPI transfers
	v5.3.1
		2015-02-12
		+ Add Group snapshot, again
		+ Add Group recall, again (see new Protocol)
		+ Added group mutes (for test) v5.3.1 is mutes bypassed

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

#define EX08_ID				0x12;
#define EX08MF_ID			0x22;
#define MAJOR				0;
#define MINOR				9;

#define SLOW		103
#define FAST		130



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
	struct{
		unsigned char id;
		unsigned :4;
		unsigned id_change_flag:1;
		unsigned :3;
	}id[8];
	struct{
		unsigned lo_byte:8;
		unsigned :6;
		unsigned hi_byte:2;
	}vcaGroup[8];
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
// ram near unsigned char tempOUTdata[16];
ram near signed int VCAout[8];
ram near signed int VCAoutOld[8];
ram near signed int DACsetPoint[8];
ram near unsigned char cueTableCntr;
ram near unsigned char cueTableFlag;

#pragma udata

unsigned char MOTORFADERS = 0;
unsigned char HANDSHAKE = 0;
unsigned char LocalMuteBits = 0; 				// 8 mute bits.
unsigned char SwitchBits = 0; 					// 8 switch bits.
unsigned char StoredSwitchBits = 0; 			// 8 accumulated switch bits.

unsigned int BlinkCnt = 0;
unsigned int status_bits;
unsigned int VCAfader[8];
unsigned char muxIndex=0;
unsigned char lastMuxedIndex=0;
unsigned char VCAgroup=0;
unsigned char fpsCntr;
unsigned char fpsTmr = FAST;
union {
	unsigned int word[8];
	unsigned char bytes [16];
}VCAgroupLin;
union {
	unsigned int word[8];
	unsigned char bytes [16];
}MFlevels;

// unsigned char grpMute[8];
// unsigned char grpMuteReleaseArm[8];

byte BlinkLED = 1;
byte LEDtoggle = 1;
unsigned int testCV=0;
unsigned char VCAyes=0;

unsigned char CARD_ID = 1;



unsigned char automationState = 1;
unsigned char grpSnapshot = 0;
unsigned char grpRecall = 0;
unsigned char hardwareReportState = 0;
unsigned char totalRecallState = 0;
unsigned char ledTRblink;
unsigned int ledTRcntr;
unsigned char statusFlag = 0;

int DACdelta[8];
int DACdeltaBuf[8];

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
	unsigned char MFtimerIndex=0;
	unsigned int tempVCA;

// *********************************** Prototypes ****************************************
void Init(void);
void Read_Mute(byte);
void Set_VCA(void);
void Set_Mutes(void);
void Motor_Faders(unsigned char);

int PGtoVCA(int);
int VCAtoPG(int);

char ReadEEPROM(char address);
void WriteEEPROM(char address,char data);

#pragma code


// *********************************** Interrupts ****************************************

#pragma interrupt YourHighPriorityISRCode

	void YourHighPriorityISRCode()
	{
		unsigned char n, chn, i;
//		unsigned char last_clk=0;
//		unsigned char clk=0;
//		static unsigned int ADval = 0;
//		unsigned char inCmd = 0;


		if (INTCONbits.INT0IF)									// Interrupt flag for RB0
		{
			cnt=0;
			SSP_write();
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

				cueTableCntr=0;
				fpsCntr=0;

/*  +++++++++++++   This is new. Reset cueTable timer so it syncs to incomming data +++++++++++++++ 	*/
				INTCONbits.TMR0IF = 0;
				TMR0L=130;
			}
			INTCONbits.INT0IF=0;								// clear int flag
		}

		if (INTCON3bits.INT2IF)									// Interrupt flag for RB1
		{
			Q_Frame_Flag = 1;									// Strobe every Q frame
			INTCON3bits.INT2IF = 0;								// Clear interrupt on port RB1
		}


	if (PIR1bits.ADIF)									// Interrupt flag for ADC
	{
		VCAfader[lastMuxedIndex] = ADRESH;	
		VCAfader[lastMuxedIndex] = (VCAfader[lastMuxedIndex]<<8)+ADRESL;				// put the word together
		PIR1bits.ADIF = 0;									// Clear interrupt	
	}
/*
	Fires with a 2ms interval
	Builds a cue table for operations
	16 slots per cycle
	each slot must not exceed 2ms

	Motor Fader Index reset on every busComm
	The other circulate freely

	Cue Table (0-15):

	Odd	- MUX ADC
		  Update DAC + Mute
		  Read Switches

	Even	- Read ADC + Mute
		  Update DAC + Mute
		  Update LEDs

*/


	if (INTCONbits.TMR0IF)										// Timer base for creating slots in between transfers
	{			
		cueTableCntr++;
		cueTableFlag=1;	

		BlinkCnt++;

//		BlinkLED=(BlinkCnt&0x0040)!=0;
//		BlinkTouchStatusLED=(BlinkCnt&0x0380)!=0;

		INTCONbits.TMR0IF = 0;
		TMR0L=130;	
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
	T1CONbits.T1OSCEN=0; 			// Turn off OSC Timer 1 thing. Didn't effect anything after all.�
	TRISA = 0x0D;					// Port A: RA0=ADC, RA1=LED, RA2=VREF-, RA3=VREF+, RA5=MUTE_DATA, RA6=OSC;
	TRISB = 0x07;					// Port B: RB0, RB1, RB2=P.Port
	TRISC = 0x09; 					// Port C: RC0=SW_DATA, RC1=SW_LOAD, RC2=Clock, RC3=MUTE_IN
	TRISD = 0xFF;
	TRISE = 0x00;


    OpenADC(	ADC_FOSC_32     &
				ADC_RIGHT_JUST	&
				ADC_16_TAD,
				ADC_CH0		&
				ADC_INT_ON		&
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

	PIE1bits.ADIE=1;
	PIR1bits.ADIF=0;

	INTCON2bits.INTEDG0 = 0; // Chip Select is inverted
	INTCON2bits.INTEDG2 = 0; // Strobe too
	INTCONbits.INT0IE = 1; // Bank Select RB0 interrupt - Bank Select
	INTCON3bits.INT2IE = 1; ; // Clock RB2 interrupt - Strobe


	OpenTimer0( TIMER_INT_ON &
	T0_8BIT &
	T0_SOURCE_INT &
	T0_PS_1_256 );		// Frequency for writing to ADC/DAC

	MUX[0]=0x2;
	MUX[1]=0x0;
	MUX[2]=0x1;
	MUX[3]=0x3;
	MUX[4]=0x5;
	MUX[5]=0x6;
	MUX[6]=0x7;
	MUX[7]=0x4;

	cueTableCntr=0;
	cueTableFlag=0;
	fpsCntr=0;
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
	unsigned char chIndex=0;
	unsigned char copyBufferFlag=1;
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

	for(i=0;i<16;i++)
	{
//		VCAgroupLin.bytes[i]=ReadEEPROM(i);
		VCAgroupLin.word[i]=816;
	}

	while(1)
	{
		// Flag for trigger a new packet in (One per frame)

		if(ParallelPortflag)	
		{
			ParallelPortflag=0;	
			copyBufferFlag=1;

			// First check for commands 
			// All ID channels over 96 is consider a command

			if(INbuffer.id[0].id_change_flag && INbuffer.id[0].id>96)
			{
				switch (INbuffer.id[0].id-96)
				{
					// CMD 1 = grpRecall
					case 1:
						grpRecall=1;
					break;
	
					// CMD 2 = grpSnapshot
					case 2:
						grpSnapshot=1;
					// don't copy buffer
						copyBufferFlag=0;
					break;
				}
			}

			// When grpRecall reach 2nd state the incomming level is targeted for the Group levels
			if (grpRecall==2)
			{
				for(i=0;i<8;i++)
				{
//					VCAgroupLin.word[i]=INbuffer.word[i]&0x3FF;
//					grpMute[i]=(INbuffer.word[i]&0x08)>>7;
				}
			}	

			if (grpSnapshot==2)
			{
				for(i=0;i<8;i++)
				{
					OUTdata.word[i]=MFlevels.word[i];
				}
				grpSnapshot=0;
			}

			// Copy the data from the buffer. Not when the level field is occupied by command
			if(copyBufferFlag)
			{
				for(n=0;n<8;n++)	
				{
					INdata.word[n]=INbuffer.word[n];		
				}
			}

			LED=!LED;
		}
	

		if(cueTableFlag)
		{
			muxIndex=(cueTableCntr>>1)&7;
				switch (cueTableCntr)		// stretch the 3 bytes over the whole frame
				{
					case 2:
						Motor_Faders(0);
					break;
					case 4:
						Motor_Faders(1);
					break;
					case 6:
						Motor_Faders(2);
						Set_VCA();
					break;
				}

				Read_Mute(lastMuxedIndex);
				LATE = MUX[muxIndex]; 	 
				lastMuxedIndex=muxIndex;


			if((cueTableCntr&1)==0)	// even
			{
			/*
				ADC_value=VCAtoPG(1023-VCAfader[muxIndex]);
				INTCONbits.INT0IE = 0;
				OUTdata.channel[muxIndex].vca_lo=ADC_value&0xFF;
				OUTdata.channel[muxIndex].vca_hi=ADC_value>>8;
				INTCONbits.INT0IE = 1;
			*/
			//	Set_Mutes();
			//	Set_VCA();			// 1.28ms

			}

			else				// odd
			{
			//	ConvertADC(); // Start conversion
				// Read Mute + Start Conversion
				Set_Mutes();
			//	Set_VCA();			// 1.28ms
			/*
				if(muxIndex=7)
				{
			//		Set_Leds();
				}
			*/
			}
			cueTableFlag=0;
		}
	}
}

// *********************************** Motor Fader Communication ****************************************

void Motor_Faders(unsigned char byteSwitch)
{
	unsigned char i,j,n,m;
	unsigned char OutByte;
	unsigned int VCAGroupValueTemp =0;
	static unsigned char VCAgroupState = 0;
	static unsigned char tempOUTdata[16];
	unsigned static char groupSave=0;


	LED_LOAD=0;											// Clear all regs
	MUTE_LOAD=0;                                        // This is probably not neccesary

	if(grpRecall==1 && byteSwitch==0)
	{
		VCAgroupState=1;
		VCAgroup=0;
	}

	if(VCAgroupState==1 && byteSwitch==0)		// First state of VCA group switch detected
	{
		for(i=0;i<8;i++)
		{
			INdata.data[i*2]=0x01+!VCAgroup;		// 1 for standard mode, 2 for vca group
			INdata.data[(i*2)+1]=0x12;			// 0x1X is only used for commands. 0xX2 is fader mode
		}
	}

	if(VCAgroupState==2 && byteSwitch==0 && !VCAgroup)		// First state of VCA group switch detected
	{
		for(i=0;i<8;i++)
		{
			INdata.data[i*2]=VCAgroupLin.bytes[i*2];	
			INdata.data[(i*2)+1]=0x13+(VCAgroupLin.bytes[(i*2)+1]<<5);	
		}
	}


	for(n=0;n<8;n++)
	{
	// Clock bit "n" from all the 8 bytes

		for(i=0;i<8;i++)	// SDO (TRIM LED)
		{
			// Msb out first
			if(byteSwitch==0)
			{
				OutByte =INdata.data[(7-i)*2]&0b00111111;					// 6 bits from first byte
				OutByte+=0b01000000;										// add sync bits
			}
			if(byteSwitch==1)
			{
				OutByte =((INdata.data[(7-i)*2])&0b11000000)>>6;				// 2 bits from first byte, shift in place
				OutByte+=((INdata.data[((7-i)*2)+1])&0b00001111)<<2;		// 4 bits from second byte, shift in place
				OutByte+=0b10000000;										// add sync bits
			}
			if(byteSwitch==2)
			{
				OutByte=((INdata.data[((7-i)*2)+1])&0b11110000)>>4;			// 4 bits from second byte, shift in place
				OutByte+=0b11000000;										// add sync bits
			}

			OutByte>>=(7-n);												// Align byte for mask bit 1
	 		MF_REG_DATA=~(OutByte & 1);

			CLOCK_PIN=1;
			CLOCK_PIN=0;
		}

	// Next 8 bits is for preparing clock rise to all the MF MCUs

		MF_REG_DATA = 0; // Inverted

		for(i=0;i<8;i++) 	// SCK (ABS LED)
		{
			CLOCK_PIN=1;
			CLOCK_PIN=0;
		}

	// When 8 data bits and 8 clock bits are set. Load to clock the bit into the MF MCU.

		LED_LOAD=1;
		LED_LOAD=0;

	// Maintain the data bits for the falling SPI clock

		for(i=0;i<8;i++)	// SDO (TRIM LED)
		{
			// Msb out first
			if(byteSwitch==0)
			{
				OutByte =INdata.data[(7-i)*2]&0b00111111;					// 6 bits from first byte
				OutByte+=0b01000000;										// add sync bits
			}
			if(byteSwitch==1)
			{
				OutByte =((INdata.data[(7-i)*2])&0b11000000)>>6;				// 2 bits from first byte, shift in place
				OutByte+=((INdata.data[((7-i)*2)+1])&0b00001111)<<2;		// 4 bits from second byte, shift in place
				OutByte+=0b10000000;										// add sync bits
			}
			if(byteSwitch==2)
			{
				OutByte=((INdata.data[((7-i)*2)+1])&0b11110000)>>4;			// 4 bits from second byte, shift in place
				OutByte+=0b11000000;										// add sync bits
			}
			OutByte>>=(7-n);												// Align byte for mask bit 1
	 		MF_REG_DATA=~(OutByte & 1);

			CLOCK_PIN=1;
			CLOCK_PIN=0;
		}

		MF_REG_DATA = 1;
		
		// SPI input is coming on byte 1 and 2

		if(byteSwitch>0)
		{
			SWITCH_LOAD = 0;
			SWITCH_LOAD = 1;
			for(i=0;i<8;i++) 	// SCK (ABS LED)
			{
				tempOUTdata[((7-i)*2)+(byteSwitch>>1)] <<= 1;
				if(SWITCH_DATA) tempOUTdata[((7-i)*2)+(byteSwitch>>1)]+=0x01;
				else for(j=0;j<2;j++){;}
				CLOCK_PIN=1;
				CLOCK_PIN=0;
			}
		}
		else
		{
			for(i=0;i<8;i++) 	// SCK (ABS LED)
			{
				CLOCK_PIN=1;
				CLOCK_PIN=0;
			}
		}
	// Strobe LED chip again to trigger clock-low

		LED_LOAD=1;
		LED_LOAD=0;
	}

	if(byteSwitch==2)								// only after second byte has been read
	{

		if(VCAgroupState==0)
		{

			for(i=0;i<8;i++)						// check for vca mode
			{
				if((tempOUTdata[(i*2)+1]&0x30)==0x30)		// Normally forbidden.MF sends a fader mode switch command
				{
					tempOUTdata[(i*2)+1]&=0x03;			// clear this before sending to host
					VCAgroupState=1;					// flag for sending out fader mode next loop
					if(INdata.channel[i].status==0x03)		// Clear Write Status (if set) when jumping to Group Mode
					{
						OUTdata.data[(i*2)+1]+=0x0C;			// clear this before sending to host
					}
				}
			}

			if(grpSnapshot==1)							// if not in VCA group mode = copy buffer
			{
				for(i=0;i<8;i++)
				{
					MFlevels.word[i]=OUTdata.data[i];
					OUTdata.data[(i*2)]=tempOUTdata[(i*2)];		// copy buffer
					OUTdata.data[(i*2)+1]=tempOUTdata[(i*2)+1]&0x3;		// copy buffer
//					OUTdata.data[(i*2)+1]+=0b11000100;
//					OUTdata.data[(i*2)+1]+=0b11000100+(grpMute[i]<<5);
					OUTdata.data[(i*2)+1]+=0b11000100+((testbit_on(LocalMuteBits,i)<<5));

				}
				grpSnapshot=2;
			}

			if(!VCAgroup)							// if not in VCA group mode = copy buffer
			{
				for(i=0;i<16;i++)
				{
					OUTdata.data[i]=tempOUTdata[i];		// copy buffer
				}
			}
			else
			{
			// This updates VCAout (group) from motor fader
				for(i=0;i<8;i++)
				{
				//	OUTdata.data[(i*2)+1]&=0x03;			// make sure any "write drop out" event clear ??

					if(grpRecall == 0)
					{
//						VCAgroupLin.bytes[(i*2)]=tempOUTdata[(i*2)];
//						VCAgroupLin.bytes[(i*2)+1]=tempOUTdata[(i*2)+1];
						VCAout[i]=1023-(PGtoVCA(VCAgroupLin.word[i]&0x3ff));

// this block is for muting VCA groups from MF faders
/*
						if((tempOUTdata[(i*2)+1]&0xC0)!=0)
						{
							// Mute pressed
							if((tempOUTdata[(i*2)+1]&0x40))
							{
								if(!grpMute[i]) {grpMute[i]=1;grpMuteReleaseArm[i]=0;}
								else grpMuteReleaseArm[i]=1;
							}

							// Mute released
							if((tempOUTdata[(i*2)+1]&0x80) && grpMuteReleaseArm[i])
							{
								grpMute[i]=0;
							}
						}
*/
					}
				}
			}

		}
		else
		{

			if(VCAgroupState>3) 
			{
				VCAgroupState=0;
				VCAgroup=!VCAgroup;
//				if(VCAgroup)groupSave=1;
			}
			else VCAgroupState++;

		}

		if(statusFlag && byteSwitch!=0)		// flag is set for recalling VCA group level
		{
			VCAgroupState=1;
			VCAgroup=1;
			statusFlag=0;
		}

		if(grpRecall==2)grpRecall=0;
		if(grpRecall==1)grpRecall=2;
/*
		if(groupSave>0 && byteSwitch!=0)
		{
			WriteEEPROM(groupSave-1,VCAgroupLin.bytes[groupSave-1]);
			groupSave++;
			if(groupSave>16)groupSave=0;
		}
*/
	}
}

// *********************************** DAC only ****************************************
void Set_VCA(void)
{
	unsigned int loopCnt = 0;
	unsigned int word;
	unsigned int addr;
	unsigned int DACvalue;
	unsigned char ch;
	unsigned char offset=10;
	for(ch=0;ch<8;ch++)
	{

		if(VCAout[ch]<offset)DACvalue=0;
		else DACvalue = VCAout[ch]-offset;
	
//		if(MUTE_DATA=testbit_on(LocalMuteBits,ch))DACvalue=1023;
	
		addr = ch+1;								// address for the DAC ( 1 of 8)
		word = (addr<<12)+(DACvalue<<2);			// align the data right
	
		CLOCK_PIN = 0;								// prepare DAC chip

		DAC_LOAD = 0;

		for(loopCnt=0;loopCnt<16;loopCnt++)
		{		// shift the DATA out
	  		DAC_DATA=testbit_on(word,15-loopCnt);
			CLOCK_PIN = 1;
			CLOCK_PIN = 0;
		}
		DAC_LOAD = 1;								// Release the DAC chip
	}
}

// ****************************** Read Mute Pin************************************


void Read_Mute(unsigned char chn)
	{
		if(MUTE_IN) 
		{
			bit_set(LocalMuteBits,chn);							// Set bit in a storage byte
		}
		else
		{
			bit_clr(LocalMuteBits,chn);							// Clear bit in a storage byte
		}
	}


// *********************************** Mute out register ****************************************

void Set_Mutes(void)
{
	unsigned char i;
	MUTE_LOAD=0;
	for(i=0;i<8;i++)								// First send Mute data
	{
		MF_REG_DATA=testbit_on(LocalMuteBits,i);
//		MF_REG_DATA=0;
		CLOCK_PIN=1;
		CLOCK_PIN=0;
	}

	for(i=0;i<16;i++)								// Then clock thru LED chip
	{
		MF_REG_DATA=1;
		CLOCK_PIN=1;
		CLOCK_PIN=0;
	}

	MUTE_LOAD=1;																						// Strobe chips
	MUTE_LOAD=0;
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


char ReadEEPROM(char address)
{
char data;
/*write the address to the register*/
EEADR=address;
/*clear the bits to select data eeprom and the eemprom memory*/
EECON1bits.EEPGD=0;
EECON1bits.CFGS=0;
/*start a read sequence*/
EECON1bits.RD=1;
/*read the value*/
return(data=EEDATA);
}

void WriteEEPROM(char address,char data)
{
/*writes the address to the register*/
EEADR=address;
/*writes the data to the register*/
EEDATA=data;
/*selects eeprom data memory*/
EECON1bits.EEPGD=0;
EECON1bits.CFGS=0;
/*enables writes to the eeprom*/
EECON1bits.WREN=1;
/*disable interrupts*/
INTCONbits.GIEH = 0;
INTCONbits.GIE=0;
/*exact sequence to write data to the eeprom*/
EECON2=0x55;
EECON2=0x0AA;

/*write data to the eeprom*/
EECON1bits.WR=1;
/*enables interrupts*/
INTCONbits.GIEH=1;

}