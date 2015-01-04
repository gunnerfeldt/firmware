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
int tol;
int bound;
BOOL fader_lo;
BOOL fader_hi;
int lobound;
int hibound;
int lotol;
int hitol;
int fader_goal;
byte slow_speed;
byte fast_speed;
byte speed;


void main(void)
{

	TRISCbits.TRISC1 = 0;
	TRISCbits.TRISC2 = 0;
	TRISAbits.TRISA0 = 1;
	TRISAbits.TRISA1 = 1;
	TRISAbits.TRISA2 = 1;
	TRISBbits.TRISB2 = 1;
	TRISBbits.TRISB3 = 1;
	TRISBbits.TRISB0 = 0;
	TRISBbits.TRISB1 = 0;
	
	OpenADC(	ADC_FOSC_32     &
				ADC_RIGHT_JUST	&
				ADC_2_TAD,
				ADC_CH12		&
				ADC_INT_OFF		&
				ADC_VREFPLUS_VDD
				, 15 );
	//			ADC_VREFPLUS_EXT
	ADCON1 = 0x0C;

	OpenTimer2(T2_PS_1_16 & TIMER_INT_OFF);
	OpenPWM1(93);									// Turn PWM on
	SetDCPWM1(0); 

	OpenPWM2(93);									// Turn PWM on
	SetDCPWM1(0); 

	SetChanADC(ADC_CH0);


fader_hi = 0;
fader_lo = 0;
fader_goal = 512;
fader_pos = fader_goal;
tol = 5;
bound = 32;


hitol = fader_goal + tol;
lotol = fader_goal - tol;
hibound = fader_goal + bound;
lobound = fader_goal - bound;

if (hitol>1023) hitol = 1023;
if (lotol<0) lotol = 0;
if (hibound>1023) hibound = 1023;
if (lobound<0) lobound = 0;

slow_speed = 148;
fast_speed = 255;
wCntr = 0;
while(1)
    {

/*
//	if (B_sw == 1)
//		{
		wCntr = wCntr +1;
		if(wCntr>64){
			wCntr=0;
        	fader_goal=fader_goal+1;}
		if(fader_goal>1023)fader_goal=0;	
	
//		}
*/



	
	SetChanADC(ADC_CH1);
	ConvertADC();
	while( BusyADC() );
	
	fader_goal = ADRESH;
	fader_goal = fader_goal << 8;
	fader_goal = fader_goal + ADRESL;
	hitol = fader_goal + tol;
	lotol = fader_goal - tol;
	hibound = fader_goal + bound;
	lobound = fader_goal - bound;


	SetChanADC(ADC_CH0);
	ConvertADC();
	while( BusyADC() );
	
	fader_pos = ADRESH;
	fader_pos = fader_pos << 8;
	fader_pos = fader_pos + ADRESL;

	if (Sw == 1)
		{
		LED2 = 1;
		if (fader_pos<lotol) 
			{	
			speed = fast_speed;
			if (fader_pos>lobound) {speed = slow_speed;}
			SetDCPWM2(speed);
			}
		else {SetDCPWM2(0);}

		if (fader_pos>hitol) 
			{	
			speed = fast_speed;
			if (fader_pos<hibound) {speed = slow_speed;}
			SetDCPWM1(speed);
			}
		else {SetDCPWM1(0);}
		}
	else
		{
		SetDCPWM1(0);
		SetDCPWM2(0);
		LED2 = 0;
		}
	if (Sw == 1)
		{LED1 = 1;}
	else
		{LED1 = 0;}


    }//end while
}//end main



