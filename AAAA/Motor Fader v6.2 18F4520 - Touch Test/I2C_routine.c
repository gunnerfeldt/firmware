
#include <usart.h>	   /* Serial UART stuff */
#include <i2c.h>	/* Master Synchonous Serial I2C */	
#include "I2C_routine.h"


// definitions, can be stripped
#define BUFSIZE 2
#define STATE_1 0b00001001 
#define STATE_2 0b00101001
#define STATE_3 0b00001100
#define STATE_4 0b00101100
#define STATE_5 0b00101000
#define AUTO_LED  LATBbits.LATB0
#define DEB0  LATEbits.LATE0
#define DEB1  LATEbits.LATE1

union indata {
	unsigned char bytes[2];
	struct  {
		unsigned vca_lo:8;
		unsigned vca_hi:2;
		unsigned status:2;
		unsigned not_used:2;
		unsigned motor_on:1;
		unsigned mute:1;
		};
};
union outdata{
	unsigned char bytes[2];
	struct  {
		unsigned vca_lo:8;
		unsigned vca_hi:2;
		unsigned status:2;
		unsigned touch_press:1;
		unsigned touch_release:1;
		unsigned mute_press:1;
		unsigned mute_release:1;
		};
};

#pragma udata access volatile_access
unsigned char index=0;
ram near volatile union indata inbuffer;
ram near volatile union outdata outbuffer;
unsigned char localTouchSense=0;



//---------------------------------------------------------------------
// SSP_Handler
//---------------------------------------------------------------------
// The I2C code below checks for 5 states:
//---------------------------------------------------------------------
// State 1: I2C write operation, last byte was an address byte.
// SSPSTAT bits: S = 1, D_A = 0, R_W = 0, BF = 1
//
// State 2: I2C write operation, last byte was a data byte.
// SSPSTAT bits: S = 1, D_A = 1, R_W = 0, BF = 1
//
// State 3: I2C read operation, last byte was an address byte.
// SSPSTAT bits: S = 1, D_A = 0, R_W = 1 
//
// State 4: I2C read operation, last byte was a data byte.
// SSPSTAT bits: S = 1, D_A = 1, R_W = 1, BF = 0
//
// State 5: Slave I2C logic reset by NACK from master.
// SSPSTAT bits: S = 1, D_A = 1, BF = 0, CKP = 1 
//----------------------------------------------------------------------		

char HandleI2C(void)
	{	
		unsigned char address;
		unsigned char I2CSTAT;
															// copy status register		
		I2CSTAT = SSPSTAT & 0b00101101;						// mask out the used bits
															// decide the state
			if (I2CSTAT == STATE_1){						// address match, write
				index = 0;									// clear buffer index
				address = SSPBUF;							// dummy read to cear BF
//				SSPCON1bits.CKP = 1; // release clock		
//				DEB1=!DEB1;
				return 1;}
			if (I2CSTAT == STATE_2){						// master write byte
				inbuffer.bytes[index] = SSPBUF;				// read data and clear BF
//				SSPCON1bits.CKP = 1; // release clock				
				index++;									// increment index
				if(index>BUFSIZE) index = 0;				// if buffer length exceeded, clear index
				return 2;}
			if ((I2CSTAT & 0b00101100) == STATE_3){			// address match, read (ignore BF bit)
				index = 0;									// clear buffer index
		//		myWriteI2C(outbuffer.bytes[index]);			// a repeating function for writing
				myWriteI2C(0x01);			// a repeating function for writing
				index++;									// increment index
				return 3;}
			if (I2CSTAT == STATE_4){						// master read, buffer is empty. no need to read it.
				if(SSPCON1bits.CKP == 0)					// make sure the clock line hasn't been released
				{
					if(index>BUFSIZE) index = 0;			// if buffer length exceeded, clear index
		//			myWriteI2C(outbuffer.bytes[index]);		// a repeating function for writing
					myWriteI2C(0x02);							// a repeating function for writing
					index++;								// increment index
					return 4;
				}
			}
			if ((I2CSTAT & 0b00101000) == STATE_5){			// NACK received when sending data to the master		
			return 5;}										// Mask RW bit in SSPSTAT

		return -1;										    // if no state, return error code
		}

//---------------------------------------------------------------------
// myWriteI2C
//---------------------------------------------------------------------

void myWriteI2C(unsigned int data)
{
//	AUTO_LED=!AUTO_LED;
	do 
	{							
		SSPCON1bits.WCOL = 0;								// clear collision bit
		SSPBUF = data;						// load hardware buffer
	}
	while(SSPCON1bits.WCOL);							// if there was a collision, try again ???? !!!! Not good with a blocking call

//	SSPCON1bits.CKP = 1;								// release the clock stretch
}

unsigned char getData(unsigned char indx)
{
	return inbuffer.bytes[indx];
}

void setData1(unsigned char data)
{
	outbuffer.bytes[0]=data;
}
void setData2(unsigned char data)
{
	outbuffer.bytes[1]=data;
}