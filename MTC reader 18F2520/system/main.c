/*********************************************************************
 *
 *                Microchip USB C18 Firmware Version 1.0
 *
 *********************************************************************
 * FileName:        main.c
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 2.30.01+
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PICmicro® Microcontroller is intended and
 * supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Rawin Rojvanit       11/19/04    Original.
 ********************************************************************/

/** I N C L U D E S **********************************************************/
#include "C:\MCC18\h\p18cxxx.h"
#include <adc.h>
#include "system\typedefs.h"                        // Required
#include "io_cfg.h"                                 // Required
#include "pwm.h"
#include "math.h"
#include "timers.h" 				// include the timer library

/** V A R I A B L E S ********************************************************/
#pragma udata

/** P R I V A T E  P R O T O T Y P E S ***************************************/


/** V E C T O R  R E M A P P I N G *******************************************/

extern void _startup (void);        // See c018i.c in your C18 compiler dir
#pragma code _RESET_INTERRUPT_VECTOR = 0x000800
void _reset (void)
{
    _asm goto _startup _endasm
}
#pragma code

#pragma code _HIGH_INTERRUPT_VECTOR = 0x000808
void _high_ISR (void)
{
    ;
}

#pragma code _LOW_INTERRUPT_VECTOR = 0x000818
void _low_ISR (void)
{
    ;
}
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code
/******************************************************************************
 * Function:        void main(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Main program entry point.
 *
 * Note:            None
 *****************************************************************************/


unsigned long wCntr;
unsigned int cnt;

int fader_pos;
int last_fader_pos;
int loop_fader_pos;
int loop;
int tol;
int bound;
int last_cv;
float lastpError;
float iError;
float pError;
float dError;
float iK;
float dK;
float pK;
float rK;
float offset;

BOOL fader_lo;
BOOL fader_hi;
int lobound;
int lastpos;
int last_pos_err;
int last_neg_err;
int err_corr;
int hibound;
int lotol;
int hitol;
int fader_goal;
int fader_tries = 0;
byte slow_speed;
byte fast_speed;
int speed;
float fspeed;
float PWM_ratio = 1.1;			// when motor power is 10v this should be 1.0


void main(void)
{

	TRISCbits.TRISC1 = 0;
	TRISCbits.TRISC2 = 0;

	TRISAbits.TRISA0 = 1;
	TRISAbits.TRISA1 = 1;
	TRISAbits.TRISA2 = 1;
	TRISAbits.TRISA3 = 1;

	TRISBbits.TRISB2 = 1;
	TRISBbits.TRISB3 = 1;
	TRISBbits.TRISB0 = 0;
	TRISBbits.TRISB1 = 0;
	
	OpenADC(	ADC_FOSC_4     &
				ADC_RIGHT_JUST	&
				ADC_2_TAD,
				ADC_CH12		&
				ADC_INT_OFF		&
				ADC_VREFPLUS_VDD
				, 15 );
	//			ADC_VREFPLUS_EXT
	ADCON1 = 0x0C;

	OpenTimer2(T2_PS_1_16 & TIMER_INT_OFF);
	OpenPWM1(512);									// Turn PWM on
	SetDCPWM1(0); 

	OpenPWM2(512);									// Turn PWM on
	SetDCPWM1(0); 

	SetChanADC(ADC_CH0);


fader_hi = 0;
fader_lo = 0;
fader_pos = fader_goal;
tol = 0;
bound = 24;


err_corr = 100;
slow_speed = 120;
fast_speed = 511;
wCntr = 0;

pK = 0.02;
dK = 0.02;
iK = 0.05;
rK = 0.02;
offset = +0.0;

	SetChanADC(ADC_CH2);
	ConvertADC();
	while( BusyADC() );
	fader_goal = ADRESH;
	fader_goal = fader_goal << 8;
	fader_goal = fader_goal + ADRESL;

	SetChanADC(ADC_CH0);
	ConvertADC();
	while( BusyADC() );
	fader_pos = ADRESH;
	fader_pos = fader_pos << 8;
	fader_pos = fader_pos + ADRESL;

while(1)
    {
	last_cv = fader_goal;
	SetChanADC(ADC_CH2);
	for(loop=0;loop<3;loop++)
	{
		ConvertADC();
		while( BusyADC() );
		loop_fader_pos = ADRESH;
		loop_fader_pos = loop_fader_pos << 8;
		loop_fader_pos = loop_fader_pos + ADRESL;
//		fader_goal = (fader_goal/2) + (loop_fader_pos/2);
		fader_goal = loop_fader_pos;
	}
	hitol = fader_goal + tol;
	lotol = fader_goal - tol;
//	hibound = fader_goal + bound;
//	lobound = fader_goal - bound;

	if (hitol>1023) hitol = 1023;
	if (lotol<0) lotol = 0;
//	if (hibound>1023) hibound = 1023;
//	if (lobound<0) lobound = 0;

	SetChanADC(ADC_CH0);

	for(loop=0;loop<5;loop++)
	{
		ConvertADC();
		while( BusyADC() );
		loop_fader_pos = ADRESH;
		loop_fader_pos = loop_fader_pos << 8;
		loop_fader_pos = loop_fader_pos + ADRESL;
		fader_pos = (fader_pos/2) + (loop_fader_pos/2);
	}


//	fader_pos = (fader_pos/2) + (last_fader_pos/2);

//		SetDCPWM1(0);
//		SetDCPWM2(512);
	if (touch == 0 | (last_cv!= fader_goal))fader_tries=0;

//	if (touch == 1 && fader_tries<10000)
	if (touch == 1)
		{
			pError = fader_goal-fader_pos;
	//		iError = iError + ((pError-(lastpError - pError)) * rK);
			if (fabs(pError)<64)iError = iError + ((pError-(lastpError - pError)) * rK);		 
			dError = ((pError+lastpError)*0.5);
			fspeed = (pK*pError)+(iK*iError)+(dK*dError);
		
			if(pError!=0) 
				{

				fader_tries++;
				}
			else
				{
				fader_tries = 10000;
				}

			lastpError = pError;

		if (fspeed>0) 
			{	
			speed = fspeed+offset;
			SetDCPWM2(speed * PWM_ratio);
			}
		else {SetDCPWM2(0);}

		if (fspeed<0) 
			{	
			speed = -fspeed+offset;
			SetDCPWM1(speed * PWM_ratio);
			}
		else {SetDCPWM1(0);}

		}

	else

		{
		SetDCPWM1(0);
		SetDCPWM2(0);
		last_fader_pos = fader_pos;
		}
    }//end while
}//end main



/*			fspeed = ((fader_goal-fader_pos)/2)+(last_neg_err/2);
			if (fspeed>50)
				{
//				fspeed = (fspeed/2.49)+80;
//				fspeed = (fspeed/275)+1.8+(fspeed/250);
				speed = fspeed;
				SetDCPWM2(speed);
				}
			else
				{
				fspeed = (fspeed/25)+1;
				speed = fspeed;
				SetDCPWM2(speed);
				}
				last_neg_err = fader_goal-fader_pos;
*/