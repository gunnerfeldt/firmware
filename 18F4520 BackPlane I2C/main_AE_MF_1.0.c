/* Compile options:  -ml (Large code model) */

//#include <stdio.h>
#include <p18f4520.h>
#include <timers.h>
#include "typedefs.h"
#include <math.h>
#include <i2c.h>
// #pragma config WDT = ON

/*
 *  IO_card.h
 *  Test
 *
 *  Created by Pelle Gunnerfeldt on 2011-04-12.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *


 */

// allocate some resources in ACCESS RAM for speedy access in interrupt routines
// all locations in this section are volatile


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
ram near unsigned char cueTableCntr;
ram near unsigned char cueTableFlag;

#pragma udata

unsigned char MOTORFADERS = 0;
unsigned char HANDSHAKE = 0;

unsigned int BlinkCnt = 0;
unsigned int status_bits;
unsigned char fpsCntr;
unsigned char fpsTmr = FAST;



byte BlinkLED = 1;
byte LEDtoggle = 1;
unsigned char statusFlag = 0;


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



BOOL clk_flg = FALSE;

	unsigned long Ltimer;
	unsigned char clk_flag = 0;
	unsigned long blinkcnt;
	unsigned long cnt;
	unsigned long Wcnt;
	unsigned long wCntr;
	unsigned long cnt1;
	unsigned long cnt2;
	unsigned long cnt3;
	byte LEDword;
	unsigned char doOnce=0;
	unsigned char MFtimerTick;

	byte LED_byte;

	unsigned char ParallelPortflag = 0;
	unsigned char Q_Frame = 0;
	unsigned char Q_Frame_Flag = 1;
	unsigned char Timer_Flag = 1;
	unsigned char MFtimer = 0;
	unsigned char MFtimerIndex=0;

// *********************************** Prototypes ****************************************
void Init(void);
void Motor_Faders(unsigned char);


#pragma code


// *********************************** Interrupts ****************************************

#pragma interrupt YourHighPriorityISRCode

	void YourHighPriorityISRCode()
	{
		unsigned char n, chn, i;


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
			}
			INTCONbits.INT0IF=0;								// clear int flag
		}

		if (INTCON3bits.INT2IF)									// Interrupt flag for RB1
		{
			Q_Frame_Flag = 1;									// Strobe every Q frame
			INTCON3bits.INT2IF = 0;								// Clear interrupt on port RB1
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

// I2C IN !!! I2C IN !!! I2C IN !!! I2C IN !!! I2C IN !!! I2C IN !!! I2C IN !!! I2C IN !!! I2C IN !!! I2C IN !!! I2C IN !!! 

	if (PIR1bits.SSPIF == 1)
	{
		PIR1bits.SSPIF = 0; // clear interrupt flag
	}

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
	T1CONbits.T1OSCEN=0; 			// Turn off OSC Timer 1 thing. Didn't effect anything after all.�
	TRISA = 0x0D;					// Port A: RA0=ADC, RA1=LED, RA2=VREF-, RA3=VREF+, RA5=MUTE_DATA, RA6=OSC;
	TRISB = 0x07;					// Port B: RB0, RB1, RB2=P.Port
	TRISC = 0x09; 					// Port C: RC0=SW_DATA, RC1=SW_LOAD, RC2=Clock, RC3=MUTE_IN
	TRISD = 0xFF;
	TRISE = 0x00;


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


	cueTableCntr=0;
	cueTableFlag=0;
	fpsCntr=0;


	OpenI2C (MASTER, SLEW_ON);
	SSPADD = 0x18; // 0x18 for 400Khz // ( (Fosc/Bitrate)/4 ) - 1. 0x63 for 100khz (0x0D)
	PIE1bits.SSPIE = 1; // SSP interrupt enable
}

// *********************************** MAIN ****************************************
void main (void)
{
	unsigned int loopCnt = 0;
	unsigned int word;
	unsigned char chn,n, i;
	Init();
	SSP_read();

 	for(wCntr=0;wCntr<100000;wCntr++)
		{
		;
		}
	LED=0;
	while(1)
	{
		if(ParallelPortflag)							// New Data arrived
		{
			ParallelPortflag=0;							// Clear transfer flag. Buffer is safe to write to
			LED=!LED;
		}
	

		if(cueTableFlag)
		{
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
					break;
				}

			if((cueTableCntr&1)==0)	// even
			{

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
}
