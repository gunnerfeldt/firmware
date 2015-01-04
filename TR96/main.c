/* Compile options:  -ml (Large code model) */

//#include <stdio.h>
#include <p18f2520.h>
#include <timers.h>
#include "typedefs.h"
#include <i2c.h>	/* Master Synchonous Serial I2C */


#pragma config WDT = OFF
	
/*
 *  TR96
 *  Test
 *
 *  Created by Pelle Gunnerfeldt on 2014-09-08.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */



#define hibyte(x)       (unsigned char)(x>>8)
#define lobyte(x)        (unsigned char)(x & 0xFF)


#define MUX 		LATA
#define MPX 		LATCbits.LATC0
#define LATCH 		LATAbits.LATA7

#define LED 		LATCbits.LATC1

#define CARD_ID  	1
#define MAJOR  0
#define MINOR  9

#define BUFSIZE 8
#define STATE_1 0b00001001 
#define STATE_2 0b00101001
#define STATE_3 0b00001100
#define STATE_4 0b00101100
#define STATE_5 0b00101000
#define STATE_6 0b00110001


#pragma udata access volatile_access
volatile unsigned char I2Cflag = 0;
volatile near unsigned char       I2CSTAT;
volatile unsigned char index;			// index counter for the I2C i/out buffer arrays
volatile near union INdataUnion {
unsigned char data[BUFSIZE];
struct  {
		unsigned mux:7;
		unsigned mpx:1;
//		unsigned mpx:1;
//		unsigned :7;
		};
}indata;
volatile near union OUTdataUnion {
unsigned char data[BUFSIZE];
struct  {
		unsigned misc:8;
		};
}outdata;


unsigned long LedRelease = 0;

#pragma udata

// *********************************** Prototypes ****************************************
void Init(void);
void HighISRCode();
void LowISRCode();
int HandleI2C(void);
void myWriteI2C(void);	



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
	if(PIR1bits.SSPIF)					// if new I2C event occured
	{
		if (HandleI2C()==2)				// when I2C transfer i done	
		{	
			I2Cflag=1;
		}
		PIR1bits.SSPIF = 0;				// reset	
	}
}

#pragma interruptlow LowISRCode
void LowISRCode()
{	

	
}	//This return will be a "retfie", since this is in a #pragma interruptlow section 


#pragma code

struct {
    unsigned BF:1;
    unsigned UA:1;
    unsigned R_W:1;
    unsigned S:1;
    unsigned P:1;
    unsigned D_A:1;
    unsigned CKE:1;
    unsigned SMP:1;
}I2CSTATbits;

// *********************************** MAIN ****************************************
void main (void)
{ 
	/*
		
         Normal Total Recall mode
         ’Multiplexer Enable bus’ = HIGH
         Set address
         Address Enable Pulse (Lo to High?)

	*/
	unsigned char stopFlag=1;
	static unsigned char oldMux = 0;
	unsigned char n = 0;
	unsigned long waitClock = 0;
	Init();
	LED=1;
	outdata.data[0]=CARD_ID;
	outdata.data[1]=MAJOR;
	outdata.data[2]=MINOR;
	outdata.data[3]=0;
	while(1)
	{

	if(LedRelease>0)
	{
		LedRelease--;
		if(!LedRelease)LED=1;
	}

	// Stop bit set & stopFlag (for triggering once) zero index, I2Cflag triggers
//	if(SSPSTATbits.P && !stopFlag){stopFlag=1;index=0;I2Cflag=1;}
	if(SSPSTATbits.P && !stopFlag){stopFlag=1;index=0;}
	// Startbit clears stopFlag
	if(SSPSTATbits.S) stopFlag=0;

// LED=1;							
		if(I2Cflag)						// When new data arrives
		{	
			I2Cflag=0;				// Clear flag. Wait for next data				
			if((indata.mux&0x7F) == 0x7F)				// MPX  command
			{
				// !!!! !!!! Reversed 2014-10-17 !!! !!!
				MPX = indata.mpx;			// Set MPX enable to bit 7 in byte	
				LED = !indata.mpx;
			}
			else
			{		
				LATCH = 0;				// Safety
				if(MPX)
				{
					MUX = indata.mux & 0x7F;	// 7 bit address
					if(MUX)
					{
						for(waitClock=0;waitClock<20;waitClock++){;}
						LATCH = 1;				// Strobe Address Latch
						for(n=0;n<25;n++){;}
						LATCH = 0;				// Release Strobe
					}
					oldMux=indata.mux;		// store tis address	
				}
			}
		}
	}

}
// *********************************** Init ****************************************
void Init(void)
{
	unsigned char I2Caddress=0;

	OSCTUNEbits.TUN0 = 1;
	OSCTUNEbits.TUN1 = 1;
	OSCTUNEbits.TUN2 = 1;
	OSCTUNEbits.TUN3 = 1;
	OSCTUNEbits.TUN4 = 1;
	OSCCONbits.IRCF0 = 1;
	OSCCONbits.IRCF1 = 1;
	OSCCONbits.IRCF2 = 1;
	OSCTUNEbits.PLLEN = 1;
	OSCTUNEbits.INTSRC = 0;

	TRISA = 0x00;
	TRISB = 0xFF;	
	TRISC = 0xFC;

	OpenI2C (SLAVE_7, SLEW_ON);
	SSPADD = 0xE0 + 0x00; // slave address
	SSPCON2bits.SEN = 0;

	/*
	SSPCON1bits.SSPM3 = 1;
	SSPCON1bits.SSPM2 = 1;
	SSPCON1bits.SSPM1 = 1;
	SSPCON1bits.SSPM0 = 0;
	*/

	LED=1;
	// enable interrupts - legacy mode
	INTCONbits.PEIE = 1;
	INTCONbits.GIE = 1;
	PIE1bits.SSPIE = 1; // SSP interrupt enable

//	INTCONbits.PEIE = 1;
//	INTCONbits.GIE = 1;
//	RCONbits.IPEN = 1;            //enable priority levels



}


//---------------------------------------------------------------------
// SSP_Handler
//---------------------------------------------------------------------
// The I2C code below checks for 5 states:
//---------------------------------------------------------------------
// State 1: I2C write operation, last byte was an address byte.
// SSPSTAT bits: S = 1, P = 0, D_A = 0, R_W = 0, BF = 1
//
// State 2: I2C write operation, last byte was a data byte.
// SSPSTAT bits: S = 1, P = 0, D_A = 1, R_W = 0, BF = 1
//
// State 3: I2C read operation, last byte was an address byte.
// SSPSTAT bits: S = 1, P = 0, D_A = 0, R_W = 1 
//
// State 4: I2C read operation, last byte was a data byte.
// SSPSTAT bits: S = 1, P = 0, D_A = 1, R_W = 1, BF = 0
//
// State 5: Slave I2C logic reset by NACK from master.
// SSPSTAT bits: S = 1, P = 0, D_A = 1, BF = 0, CKP = 1 
//
// State 6: I2C write operation with stop bit set. End of transaction.
// SSPSTAT bits: S = 0, P = 1, D_A = 1, BF = 0, CKP = 1 
//----------------------------------------------------------------------		

int HandleI2C(void)
	{	
	unsigned char address;		// where to store the dummy read. Might be used for general call
															// copy status register		
		I2CSTAT = SSPSTAT & 0b00111101;						// mask out the used bits


															// decide the state
			if (I2CSTAT == STATE_1){						// address match, write
				index = 0;									// clear buffer index
				address = SSPBUF;							// dummy read to cear BF
				SSPCON1bits.CKP = 1; // release clock		
				return 1;}
			if (I2CSTAT == STATE_2){						// master write byte
				indata.data[index] = SSPBUF;				// read data and clear BF
				SSPCON1bits.CKP = 1; // release clock				
				index++;									// increment index
				if(index>BUFSIZE) index = 0;				// if buffer length exceeded, clear index
				return 2;}
			if (I2CSTAT == STATE_6){						// master write byte and stop
				indata.data[index] = SSPBUF;				// read data and clear BF
				SSPCON1bits.CKP = 1; // release clock			
				index++;									// increment index
				if(index>BUFSIZE) index = 0;				// if buffer length exceeded, clear index
				return 2;}
			if ((I2CSTAT & 0b00101100) == STATE_3){			// address match, read (ignore BF bit)
				index = 0;									// clear buffer index
				myWriteI2C();								// a repeating function for writing
				index++;									// increment index
				return 3;}
			if (I2CSTAT == STATE_4){						// master read, buffer is empty. no need to read it.
				if(SSPCON1bits.CKP == 0){					// make sure the clock line hasn't been released
					if(index>BUFSIZE) index = 0;			// if buffer length exceeded, clear index
					myWriteI2C();							// a repeating function for writing
					index++;								// increment index
					return 4;}}
			if ((I2CSTAT & 0b00101000) == STATE_5){			// NACK received when sending data to the master		
			return 5;}										// Mask RW bit in SSPSTAT
		return -1;										// if no state, return error code
		}

void myWriteI2C(void)
	{	
		if(!MPX)
		{
			LedRelease = 100000;
			LED=0;
		}
	//	while(SSPSTATbits.BF)									// wait until bus is free
	//		{													
	//		;
	//		}
		do 
		{							
			SSPCON1bits.WCOL = 0;								// clear collision bit
			SSPBUF = outdata.data[index];						// load hardware buffer
			}while(SSPCON1bits.WCOL);							// if there was a collision, try again
			SSPCON1bits.CKP = 1;								// release the clock stretch
		}