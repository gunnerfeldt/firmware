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
	v6.2
		Try to add more secure fail exits from communication loops

	v7.0 has TR code. All pots are encoded from log to lin which comes up weird

	v7.1 try to detect TR mode and keep value linear
	
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

#define SLOW		120
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



byte BlinkLED = 1;
byte BlinkTouchStatusLED = 1;
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
unsigned char trMode=0;

int DACdelta[8];
long delta;

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
	unsigned int loopCntr=0;

unsigned int tempVCA;
unsigned char startADCflag=0;
unsigned char readADCflag=0;

// *********************************** Prototypes ****************************************
void Init(void);
void Read_ADC(void);
void Read_Mute(byte);
void Set_Get_VCA(unsigned char);
void Set_VCA(void);
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
unsigned char busLED=0;

void YourHighPriorityISRCode()
{
	unsigned int ADC_value;

	if (INTCONbits.INT0IF)									// Interrupt flag for RB0
	{
		cnt=0;
		SSP_write();									// First send the 16 bytes
// v3.2
		if(1)
		{
		
			if (!ParallelPortflag)								// Interrupt flag for RB0
		//	if (1)								// Interrupt flag for RB0
			{
				LATD = OUTdata.data[0];							// start with first byte on parallel port
				while(cnt<16)
				{
					while(SSP_clk==0){if(!SSP_en)break;}						// Wait for fisrt clock
					cnt++;										// count index
					LATD = OUTdata.data[(cnt)];					// Put byte on parallel port
					while(SSP_clk==1){if(!SSP_en)break;}						// Data must remain on the port until clock falls
					if(!SSP_en)break;								// if CS pin releases, abort
				}												// loop 16 times
				SSP_read();										// Then read
				while(cnt<32)
				{
					while(SSP_clk==0){if(!SSP_en)break;}						// Wait until clock rises
					INbuffer.data[cnt-16]=PORTD;					// read and store port in a buffer
					cnt++;										// count index
					while(SSP_clk==1){if(!SSP_en)break;}						// hold until clock falls
					if(!SSP_en)break;							// if CS pin releases, abort
				}
				SSP_read();
				if(cnt==32)ParallelPortflag=1;					// Flag for new data in

				cueTableCntr=0;
				fpsCntr=0;
			}
			SSP_read();
			ParallelPortflag=1;
		}

// this was 16 2015-01-08
		if(loopCntr>12)		// autoMode
		{
			trMode=0;
		}
		else 					// trMode
		{
			trMode=1;
		}
	
		loopCntr = 0;
		INTCONbits.INT0IF=0;								// clear int flag
	}



	if (INTCON3bits.INT2IF)									// Interrupt flag for RB1
	{
		Q_Frame_Flag = 1;									// Strobe every Q frame
		INTCON3bits.INT2IF = 0;								// Clear interrupt on port RB1
	}


	if (PIR1bits.ADIF)									// Interrupt flag for ADC
	{
		readADCflag=1;
/*	
		ADC_value = ADRESH;	
		ADC_value = (ADC_value<<8)+ADRESL;				// put the word together
	
		VCAfader[lastMuxedIndex]=ADC_value;

		Read_Mute(lastMuxedIndex);

		LATE = MUX[muxIndex]; 	 
		lastMuxedIndex=muxIndex;

		muxIndex++;
		muxIndex=muxIndex&0x7;
*/
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
	{															// Should be around 8-10	
		cueTableCntr++;
		loopCntr++;
		cueTableFlag=1;	
	
		BlinkCnt++;
	
		BlinkLED=(BlinkCnt&0x0040)!=0;
		BlinkTouchStatusLED=(BlinkCnt&0x0380)!=0;


//		LED=(busLED++&4)>>2;

		if(!trMode)		// autoMode
		{
			LED=((busLED++) >> 7) & 1;
		}
		else 					// trMode
		{	
			LED=((busLED++) >> 4) & 1;
		}
	
		INTCONbits.TMR0IF = 0;
		TMR0L=SLOW;	
		if(loopCntr>100)		// trMode and this card is not active
		{
			loopCntr=100;
			LED=1;
			SSP_read();
		}
	}

	if (PIR1bits.TMR2IF)										// Timer base for creating slots in between transfers
	{		
		startADCflag=1;
		PIR1bits.TMR2IF = 0;	
//		ConvertADC(); // Start conversion
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

    OpenADC(	ADC_FOSC_64     &
				ADC_RIGHT_JUST	&
				ADC_20_TAD,
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
//	INTCON3bits.INT2IE = 1; ; // Clock RB2 interrupt - Strobe


	OpenTimer0( TIMER_INT_ON &
	T0_8BIT &
	T0_SOURCE_INT &
	T0_PS_1_128 );		// 128 = 500 Hz / 2ms interval for Cue Table

	OpenTimer2( TIMER_INT_ON &
	T2_PS_1_4 &
	T2_POST_1_6 );


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
	signed int loopCnt = 0;
	unsigned char chn,n, i;
	unsigned char mux_cnt = 0;
	unsigned int ADC_value;
	signed int tempDelta;
	static unsigned int testDAC=0;
	static unsigned char busLED=0;

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

	while(1)
{
		SSP_read();
//		LEDaction();
		if(ParallelPortflag)							// New Data arrived
		{
			loopCnt=loopCntr;

			loopCntr=0;
			for(n=0;n<8;n++)							// loop thru channels
			{
			OUTdata.channel[n].mute_press = 0;					// clear event flag
			OUTdata.channel[n].mute_release = 0;					// clear event flag
		//		LEDaction();
				INdata.word[n]=INbuffer.word[n];		// Copy buffer
		//		INTCONbits.INT0IE = 0;


//REMOVE !!! if cousing trouble. 7.0 is without
		if(trMode)
		{
			ADC_value=VCAfader[n];
		}
		else
		{
			ADC_value=VCAtoPG(1023-VCAfader[n]);
		}

				OUTdata.channel[n].vca_lo=ADC_value&0xFF;
				OUTdata.channel[n].vca_hi=ADC_value>>8;
		//		INTCONbits.INT0IE = 1;

				// if status is not "manual". DAC feeds from computer
				if(INdata.channel[n].status)
				{
				//	DACsetPoint[n]=1023-PGtoVCA(INbuffer.word[n]&0x3FF);
					VCAout[n]=1023-PGtoVCA(INbuffer.word[n]&0x3FF);
			
				}
				else
				{
				//	DACsetPoint[n]=VCAfader[n];
					VCAout[n]=VCAfader[n];
				}

/*
				DACdelta[n]=DACsetPoint[n];
				DACdelta[n]=(DACdelta[n]-VCAout[n]);

				tempDelta=DACdelta[n];
				if(tempDelta>-loopCnt)
				{
					if(tempDelta<0)DACdelta[n]=-1;
					else DACdelta[n]=DACdelta[n]/loopCnt;
				}
				if(tempDelta<loopCnt)
				{
					if(tempDelta>0)DACdelta[n]=1;
					else DACdelta[n]=DACdelta[n]/loopCnt;
				}
*/

			}

			loopCntr=0;
	
			Read_Switches();
			ParallelPortflag=0;							// Clear transfer flag. Buffer is safe to write to


		}
	
		if(startADCflag)
		{
// DAC_DATA=1;
			startADCflag=0;
			ConvertADC(); // Start conversion
		}

		if(readADCflag)
		{
			readADCflag=0;
// DAC_DATA=0;
			ADC_value = ADRESH;	
			ADC_value = (ADC_value<<8)+ADRESL;				// put the word together
		
			VCAfader[lastMuxedIndex]=ADC_value;
	
			Read_Mute(lastMuxedIndex);
	
			LATE = MUX[muxIndex]; 	 
			lastMuxedIndex=muxIndex;
	
			muxIndex++;
			muxIndex=muxIndex&0x7;
		}


		if(cueTableFlag)
		{
	//		muxIndex=(cueTableCntr>>1)&7;
			if((cueTableCntr&1)==0)	// even
			{
	/*
				Read_Mute(lastMuxedIndex);
				LATE = MUX[muxIndex]; 	 
				lastMuxedIndex=muxIndex;
				ADC_value=VCAtoPG(1023-VCAfader[muxIndex]);
				INTCONbits.INT0IE = 0;
				OUTdata.channel[muxIndex].vca_lo=ADC_value&0xFF;
				OUTdata.channel[muxIndex].vca_hi=ADC_value>>8;
				INTCONbits.INT0IE = 1;
	*/
				Set_Mutes();
				Set_VCA();			// 1.28ms
			}

			else				// odd
			{
	/*
				ConvertADC(); // Start conversion
	*/
				// Read Mute + Start Conversion
				Set_Mutes();
				Set_VCA();			// 1.28ms
//				if(muxIndex=7)
				{
					Set_Leds();
				}
			}
			cueTableFlag=0;
		}
	}
}

// *********************************** DAC only ****************************************
void Set_VCA(void){
	unsigned int n = 0;
	unsigned int word;
	unsigned int addr;
	int DACvalue;
	unsigned char ch,localMute,hostMute;

//	DACvalue = ((VCAout[ch]+(VCAoutOld[ch]))/2);	// VCA data from computer

	for(ch=0;ch<8;ch++)
	{
//		LEDaction();

/*
		VCAout[ch] += DACdelta[ch];
		if(VCAout[ch]>1023)VCAout[ch]=1023;
		if(VCAout[ch]<0)VCAout[ch]=0;
*/

		DACvalue = ((VCAout[ch]) + (DACdelta[ch]*7)) / 8;
		if(DACvalue>1023)DACvalue=1023;
		if(DACvalue<0)DACvalue=0;
		DACdelta[ch] = DACvalue;

// 20 Dec 2016

		localMute = testbit_on(LocalMuteBits,ch);
		hostMute = INdata.channel[ch].mute;

		if(localMute)DACvalue=1023;
		if(hostMute)DACvalue=1023;

		
	
		addr = ch+1;								// address for the DAC ( 1 of 8)
		word = (addr<<12)+(DACvalue<<2);			// align the data right
	
		CLOCK_PIN = 0;								// prepare DAC chip

		DAC_LOAD = 0;

		for(n=0;n<16;n++)
		{		// shift the DATA out
	  		DAC_DATA=testbit_on(word,15-n);
			CLOCK_PIN = 1;
			CLOCK_PIN = 0;
		}

		DAC_LOAD = 1;								// Release the DAC chip
	}

//	}
}
// *********************************** Mute out register ****************************************

void Set_Mutes(void)
{
	unsigned char i,localMute,hostMute;
	MUTE_LOAD=0;
	for(i=0;i<8;i++)								// First send Mute data
	{
		localMute = testbit_on(LocalMuteBits,i);
		hostMute = INdata.channel[i].mute;
	//	MF_REG_DATA = (testbit_on(LocalMuteBits,i));
	//	MF_REG_DATA = INdata.channel[i].mute;
		MF_REG_DATA = localMute || hostMute;
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
// *********************************** Mute & Led out registers ****************************************

void Set_Leds(void)
	{
	unsigned char i;

	DAC_LOAD=1;										// Clear all regs
	LED_LOAD=0;

	for(i=0;i<8;i++) 	// ABS LED							// Send LED data
	{
		LED_DATA=0;
		if(INdata.channel[7-i].status==1)LED_DATA=1;
		if(INdata.channel[7-i].status==2 || INdata.channel[7-i].status==3)LED_DATA=BlinkTouchStatusLED;	
		CLOCK_PIN=1;
		CLOCK_PIN=0;
	}
	for(i=0;i<8;i++)	// TRIM LED
	{
		LED_DATA=(INdata.channel[7-i].status==3);												// Write is lit only in WRITE STATE
		if(INdata.channel[7-i].touchsense)LED_DATA=(BlinkLED&(INdata.channel[7-i].status!=0));		// Write blink when Touch sense is set and not in Manual
		CLOCK_PIN=1;
		CLOCK_PIN=0;
	}

	LED_LOAD=1;
	LED_LOAD=0;
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


void Read_Mute(unsigned char chn)
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
//			OUTdata.channel[chn].mute_press = 0;					// clear event flag
//			OUTdata.channel[chn].mute_release = 0;					// clear event flag
		}
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

	return;
	if(1)
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
	//		LED=LEDtoggle;
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

