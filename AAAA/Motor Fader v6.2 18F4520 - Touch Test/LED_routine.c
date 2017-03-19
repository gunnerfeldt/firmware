#include "LEDs_routine.h"
#include "I2C_routine.h"
#include <p18f4520.h>   /* for TRIS and PORT declarations */

#define AUTO_LED  LATBbits.LATB0
#define TOUCH_LED  LATBbits.LATB1
#define WRITE_LED  LATBbits.LATB2
#define MUTE_LED  LATBbits.LATB3

#pragma udata
unsigned char BlinkLED=0;

/*
	//		SEG 1
		A = 0x0800;			// 4
		B = 0x2000;			// 2
		C = 0x0020;			// 10
		D = 0x0008;			// 12
		E = 0x0004;			// 13
		F = 0x0200;			// 6
		G = 0x0001;			// 15
		DP = 0x4000;			// 1

		SEGMENTA[0] = A + B + C + D   + E + F;
		SEGMENTA[1] = B + C;
		SEGMENTA[2] = A + B + D + E + G;
		SEGMENTA[3] = A + B + C + D + G;
		SEGMENTA[4] = B + C + F + G;
		SEGMENTA[5] = A + C + D + F + G;
		SEGMENTA[6] = A + C + D + E + F + G;
		SEGMENTA[7] = A + B + C;
		SEGMENTA[8] = A + B + C + D + E + F + G;
		SEGMENTA[9] = A + B + C + D + F + G;
		// dots
		SEGMENTA[10] = DP;
		// big plus
		SEGMENTA[11] = A + A;
		// big minus
		SEGMENTA[12] = G;
		
		//		SEG 2
		A = 0x0040;			// 9
		B = 0x0080;			// 8
		C = 0x0400;			// 5
		D = 0x1000;			// 3
		E = 0x8000;			// 0
		F = 0x0010;			// 11
		G = 0x0002;			// 14
		DP = 0x0100;			// 7

		SEGMENTB[0] = A + B + C + D + E + F;
		SEGMENTB[1] = B + C;
		SEGMENTB[2] = A + B + D + E + G;
		SEGMENTB[3] = A + B + C + D + G;
		SEGMENTB[4] = B + C + F + G;
		SEGMENTB[5] = A + C + D + F + G;
		SEGMENTB[6] = A + C + D + E + F + G;
		SEGMENTB[7] = A + B + C;
		SEGMENTB[8] = A + B + C + D + E + F + G;
		SEGMENTB[9] = A + B + C + D + F + G;
		// dots
		SEGMENTB[10] = DP;
		// big plus
		SEGMENTB[11] = D + D;
		// big minus
		SEGMENTB[12] = G;


	fader_ID = ID-1;

	fader_address = fader_ID*2;
	DISPLAY = ID;
	SSPADD = 0xE0 + fader_address; // slave address
	LATDbits.LATD3 = 0;
*/

/*
void Update_LED_Display_Bits(unsigned int SHIFT_DIGITS)
	{
	unsigned int n;
	for(n=0;n<16;n++)
		{
		LATDbits.LATD0 = SHIFT_DIGITS & 1;
		SHIFT_DIGITS = SHIFT_DIGITS >> 1;
		LATDbits.LATD1 = 1;
		LATDbits.LATD1 = 0;
		}
	LATDbits.LATD2 = 1;
	LATDbits.LATD2 = 0;
	}


void Update_LED_Display(unsigned int displayint)
	{
	unsigned int SHIFT_DIGITS = 0;
	unsigned int n;
	if(displayint<10)
		{
		SHIFT_DIGITS = SEGMENTB[displayint];
		}
	else
		{
		SHIFT_DIGITS = SEGMENTA[displayint/10] + SEGMENTB[displayint%10];
		}
//	SHIFT_DIGITS = SEGMENTA[1];
	for(n=0;n<16;n++)
		{
		LATDbits.LATD0 = SHIFT_DIGITS & 1;
		SHIFT_DIGITS = SHIFT_DIGITS >> 1;
		LATDbits.LATD1 = 1;
		LATDbits.LATD1 = 0;
		}
	LATDbits.LATD2 = 1;
	LATDbits.LATD2 = 0;
	

	}
*/


void Handle_LEDs(void)
	{
	MUTE_LED = inbuffer.mute;
//	if(AttentionFlag)
		{		
//		LATDbits.LATD3 = BlinkLED;                  // LED Display enable. Define !!!!

		}
//	else
		{
//		LATDbits.LATD3 = 0;
		}
		switch (inbuffer.status)
			{
			case 0x00:
			AUTO_LED = 1;
			TOUCH_LED = 1;
			WRITE_LED = 1 & !(BlinkLED & localTouchSense) ;
			break;
			case 0x04:
			AUTO_LED = 0;
			TOUCH_LED = 1;
			WRITE_LED = 1 & !(BlinkLED & localTouchSense) ;
			break;
			case 0x08:
			AUTO_LED = 0;
			TOUCH_LED = 0;
			WRITE_LED = 1 & !(BlinkLED & localTouchSense) ;
			break;
			case 0x0C:
			AUTO_LED = 0;
			TOUCH_LED = 1;
			WRITE_LED = 1 & (BlinkLED & localTouchSense) ;
			break;
			}
	}

/*
int Calculate_dB_Display(void){
	signed double DIFF;															// variable for exact difference
	int DIFF_DISPLAY;													// variable for truncated difference
	DIFF = FADER_USB;
	DIFF = (DIFF - FADER_IN)*0.05; 							// difference in dB

	if(DIFF==0){															// spot on
		return SEGMENTB[0] & (BlinkLED * 0xFFFF);							// result: blinking zero
		}

	if(DIFF>0){															// if positive difference
		if(DIFF>=10){													// over 10dB +
			return big_plus;												// result: big plus
			}
		else{
			if(DIFF>=1){													// between 1 and 9 dB
				DIFF_DISPLAY = DIFF;									// truncate
				return SEGMENTB[DIFF_DISPLAY];						// result: difference, no sign
				}
			else{															//Â between 0.1 and 0.9 dB
				DIFF_DISPLAY = DIFF * 10;								// truncate and multiply
				return (0x4000 + SEGMENTB[DIFF_DISPLAY]);	// result: difference, with DP
				}		
			}
		}

	else	{																// if negative difference
		if(DIFF<=-10){													// under 10dB -
			return big_minus;												// result: big minus
			}
		else{
			if(DIFF<=-1){												// between -1 and -9 dB
				DIFF_DISPLAY = fabs(DIFF);								// truncate absolute
				return 0x0001 + SEGMENTB[DIFF_DISPLAY];		// result: difference, signed
				}
			else{															//Â between -0.1 and -0.9 dB
				DIFF_DISPLAY = fabs(DIFF * 10);							// truncate and multiply absolute
				return (0x4000 + SEGMENTB[DIFF_DISPLAY]
				+ 0x0001);										// result: difference, signed with DP
				}		
			}
		}
	}
*/