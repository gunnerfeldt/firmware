
#include <p18f4520.h>   /* for TRIS and PORT declarations */
#include <adc.h>
#include <math.h>
#include <pwm.h>
#include "PWM_routine.h"
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

/* ****************** Bourns (old) - 10 V ********************
const unsigned int pwmOffset = 150;	
const signed long pK = 50;	
const signed long iK = 5;	
const signed long dK = 180;
const long gain = 10;			// Was 5 before, with ~9V. Now runned with 11V.
const signed int SKEW = 0;		// -100 to 100 . Fader move threshold up / down correction
const signed int iError_max = 1023;  
*/

/*// ****************** Bourns - 10 V ********************
const unsigned int pwmOffset = 150;	
const signed long pK = 300;	
const signed long iK = 30;	
const signed long dK = 2200;
const signed long gain = 8;			// Was 5 before, with ~9V. Now runned with 11V.
const signed int SKEW = 0;		// -100 to 100 . Fader move threshold up / down correction
const signed int iError_max = 1023;  
*/			


/* ****************** LMH2 - 10 V ********************
const unsigned int pwmOffset = 100;	
const signed long pK =10;	
const signed long iK = 2;	
const signed long dK = 170;
const long gain = 8;			
const signed int SKEW = 0;		// -100 to 100 . Fader move threshold up / down correction
const signed int iError_max = 100;  
*/

// ****************** PGFM3200 - 18 V ********************
const unsigned int pwmOffset = 0;	
const signed long pK = 500;	
const signed long iK = 0;	
const signed long dK = 1200;
const signed long gain =8;			// Was 5 before, with ~9V. Now runned with 11V.
const signed int SKEW = 0;		// -100 to 100 . Fader move threshold up / down correction
const signed int iError_max = 1023; 		


const int TOL = 0;
const int pErrorThreshold = 10;	// Threshold for repositioning while in idle state. ie - no new data in and not touched.
unsigned int SettleCnt=0;
unsigned int SettleThrs=500;		// Threshold for SettleDelay. SettleDelay * fps in Hz / 1000
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
/*
ram unsigned int PWM1;
ram unsigned int PWM2;
ram signed int pError;	
ram signed int dError;
*/
/************************************************************************************************

    Calculate PWM values
    Input: Goal to chase. 10 bit value

*************************************************************************************************/


#pragma code
void Calculate_Motor_PWM (int FaderGoal, int FaderPosition)
{
	signed int dError;
	signed int pError;	

	pError = FaderGoal-FaderPosition;

//	dError = (pError-lstP);  
	dError = (FaderPosition-lstInput); 
//	dError += ((FaderPosition-lstInput)*(pError/16));    
                             

	if(fabs(pError)>=fabs(lstP))iError += (iK*pError);           
	else iError/=8;
	
	iError/=2;

	if (iError>MAXI) iError =MAXI;                              
	if (iError<-MAXI) iError =-MAXI;

	lstP = pError;		     
	lstInput = FaderPosition;		                                                    // Previous error

//	fspeed = ((((pK*pError)+(iK*iError)+(dK*dError))*gain)/16);            	// Algorithm for PWM
	fspeed = ((((pK*pError)+(iError)-(dK*dError))*gain));           	 	// Algorithm for PWM

/*
	if (fspeed>OUTMAX) fspeed =OUTMAX;                              
	if (fspeed<-OUTMAX) fspeed =-OUTMAX;
*/

	fspeed = fspeed/100;


}

/************************************************************************************************

    Output PWM values

*************************************************************************************************/

void Handle_Fader(void)
{
	unsigned int PWM1;
	unsigned int PWM2;
	signed int skewedStartVal=0;


	if ((inbuffer.status!=3) || !FaderReady)                // If host motors off or touch. Check touch variable !!!
	{
		if(fspeed<000)                                   // DOWN
		{                  
			PWM1=(fabs(fspeed));
			if(PWM1>maxPWM) {PWM1 = maxPWM;}
			PWM2=0;
			SetDCPWM2(PWM1);
			SetDCPWM1(PWM2);
			MOTOR_ON = 1;                           // This turns on motor driver
		}
		else if(fspeed>000)                              // UP
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