
#include <p18f4520.h>   /* for TRIS and PORT declarations */
#include <adc.h>
#define COMP_ADC		ADC_CH0
#define TEST_ADC		ADC_CH1

#define AUTO_LED  LATBbits.LATB0
#define TOUCH_LED  LATBbits.LATB1
#define WRITE_LED  LATBbits.LATB2
#define MUTE_LED  LATBbits.LATB3


/************************************************************************************************

    Calculate PWM values
    Input: Goal to chase. 10 bit value

*************************************************************************************************/
/*
void Calculate_Motor_PWM (int FADER_Goal)
	{
	int Scaled_Max;	
	static signed int D_REG;
	static signed int D_SPEED;
	static signed long lstP;




	pError = FADER_Goal-FaderPosition;	                                                // Difference 

		if (pError != 0)                                                            // If it's a differnece
			{   
			iError += (pError*iKmult);                                              // Integral error ??
			Scaled_Max = iError_max; // *10;                                        // ??
			if (iError>Scaled_Max) iError =Scaled_Max;                              // ??
			if (iError<-Scaled_Max) iError =-Scaled_Max;

			dError = (pError-lstP);	                                                // Derivate error
			lstP = pError;		                                                    // Previous error
			fspeed = (((pK*pError)+(iK*iError)+(dK*dError))/(101-gain));            // Algorithm for PWM


			}
		else
			{                                                                       // if no error > clear all
			GOAL_CNT = SET_TIME;                                                    // Not good for over shoot
			iError = 0;
			pError = 0;
			dError = 0;
			D_REG = 0;
			lstP = 0;
			fspeed = 0;
			HARD_MOTOR_ON = 0;
			snapshot_flag = 0;
			}
	}

*/
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
	while( BusyADC() );	           
	FADER_POS = ADRESH;
	FADER_POS = FADER_POS << 8;
	FADER_POS = FADER_POS + ADRESL;
	return FADER_POS;
}


/************************************************************************************************

    Output PWM values

*************************************************************************************************/
/*
void Handle_Fader(void)
	{
	unsigned int PWM1;
	unsigned int PWM2;


	if (HARD_MOTOR_ON == 0 || touch)                // If host motors off or touch. Check touch variable !!!
		{
		SetDCPWM2(0);                               // Clear PWM
		SetDCPWM1(0);                               
		motor_enable = 0;
		iError = 0;
		dError = 0;
		lastpError = 0;
		return;
		}




	if(fspeed<-1)                                   // Hmmm. -1. is fspeed without decimals
		{                                           // and should it not be 0 ?????
		PWM1=fabs(fspeed);
		if(PWM1>maxPWM) PWM1 = maxPWM;
		PWM2=0;
		motor_enable = 1;                           // This turns on motor driver
		SetDCPWM1(PWM1);
		SetDCPWM2(PWM2);
		}
	else if(fspeed>1)
		{
		PWM2=fabs(fspeed);
		if(PWM2>maxPWM) PWM2 = maxPWM;
		PWM1=0;
		motor_enable = 1;
		SetDCPWM1(PWM1);
		SetDCPWM2(PWM2);
		}
	else
		{
		SetDCPWM2(0);
		SetDCPWM1(0);
		motor_enable = 0;
		return;
		}
	}
*/