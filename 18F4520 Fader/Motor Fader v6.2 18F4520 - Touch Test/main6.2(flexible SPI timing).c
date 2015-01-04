/* Compile options:  -ml (Large code model) */

//#include <stdio.h>
#include <p18f4520.h>
#include <timers.h>
#include "typedefs.h"
//#include <i2c.h>	/* Master Synchonous Serial I2C */
#include <spi.h>
#include <adc.h>
#include <math.h>
//#include "I2C_routine.h"
#include "SPI_routine.h"
#include "PWM_routine.h"
#include "SWITCHES_routine.h"
#include "LEDs_routine.h"
/*
New in 4.0
==========
+ faderMode
		0 = not initialized
		1 = standard Control Surface Mode
		2 = VCA Group Mode
		3 = Audio Fader Mode
+ vcaValue added

Need to be fixed:
=================
- Chase timeout need to reset when error is greater than tolerance
- Fix init fader sequence with fader id delay
- Implement VCA group mode
- Hunt the latch twitch!
	Try clearing the interpolation when status is changed


New in 6.1
==========
- Try 3 bytes SPI transfer.3 bits index

6.2
==========
- Make fader readey for USB-HUI inteface
- SPI data comes randomly
- Interpolation needs to be adjusted

*/

// *************************** F  A  D  E  R    I  D  ************************************
// *************************** F  A  D  E  R    I  D  ************************************
// *************************** F  A  D  E  R    I  D  ************************************
// *************************** F  A  D  E  R    I  D  ************************************

#define FADER_ID	1

// *************************** F  A  D  E  R    I  D  ************************************
// *************************** F  A  D  E  R    I  D  ************************************
// *************************** F  A  D  E  R    I  D  ************************************
// *************************** F  A  D  E  R    I  D  ************************************

#define ATTENTION_RELEASE		6				// Release time for attention BLINK
#define INIT_SPEED		30				//

#pragma config WDT = OFF

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

/*
#define DEB0 LATBbits.LATB0
#define DEB1 LATBbits.LATB1
#define DEB2 LATBbits.LATB2
*/

#define AUTO_LED  		LATBbits.LATB0
#define TOUCH_LED  		LATBbits.LATB1
#define WRITE_LED  		LATBbits.LATB2
#define MUTE_LED  		LATBbits.LATB3

#define DEBUG0  		LATDbits.LATD0
#define SDA  			PORTCbits.RC4
#define SCL  			PORTCbits.RC3
#define MOTOR_ON 		LATCbits.LATC0

#define hibyte(x)       (unsigned char)(x>>8)
#define lobyte(x)        (unsigned char)(x & 0xFF)

#define SPIidleThreshold	100



#pragma udata access volatile_access
ram near unsigned int PreviousFaderGoal;
ram near unsigned char NewDataIn;
ram near unsigned char WorkFader;
unsigned int Steps=30;
ram near unsigned int LoopCnt;
ram near unsigned int SPIsyncDelayTmr;
ram near unsigned int debugTime;
ram near unsigned int InitCntDelay;
ram near unsigned int FaderGoalSteps;
ram near unsigned int FaderPosition;
ram near unsigned char I2Cstate;
ram near unsigned char syncByte[2];
ram near unsigned char syncByteOut[2];
ram near unsigned char syncByte1;
ram near unsigned char syncByte2;
ram near unsigned char ShopSlots;
// ram near unsigned int Cnt;
 ram near unsigned int TicksPerFrame;
ram near unsigned char TickMain;
ram near unsigned char postScaler;

#pragma udata
unsigned int Tick=8;
unsigned int BlinkCnt = 0;
unsigned int AttCnt = 0;
unsigned char SSLchannel=FADER_ID;
unsigned char sslVCAgroup = 0;
unsigned char xID=FADER_ID;
unsigned char AttentionBlink=0;
unsigned char BlinkLED=0;
unsigned char FaderReady=0;
unsigned char testVal=0;
unsigned char HANDSHAKE=1;
unsigned char handShakeFlag=0;
unsigned char faderMode=1;
unsigned int vcaValue=827;				// find 0dB
unsigned char tmrSnap = 0;
unsigned char temp=0;
unsigned char mem=0;
unsigned char touchThreshold=220;
unsigned int writeCntr = 0;
unsigned int FaderPosToSend=0;
unsigned char LocalStatus = 0;
unsigned char faderFlag = 0;

unsigned int onlineCntr = 200;
unsigned int online = 0;
unsigned int const ONLINETIME = 250;		// ms
unsigned int const ERRORTOL = 2;			// steps

unsigned int cntr =0;
unsigned int faderGoal;

signed long interSetPoint;
signed int setPoint;
signed int softSetPoint;
signed long delta;

// *********************************** Prototypes ****************************************
void Init(void);
void HighISRCode();
void LowISRCode();
void unpackBuffer (void);
void Init_Display (void);
unsigned int Init_Fader (void);
char ReadEEPROM(char address);
void WriteEEPROM(char address,char data);

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
	static unsigned char postScaler=0;

// ************************ P W M  I n t e r r u p t ******************************************
	if (INTCONbits.TMR0IF)									// Timer base
	{
		LoopCnt++;
		BlinkCnt++;
		cntr++;
		postScaler++;


		if(postScaler&0x2==0x2)
		{
			Scan_Touch();
			Start_ADC();
		}
		else
		{ 
			FaderPosition=Read_ADC(); 

			// Interpolate
			interSetPoint+=delta;
			softSetPoint=interSetPoint/100;							

			if(softSetPoint>1023)softSetPoint=1023;
			if(softSetPoint<0)softSetPoint=0;

			if(!LocalTouch)	// Not touched: Do fader motion if needed
			{
				// check if timer runned out
				if(onlineCntr>0)
				{
					// Calculate Motor Speed and Direction
					Calculate_Motor_PWM(softSetPoint,FaderPosition);
					// Update PWM
					Handle_Fader(1);										// 0.04ms
				}
				else
				{
					Handle_Fader(0);										// 0.04ms
				}
			}
			else
			{
				MOTOR_ON = 0;
			}

			faderFlag=1;
			Start_Scan_Touch();
		}
		if(BlinkCnt==200){BlinkLED=!BlinkLED;BlinkCnt=0;}
								// Takes 0.03ms
		INTCONbits.TMR0IF = 0;
	}
}

#pragma interruptlow LowISRCode
void LowISRCode()
{

	unsigned char tempByte;
	unsigned char cntrBits;
	static unsigned char CntrX = 0;
	static unsigned char errorMask = 0;

// ************************ S P I  I n t e r r u p t ******************************************
	if(PIR1bits.SSPIF)					                        // if new SPI event occured
	{
		tempByte=SSPBUF;
		cntrBits=tempByte>>6;
		PIR1bits.SSPIF = 0;
		
		switch (cntrBits)
		{
			case 1:
				outbuffer.word=(outbuffer.word&0xfc00)+FaderPosToSend;					// Make CV data read to ship!
				syncByte[0]=tempByte & 0b00111111;
				SSPBUF = outbuffer.bytes[0];
				syncByte2 = outbuffer.bytes[1];
				errorMask+=0x1;
			break;

			case 2:
				syncByte[0]+=(tempByte & 0b00000011) << 6;
				syncByte[1]=(tempByte & 0b00111100) >> 2;
				SSPBUF = syncByte2;
				errorMask+=0x2;
			break;

			case 3:
				syncByte[1]+=(tempByte & 0b00001111) << 4;
				if(errorMask==0x3)
				{
					NewDataIn=1;
					inbuffer.bytes[0]=syncByte[0];
					inbuffer.bytes[1]=syncByte[1];
				}
				errorMask=0x0;
				
			break;

	
			default:

				LATCbits.LATC5=0;
				SSPCON1bits.SSPEN=0;
				OpenSPI(SLV_SSOFF, MODE_01, SMPMID);
				SSPBUF = 0;
				errorMask=0x0;
				// error;
			break;
		}		

	}




}	//This return will be a "retfie", since this is in a #pragma interruptlow section


#pragma code

// *********************************** MAIN ****************************************
void main (void)
{
	unsigned int thrsDisplay;
	signed int error;
	Init();

		AUTO_LED=1;
		TOUCH_LED=1;
		WRITE_LED=0;
		MUTE_LED=1;
		SlideShow(0);
	//	HANDSHAKE = 1;

	LoopCnt=0;

	while(1)
	{
		// interval every 2ms
		if(faderFlag)
		{
			faderFlag=0;    
     
			if(onlineCntr>0)onlineCntr--;
			
			switch (faderMode)
			{
				case 1:
					if(LocalTouch || LocalStatus==3)FaderPosToSend=FaderPosition;
				break;
				
				case 2:
					FaderPosToSend=vcaValue;
				break;
				
				case 3:

				break;
			}
	
			// Interval for incomming data

			if(NewDataIn)
			{
				NewDataIn=0;
				// Check buffer for commands
				unpackBuffer();

				// Find out value for delta divider
				TicksPerFrame=(TicksPerFrame+LoopCnt)/2;
				LoopCnt=0;

if(TicksPerFrame>35)TicksPerFrame=35;

				// Release blink attention
				if(AttCnt>0)AttCnt--;
				AttentionBlink=AttCnt;

				// When init sequence is done, update setPoint from incomming data
				if(FaderReady)
				{
					if(LocalTouch || LocalStatus==3) setPoint=FaderPosition;
					else setPoint=faderGoal;

					if(LocalTouch && faderMode==2) vcaValue=FaderPosition;
				}

				// Init Fader Sequence
				else
				{
					setPoint=Init_Fader();
				}


				// Find out delta value
				delta=(setPoint-(softSetPoint));
				delta=delta*100;
				delta=delta/((TicksPerFrame>>1));
				
				// Not critical stuff is handle outside this
							
				TickMain=1;
			}
		}


		if(TickMain)
		{
			TickMain=0;

			// Error threshold for correction. Clears timer
			if(fabs(setPoint-FaderPosition)>ERRORTOL)onlineCntr=ONLINETIME;

			if(FaderReady)
			{
				if(writeCntr>50){writeCntr=0;faderMode=3;}		// set touch sense threshold
	
				if(faderMode==1 && !LocalTouch) Update_LED_Display(SSLchannel);
				if(faderMode==2 && !LocalTouch) Update_LED_Display_Group(sslVCAgroup);
				if(faderMode==1 && LocalTouch) Update_LED_Display_Bits(Calculate_dB_Display(faderGoal, FaderPosition));
	
				if(faderMode==3)
				{
					thrsDisplay = touchThreshold;
					Update_LED_Display(thrsDisplay);
				}
				Handle_LEDs(faderMode);

				Read_Switches();
				if(outbuffer.status==0x03)FaderPosToSend=FaderPosition;
			}

		}

	}
}
// *********************************** Init ****************************************
void Init(void)
{
	unsigned char i;
	unsigned int cntDown=0xFFF;
//	unsigned char I2Caddress=0;
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
/*

		7		6		5		4		3		2		1		0
Port A	1 OSC	1 OSC	1 MutSW	1 Ref+	1 Ref-			1 TchX	1 FdrADC
Port B	0 PGD	0 PGC	0 PGM	1 AltSW	0 MutLD 0 WrtLD	0 TchLD	0 AutLD
Port C					0 StSW	1 LDtrm	1 LDabs	0 PWM+	0 PWM-	0 MtrEN
Port D	1 AutSW 0 LDstr	0 LDclk	0 LDsdo	0 muxD	0 muxC	0 muxB	0 muxA
Port E									X MCLR	1 TchAD	1 WtSW	1 TchSW
*/
	TRISEbits.PSPMODE = 0;

	TRISA = 0xFF;
	TRISB = 0x10;
	TRISC = 0x28;
	TRISD = 0x80;
	TRISE = 0x07;

/*
	TRISB = 0xF0;
	TRISC = 0xD8;
	TRISD = 0x80;
	TRISE = 0xFC;
*/

//	DEBUG0=0;
	INTCONbits.PEIE = 1;
	INTCONbits.GIE = 1;
	RCONbits.IPEN = 1;            //enable priority levels


		inbuffer.bytes[0]=0;
		inbuffer.bytes[1]=0;
		outbuffer.bytes[0]=0;
		outbuffer.bytes[1]=0;

	// !!! No Ref- on rev 8.0

	touchThreshold=ReadEEPROM(0);
	if(touchThreshold<1 || touchThreshold>99)touchThreshold=50;
//			WriteEEPROM(0,50);

	OpenADC(	ADC_FOSC_32     	&
				ADC_RIGHT_JUST		&
				ADC_4_TAD,
				ADC_CH12			&
				ADC_INT_OFF			&
				ADC_VREFPLUS_EXT
				, 15 );
	ADCON1 = 0x0C;

	// OpenPWM1(0 to 255)  PWM period value
	OpenTimer2(T2_PS_1_1 & TIMER_INT_OFF & T2_POST_1_1);	// 31.248 kHz
	IPR1bits.TMR2IP=1;			// TMR2 high prio interrupts
	PR2=0xff;
	OpenPWM1(0xFF);									// Turn PWM on
	SetDCPWM1(0);

	OpenPWM2(0xFF);									// Turn PWM on
	SetDCPWM2(0);

	InitCntDelay=0;
	TickMain=0;

//	DEBUG0=1;
	while(cntDown--)
	{
		if(SCL)cntDown=0xFFF;
	}
//	DEBUG0=0;

	OpenSPI(SLV_SSOFF, MODE_01, SMPMID);
	PIE1bits.SSPIE = 1; // SSP interrupt enable
	IPR1bits.SSPIP = 0; // Low Prio SPI

	OpenTimer0( TIMER_INT_ON &
	T0_8BIT &
	T0_SOURCE_INT &
	T0_PS_1_16);
	INTCON2bits.TMR0IP=1;			// TMR0 loprio interrupts

	DEBUG0=0;

}

void unpackBuffer(void)
{
	if(!inbuffer.CMD_FLAG)
	{
		LocalStatus=inbuffer.status;
		if(faderMode==1)faderGoal=inbuffer.word&0x3FF;
		if(faderMode==2)faderGoal=vcaValue;
		return;
	}
	
	switch(inbuffer.CMD) 
	{
	// ID change
		case 0:
			SSLchannel = inbuffer.CHANNEL_ID;
			faderMode = 1;							// channel status switch to standard mode
			AttCnt=0;								// reset blink ??????

		break;
	// Handshake
	    case 1:
			handShakeFlag = 1;
		break;
	// Set mode
	    case 2:
			faderMode = inbuffer.CHANNEL_ID;		// 7 bit number
			if(faderMode==2)
			{
				faderGoal=vcaValue;
				sslVCAgroup=((SSLchannel-1)%8)+1;
			}
			onlineCntr=ONLINETIME;
		break;
	// Update vcaValue
	    case 3:
			vcaValue = inbuffer.HI_BYTE;
			vcaValue <<= 8;
			vcaValue += inbuffer.LO_BYTE;
			faderGoal=vcaValue;
			onlineCntr=ONLINETIME;
			break;
	// the Wave
	    case 4:
		// Do the wave. Maybe handShakeFlag is enough? Try!
			handShakeFlag = 1;
		break;
	// default
	    default: break;
	}

	if(faderMode==1)
	{
		// Attention blink
		if(inbuffer.BLINK_EVENT)AttCnt=ATTENTION_RELEASE*10;
	}
}

unsigned int Init_Fader (void)
{
	static unsigned	char TestPhase=0;
	static int InitCnt=0;
	static int SeqCnt=0;
	static int SeqDelay=0;
	static unsigned int FaderGoal=0;
	unsigned char I2Caddress=0;

	outbuffer.status=0;
	outbuffer.mute_press=0;
	outbuffer.mute_release=0;
	outbuffer.touch_press=0;
	outbuffer.touch_release=0;

	SeqDelay++;
	if(SeqDelay>(20-(FADER_ID*8)))
	{
		SeqCnt++;
		if((SeqCnt>>3)<24)SlideShow(SeqCnt>>3);
		else SlideShow(0);
	}
	else SlideShow(0);


	if(TestPhase==0)
	{
		AUTO_LED=1;
		TOUCH_LED=1;
		WRITE_LED=1;
		MUTE_LED=1;

		FaderGoal=0;
		InitCnt++;
		if(InitCnt>10)
		{
			TestPhase=1;
			InitCntDelay=0;
		}
	}
	if(TestPhase==1)
	{
		InitCntDelay++;
		if(InitCntDelay>(FADER_ID<<3))
		{
			if(FaderGoal<(1023-INIT_SPEED))FaderGoal+=INIT_SPEED;
			else
				{
				FaderGoal=1023;
				InitCnt++;
				if(InitCnt>50)
				{
					Start_ADC();
					TopLimit=Read_ADC();
					if(TopLimit<800)TopLimit=1023;
					InitCnt=0;
					TestPhase=2;
				}
			}
		}
	}
	if(TestPhase==2)
	{
		if(FaderGoal>INIT_SPEED)FaderGoal-=INIT_SPEED;
		else
			{
			FaderGoal=0;
			InitCnt++;
			if(InitCnt>50)
			{
				Start_ADC();
				BotLimit=Read_ADC();
				if(BotLimit>50)BotLimit=0;
				InitCnt=0;
				SetScale();
				FaderReady=1;
				vcaValue=827;
				faderMode=2;
				onlineCntr=ONLINETIME;
				TestPhase=0;

//				I2Caddress =(FADER_ID-1);
//				I2Caddress <<= 1;
//				OpenI2C (SLAVE_7, SLEW_ON);
//				SSPADD = 0xE0+I2Caddress; 	// slave address
//				SSPCON2bits.SEN = 1;     		// hmmm clock streching ????
//				PIE1bits.SSPIE = 1; // SSP interrupt enable
//
//					TopLimit=1010;
//					BotLimit=0;

				TRISCbits.TRISC3 = 1; //SCLK
				TRISCbits.TRISC4 = 1; //MOSI
//				SSPCON1bits.SSPEN=0;
//				SSPCON1bits.SSPEN=1;
//				OpenSPI(SLV_SSOFF, MODE_01, SMPMID);
//				PIE1bits.SSPIE = 1; // SSP interrupt enable
			}
		}
	}
	return FaderGoal;
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
