#include "typedefs.h"
#include "I2C_routine.h"
#include "SWITCHES_routine.h"
#include <p18f4520.h>   /* for TRIS and PORT declarations */
#include <adc.h>


#define TOUCH_ADC		ADC_CH7
#define TOUCH_X_ADC		ADC_CH1
#define TOUCH_X_OUTPUT	TRISAbits.TRISA1 = 0
#define TOUCH_X_HIGH	LATAbits.LATA1 = 1

#define TOUCH_OUTPUT	TRISEbits.TRISE2 = 0
#define TOUCH_INPUT		TRISEbits.TRISE2 = 1
#define TOUCH_HI		LATEbits.LATE2 = 1
#define TOUCH_LOW		LATEbits.LATE2 = 0

#pragma udata access volatile_access

unsigned char LocalTouch=0;

unsigned char TOUCH_RELEASE;
#pragma udata

#pragma code



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
	static unsigned int touch_int;
	static unsigned int touchReleaseCount = 0;
	while( BusyADC() );
	fader_touch_sens = ADRESH;
	fader_touch_sens = fader_touch_sens << 8;
	fader_touch_sens = fader_touch_sens + ADRESL;

	scaledThreshold = touchThreshold;
	scaledThreshold <<=1;	

	if (fader_touch_sens<(scaledThreshold+90)) 
	{	
		touch_int=(touch_int<<1)+1;
	}
	else
	{	
		touch_int=(touch_int<<1);		
	}

	// touch need X ones in a sequence
	if((touch_int & 0x03)==0x03)
	{
		LocalTouch = 1;
		touchReleaseCount=0;
	}

	// touch need X ones in a sequence
	if((touch_int)==0x00)
	{
		touchReleaseCount++;
		if(touchReleaseCount>TOUCH_RELEASE)LocalTouch = 0;
		
	}

}	