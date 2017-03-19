/* Compile options:  -ml (Large code model) */

//#include <stdio.h>
#include <p18f4520.h>
#include <timers.h>
#include "typedefs.h"
//#include <i2c.h>	/* Master Synchonous Serial I2C */
#include <spi.h>	
#include <adc.h>
//#include "I2C_routine.h"
#include "SPI_routine.h"
#include "PWM_routine.h"
#include "SWITCHES_routine.h"
#include "LEDs_routine.h"


// *************************** F  A  D  E  R    I  D  ************************************
// *************************** F  A  D  E  R    I  D  ************************************
// *************************** F  A  D  E  R    I  D  ************************************
// *************************** F  A  D  E  R    I  D  ************************************

#define FADER_ID	1

// *************************** F  A  D  E  R    I  D  ************************************
// *************************** F  A  D  E  R    I  D  ************************************
// *************************** F  A  D  E  R    I  D  ************************************
// *************************** F  A  D  E  R    I  D  ************************************

#define ATTENTION_RELEASE		4				// (seconds) Release time for attention BLINK
#define INIT_SPEED		20				// 

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

#define hibyte(x)       (unsigned char)(x>>8)
#define lobyte(x)        (unsigned char)(x & 0xFF)



#pragma udata access volatile_access
ram near unsigned int PreviousFaderGoal;
ram near unsigned int FaderGoal;
ram near unsigned char NewDataIn;
ram near unsigned char WorkFader;
unsigned int Steps=30;
ram near unsigned int LoopCnt;
ram near unsigned int SPItimer;
ram near unsigned int InitCntDelay;
ram near unsigned int FaderGoalSteps;
ram near unsigned int FaderPosition;  
ram near unsigned char I2Cstate;
ram near unsigned char syncByte1;
ram near unsigned char syncByte2;
ram near unsigned char ShopSlots;
// ram near unsigned int Cnt;
 ram near unsigned int TicksPerFrame;
ram near unsigned char TickMain;

#pragma udata
unsigned int Tick=8;
unsigned int BlinkCnt = 0;
unsigned int AttCnt = 0;
unsigned char SSLchannel=FADER_ID;
unsigned char xID=FADER_ID;
unsigned char AttentionBlink=0;
unsigned char BlinkLED=0;
unsigned char FaderReady=0;
unsigned char testVal=0;
unsigned char HANDSHAKE=1;
unsigned char handShakeFlag=0;




// *********************************** Prototypes ****************************************
void Init(void);
void HighISRCode();
void LowISRCode();
void Init_Display (void);
unsigned int Init_Fader (void);

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
	unsigned char tempByte;
//	if(PIR1bits.TMR2IF)					                        // 
//	{
//		PIR1bits.TMR2IF=0;
//
//	}

// ************************ I 2 C  I n t e r r u p t ******************************************
//	if(PIR1bits.SSPIF)					                        // if new I2C event occured
//	{	
//		I2Cstate=HandleI2C();                                   // Service I2C line. Should be fast
//	    PIR1bits.SSPIF = 0;				                        // reset I2C interrupt
//		if(I2Cstate==0x0A)                                      // 0x0A - last incoming byte
//		{
//			if(!(inbuffer.bytes[1]&0x30))
//			{
//			}
//		    NewDataIn=1;                                        // Flag for new I2C data in
//		}
//	}

// ************************ S P I  I n t e r r u p t ******************************************
	if(PIR1bits.SSPIF)					                        // if new SPI event occured
	{	
		tempByte=SSPBUF;
	    PIR1bits.SSPIF = 0;				                        // reset SPI interrupt

		if(SPItimer>9)											// first byte
		{
			syncByte1=tempByte;
//	 		SSPCON1bits.WCOL = 0;								//Clear any previous write collision
			if(handShakeFlag)
			{
				SSPBUF = 0xF0;
				handShakeFlag=0;
			}
			else
			{
				SSPBUF = syncByte2;           						// write byte to SSPBUF register
			}
		    NewDataIn=0;                                        // Flag for new SPI data in
//			AUTO_LED=!AUTO_LED;
		}
		else													// second byte
		{
			DEBUG0=1;
			inbuffer.bytes[0]=syncByte1;
			inbuffer.bytes[1]=tempByte;
 //			SSPCON1bits.WCOL = 0;								//Clear any previous write collision
			if(handShakeFlag)
			{
				SSPBUF = 0xF0;
			}
			else
			{
				SSPBUF = outbuffer.bytes[0];          				// write byte to SSPBUF register
			}
			syncByte2 = outbuffer.bytes[1];
//			TOUCH_LED=!TOUCH_LED;

			// If fader data came in, put it in place
			// Check the Command Flag. if 0 it must be fader data
			if(!inbuffer.CMD_FLAG)
			{
		    	NewDataIn=1;                                        // Flag for new SPI data in
			}
			// Check out the Command
			else
			{
				switch(inbuffer.CMD) {
				  	// ID change
					case 0: 
					SSLchannel = inbuffer.CHANNEL_ID;
					break;
				  	// Handshake
				    case 1:
					handShakeFlag = 1; 
					break;
				  	// ??
				    case 2:  
					SSLchannel = 0;
					break;
				    default: break;
				    }
				// Attention blink
				if(inbuffer.BLINK_EVENT)AttCnt=ATTENTION_RELEASE*10;
			}
	//		PIE1bits.SSPIE = 0; // SSP interrupt disable
	//		CloseSPI();
			DEBUG0=0;
		}
		SPItimer=0;
	}

}

#pragma interruptlow LowISRCode
void LowISRCode()
{	
	static unsigned int testCV=0;

// ************************ P W M  I n t e r r u p t ******************************************

	if (INTCONbits.TMR0IF)									// Timer base
	{	

//		TicksPerFrame++;
		// Timer to pick out byte 0 or 1. Short between 0 and 1. Long between 1 and 0;
		SPItimer++;
		// Timer for blinking
		BlinkCnt++;	
		if(SPItimer>9)											// first byte
		{
	//		OpenSPI(SLV_SSOFF, MODE_01, SMPMID);
	//		PIE1bits.SSPIE = 1; // SSP interrupt enable
		}

		if(1) // Handshake ??
		{
			LoopCnt++;																// Count how many ticks
			Start_ADC(); 															// 0.03ms
			FaderPosition=Read_ADC();                            					// Sample Fader CV	
			// Interpolate		
			FaderGoalSteps=(((Steps-LoopCnt)*PreviousFaderGoal)+(LoopCnt*FaderGoal))/Steps;		// 0.14ms
			// Calculate Motor Speed and Direction
			Calculate_Motor_PWM(FaderGoalSteps,FaderPosition);	
			// Update PWM		
			Handle_Fader();										// 0.04ms
			// Maybe this is not Atomic?
			outbuffer.word=(outbuffer.word&0xfc00)+FaderPosition;					// Make CV data read to ship!
			// Check Knob Touch 				
			Start_Scan_Touch();	           											                
			Scan_Touch();    
	
			// Make sure Fader init sequence is not running
			if(FaderReady)			
			{
				// Only when new data has arrived
				if(NewDataIn)
				{
					PreviousFaderGoal=FaderGoal;
					FaderGoal=inbuffer.word&0x3ff;
					NewDataIn=0;
		    		Steps=(Steps+LoopCnt-1)/2;                                      // Steps = Passed PWM ticks
		    		LoopCnt=0; 
					TickMain=1;
				}

			// Timer for stop trying to find the goal
				if(LocalTouch || (FaderGoal!=PreviousFaderGoal)){SettleCnt=0;}
				else{SettleCnt++;}		                                         
			}
			
			// Init Fader Sequence
			if(!FaderReady && (LoopCnt>15))							// done with the transfer
			{
				PreviousFaderGoal=FaderGoal;
				FaderGoal=Init_Fader();
				Steps=LoopCnt;
				LoopCnt=0;
			}
		}
		INTCONbits.TMR0IF = 0;
	}

	
}	//This return will be a "retfie", since this is in a #pragma interruptlow section 


#pragma code

// *********************************** MAIN ****************************************
void main (void)
{ 
	Init();

		AUTO_LED=1;
		TOUCH_LED=1;
		WRITE_LED=0;
		MUTE_LED=1;
		Update_LED_Display(0);
	//	HANDSHAKE = 1;

	LoopCnt=0;

//	while(1)
//	{
//		Update_LED_Display(1);
//	}
	while(1)
	{
		if((BlinkCnt>50) && !NewDataIn)
		{
			BlinkLED=!BlinkLED;
			BlinkCnt=0;
			if(AttCnt>0)AttCnt--;
			AttentionBlink=AttCnt;
		}
	



		if(TickMain)
		{
			TickMain=0;
//			Update_LED_Display(FaderGoal>>4);
			Update_LED_Display(SSLchannel);

			Handle_LEDs();
			if(FaderReady)					
			{
				Read_Switches();
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

/*
	OpenADC(	ADC_FOSC_32     	&
				ADC_RIGHT_JUST		&
				ADC_2_TAD,
				ADC_CH12			&
				ADC_INT_OFF			&
				ADC_VREFPLUS_EXT	&
				ADC_VREFMINUS_EXT
				, 15 );		
*/
	OpenADC(	ADC_FOSC_32     	&
				ADC_RIGHT_JUST		&
				ADC_2_TAD,
				ADC_CH12			&
				ADC_INT_OFF			&
				ADC_VREFPLUS_EXT
				, 15 );		
	ADCON1 = 0x0C;

	// OpenPWM1(0 to 255)  PWM period value
	OpenTimer2(T2_PS_1_1 & TIMER_INT_OFF & T2_POST_1_1);	// 31.248 kHz
	IPR1bits.TMR2IP=1;			// TMR2 high prio interrupts
//	PR2=2;
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

	OpenTimer0( TIMER_INT_ON &
	T0_8BIT &
	T0_SOURCE_INT &
	T0_PS_1_64 );
	INTCON2bits.TMR0IP=0;			// TMR0 loprio interrupts

	DEBUG0=0;
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
	if(SeqDelay>(65-(FADER_ID*8)))
	{
		SeqCnt++;
		if((SeqCnt>>3)<0x08)SlideShow(SeqCnt>>3);
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
				if(InitCnt>20)
				{
					Start_ADC(); 
					TopLimit=Read_ADC(); 
					if(TopLimit<985)TopLimit=1022;
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
			if(InitCnt>20)
			{		
				Start_ADC(); 
				BotLimit=Read_ADC(); 
				if(BotLimit>35)BotLimit=1;
				InitCnt=0;
				SetScale();	
				FaderReady=1;
				TestPhase=0;

//				I2Caddress =(FADER_ID-1);
//				I2Caddress <<= 1;
//				OpenI2C (SLAVE_7, SLEW_ON);
//				SSPADD = 0xE0+I2Caddress; 	// slave address
//				SSPCON2bits.SEN = 1;     		// hmmm clock streching ????
//				PIE1bits.SSPIE = 1; // SSP interrupt enable
//
				
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









