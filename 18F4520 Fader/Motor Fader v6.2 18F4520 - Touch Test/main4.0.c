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
- Fix display letters
- Fix dB calculation
	Fixed !
- Fix init fader sequence with fader id delay
- Implement VCA group mode
	Fixed. Mute doesn't work !!!
- Hunt the latch twitch!
	Try clearing the interpolation when status is changed
- Start up idle. Wait for command and channel id before the wave


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

#define ATTENTION_RELEASE		4				// (seconds) Release time for attention BLINK
#define INIT_SPEED		15				// 

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
unsigned int vcaValue=800;				// find 0dB
unsigned char tmrSnap = 0;
unsigned char temp=0;
unsigned char mem=0;
unsigned char touchThreshold=220;
unsigned int writeCntr = 0;
unsigned int FaderPosToSend=0;
unsigned char LocalStatus = 0;




// *********************************** Prototypes ****************************************
void Init(void);
void HighISRCode();
void LowISRCode();
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
	unsigned char tempByte;
	static unsigned char CntrX = 0;
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



		if(SPItimer>40)											// first byte
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
			AUTO_LED=!AUTO_LED;
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
			TOUCH_LED=!TOUCH_LED;

			// If fader data came in, put it in place
			// Check the Command Flag. if 0 it must be fader data
			if(!inbuffer.CMD_FLAG)
			{
		    	NewDataIn=1;                                        // Flag for new SPI data in
				LocalStatus=inbuffer.status;
				WRITE_LED=!WRITE_LED;
				CntrX = (CntrX+TicksPerFrame)/2;
	//			Update_LED_Display(CntrX);
				TicksPerFrame=0;
			}
			// Check out the Command
			else
			{
				switch(inbuffer.CMD) {
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
						FaderPosToSend=vcaValue;
						sslVCAgroup=((SSLchannel-1)%8)+1;
					}
					break;
				// ??
				    case 3:  
					SSLchannel = 0;
					break;
				// the Wave
				    case 4:  
					// Do the wave. Maybe handShakeFlag is enough? Try!
					handShakeFlag = 1; 
					break;
				// default
				    default: break;
				    }
				// Attention blink
				if(inbuffer.BLINK_EVENT)AttCnt=ATTENTION_RELEASE*10;
			}
			SSPCON1bits.SSPEN=0;	// Stop SPI

			DEBUG0=0;
		}
		SPItimer=0;
	}

}

#pragma interruptlow LowISRCode
void LowISRCode()
{	

// ************************ P W M  I n t e r r u p t ******************************************

	if (INTCONbits.TMR0IF)									// Timer base
	{	
		FaderPosition=Read_ADC();                            					// Sample Fader CV
		Start_Scan_Touch();	    	

		postScaler++;
		SPItimer++;
		TicksPerFrame++;
		LoopCnt++;	
		SettleCnt++;															// Count how many ticks


		if(TicksPerFrame==45)		// Must Trigger once
		{
			SSPCON1bits.SSPEN=1;	// Start SPI
		}

		if(TicksPerFrame>75)		// If lost reste after 1 frame;
		{
			SSPCON1bits.SSPEN=1;	// Start SPI
			TicksPerFrame=0;
		}

		if(postScaler>8)			// I frame is 70-80 ticks;
		{
			BlinkCnt++;	  
			postScaler=0;	
		}


		if(1) // Handshake ??
		{
	// Filter added 2014-08-04
	//		FaderPosition=(FaderPosition+Read_ADC())/2;                            					// Sample Fader CV	

/*
			if(LocalTouch)FaderPosToSend=FaderPosition;
			if(faderMode==2 && LocalTouch)				// VCA Group Mode
			{
				vcaValue=FaderPosition;					// if VCA group mode and fader is touched. Update stored vcaValue
				FaderGoal=vcaValue;
				PreviousFaderGoal=FaderGoal;	// no need for smoothing when in direct control loop (Fader wiper -> Fader Goal)			
			}
			if(faderMode==1)FaderPosToSend=FaderPosition;
			if(faderMode==3)				// VCA Group Mode
			{
				FaderGoal=FaderPosition;
				PreviousFaderGoal=FaderGoal;	// no need for smoothing when in direct control loop (Fader wiper -> Fader Goal)			
			}
*/
			if(!LocalTouch)	// Not touched: Do fader motion if needed
			{
				// Interpolate		
				FaderGoalSteps=(((Steps-LoopCnt)*PreviousFaderGoal)+(LoopCnt*FaderGoal))/Steps;		// 0.14ms
				// Calculate Motor Speed and Direction
				Calculate_Motor_PWM(FaderGoalSteps,FaderPosition);	
				// Update PWM		
				Handle_Fader();										// 0.04ms  
			}
			else
			{
				MOTOR_ON = 0;
				SettleCnt=0;
			}

			outbuffer.word=(outbuffer.word&0xfc00)+FaderPosToSend;					// Make CV data read to ship!
  

			// Make sure Fader init sequence is not running
//			if(FaderReady)			
//			{
			// Timer for stop trying to find the goal
//				if(LocalTouch)SettleCnt=0;

				// Only when new data has arrived
				if(NewDataIn && FaderReady )
				{
					if(faderMode==1)					// Standard Control Surface Mode
					{
					//	if(FaderGoal!=PreviousFaderGoal)SettleCnt=0;
						PreviousFaderGoal=FaderGoal;	// smoothing is good!
//						FaderGoal=inbuffer.word&0x3ff;
					//	if(FaderGoal>1023)FaderGoal=1023;
					}
					if(faderMode==2)					// VCA Group Mode
					{
						FaderGoal=vcaValue;
						PreviousFaderGoal=FaderGoal;	// no need for smoothing when in direct control loop (Fader wiper -> Fader Goal)
					}
					if(faderMode==3)					// Touch Trim Mode
					{
					//	FaderGoal=touchThreshold*4;
					//	PreviousFaderGoal=FaderGoal;	// no need for smoothing when in direct control loop (Fader wiper -> Fader Goal)
					}
		    		Steps=(Steps+LoopCnt-1)/2;      // Steps = Passed PWM ticks
		    		LoopCnt=0; 
					TickMain=1;
					NewDataIn=0;
				}                           
//			}

			// Init Fader Sequence
			if(!FaderReady && (LoopCnt>15))							// done with the transfer
			{
				PreviousFaderGoal=FaderGoal;
				FaderGoal=Init_Fader();
				Steps=LoopCnt;
				LoopCnt=0;
			}
		}
     											                
		Scan_Touch();
		Start_ADC(); 					// Takes 0.03ms
		INTCONbits.TMR0IF = 0;
	}

	
}	//This return will be a "retfie", since this is in a #pragma interruptlow section 


#pragma code

// *********************************** MAIN ****************************************
void main (void)
{ 
	unsigned int thrsDisplay;
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
		if((BlinkCnt>20) && !NewDataIn)
		{
			BlinkLED=!BlinkLED;
			BlinkCnt=0;
			if(AttCnt>0)AttCnt--;
			AttentionBlink=AttCnt;
		}
	
		//
/*
		if(PORTCbits.RC3 && tmrSnap>19){
		temp=tmrSnap;
		tmrSnap=0;
		}				// if SPI clock is active, reset idle detection timer
*/


		if(TickMain)
		{
			TickMain=0;
			if(writeCntr>50){writeCntr=0;faderMode=3;}		// set touch sense threshold
//			Update_LED_Display(FaderGoal>>4);
//			Update_LED_Display(faderMode);

			if(faderMode==1 && !LocalTouch) Update_LED_Display(SSLchannel);
//			if(faderMode==1) Update_LED_Display(CntrX);

			if(faderMode==2 && !LocalTouch) Update_LED_Display_Group(sslVCAgroup);
			if(faderMode==1 && LocalTouch) Update_LED_Display_Bits(Calculate_dB_Display(FaderGoal, FaderPosition));

			if(faderMode==3) 
			{
				thrsDisplay = touchThreshold;
				Update_LED_Display(thrsDisplay);
			}

//			Handle_LEDs(faderMode);
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

	touchThreshold=ReadEEPROM(0);
	if(touchThreshold<1 || touchThreshold>99)touchThreshold=50;
//			WriteEEPROM(0,50);

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

	OpenTimer0( TIMER_INT_ON &
	T0_8BIT &
	T0_SOURCE_INT &
	T0_PS_1_4 );
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
					TopLimit=Read_ADC()-15;
					if(TopLimit<800)TopLimit=1022;
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







