/* Compile options:  -ml (Large code model) */

//#include <stdio.h>
#include <p18f4520.h>
#include <timers.h>
#include "typedefs.h"
#include <spi.h>	
#include <adc.h>
#include <math.h>
#include "SPI_routine.h"
#include "PWM_routine.h"
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

#define LED  		LATBbits.LATB0

#define DEBUG0  		LATDbits.LATD0 // PIN 19
#define MOTOR_ON 		LATCbits.LATC0

#define hibyte(x)       (unsigned char)(x>>8)
#define lobyte(x)        (unsigned char)(x & 0xFF)

#define SPIidleThreshold	100

#define SDA  			PORTCbits.RC4
#define SCL  			PORTCbits.RC3



#pragma udata access volatile_access
ram near unsigned int PreviousFaderGoal;
ram near unsigned int FaderGoal;
ram near unsigned char NewDataIn;
ram near unsigned char WorkFader;
unsigned int Steps=30;
ram near unsigned int LoopCnt;
ram near unsigned int SPItimer;
ram near unsigned int debugTime;
ram near unsigned int InitCntDelay;
ram near unsigned int FaderGoalSteps;
ram near unsigned int FaderPosition;  
ram near unsigned char syncByte1;
ram near unsigned char syncByte2;
ram near unsigned char ShopSlots;
// ram near unsigned int Cnt;
 ram near unsigned int TicksPerFrame;
ram near unsigned char TickMain;
ram near unsigned char postScaler;

#pragma udata
unsigned char TestPhase=0;
unsigned int InitCnt=0;
unsigned int Tick=8;
unsigned char FaderReady=0;
unsigned char testVal=0;
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
unsigned int const ERRORTOL = 3;
unsigned int const ONLINETIME = 50;

extern unsigned int TOUCH_RELEASE;



// *********************************** Prototypes ****************************************
void Init(void);
void HighISRCode();
void LowISRCode();
unsigned int Init_Fader (void);
char ReadEEPROM(char address);
void WriteEEPROM(char address,char data);
extern void SetFaderMacro(unsigned char);

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
	static int idleSpiCnt = 0;

// ************************ P W M  I n t e r r u p t ******************************************
	if (INTCONbits.TMR0IF)									// Timer base
	{		
		postScaler++;
		SPItimer++;
/*
		if(SCL)idleSpiCnt=0;
		if(++idleSpiCnt==10){SSPCON1bits.SSPEN==0;}
*/
		if((postScaler&0x03)==0x03)			// I frame is 70-80 ticks;
		{			       
			LoopCnt++;	
			Start_ADC();
			FaderPosition=Read_ADC();                            					// Sample Fader CV
		//	Start_Scan_Touch();	   
			faderFlag=1;          
		//	Scan_Touch(); 

			if(!LocalTouch)	// Not touched: Do fader motion if needed
			{
				// Interpolate		
				FaderGoalSteps=(((Steps-LoopCnt)*PreviousFaderGoal)+(LoopCnt*FaderGoal))/Steps;		// 0.14ms
				// Calculate Motor Speed and Direction
				Calculate_Motor_PWM(FaderGoalSteps,FaderPosition);	
				// Update PWM		
				if(online){Handle_Fader();}										// 0.04ms  
				
			}
			else
			{
				MOTOR_ON = 0;
			}
		}

		if((postScaler&0x0F)==0x0F)			// I frame is 70-80 ticks;
		{	
			Start_Scan_Touch();         
			Scan_Touch(); 
		}
		INTCONbits.TMR0IF = 0;
	}

}

#pragma interruptlow LowISRCode
void LowISRCode()
{	

	unsigned char tempByte;
	static unsigned char CntrX = 0;
	static unsigned char SpiCntr = 0;

// ************************ S P I  I n t e r r u p t ******************************************
	if(PIR1bits.SSPIF)					                        // if new SPI event occured
	{	
		tempByte=SSPBUF;
	    	PIR1bits.SSPIF = 0;				                        // reset SPI interrupt
		if(SpiCntr==0)											// first byte
		{
			SpiCntr++;
			syncByte1=tempByte;
			SSPBUF = ((syncByte2 & 0x33) + 0x08);           	// write second byte + OA stamp
		    NewDataIn=0;                                        // Flag for new SPI data in
LED=(!LED & ((syncByte2&0x10)!=0x10));
		}
		else													// second byte
		{
			SpiCntr=0;
			inbuffer.bytes[0]=syncByte1;
			inbuffer.bytes[1]=tempByte;
			SSPBUF = outbuffer.bytes[0];          				// write byte to SSPBUF register
			syncByte2 = outbuffer.bytes[1];
			

			// If fader data came in, put it in place
			// Check the Command Flag. if 0 it must be fader data
		   	NewDataIn=1;                                        // Flag for new SPI data in
		}

		SPItimer=0;
	}
}	//This return will be a "retfie", since this is in a #pragma interruptlow section 


#pragma code

// *********************************** MAIN ****************************************
void main (void)
{ 
	unsigned int thrsDisplay;
	signed int error;
	static unsigned char lastTouch = 0;
	static signed int waveCV = 0;
	static signed char waveAdd = 5;
	Init();

	//	HANDSHAKE = 1;

	LoopCnt=0;

	while(1)
	{	
		if((faderFlag))
		{
			faderFlag=0;	

			error = FaderGoal;
			error -= FaderPosition;
			if(fabs(error)>ERRORTOL){onlineCntr=ONLINETIME;}



		if(1) // Handshake ??
		{


			if(LocalTouch) {FaderPosToSend=FaderPosition;onlineCntr=ONLINETIME;}
			FaderPosToSend=FaderPosition;


				// Only when new data has arrived
				if(NewDataIn && FaderReady )
				{
					// Command mask
					if((inbuffer.word & 0x0C00) == 0x0800)
					{
						// Check for commands
						switch(inbuffer.word & 0xF000) 
						{
						
							// Command 2 - Set touch release. Save it to EEPROM
					    		case 0x2000:
								WriteEEPROM(1,inbuffer.word & 0xFF);			// byte
								TOUCH_RELEASE = inbuffer.word & 0xFF;
						//		FaderReady=0;
						//		TestPhase==0;
						//		InitCnt=0;
						//		_asm GOTO 0x0000 _endasm
							break;

							// Command 3 - Set touch threshold. Save it to EEPROM
					    		case 0x3000:
								WriteEEPROM(0,inbuffer.word & 0xFF);			// 0-99
								touchThreshold=inbuffer.word & 0xFF;
						//		FaderReady=0;
						//		TestPhase==0;
						//		InitCnt=0;
						//		_asm GOTO 0x0000 _endasm
							break;


							// Command 4 - Set fader PID macro. Save it to EEPROM
					    		case 0x4000:
								WriteEEPROM(2,inbuffer.word & 0xFF);			// 0-99
								FaderReady=0;
								TestPhase==0;
								InitCnt=0;
								SetFaderMacro(inbuffer.word & 0x07);
						//		_asm GOTO 0x0000 _endasm
							break;

							// default
				    			default: break;
						}
					}
					// If no command. It's fader data
					else
					{
						PreviousFaderGoal=FaderGoal;	// 
						FaderGoal=inbuffer.word&0x3ff;
// FaderGoal=waveCV;
				    		Steps=(Steps+LoopCnt-1)/2;      // Steps = Passed PWM ticks
				    		LoopCnt=0; 
						TickMain=1;
						NewDataIn=0;
					}
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

			if(onlineCntr==0){online=0;}
			else {online=1;onlineCntr--;}

		}

		}



		if(TickMain)
		{
			TickMain=0;
			outbuffer.word=(outbuffer.word&0xfc00)+FaderPosToSend;					// Make CV data read to ship!
			
			if(FaderReady)					
			{
				outbuffer.touch_press=LocalTouch;

/*
				if(LocalTouch!=lastTouch)
				{
					outbuffer.touch_press=LocalTouch;
					outbuffer.touch_release=lastTouch;
					lastTouch=LocalTouch;
				}
				else
				{
					outbuffer.touch_press=0;
					outbuffer.touch_release=0;
				}
*/
				
			}
		
		}

	}
}
// *********************************** Init ****************************************
void Init(void)
{
	unsigned char i;
	unsigned int cntDown=0xFFF;
	long dly =200000;
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
Port A	1 OSC	1 OSC	1 SPI SS	1 Ref+	1 Ref-	1		1 TchX	1 FdrADC
Port B	0 PGD	0 PGC	0 PGM	1 		0 	 	0 		0 		0 LED
Port C	0		0		0 SDO	1 SDI	1 SCK	0 PWM+	0 PWM-	0 MtrEN
Port D	0 	 	0 		0 		0 		0 		0 		0 		0 
Port E									X MCLR	1 TchAD	1 		1 	
*/
	TRISEbits.PSPMODE = 0;

	TRISA = 0xFF; 
	TRISB = 0x10;	
	TRISC = 0x28;
	TRISD = 0x00;
	TRISE = 0x04;

		inbuffer.bytes[0]=0;
		inbuffer.bytes[1]=0;
		outbuffer.bytes[0]=0;
		outbuffer.bytes[1]=0;


	SetFaderMacro(ReadEEPROM(2));
	touchThreshold=ReadEEPROM(0);
	TOUCH_RELEASE = ReadEEPROM(1);
	TOUCH_RELEASE = (TOUCH_RELEASE<<1);
	if(touchThreshold<1 || touchThreshold>99)touchThreshold=50;

// touchThreshold=50;
// TOUCH_RELEASE = 50;

	while(--dly)
	{LED=0;}
	LED=1;
	

	INTCONbits.PEIE = 1;
	INTCONbits.GIE = 1;
	RCONbits.IPEN = 1;            //enable priority levels



	OpenADC(	ADC_FOSC_32     	&
				ADC_RIGHT_JUST		&
				ADC_2_TAD,
				ADC_CH12			&
				ADC_INT_OFF			&
				ADC_VREFPLUS_EXT
				, 15 );		
	ADCON1 = 0x0C;

	OpenTimer2(T2_PS_1_1 & TIMER_INT_OFF & T2_POST_1_1);	// 31.248 kHz
	IPR1bits.TMR2IP=1;			// TMR2 high prio interrupts
	PR2=0xff;
	OpenPWM1(0xFF);									// Turn PWM on
	SetDCPWM1(0); 

	OpenPWM2(0xFF);									// Turn PWM on
	SetDCPWM2(0);  

	InitCntDelay=0;
	TickMain=0;

	while(cntDown--)
	{
		if(SCL)cntDown=0xFFF;
	}

	/*
		SSON - SS pin is used as sync pin
		MODE_00   -
			CKE=1		// data is transmitted on falling edge
			CKP=0		// Clock is idle low
		MODE_01   -
			CKE=0		// data is transmitted on rising edge
			CKP=0		// Clock is idle low
		MODE_10   -
			CKE=1		// data is transmitted on falling edge
			CKP=1		// Clock is idle high
		MODE_11   -
			CKE=0		// data is transmitted on raising edge
			CKP=1		// Clock is idle high
	*/


	OpenSPI(SLV_SSON, MODE_00, SMPMID);
	PIE1bits.SSPIE = 1; // SSP interrupt enable
	IPR1bits.SSPIP = 0; // Low Prio SPI

	OpenTimer0( TIMER_INT_ON &
	T0_8BIT &
	T0_SOURCE_INT &
	T0_PS_1_4 );
	INTCON2bits.TMR0IP=1;			// TMR0 loprio interrupts

	DEBUG0=0;

}



unsigned int Init_Fader (void)
{
	static unsigned int FaderGoal=0;

	outbuffer.status=0;
	outbuffer.mute_press=0;
	outbuffer.mute_release=0;
	outbuffer.touch_press=0;
	outbuffer.touch_release=0;

	

	if(TestPhase==0)
	{
		
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
				TestPhase=0;

				
				TRISCbits.TRISC3 = 1; //SCLK
				TRISCbits.TRISC4 = 1; //MOSI
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





