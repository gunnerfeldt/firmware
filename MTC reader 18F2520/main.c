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
	 #include <usart.h> 
	 #include "system\typedefs.h"                        // Required
	 #include "io_cfg.h"                                 // Required

 	#include "timers.h" 				// include the timer library




/** V A R I A B L E S ********************************************************/
#pragma udata
unsigned long mtcCntr = 0;	// LED lock delay
unsigned int mtcCntr2 = 0;	// Send USB when this is over 2
BOOL status_byte = FALSE;			// flag for 0xF1, statusbyte
BOOL MTC_start = FALSE;			// start flag
BOOL MTC_locked = FALSE;			// locked flag
unsigned char MTC_subframe_tick = 0;
unsigned char MTC_in;
unsigned char MTC_subframe = 0;
unsigned char MTC_frame = 0;
unsigned char MTC_second = 0;
unsigned char MTC_minute = 0;
unsigned char MTC_hour = 0;
unsigned char MTC_type;
unsigned char MTC_message;
unsigned char MTC_frame_ls;
unsigned char MTC_frame_ms;
unsigned char MTC_sec_ls;
unsigned char MTC_sec_ms;
unsigned char MTC_min_ls;
unsigned char MTC_min_ms;
unsigned char MTC_hour_ls;
unsigned char MTC_hour_ms;
unsigned char MTC_fps;
unsigned char MTC_fps_max;
BOOL MTC_full_byte = FALSE;
unsigned char MTC_frame_temp;
unsigned char MTC_second_temp;
unsigned char MTC_minute_temp;
unsigned char MTC_hour_temp;
unsigned char MTC_toggle = 0;
unsigned char mtcOut[6];
unsigned char midi_count = 0;

unsigned long loop;
unsigned char cnt; 
unsigned char clk_flag = 0;

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void Read_MTC(void);
static void InitializeSystem(void);
void Scan_Parallell_Port(void);

/** V E C T O R  R E M A P P I N G *******************************************/

extern void _startup (void);        // See c018i.c in your C18 compiler dir
#pragma code _RESET_INTERRUPT_VECTOR = 0x000800
void _reset (void)
{
    _asm goto _startup _endasm
}
#pragma code

/** D E C L A R A T I O N S **************************************************/

/* MTC masks */


#define MESS_TYPE_MASK  0b01110000
#define MESS_MASK		0b00001111
#define FRAME_MASK  	0b00011111
#define SEC_MASK		0b00111111
#define MIN_MASK  		0b00111111
#define HOUR_MASK		0b00011111
#define TYPE_MASK		0b01100000



#define	LED1				LATEbits.LATE0
#define	LED2				LATEbits.LATE1


#define SSP_en          	!PORTBbits.RB0
#define SSP_clk          	PORTBbits.RB1
#define SSP_write()         TRISD = 0;
#define SSP_read()         	TRISD = 255;

#pragma code _HIGH_INTERRUPT_VECTOR = 0x000808
void _high_ISR (void)
{
	if (PIR1bits.RCIF == 1)				// if data received !!!! For testing I cancelled this
		{
//		LED1=1;
		PIR1bits.RCIF = 0;	
		}
}

#pragma code _LOW_INTERRUPT_VECTOR = 0x000818
void _low_ISR (void)
{
	if (PIR1bits.RCIF == 1)				// if data received !!!! For testing I cancelled this
		{
//		LED1=!LED1;
		PIR1bits.RCIF = 0;	
		}
}
#pragma code



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





void main(void)
{
InitializeSystem();
INTCON2bits.RBPU = 1;	// pull up port b

	LED1 = 0;
	LED2 = 0;

//while(1)
//	{
//	LED1=1;
//	LED2=1;
//	}


while(1)
	{
//	LED1=!LED1;
//	LED2=!LED2;
//	for(mtcCntr=0;mtcCntr<99999;mtcCntr++)
//	{;}
//	LED2=SSP_en;
//	if(SSP_en != 1)						// always check if USB card is trying to communicate
//		{
//		if (midi_count =0)
//			{
			Read_MTC();
//			}
//		}




	if(SSP_en)											// poll for parallel comm
		{
//		LED2=!LED2;
		Scan_Parallell_Port();								// communicate with USB card
		}
	else
		{
		;
		}

	}	

}//end main



/******************************************************************************
 * Function:        void Read_MTC(void)
 *
 * PreCondition:    
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    Read and store Midi Time Code
 *
 * Overview:        Service loop for transfer every (MTC) frame to USB host.
 *
 * Note:            None
 *****************************************************************************/
/*		MTC quarter frames
	   	8 x 0xF1 followed by a byte 0nnndddd
			nnn = message
				000 = Frams LS
				001	= Frame MS
				010 = Seconds LS
				011 = Seconds MS
				100 = Minutes LS
				101 = Minutes MS
				110 = Hours LS
				111 = Hours MS
			dddd = data, needs to put together MS (ddddxxxx) + LS (xxxxdddd)
				Frame: xxxyyyyy
					xxx = undefined
					yyyyy = frame number
				Sec: xxyyyyyy
					xx = ud
					yyyyyy = sec number
				Min: xxyyyyyy
					xx = ud
					yyyyyy = min number
				Hour: xyyzzzzzz
					x = ud
					yy = Type
						00 = 24 FPS
						01 = 25 FPS
						10 = 30 FPS drop
						11 = 30 FPS non drop
					zzzzz = hour number
*/
void Read_MTC(void){

			if (PIR1bits.RCIF == 1)				// if data received !!!! For testing I cancelled this
			{

			MTC_in = ReadUSART();									// read USART
			if (MTC_in==0xF1) {
				status_byte = TRUE;					// flag if it's a status byte
			}			
			else{											
				if (status_byte){									// if not but status is set, remember to clear this				
						
						MTC_type = (MTC_in & MESS_TYPE_MASK)>>4;		// isolate the message type
						MTC_message = (MTC_in & MESS_MASK);			// isolate the message
						switch (MTC_type){							// look for the frame start

							case 0:										// frame start
							//	LED1=1;
								MTC_locked = TRUE;						// FLAG FOR RUNNING
								mtcOut[0] = 1;
								mtcCntr2 = mtcCntr2 + 1;			// Count full byte up
								mtcCntr = 0;							// reset timer for led
								MTC_start = TRUE;
								MTC_frame_ls = MTC_message;
								MTC_subframe = 1;
								
								break;

							case 1:
								MTC_frame_ms = MTC_message;
								MTC_frame_temp = FRAME_MASK &
											((MTC_frame_ms << 4) + MTC_frame_ls);	// load frame
								MTC_subframe = 2;
								break;

							case 2:							
								MTC_sec_ls = MTC_message;
								MTC_subframe = 3;
								break;

							case 3:
								MTC_sec_ms = MTC_message;
								MTC_second_temp = SEC_MASK &
											((MTC_sec_ms << 4) + MTC_sec_ls);		// load sec
								MTC_subframe = 4;
								midi_count =1;
								break;

							case 4:								
								MTC_min_ls = MTC_message;
								MTC_frame = MTC_frame + 1;							// increase frames	
								MTC_subframe = 1;
								break;

							case 5:
								MTC_min_ms = MTC_message;
								MTC_minute_temp = MIN_MASK &
											((MTC_min_ms << 4) + MTC_min_ls);		// load min
								MTC_subframe = 2;
								break;

							case 6:							
								MTC_hour_ls = MTC_message;
								MTC_subframe = 3;
								break;


							case 7:
								MTC_hour_ms = MTC_message;
								MTC_fps = (0b00000110 & MTC_hour_ms)>>1;  			// load MTC type
								MTC_hour_temp = HOUR_MASK &
											((MTC_hour_ms << 4) + MTC_hour_ls);		// load hour
								MTC_subframe = 4;	
				
								MTC_frame = MTC_frame_temp;
								MTC_second = MTC_second_temp;
								MTC_minute = MTC_minute_temp;
								MTC_hour = MTC_hour_temp;
								midi_count =1;



								switch (MTC_fps){									// set max frame count
								case 0:				// 24 fps
									MTC_fps_max = 23;
									break;
								case 1:				// 25 fps
									MTC_fps_max = 24;
									break;
								case 2:				// 30 fps
									MTC_fps_max = 29;
									break;
								case 3:				// 30 fps
									MTC_fps_max = 29;
									break;
								}
								break;				
							default:
						//		status_byte=FALSE;
						//		MTC_start=FALSE;
								
								break;

							}// end switch						
		




						}// end if status byte
				else{													// junk, clear
					status_byte=FALSE;
					MTC_start=FALSE;
					
					}				
				}// end else

			PIR1bits.RCIF = 0;
			}// end USART data arrived	
			PIR1bits.RCIF = 0;

		if (mtcCntr < 30000)
			mtcCntr++;
		else {
			LED1=0;						// turn of locked LED
			mtcOut[0] = 0;
			MTC_locked = FALSE;			// Not locked
			mtcCntr2 = 0;				// Reset the full byte received flag
			MTC_full_byte = FALSE;				// Reset the full byte received flag
			}		
		if (mtcCntr2 == 2){				// When the incoming midi laped 2 times
			mtcCntr2 = 1;				// Go back one step
			MTC_full_byte = TRUE;			// flag for full byte
			
		}	
		else{
			MTC_full_byte = FALSE;				// Reset the full byte received flag
			
		}	
		 
								
						if (MTC_locked)
							{mtcOut[1] = MTC_fps + 1;
							LED1=1;						// turn on locked LED
							}
						else
							{mtcOut[1] = 0;}

						mtcOut[2] = MTC_frame;
						mtcOut[3] = MTC_second;
						mtcOut[4] = MTC_minute;
						mtcOut[5] = MTC_hour;
}


static void InitializeSystem(void)
{

	TRISBbits.TRISB0 = 1; // Chip Select
	TRISBbits.TRISB1 = 1; // Clock
 
	TRISEbits.TRISE0 = 0; // LED 1
	TRISEbits.TRISE1 = 0; // LED 2

	TRISEbits.PSPMODE = 0; //	SPP off

    RCONbits. IPEN = 0;				// no int priority
//	INTCONbits.GIEL = 1;			// enable peripheral int
//	INTCONbits.GIE = 1; 			// enable global interrupts 
//	INTCONbits.TMR0IE =1;
//	INTCON2bits.T0IP = 0;
//   OpenTimer0 (TIMER_INT_ON & T0_SOURCE_INT & T0_8BIT & T0_PS_1_32);
//   OpenTimer0 (TIMER_INT_ON & T0_SOURCE_INT & T0_8BIT & T0_PS_1_128);

//	T3CON = 0b00010001; //timer3 on, 1:2 prescaler
//	INTCON2 &= 0b1000000;


	OpenUSART (USART_TX_INT_OFF &
	USART_RX_INT_OFF &
	USART_ASYNCH_MODE &
	USART_EIGHT_BIT &
	USART_CONT_RX &
	USART_BRGH_HIGH, 79);

	ADCON1 = 0xFF;
}//end InitializeSystem

void Scan_Parallell_Port(void)
	{	


	loop = 0;

	cnt=1;											// reset counter
	clk_flag=0;										// flag for Lo/Hi trans
//	TRISCbits.TRISC2 = 1;	
	SSP_write();
	while(cnt<5)									// 6 clock pulses
		{
			LATD = mtcOut[cnt];			
		if(SSP_en == 0)								// check that USB card is still on
			{
			midi_count =0;
			SSP_read();
			return;									// else break
			}
		
		if(SSP_clk == 1 && clk_flag == 0)			// Clock rise
			{

			clk_flag = 1;							// write
			cnt++;									// count up
			LATD = mtcOut[cnt];	
			}

		if(SSP_clk == 0)						// clock hi to lo reset
			{

			loop++;
			clk_flag=0;
	
			}

		if(cnt==5)	LED2=!LED2;
		};
			SSP_read();
				while(SSP_en == 1)						// hold til USB card releases CS
				{
				;
				}
								// release par. port
			midi_count =0;

	}



