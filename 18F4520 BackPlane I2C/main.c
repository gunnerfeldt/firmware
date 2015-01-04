/* Compile options:  -ml (Large code model) */

//#include <stdio.h>
#include <p18f4520.h>
#include <timers.h>
#include "typedefs.h"
#include <math.h>
#include <i2c.h>
// #pragma config WDT = OFF
	
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


#define SSP_en          		!PORTBbits.RB0
#define SSP_clk          		PORTBbits.RB1
#define STROBE          		PORTBbits.RB2
#define SSP_write()         	TRISD = 0;
#define SSP_read()         		TRISD = 255;

#define WAIT_OVERFLOW			25000

#define CARD_ID  	1
#define CARD_MAJOR  1
#define CARD_MINOR  0

#define DEB0 LATEbits.LATE0
#define DEB1 LATEbits.LATE1
#define DEB2 LATEbits.LATE2


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

#define LED  LATBbits.LATB4
byte mask;

byte sim = 0;

byte OddEven = 0;

long cntr10 = 0;

#pragma udata access volatile_access

 ram near unsigned char datain[2];

#pragma udata access volatile_access

//
//byte BankTemp[24];		// data to shuffle in/out
//byte BankIn[24];		// data to shuffle in/out
//byte BankOut[24];		// data to shuffle in/out

union INdataUnion {
	unsigned char data[16];
	unsigned int word[8];
	struct{
		unsigned vca_lo:8;
		unsigned vca_hi:2;
		unsigned status:2;
		unsigned not_used:2;
		unsigned touchsense:1;
		unsigned mute:1;
		}channel[8];
};
union OUTdataUnion {
	unsigned char data[16];
	unsigned int word[8];
	struct{
		unsigned vca_lo:8;
		unsigned vca_hi:2;
		unsigned status_press:1;
		unsigned status_release:1;
		unsigned not_used:2;
		unsigned mute_press:1;
		unsigned mute_release:1;
		}channel[8];
};

ram near union INdataUnion INdata;
ram near union INdataUnion INbuffer;
ram near union OUTdataUnion OUTdata;
ram near volatile unsigned char ParallelPortflag;

#pragma udata


unsigned int BlinkCnt = 0;
byte BlinkLED = 1;
unsigned int WaitCnt=0;
unsigned char errorCode=0;

unsigned int LedRelease = 0;



	unsigned long Ltimer;
	unsigned char clk_flag = 0; 

	unsigned char fader_response = 0;


	unsigned long blinkcnt; 
	unsigned long cnt; 
	unsigned long Wcnt; 
	unsigned long wCntr; 
	unsigned long cnt1; 
	unsigned long cnt2;
	unsigned long cnt3; 
	unsigned char FaderAlive[8];
	unsigned char CurrentFaderAddress=0;
	unsigned char CheckFader=0;
	unsigned char setupFlag = 0;

	byte LED_byte;

	unsigned char Q_Frame_Flag = 1;

// *********************************** Prototypes ****************************************
void Init(void);
// void WaitI2C(void);
int ReadI2C_Automan( void );
void HighISRCode();
void LowISRCode();

// ********************************* Interrupt vectors ***********************************
#pragma code high_vector=0x08
void interrupt_at_high_vector(void)
{
  _asm GOTO HighISRCode _endasm
}

#pragma code low_vector=0x18
void interrupt_at_low_vector (void)
{
  _asm GOTO LowISRCode _endasm
}

// *********************************** Interrupts ****************************************

#pragma interrupt HighISRCode
void HighISRCode()
{
		unsigned char n, chn;
		unsigned char last_clk=0;
		unsigned char clk=0;
		unsigned char Qframe=0;

		if (INTCONbits.INT0IF)									// Interrupt flag for RB0
		{
			cnt=0;
			SSP_write();
			LATD = OUTdata.data[(0)];				// Put byte on parallel port

			{			

				while(cnt<4)
				{
					while(SSP_clk==0){;}
					cnt++;
					LATD = OUTdata.data[(cnt)];				// Put byte on parallel port
					while(SSP_clk==1){;}
					if(!SSP_en)break;
				}
				if(setupFlag)
				{
					setupFlag=0;
				}
				else
				{
					SSP_read();
					
					while(cnt<8)
					{
						while(SSP_clk==0){;}
						INdata.data[cnt-4]=PORTD;			// read and store port in a buffer
						cnt++;
						while(SSP_clk==1){;}
						if(!SSP_en)break;
					}	
						
					if(cnt==8){ParallelPortflag=1;}		// Flag for new data in
					else(cnt=0);
				}
				SSP_read();
				
			}

			INTCONbits.INT0IF=0;											
		}

	// I2C IN !!! I2C IN !!! I2C IN !!! I2C IN !!! I2C IN !!! I2C IN !!! I2C IN !!! I2C IN !!! I2C IN !!! I2C IN !!! I2C IN !!! 

		if (PIR1bits.SSPIF == 1)
		{
			PIR1bits.SSPIF = 0; // clear interrupt flag
		}






		if (INTCON3bits.INT2IF)									// Interrupt flag for RB1
		{
//			Q_Frame_Flag = 1;		
			INTCON3bits.INT2IF = 0;							// Clear interrupt on port RB1		
		}

		if (INTCONbits.TMR0IF)									// Timer base for creating slots in between transfers
		{			
//			Q_Frame_Flag = 1;
			INTCONbits.TMR0IF = 0;
		}

	}

	#pragma interruptlow LowISRCode
	void LowISRCode()
	{
	}	//This return will be a "retfie", since this is in a #pragma interruptlow section 


#pragma code
// *********************************** MAIN ****************************************
void main (void)
{
	Init();

	SSP_read();
	LED=1;
 	for(wCntr=0;wCntr<30000;wCntr++)
		{
		;
		}
	while(1)
	{
		if(LedRelease>0)LedRelease--;
		else LED=1;

		if(ParallelPortflag)							// New Data arrived
		{

			LED=0;	
			ParallelPortflag=0;
			LedRelease = 30000;

			if(INdata.data[3]==0x11)
			{
				setupFlag = 1;
				OUTdata.data[0]= 0;
				OUTdata.data[1]= 0;
				OUTdata.data[2]= 0;
				OUTdata.data[3]= 0;
			
				IdleI2C();
				StartI2C();
				IdleI2C();
				if(WriteI2C(0xE1+00)==0);  // WRITE address. Must skip bit 0. Bit 0 is for READ!!!
				{
						IdleI2C();
						OUTdata.data[0] = ReadI2C();
						if(OUTdata.data[0]==0xff)OUTdata.data[0]=0;
						AckI2C();
						IdleI2C();
						OUTdata.data[1] = ReadI2C();
						AckI2C();
						IdleI2C();
						OUTdata.data[2] = ReadI2C();
						NotAckI2C();
						IdleI2C();
						StopI2C();
						
				}
			}
			else
			{
DEB0=1;
				IdleI2C();
				StartI2C();
				IdleI2C();
				if(WriteI2C(0xE0+00)==0);  // WRITE address. Must skip bit 0. Bit 0 is for READ!!!
				{
DEB1=1;
					IdleI2C();
					WriteI2Cstop(INdata.data[0]);		// only ONE byte for now. Might change
DEB0=0;
					IdleI2C();
					StopI2C();
DEB1=0;
				}
			}
		}
	}
}


// *********************************** Init ****************************************
void Init(void)
{
	TRISA = 0x0F;
	TRISB = 0x07;
	TRISC = 0x00; 	
	TRISD = 0xFF;
	TRISE = 0x00;
	
	CMCON = 0x07; /* Disable Comparator */

	INTCONbits.GIE = 1;	// Enables Low Prio interrupts
	INTCONbits.PEIE = 1;		// Enables High Prio 
//	RCONbits.IPEN = 1;		// Enables Priorites
	INTCONbits.GIEL = 1;	// Enables Low Prio interrupts
	INTCONbits.GIEH = 1;		// Enables High Prio 

	INTCON2bits.INTEDG0 = 0; // Chip Select is inverted
//	INTCON2bits.INTEDG2 = 0; // Strobe too
	INTCONbits.INT0IE = 1; // Bank Select RB0 interrupt - Bank Select
//	INTCON3bits.INT2IE = 1; ; // Clock RB2 interrupt - Strobe

/*
	OpenTimer0( TIMER_INT_ON &
	T0_8BIT &
	T0_SOURCE_INT &
	T0_PS_1_128 );		// Frequency 

	TRISCbits.TRISC3=0;
	TRISCbits.TRISC4=0;
	LATCbits.LATC3=1;
	LATCbits.LATC4=1;
	LATCbits.LATC3=0;
	LATCbits.LATC4=0;
	LATCbits.LATC3=1;
	LATCbits.LATC4=1;
	TRISCbits.TRISC3=1;
	TRISCbits.TRISC4=1;

*/

	OpenI2C (MASTER, SLEW_ON);
	SSPADD = 0x18; // 0x18 for 400Khz // ( (Fosc/Bitrate)/4 ) - 1. 0x63 for 100khz (0x0D)
	PIE1bits.SSPIE = 1; // SSP interrupt enable

	SSP_read();
}








