
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
const unsigned int maxPWM =1023;

/* ****************** Bourns (old) - 10 V ********************
const unsigned int pwmOffset = 150;	
const signed long pK = 50;	
const signed long iK = 5;	
const signed long dK = 180;
const long gain = 10;			// Was 5 before, with ~9V. Now runned with 11V.
const signed int SKEW = 0;		// -100 to 100 . Fader move threshold up / down correction
const signed int iError_max = 1023;  
*/

// ****************** Bourns - 10 V ********************
const unsigned int pwmOffset = 150;	
const signed long pK = 50;	
const signed long iK = 5;	
const signed long dK = 180;
const long gain = 1;			// Was 5 before, with ~9V. Now runned with 11V.
const signed int SKEW = 0;		// -100 to 100 . Fader move threshold up / down correction
const signed int iError_max = 1023;  			


/* ****************** LMH2 - 10 V ********************
const unsigned int pwmOffset = 100;	
const signed long pK =10;	
const signed long iK = 2;	
const signed long dK = 170;
const long gain = 8;			
const signed int SKEW = 0;		// -100 to 100 . Fader move threshold up / down correction
const signed int iError_max = 100;  
*/

/*// ****************** PGFM3200 - 18 V ********************
const unsigned int pwmOffset = 000;	
const signed long pK = 50;	
const signed long iK = 1;	
const signed long dK = 500;
const long gain = 5;			
const signed int SKEW = 0;		// -100 to 100 . Fader move threshold up / down correction
const signed int iError_max = 300;  			
*/

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
/*
	static signed int iError;
	static signed long lstP;
*/
	unsigned int PWM1;
	unsigned int PWM2;
	signed int dError;
	signed int pError;	

	pError = FaderGoal-FaderPosition;

	dError = (pError-lstP);                                           // Integral error ??

	iError += (pError);  
	lstP = pError;		                                                    // Previous error

//	fspeed = ((((pK*pError)+(iK*iError)+(dK*dError))*gain)/16);            // Algorithm for PWM
	fspeed = ((((pK*pError)+(iK*iError)+(dK*dError))*gain));            // Algorithm for PWM

}

void Calculate_Motor_PWM_old (int FaderGoal, int FaderPosition)
	{
	unsigned int PWM1;
	unsigned int PWM2;
	signed int pError;	
	static signed int D_REG;
	static signed int D_SPEED;
	static signed long lstP;
	static int LastGoal=0;
	static signed int iError;
	signed int dError;
	static signed int prevDerror = 0;
	unsigned int posPerror;
	unsigned int lastPosPerror;
	unsigned char lstSig, sig;
/*
	if(FaderGoal==BotLimit)FaderGoal=BotLimit+1;
	if(FaderGoal==TopLimit)FaderGoal=TopLimit-1;
*/
	pError = FaderGoal-FaderPosition;
	posPerror = fabs(pError);
	lastPosPerror = fabs(lstP);

	lstSig=(lastPosPerror==lstP);
	sig=(posPerror==pError);

	if(posPerror>pErrorThreshold)SettleCnt=0;				// a Big enough error must move fader even if it's idle

	dError = (pError-lstP);
//	dError = (prevDerror + (dError*7))/8;
//	iError += (pError/16);                                              // Integral error ??
	iError += (pError);  
	iError = (iError/32);

	if (iError>iError_max) iError =iError_max;                              // ??
	if (iError<-iError_max) iError =-iError_max;

	if(lstSig!=sig)iError=0;

//	LastGoal=FaderGoal;
	  
//	iError = iError - dError;                                              // Derivate error

//	dError = ((prevDerror) + (dError))/2;
	prevDerror = dError;

	lstP = pError;		                                                    // Previous error
	if(posPerror>TOL)
	{		                                                    // Previous error

		fspeed = ((((pK*pError)+(iK*iError)+(dK*dError))*gain)/16);            // Algorithm for PWM
/*
		fspeed=((D_SPEED*1)+fspeed)/2;
		D_SPEED=fspeed;
*/
	}

	else
	{
		fspeed = 0;            // Algorithm for PWM
		iError=0;
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


// 1023 max
// 500 doesn't move
//
	
	if(SettleCnt<SettleThrs || !FaderReady)
	{
		if ((inbuffer.status!=3) || !FaderReady)                // If host motors off or touch. Check touch variable !!!
		{
			if(fspeed<0)                                   // DOWN
			{                                           // and should it not be 0 ?????
			//	PWM1=fabs(fspeed);
				skewedStartVal = pwmOffset+(5*(-SKEW));
			//	PWM1=skewedStartVal+(fabs(fspeed));

				PWM1=(fabs(fspeed));
				if(PWM1>maxPWM) {PWM1 = maxPWM;}
				PWM2=0;
			//	PWM2=maxPWM-PWM1;
				SetDCPWM2(PWM1);
				SetDCPWM1(PWM2);
				MOTOR_ON = 1;                           // This turns on motor driver
			}
			else if(fspeed>0)                              // UP
			{
			//	PWM2=fabs(fspeed);
				skewedStartVal = pwmOffset+(6*(+SKEW));
			//	PWM2=skewedStartVal+(fabs(fspeed));
			//	PWM2=skewedStartVal+(fabs(fspeed));

				PWM2=skewedStartVal+(fabs(fspeed));
				if(PWM2>maxPWM) {PWM2 = maxPWM;}
				PWM1=0;
			//	PWM1=maxPWM-PWM2;
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
	else
	{	
		SettleCnt=SettleThrs;
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