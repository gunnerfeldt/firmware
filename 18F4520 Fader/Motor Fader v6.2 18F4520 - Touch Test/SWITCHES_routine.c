#include "typedefs.h"
#include "I2C_routine.h"
#include "SWITCHES_routine.h"
#include <p18f4520.h>   /* for TRIS and PORT declarations */
#include <adc.h>

#define WRITE_LED  LATBbits.LATB2

#define AUTO_SW  !PORTDbits.RD7
#define TOUCH_SW  !PORTEbits.RE0
#define WRITE_SW  !PORTEbits.RE1
#define MUTE_SW  !PORTAbits.RA4
#define ALT_SW  !PORTBbits.RB4

#define TOUCH_ADC		ADC_CH7
#define TOUCH_X_ADC		ADC_CH1
#define TOUCH_X_OUTPUT	TRISAbits.TRISA1 = 0
#define TOUCH_X_HIGH	LATAbits.LATA1 = 1

#define TOUCH_OUTPUT	TRISEbits.TRISE2 = 0
#define TOUCH_INPUT		TRISEbits.TRISE2 = 1
#define TOUCH_HI		LATEbits.LATE2 = 1
#define TOUCH_LOW		LATEbits.LATE2 = 0

// #define TOUCH_THRESHOLD 	220 // 250 Higher value = more sensitive
								// Set in EEPROM Now !!!
#define TOUCH_RELEASE	100	// 30


#pragma udata access volatile_access
unsigned char LocalTouch=0;

#pragma udata
unsigned char StoredSwitchBits=0;
unsigned int touch_rel;
unsigned int touch_press;


#pragma code
//---------------------------------------------------------------------
// Read Switches and detect lo to hi
//---------------------------------------------------------------------
void Read_Switches(void)
{
	unsigned char SwitchXOR=0;
	Switches PresSwitches;
	Switches RelSwitches;
	Switches SwitchBits;

	SwitchBits.byte=0;
	PresSwitches.byte=0;
	RelSwitches.byte=0;

	SwitchBits.autoSW=AUTO_SW;
	SwitchBits.touchSW=TOUCH_SW;
	SwitchBits.writeSW=WRITE_SW;
	SwitchBits.muteSW=MUTE_SW;

	if(faderMode==1)	// only switch status in mode 1
	{
		if(TOUCH_SW)writeCntr++;
		else writeCntr=0;
	}
	
	

	SwitchBits.altSW=ALT_SW;
	SwitchBits.touchSense=LocalTouch;

	outbuffer.status=0;
	outbuffer.touch_press=0;
	outbuffer.touch_release=0;
	outbuffer.mute_press=0;
	outbuffer.mute_release=0;

	if(SwitchBits.byte!=StoredSwitchBits) {                            // If previous 8 bits are NOT equal with the current 8 bits:
	    SwitchXOR=SwitchBits.byte^StoredSwitchBits;                    // Create a mask with all changed bits
	    PresSwitches.byte=SwitchBits.byte&SwitchXOR;                        // Mask out all Pressed switches
	    RelSwitches.byte=StoredSwitchBits&SwitchXOR;                    // Mask out all Released Switches
	
		if(faderMode==1)
		{
			if(PresSwitches.autoSW)outbuffer.status=0x01;
			if(PresSwitches.touchSW)outbuffer.status=0x02;
			if(PresSwitches.writeSW)outbuffer.status=0x03;
			if(PresSwitches.touchSense)outbuffer.touch_press=1;
			if(RelSwitches.touchSense)outbuffer.touch_release=1;
			if(PresSwitches.muteSW)outbuffer.mute_press=1;
			if(RelSwitches.muteSW)outbuffer.mute_release=1;
			if(PresSwitches.altSW){
				outbuffer.touch_press=1;
				outbuffer.touch_release=1;
				if(LocalStatus==0x0C) outbuffer.status=0x03;		// Jump out of Write !! This maybe need to be done at IO card
			} // fader mode switch
		}
		if(faderMode==2)
		{
			if(PresSwitches.altSW){outbuffer.touch_press=1;outbuffer.touch_release=1;} // fader mode switch
		}
		if(faderMode==3)
		{
			if(PresSwitches.touchSW){
				faderMode=1;
				writeCntr=0;
				WriteEEPROM(0,touchThreshold);
				} // fader mode switch
			if(PresSwitches.touchSense)outbuffer.touch_press=1;
			if(RelSwitches.touchSense)outbuffer.touch_release=1;
//			if(PresSwitches.altSW){outbuffer.touch_press=1;outbuffer.touch_release=1;} // fader mode switch
			if(PresSwitches.writeSW){
				touchThreshold++;
				if(touchThreshold>99)touchThreshold=99;
			}
			if(PresSwitches.autoSW){
				touchThreshold--;
				if(touchThreshold<1)touchThreshold=1;
			}
		}
	}
	StoredSwitchBits=SwitchBits.byte;   
}

//---------------------------------------------------------------------
// scan_Touch
//---------------------------------------------------------------------
void Start_Scan_Touch(void)                                  
	{
	TOUCH_X_OUTPUT;
	TOUCH_X_HIGH;
	SetChanADC(TOUCH_X_ADC);
	TOUCH_OUTPUT;
	TOUCH_LOW;
	TOUCH_INPUT;

	SetChanADC(TOUCH_ADC);
	ConvertADC();
	}
void Scan_Touch(void)                                  
	{
	unsigned int fader_touch_sens;
	unsigned int scaledThreshold = touchThreshold;
	while( BusyADC() );
	fader_touch_sens = ADRESH;
	fader_touch_sens = fader_touch_sens << 8;
	fader_touch_sens = fader_touch_sens + ADRESL;

	scaledThreshold = touchThreshold;
	scaledThreshold <<=1;	

	if (fader_touch_sens<(scaledThreshold+90)) 
		{	
		if (touch_press > 0) 
			{
			LocalTouch = 1;
			touch_rel = 0;
			}
		else 
			{
			touch_press +=1;
			BlinkLED = 1;
			BlinkCnt = 0;
			}
		}
	else
		{
		if (touch_rel > 16) touch_press = 0;
		if (touch_rel > TOUCH_RELEASE) 
			{
			LocalTouch = 0;
			}
		else 
			{touch_rel +=1;}			
		}

	}	