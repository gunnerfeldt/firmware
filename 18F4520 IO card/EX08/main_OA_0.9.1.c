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
 */

// allocate some resources in ACCESS RAM for speedy access in interrupt routines
// all locations in this section are volatile


#define SPI_IN_DATA			PORTCbits.RC0
#define SPI_IN_LATCH			LATCbits.LATC1
#define SPI_REG_CLK			LATCbits.LATC2
#define SPI_SS				LATCbits.LATC3
#define SPI_CLK				LATCbits.LATC4
#define SPI_OUT_DATA			LATCbits.LATC5
#define SPI_OUT_LOAD			LATCbits.LATC6


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

#define MAJOR				0
#define MINOR				9

#define DEBUG1			LATEbits.LATE0 	//pin 8
#define DEBUG2			LATEbits.LATE1	// pin 9


#define WAIT2       for(j=0;j<2;j++){;}
#define WAIT4       for(j=0;j<4;j++){;}
#define WAIT6       for(j=0;j<6;j++){;}
#define WAIT8       for(j=0;j<8;j++){;}
#define WAIT10       for(j=0;j<10;j++){;}
#define WAIT12       for(j=0;j<12;j++){;}


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

unsigned char HANDSHAKE = 0;

unsigned int BlinkCnt = 0;
unsigned int status_bits;
byte BlinkLED = 1;
byte LEDtoggle = 1;
unsigned int testCV=0;

unsigned char hardwareReportState = 0;

int adc;				// ADC int
byte adcMSB;			// ADC byte
byte adcLSB;			// ADC byte
byte adcchn = 0;
byte error;

const unsigned char TICK_RATE = 8;
BOOL clk_flg = FALSE;

	unsigned long Ltimer;
	unsigned char clk_flag = 0; 
//	unsigned char swbuf[40]; 
	unsigned long blinkcnt; 
	unsigned long cnt; 
	unsigned long Wcnt; 
	unsigned long wCntr; 
	unsigned long cnt1; 
	unsigned long cnt2;
	unsigned long cnt3; 
	unsigned char MFtimerTick;


	unsigned char ParallelPortflag = 0;
	unsigned char Q_Frame = 0;
	unsigned char Q_Frame_Flag = 1;
	unsigned char Timer_Flag = 1;
	unsigned char MFtimer = 0;

// *********************************** Prototypes ****************************************
void Init(void);
void Read_Mute(byte);
void Read_Switches(void);
void Set_Mutes(void);
void Set_Leds(void);
void Motor_Faders(unsigned char);
void LEDaction(void);


#pragma code


// *********************************** Interrupts ****************************************

#pragma interrupt YourHighPriorityISRCode

	void YourHighPriorityISRCode()
	{
		unsigned char n, chn, i,j;
		unsigned char last_clk=0;
		unsigned char clk=0;
		unsigned char inCmd = 0;

		if (INTCONbits.INT0IF)									// Interrupt flag for RB0
		{	
			cnt=0;	
			if(HANDSHAKE)
			{
				SSP_write();										// Is this bad?
			}										// First send the 16 bytes


			if(!hardwareReportState)
			{
				if (!ParallelPortflag)								// Interrupt flag for RB0
				{
					
					LATD = OUTdata.data[0];							// start with first byte on parallel port
					while(cnt<16)
					{	
						LATD = OUTdata.data[(cnt)];					// Put byte on parallel port
						while(SSP_clk==0){;}						// Wait for fisrt clock
						cnt++;
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
	long dly = 100000; 

	ADCON1 = 0b00111110;
	T1CONbits.T1OSCEN=0; 			// Turn off OSC Timer 1 thing. Didn't effect anything after all.ö
	TRISA = 0xFD;					// Port A: RA1=LED, RA2=VREF-, RA3=VREF+, RA6=OSC;
	TRISB = 0x07;					// Port B: RB0, RB1, RB2=P.Port
	TRISC = 0x01; 					// Port C: RC0=SW_DATA, RC1=SW_LOAD, RC2=Clock, RC3=MUTE_IN
	TRISD = 0xFF;
	TRISE = 0x00;

	HANDSHAKE=1;

	CMCON = 0x07; /* Disable Comparator */

	// Set buffers to zero. Just in case
	for(n=0;n<16;n++)
	{
		OUTdata.data[n]=0;
		INdata.data[n]=0;
	}

	while(--dly){LED=0;}
	LED=1;

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
/*                      
	for(i=0;i<16;i++) 	// SCK (ABS LED)	
	{
		MF_REG_DATA = 0;
		CLOCK_PIN=1;
		CLOCK_PIN=0;	
	}				
*/					
 	for(wCntr=0;wCntr<100000;wCntr++)
		{
		;
		}
	LED=0;
	while(1)
	{
	//	LEDaction();
		if(ParallelPortflag)							// New Data arrived
		{
			LED=!LED;	
			LEDtoggle=!LEDtoggle;
			for(n=0;n<8;n++)							// loop thru channels
			{
				if(INbuffer.cmd[n].flag==0 && !hardwareReportState)				// same as id change flag
				{
					INdata.word[n]=INbuffer.word[n];		// Copy buffer
				}
				else
				{
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

					}

				}
			}


	
         Motor_Faders(0);		// Q frame 0
		MFtimer=0;
		ParallelPortflag=0;
		}
		else
		{
			if(Timer_Flag)						// Frequency?
			{
				Timer_Flag = 0;
				Q_Frame_Flag = 0;
	
				BlinkCnt++;
				if(BlinkCnt>30)
				{
					BlinkLED=!BlinkLED;
					BlinkCnt=0;
				}
			}

	         if(MFtimerTick)						// New Data arrived
			{
				Motor_Faders(1);		// Q frame 1
				MFtimerTick=0;
			}
		}	
	}
}

// *********************************** Motor Fader Communication ****************************************

void Motor_Faders(unsigned char byteSwitch)
{
	unsigned char i,n,m,j;
	unsigned char OutByte;
	unsigned char debugByte;
	static unsigned int handshakeTmr = 0x6F;
	static unsigned char fakeChnNo = 1;
	static unsigned int fakeCnt = 1;
	static unsigned char SendFaderIDs=0;
	static signed int waveCV = 0;
	static signed char waveAdd = 5;

if(hardwareReportState) return;


/*
	if(!HANDSHAKE)
	{
		for(i=0;i<8;i++)
		{
//			INdata.data[i*2]=0x02;	
//			INdata.data[(i*2)+1]=0x11;	// 0x1X is only used for commands. 0xX1 is handshake.
		}
	}


		waveCV+=waveAdd;
		if(waveCV>1023)
		{
			waveCV=1023;
			waveAdd=-5;
		}
		if(waveCV<0)
		{
			waveCV=0;
			waveAdd=5;
		}

if(	!byteSwitch )
{
	INdata.data[0]=waveCV & 0xFF;	
	INdata.data[1]=waveCV >> 8;
}
*/
//	INdata.data[0]=0x20;	
//	INdata.data[1]=0x03;



	SPI_SS=0;
    // This loop is running thru all the bits of the 8 bytes. 
 WAIT2;
     
	for(n=0;n<8;n++)
	{		

		// Capture the returning data. So strobe the Switch Reg to latch the current pins.
		// Remember. This PIC latch 8 bits which are parallel her and serial to the motofaders.	
		SPI_IN_LATCH = 0;
WAIT2;
		SPI_IN_LATCH = 1;
	
		// Clock bit "n" from all the 8 bytes
		for(i=0;i<8;i++)	// SDO
		{

			OutByte=(INdata.data[((7-i)*2)+byteSwitch]>>(7-n));
	 		SPI_OUT_DATA=(OutByte & 1);

			// Ths shift register outputs the serial data
			// Msb out first. "byteSwitch" determines if it's byte 0 or 1
			// Shift the data left. Msb first.	
			tempOUTdata[((7-i)*2)+byteSwitch] <<= 1;
			if(SPI_IN_DATA)tempOUTdata[((7-i)*2)+byteSwitch]+=0x01;	

    			// Shift in / out Local shift registers
			SPI_REG_CLK=1;
WAIT2;
			SPI_REG_CLK=0;	
		}

		// When 8 data bits are set. Latch SPI out register
		SPI_OUT_LOAD=1;
WAIT2;
		SPI_OUT_LOAD=0;

		// clock Motor Faders SPI ports
		SPI_CLK=1;
WAIT2;
		SPI_CLK=0;
		
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
					HANDSHAKE=1;
				}
				OUTdata.data[i]=0;			// Must clear this before sending to host
			}
		}
	}
	else											// not init sequence
	{
		if(byteSwitch)								// only after second byte has been read
		{
				for(i=0;i<8;i++)
				{
					// Look for OA stamp 0x08 in the mask 0b0000xx00 of the hi byte
					// keeps offline / faulty faders masked out
					if((tempOUTdata[(i*2)+1] & 0x0C)==0x08)
					{	
						OUTdata.data[(i*2)]=tempOUTdata[(i*2)];		// copy buffer
						OUTdata.data[(i*2)+1]=tempOUTdata[(i*2)+1];		// copy buffer
					}
					else
					{
						OUTdata.data[(i*2)]=0;		// copy buffer
						OUTdata.data[(i*2)+1]=0;		// copy buffer
					}
				}

		WAIT2;
		SPI_SS=1;
		}
	}

	
}


// *********************************** Mute out register ****************************************

void Set_Mutes(void)
	{

	}
// *********************************** Mute & Led out registers ****************************************

void Set_Leds(void)
	{

	}


// *********************************** Read Status Switches ****************************************
void Read_Switches(void)
	{

}


// ****************************** LED action************************************


void LEDaction(void)
{
	static unsigned int LEDcntr=0x8000;
	static unsigned int LEDdim=0xFFFF;
	static unsigned int LEDcntr2=0x0;
	
return;

/*
	if(INdata.channel[0].status)LED=0;
	else LED=1;
*/

	if(HANDSHAKE)
	{
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
		LEDcntr2++;
		if(LEDcntr2==0xFFFF)
		{
			LEDcntr2=0x0;
			LED=!LED;
		}
	}
}

