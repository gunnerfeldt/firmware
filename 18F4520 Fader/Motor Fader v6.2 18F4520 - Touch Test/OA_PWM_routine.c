
#include <p18f4520.h>   /* for TRIS and PORT declarations */
#include <adc.h>
#include <math.h>
#include <pwm.h>
#include "PWM_routine_OA.h"
#include "I2C_routine.h"

#define COMP_ADC		ADC_CH0
#define TEST_ADC		ADC_CH1

#define MOTOR_ON 		LATCbits.LATC0

#define AUTO_LED  		LATBbits.LATB0
#define TOUCH_LED  		LATBbits.LATB1
#define WRITE_LED  		LATBbits.LATB2
#define MUTE_LED  		LATBbits.LATB3


#pragma udata
const unsigned int maxPWM = 750;
const signed int MAXI =8000;


signed int lastpError;
signed int lastiError;

unsigned int TopLimit=1023;
unsigned int BotLimit=0;
unsigned long ScaleRatio=100; 


#pragma ram udata
ram signed long fspeed; 

ram signed int iError;
ram signed long lstP;
ram signed long lstInput;

unsigned int pwmOffset;	
signed long pK;	
signed long iK;	
signed long dK;
long gain;	
signed int SKEW;
signed int iError_max;  

void SetFaderMacro(unsigned char);

/************************************************************************************************

    Calculate PWM values
    Input: Goal to chase. 10 bit value

*************************************************************************************************/


#pragma code
void Calculate_Motor_PWM (int FaderGoal, int FaderPosition)
{
	signed int dError;
	signed int pError;	
	static signed int lastDerror;	

	pError = FaderGoal-FaderPosition;

	dError = (FaderPosition-lstInput);  
              
	if(fabs(dError)>fabs(lastDerror))dError = (dError+lastDerror)/2;               

	if(fabs(pError)>=fabs(lstP))iError += (iK*pError);           
	else iError/=8;
	
	iError/=2;

	if (iError>MAXI) iError =MAXI;                              
	if (iError<-MAXI) iError =-MAXI;

	lstP = pError;		     
	lstInput = FaderPosition;		                                                    // Previous error

	fspeed = ((((pK*pError)+(iError)-(dK*dError))*gain));           	 	// Algorithm for PWM

	fspeed = fspeed/100;

	lastDerror = dError;

	if(LocalTouch)
	{
		iError=0;
		lastDerror=0;
	}
}

/************************************************************************************************

    Output PWM values

*************************************************************************************************/

void Handle_Fader(void)
{
	unsigned int PWM1;
	unsigned int PWM2;
	signed int skewedStartVal=0;


	if (1)                // If host motors off or touch. Check touch variable !!!
	{
		if(fspeed<0)                                   // DOWN
		{                  
			PWM1=(fabs(fspeed));
			if(PWM1>maxPWM) {PWM1 = maxPWM;}
			PWM2=0;
			SetDCPWM2(PWM1);
			SetDCPWM1(PWM2);
			MOTOR_ON = 1;                           // This turns on motor driver
		}
		else if(fspeed>0)                              // UP
		{

			PWM2=skewedStartVal+(fabs(fspeed));
			if(PWM2>maxPWM) {PWM2 = maxPWM;}
			PWM1=0;
			SetDCPWM2(PWM1);
			SetDCPWM1(PWM2);
			MOTOR_ON = 1;
		}
		else
		{
			SetDCPWM2(0);
			SetDCPWM1(0);
			MOTOR_ON = 0;
		}
	}
	else
	{	
		SetDCPWM2(0);
		SetDCPWM1(0);
		MOTOR_ON = 0;
		}
}



/************************************************************************************************

    Sample Fader

*************************************************************************************************/
void Start_ADC (void)
{
	SetChanADC(COMP_ADC);
	ConvertADC();  
//	AUTO_LED=!AUTO_LED;    
}

unsigned int Read_ADC(void)
{
	unsigned int FADER_POS;
	signed long ScaledPos;
	while( BusyADC() );	           
	FADER_POS = ADRESH;
	FADER_POS = FADER_POS << 8;
	FADER_POS = FADER_POS + ADRESL;
	if(!FaderReady)
	{
		return FADER_POS;
	}
	else
	{
//		return FADER_POS;

		ScaledPos = FADER_POS;
		ScaledPos -=BotLimit;
		if(ScaledPos<0)ScaledPos=0;
		ScaledPos=ScaledPos*ScaleRatio;
		ScaledPos=ScaledPos/100;
//		if(ScaledPos<0)ScaledPos=0;
		if(ScaledPos>1023)ScaledPos=1023;
		return ScaledPos;

	}

}

void SetScale(void)
{
	unsigned long n;
	n=TopLimit-BotLimit; 		// Whole scale
	ScaleRatio = (102300)/n;
}

/************************************************************************************************

    Fader Macros

*************************************************************************************************/
void SetFaderMacro(unsigned char macro)
{
	switch (macro)
	{
		case 1:
		// ****************** Alps - 12 V ********************

		pwmOffset = 150;	
		pK = 100;	
		iK = 5;	
		dK = 1500;
		gain = 5;		
		SKEW = 0;			// -100 to 100 . Fader move threshold up / down correction
		iError_max = 1023;  

		break;
		
		
		case 2:
		// ****************** Bourns - 12 V ********************

		pwmOffset = 150;	
		pK = 300;	
		iK = 30;	
		dK = 2200;
		gain = 8;			
		SKEW = 0;		// -100 to 100 . Fader move threshold up / down correction
		iError_max = 1023; 
			
		break;
		
		
		case 3:
		// ****************** LMH2 - 12 V ********************
		pwmOffset = 100;	
		pK =10;	
		iK = 2;	
		dK = 170;
		gain = 8;			
		SKEW = 0;		// -100 to 100 . Fader move threshold up / down correction
		iError_max = 100;  
		
		break;
		
		case 4:
		// ****************** PGFM3200 - 18 V ********************
		
		pwmOffset = 100;	
		pK = 700;	
		iK = 50;	
		dK = 500;
		gain =10;		
		SKEW = 0;		// -100 to 100 . Fader move threshold up / down correction
		iError_max = 1023; 		
		
		break;
		
		default: 
		// ****************** Alps - 12 V ********************

		pwmOffset = 150;	
		pK = 150;	
		iK = 3;	
		dK = 500;
		gain = 6;		
		SKEW = 0;			// -100 to 100 . Fader move threshold up / down correction
		iError_max = 1023;  

		break;
	}
}