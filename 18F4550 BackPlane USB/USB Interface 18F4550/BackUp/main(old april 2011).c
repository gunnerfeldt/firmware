/********************************************************************
 FileName:		main.c
 Dependencies:	See INCLUDES section
 Processor:		PIC18 or PIC24 USB Microcontrollers
 Hardware:		The code is natively intended to be used on the following
 				hardware platforms: PICDEM™ FS USB Demo Board, 
 				PIC18F87J50 FS USB Plug-In Module, or
 				Explorer 16 + PIC24 USB PIM.  The firmware may be
 				modified for use on other USB platforms by editing the
 				HardwareProfile.h file.
 Complier:  	Microchip C18 (for PIC18) or C30 (for PIC24)
 Company:		Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the “Company”) for its PIC® Microcontroller is intended and
 supplied to you, the Company’s customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************
 File Description:

 Change History:
  Rev   Description
  1.0   Initial release
  2.1   Updated for simplicity and to use common
        coding style
  2.6   Added Support for PIC32MX795F512L & PIC24FJ256DA210
********************************************************************/

/** INCLUDES *******************************************************/
#include "USB/usb.h"
#include "USB/usb_function_generic.h"
#include <timers.h>
#include <delays.h> 
#include <usart.h> 
#include "HardwareProfile.h"
#include <p18f4550.h> 

/** CONFIGURATION **************************************************/
        #pragma config PLLDIV   = 5         // (20 MHz crystal on PICDEM FS USB board)
        #pragma config CPUDIV   = OSC1_PLL2   
        #pragma config USBDIV   = 2         // Clock source from 96MHz PLL/2
        #pragma config FOSC     = HSPLL_HS
        #pragma config FCMEN    = OFF
        #pragma config IESO     = OFF
        #pragma config PWRT     = OFF
        #pragma config BOR      = ON
        #pragma config BORV     = 3
        #pragma config VREGEN   = ON      //USB Voltage Regulator
        #pragma config WDT      = OFF
        #pragma config WDTPS    = 32768
        #pragma config MCLRE    = ON
        #pragma config LPT1OSC  = OFF
        #pragma config PBADEN   = OFF
//      #pragma config CCP2MX   = ON
        #pragma config STVREN   = ON
        #pragma config LVP      = OFF
//      #pragma config ICPRT    = OFF       // Dedicated In-Circuit Debug/Programming
        #pragma config XINST    = OFF       // Extended Instruction Set
        #pragma config CP0      = OFF
        #pragma config CP1      = OFF
//      #pragma config CP2      = OFF
//      #pragma config CP3      = OFF
        #pragma config CPB      = OFF
//      #pragma config CPD      = OFF
        #pragma config WRT0     = OFF
        #pragma config WRT1     = OFF
//      #pragma config WRT2     = OFF
//      #pragma config WRT3     = OFF
        #pragma config WRTB     = OFF       // Boot Block Write Protection
        #pragma config WRTC     = OFF
//      #pragma config WRTD     = OFF
        #pragma config EBTR0    = OFF
        #pragma config EBTR1    = OFF
//      #pragma config EBTR2    = OFF
//      #pragma config EBTR3    = OFF
        #pragma config EBTRB    = OFF




/** VARIABLES ******************************************************/
    #pragma udata BIG_ARRAY=0x100
unsigned char big_array[256];

    #pragma udata

    #pragma udata USB_VARIABLES2=0x600

USB_VOLATILE BYTE EP1OUTEvenBuffer[63];	//User buffer for receiving OUT packets sent from the host
USB_VOLATILE BYTE EP1OUTOddBuffer[63];	//User buffer for receiving OUT packets sent from the host

unsigned char PacketInA[64];
unsigned char PacketInB[64];

    #pragma udata

    #pragma udata USB_VARIABLES=0x500
unsigned char USBoutTimeOut = 0;
unsigned char PacketInC[64];
unsigned char PacketInD[64];
// unsigned char PacketIn[64];
unsigned char mtc_array[6];
unsigned char SSPpacketIn[15];
unsigned char PacketInCntr = 0;
unsigned long wCntr;
unsigned int cnt;
unsigned char bCntr;
unsigned char usb_Cntr;
unsigned char bus_transfer_flag=0;
unsigned int timerCntr = 0;
unsigned char MTC_fake_Cntr = 0;
unsigned char data_index = 0;
unsigned char Port_B;
unsigned char command;
unsigned char PacketsCntr = 0;
unsigned char CommTick = 0;		// 1 when timer overflows


unsigned char cnt2;




#pragma udata
BOOL blinkStatusValid;
USB_HANDLE USBGenericOutHandle;
USB_HANDLE USBGenericInHandle;
USB_HANDLE USBIntInHandle;
USB_HANDLE EP1OUTEvenHandle;
USB_HANDLE EP1OUTOddHandle;
// unsigned char INPacket[64];		//User application buffer for sending IN packets to the host


BOOL EP1OUTEvenNeedsServicingNext;	//TRUE means even need servicing next, FALSE means odd needs servicing next




// #pragma udata

/** PRIVATE PROTOTYPES *********************************************/
static void InitializeSystem(void);
void USBDeviceTasks(void);
void YourHighPriorityISRCode(void);
void YourLowPriorityISRCode(void);
void UserInit(void);
void ProcessIO(void);
void data_comm(unsigned char PacketsCntr);
void timer_isr (void);

void Read_MTC_Comm(void);

/** VECTOR REMAPPING ***********************************************/
#if defined(__18CXX)
	//On PIC18 devices, addresses 0x00, 0x08, and 0x18 are used for
	//the reset, high priority interrupt, and low priority interrupt
	//vectors.  However, the current Microchip USB bootloader 
	//examples are intended to occupy addresses 0x00-0x7FF or
	//0x00-0xFFF depending on which bootloader is used.  Therefore,
	//the bootloader code remaps these vectors to new locations
	//as indicated below.  This remapping is only necessary if you
	//wish to program the hex file generated from this project with
	//the USB bootloader.  If no bootloader is used, edit the
	//usb_config.h file and comment out the following defines:
	//#define PROGRAMMABLE_WITH_USB_HID_BOOTLOADER
	//#define PROGRAMMABLE_WITH_USB_LEGACY_CUSTOM_CLASS_BOOTLOADER
	

		#define REMAPPED_RESET_VECTOR_ADDRESS			0x00
		#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x08
		#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x18

	
	#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)||defined(PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER)
	extern void _startup (void);        // See c018i.c in your C18 compiler dir
	#pragma code REMAPPED_RESET_VECTOR = REMAPPED_RESET_VECTOR_ADDRESS
	void _reset (void)
	{
	    _asm goto _startup _endasm
	}
	#endif
	#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS
	void Remapped_High_ISR (void)
	{
	     _asm goto YourHighPriorityISRCode _endasm
	}
	#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS
	void Remapped_Low_ISR (void)
	{
	     _asm goto YourLowPriorityISRCode _endasm
	}
	

	#pragma code
	
	
	//These are your actual interrupt handling routines.
	#pragma interrupt YourHighPriorityISRCode
	void YourHighPriorityISRCode()
	{
		//Check which interrupt flag caused the interrupt.
		//Service the interrupt
		//Clear the interrupt flag
		//Etc.

        #if defined(USB_INTERRUPT)
	        USBDeviceTasks();
        #endif
	
	}	//This return will be a "retfie fast", since this is in a #pragma interrupt section 
	#pragma interruptlow YourLowPriorityISRCode
	void YourLowPriorityISRCode()
	{
		//Check which interrupt flag caused the interrupt.
		//Service the interrupt
		//Clear the interrupt flag
		//Etc.
		if (INTCONbits.TMR0IF)
			{
//			mLED_1=1;
//			Read_MTC();
			INTCONbits.TMR0IF = 0;	// Clear flag
//			mLED_1=0;
			}
	
	}	//This return will be a "retfie", since this is in a #pragma interruptlow section 



#endif




/** DECLARATIONS ***************************************************/
 #define SSP_rw          	TRISD
 #define SSP_clk          	LATBbits.LATB3
 #define MUX_en          	LATBbits.LATB2
 #define MUX_A          	LATBbits.LATB4
 #define MUX_B          	LATBbits.LATB5
 #define MUX_C          	LATBbits.LATB6
 #define MUX_D         	 	LATBbits.LATB7
// #define SSP_rd          	LATBbits.LATB2
 #define loop	          	10
 #define READ          		255
 #define WRITE          		0
 #define On          		1
 #define Off          		0

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
 *******************************************************************/

#if defined(__18CXX)
void main(void)
#else
int main(void)
#endif
{   
    InitializeSystem();

    #if defined(USB_INTERRUPT)
        USBDeviceAttach();
    #endif


    while(1)
    {

       	ProcessIO(); 


		if (CommTick==1)
			{
			mLED_2_Toggle();
				data_comm(0);
				data_comm(1);
				data_comm(2);
				data_comm(3);
				data_comm(4);
				data_comm(5);
//				data_comm(6);
//				data_comm(7);
//				data_comm(8);
//				data_comm(9);
//				data_comm(10);
//				data_comm(11);

				data_comm(12);

				data_comm(13);
			CommTick = 0;
			}




 
    }//end while
}//end main


/********************************************************************
 * Function:        static void InitializeSystem(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        InitializeSystem is a centralize initialization
 *                  routine. All required USB initialization routines
 *                  are called from here.
 *
 *                  User application initialization routine should
 *                  also be called from here.                  
 *
 * Note:            None
 *******************************************************************/
static void InitializeSystem(void)
{

	TRISCbits.TRISC1 = 0;
	TRISCbits.TRISC2 = 0;
	TRISCbits.TRISC7 = 1;
	TRISAbits.TRISA0 = 1;
	TRISAbits.TRISA1 = 1;
	TRISAbits.TRISA2 = 1;

/*
    RCONbits. IPEN = 1;
	INTCONbits.GIEL = 1;
	INTCONbits.TMR0IE =1;
	INTCON2bits.T0IP = 0;
   OpenTimer0 (TIMER_INT_ON & T0_SOURCE_INT & T0_8BIT & T0_PS_1_32);
//   OpenTimer0 (TIMER_INT_ON & T0_SOURCE_INT & T0_8BIT & T0_PS_1_128);
 */
//  INTCONbits.GIE = 1; //enable global interrupts 
//	T3CON = 0b00010001; //timer3 on, 1:2 prescaler
//	INTCON2 &= 0b1000000;
	TRISC=0b00111001; 

/*
	OpenUSART (USART_TX_INT_OFF &
	USART_RX_INT_OFF &
	USART_ASYNCH_MODE &
	USART_EIGHT_BIT &
	USART_CONT_RX &
	USART_BRGH_HIGH, 95);
*/

    #if defined(USE_USB_BUS_SENSE_IO)
    tris_usb_bus_sense = INPUT_PIN; // See HardwareProfile.h
    #endif

    #if defined(USE_SELF_POWER_SENSE_IO)
    tris_self_power = INPUT_PIN;	// See HardwareProfile.h
    #endif
    
	USBGenericOutHandle = 0;	
	USBGenericInHandle = 0;		
	USBIntInHandle = 0;		

    UserInit();			//Application related initialization.  See user.c

    USBDeviceInit();	//usb_device.c.  Initializes USB module SFRs and firmware
    					//variables to known states.

	TRISB = 0;
	MUX_en = 1;

}//end InitializeSystem



void UserInit(void)
{
    mInitAllLEDs();
    mInitAllSwitches();


}//end UserInit




/******************************************************************************
 * Function:        void ProcessIO(void)
 *
 *****************************************************************************/
void ProcessIO(void)
{   


    if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) return;
    USBoutTimeOut = 0;
	while(CommTick==0)
	{

//	if (USBoutTimeOut>1000) return;
	USBoutTimeOut++;

	if(EP1OUTEvenNeedsServicingNext == TRUE)	//Check which buffer (even/odd) the next set of data is going to arrive in
	{
		if(!USBHandleBusy(EP1OUTEvenHandle))	//Check if the endpoint has received any data from the host.
		{  
		switch (EP1OUTEvenBuffer[0])
			{
			case 1:
				for(cnt=0;cnt<48;cnt++)
					{
					big_array[cnt] = EP1OUTEvenBuffer[cnt+4];
					if (cnt<8) big_array[192+cnt] = EP1OUTEvenBuffer[cnt+52];
					} 
			break;
			case 2: 
			mLED_1 = 1;
				for(cnt=0;cnt<48;cnt++)
					{
					big_array[cnt+48] = EP1OUTEvenBuffer[cnt+4];
					if (cnt<8) big_array[200+cnt] = EP1OUTEvenBuffer[cnt+52];
					} 
			break;
			case 3:
				for(cnt=0;cnt<48;cnt++)
					{
					big_array[cnt+96] = EP1OUTEvenBuffer[cnt+4];
					} 
			break;
			case 4:
				for(cnt=0;cnt<48;cnt++)
					{
					big_array[cnt+144] = EP1OUTEvenBuffer[cnt+4];
					} 
				CommTick = 1;
			break;
			}

		    EP1OUTEvenHandle = USBTransferOnePacket(1, OUT_FROM_HOST,(BYTE*)&EP1OUTEvenBuffer,64);
			EP1OUTEvenNeedsServicingNext = FALSE;
		}
	}	
	else //else EP1OUTOdd needs servicing next
	{
		if(!USBHandleBusy(EP1OUTOddHandle))		//Check if the endpoint has received any data from the host.
		{   
		switch (EP1OUTOddBuffer[0])
			{
			case 1:
				for(cnt=0;cnt<48;cnt++)
					{
					big_array[cnt] = EP1OUTOddBuffer[cnt+4];
					if (cnt<8) big_array[192+cnt] = EP1OUTOddBuffer[cnt+52];
					} 
				break;
			case 2:
				mLED_1 = 1;
				for(cnt=0;cnt<48;cnt++)
					{
					big_array[cnt+48] = EP1OUTOddBuffer[cnt+4];
					if (cnt<8) big_array[200+cnt] = EP1OUTOddBuffer[cnt+52];
					} 
				break;
			case 3:
				for(cnt=0;cnt<48;cnt++)
					{
					big_array[cnt+96] = EP1OUTOddBuffer[cnt+4];
					} 
				break;
			case 4:
				for(cnt=0;cnt<48;cnt++)
					{
					big_array[cnt+144] = EP1OUTOddBuffer[cnt+4];
					} 
				CommTick = 1;
				mLED_1 = !mLED_1;
				break;
			}		

		    //Re-arm the EP1OUTOdd BDT entry so the EP1OUTOddBuffer[] can receive
		    //the second to next data packet sent by the host.

		    EP1OUTOddHandle = USBTransferOnePacket(1, OUT_FROM_HOST,(BYTE*)&EP1OUTOddBuffer,64);
		    EP1OUTEvenNeedsServicingNext = TRUE;
			} 	    
		}




/*		PacketIn[0]=PacketInCntr+1;
		PacketIn[1] = MTC_fps;
		PacketIn[2] = MTC_frame;
		PacketIn[3] = MTC_second;
		PacketIn[4] = MTC_minute;
		PacketIn[5] = MTC_hour;
*/
/*
			if (CommTick==1)
				{			
				while(USBHandleBusy(USBIntInHandle))
					{
					;
					}
					PacketInA[0]=0;
//					PacketInA[7]=63;
					USBIntInHandle = USBGenWrite(USBGEN_EP_NUM,(BYTE*)&PacketInA,64);
				while(USBHandleBusy(USBIntInHandle))
					{
					;
					}
					PacketInB[0]=1;
//					PacketInB[7]=63;
					USBIntInHandle = USBGenWrite(USBGEN_EP_NUM,(BYTE*)&PacketInB,64);
				while(USBHandleBusy(USBIntInHandle))
					{
					;
					}
					PacketInC[0]=2;
//					PacketInC[56]=2;
					USBIntInHandle = USBGenWrite(USBGEN_EP_NUM,(BYTE*)&PacketInC,64);
				while(USBHandleBusy(USBIntInHandle))
					{
					;
					}
					PacketInD[0]=3;
//					PacketInD[56]=2;
					USBIntInHandle = USBGenWrite(USBGEN_EP_NUM,(BYTE*)&PacketInD,64);
				mLED_1 = 0;
				}
*/
		}			// Hold Loop until all data arrived to the pic
						


}//end ProcessIO
void Read_MTC_Comm(void)
	{
	// mux for mtc comm

//	MUX_en = 1;			// erase this when the mux is done

	MUX_en = 1;
	MUX_A = 1;			// 1
	MUX_B = 0;			// 2
	MUX_C = 1;			// 4
	MUX_D = 1;			// 8
	MUX_en = 0;
		for(wCntr=0;wCntr<200;++wCntr)
			{			
			;
			}
	SSP_rw = READ;
	for(cnt=1;cnt<6;cnt++)
		{
		PacketInA[cnt] = PORTD;
		SSP_clk= On;
		for(wCntr=0;wCntr<loop*2;++wCntr)
			{
			;
			}
		SSP_clk= Off;
		for(wCntr=0;wCntr<loop*2;++wCntr)
			{
			;
			}
		}

	MUX_en = 1;
	}

void data_comm(unsigned char PacketsCntr)
{
// *************** Packet A ***************

	//  Write Op


//	MUX_en = 1;

//	INTCONbits.TMR0IE = 0;



	if(PacketsCntr==13)			// MTC micro
		{
		Read_MTC_Comm();
		}
	else
		{


	// 	Address the mux

	Port_B = PORTB & 0b00001111;
	Port_B = Port_B + (PacketsCntr << 4);
	PORTB = Port_B;



	MUX_en = 0;

//	SSP_rw = READ;
//	while (PORTD!=0)
//		{
//		;
//		}

		for(wCntr=0;wCntr<60;++wCntr)
			{			
			;
			}
		SSP_rw = WRITE;

//	**********	Write operation
				for(cnt=0;cnt<16;cnt++)
					{

					LATD = big_array[(PacketsCntr*16) + cnt];

					for(wCntr=0;wCntr<loop;++wCntr)
						{
						;
						}
					SSP_clk= On;

					for(wCntr=0;wCntr<loop;++wCntr)
						{
							;
						}
					SSP_clk= Off;

					}
//	**********	Read operation
				SSP_rw = READ;
				for(wCntr=0;wCntr<100;++wCntr)
					{			
					;
					}
				for(cnt=0;cnt<16;cnt++)
					{
					SSPpacketIn[cnt] = PORTD;
					SSP_clk= On;
					for(wCntr=0;wCntr<loop;++wCntr)
						{
							;
						}

//					SSPpacketIn[cnt] = PORTD;

					SSP_clk= Off;
					for(wCntr=0;wCntr<loop;++wCntr)
						{
						;
						}
					}
//					Clear MUX
					MUX_en = 1;
					bus_transfer_flag = 1;

					SSPpacketIn[15] =PORTD;
					SSP_rw = READ;

		switch(PacketsCntr)
			{
			case 0:
				for (cnt=0;cnt<16;cnt++)
					{
					PacketInA[8+cnt] = SSPpacketIn[cnt];
					}

			break;
			case 1:
				for (cnt=0;cnt<16;cnt++)
					{
					PacketInA[24+cnt] = SSPpacketIn[cnt];
					}			
			break;
			case 2:
				for (cnt=0;cnt<16;cnt++)
					{
					PacketInA[40+cnt] = SSPpacketIn[cnt];
					}			
			break;
			case 3:
				for (cnt=0;cnt<16;cnt++)
					{
					PacketInB[8+cnt] = SSPpacketIn[cnt];
					}			
			break;
			case 4:
				for (cnt=0;cnt<16;cnt++)
					{
					PacketInB[8+cnt+16] = SSPpacketIn[cnt];
					}			
			break;
			case 5:
				for (cnt=0;cnt<16;cnt++)
					{
					PacketInB[8+cnt+32] = SSPpacketIn[cnt];
					}			
			break;
			case 6:
				for (cnt=0;cnt<16;cnt++)
					{
					PacketInC[8+cnt] = SSPpacketIn[cnt];
					}		
			break;
			case 7:
				for (cnt=0;cnt<16;cnt++)
					{
					PacketInC[8+cnt+16] = SSPpacketIn[cnt];
					}			
			break;
			case 8:
				for (cnt=0;cnt<16;cnt++)
					{
					PacketInC[8+cnt+32] = SSPpacketIn[cnt];
					}			
			break;
			case 9:
				for (cnt=0;cnt<16;cnt++)
					{
					PacketInD[8+cnt] = SSPpacketIn[cnt];
					}			
			break;
			case 10:
				for (cnt=0;cnt<16;cnt++)
					{
					PacketInD[8+cnt+16] = SSPpacketIn[cnt];
					}				
			break;
			case 11:
				for (cnt=0;cnt<16;cnt++)
					{
					PacketInD[8+cnt+32] = SSPpacketIn[cnt];
					}				
			break;
			case 12:
				for (cnt=0;cnt<8;cnt++)
					{
					PacketInA[56+cnt] = SSPpacketIn[cnt];

//					PacketInC[56+cnt] = SSPpacketIn[cnt];

					PacketInB[56+cnt] = SSPpacketIn[cnt+8];

//					PacketInD[56+cnt] = SSPpacketIn[cnt+8];
					}			
			break;
			}



		}
		
//		}

}






// ******************************************************************************************************
// ************** USB Callback Functions ****************************************************************
// ******************************************************************************************************
// The USB firmware stack will call the callback functions USBCBxxx() in response to certain USB related
// events.  For example, if the host PC is powering down, it will stop sending out Start of Frame (SOF)
// packets to your device.  In response to this, all USB devices are supposed to decrease their power
// consumption from the USB Vbus to <2.5mA each.  The USB module detects this condition (which according
// to the USB specifications is 3+ms of no bus activity/SOF packets) and then calls the USBCBSuspend()
// function.  You should modify these callback functions to take appropriate actions for each of these
// conditions.  For example, in the USBCBSuspend(), you may wish to add code that will decrease power
// consumption from Vbus to <2.5mA (such as by clock switching, turning off LEDs, putting the
// microcontroller to sleep, etc.).  Then, in the USBCBWakeFromSuspend() function, you may then wish to
// add code that undoes the power saving things done in the USBCBSuspend() function.

// The USBCBSendResume() function is special, in that the USB stack will not automatically call this
// function.  This function is meant to be called from the application firmware instead.  See the
// additional comments near the function.

/******************************************************************************
 * Function:        void USBCBSuspend(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Call back that is invoked when a USB suspend is detected
 *
 * Note:            None
 *****************************************************************************/
void USBCBSuspend(void)
{
	//Example power saving code.  Insert appropriate code here for the desired
	//application behavior.  If the microcontroller will be put to sleep, a
	//process similar to that shown below may be used:
	
	//ConfigureIOPinsForLowPower();
	//SaveStateOfAllInterruptEnableBits();
	//DisableAllInterruptEnableBits();
	//EnableOnlyTheInterruptsWhichWillBeUsedToWakeTheMicro();	//should enable at least USBActivityIF as a wake source
	//Sleep();
	//RestoreStateOfAllPreviouslySavedInterruptEnableBits();	//Preferrably, this should be done in the USBCBWakeFromSuspend() function instead.
	//RestoreIOPinsToNormal();									//Preferrably, this should be done in the USBCBWakeFromSuspend() function instead.

	//IMPORTANT NOTE: Do not clear the USBActivityIF (ACTVIF) bit here.  This bit is 
	//cleared inside the usb_device.c file.  Clearing USBActivityIF here will cause 
	//things to not work as intended.	
	

    #if defined(__C30__)
    #if 0
        U1EIR = 0xFFFF;
        U1IR = 0xFFFF;
        U1OTGIR = 0xFFFF;
        IFS5bits.USB1IF = 0;
        IEC5bits.USB1IE = 1;
        U1OTGIEbits.ACTVIE = 1;
        U1OTGIRbits.ACTVIF = 1;
        Sleep();
    #endif
    #endif
}


/******************************************************************************
 * Function:        void _USB1Interrupt(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called when the USB interrupt bit is set
 *					In this example the interrupt is only used when the device
 *					goes to sleep when it receives a USB suspend command
 *
 * Note:            None
 *****************************************************************************/
#if 0
void __attribute__ ((interrupt)) _USB1Interrupt(void)
{
    #if !defined(self_powered)
        if(U1OTGIRbits.ACTVIF)
        {
            IEC5bits.USB1IE = 0;
            U1OTGIEbits.ACTVIE = 0;
            IFS5bits.USB1IF = 0;
        
            //USBClearInterruptFlag(USBActivityIFReg,USBActivityIFBitNum);
            USBClearInterruptFlag(USBIdleIFReg,USBIdleIFBitNum);
            //USBSuspendControl = 0;
        }
    #endif
}
#endif

/******************************************************************************
 * Function:        void USBCBWakeFromSuspend(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The host may put USB peripheral devices in low power
 *					suspend mode (by "sending" 3+ms of idle).  Once in suspend
 *					mode, the host may wake the device back up by sending non-
 *					idle state signalling.
 *					
 *					This call back is invoked when a wakeup from USB suspend 
 *					is detected.
 *
 * Note:            None
 *****************************************************************************/
void USBCBWakeFromSuspend(void)
{
	// If clock switching or other power savings measures were taken when
	// executing the USBCBSuspend() function, now would be a good time to
	// switch back to normal full power run mode conditions.  The host allows
	// a few milliseconds of wakeup time, after which the device must be 
	// fully back to normal, and capable of receiving and processing USB
	// packets.  In order to do this, the USB module must receive proper
	// clocking (IE: 48MHz clock must be available to SIE for full speed USB
	// operation).
}

/********************************************************************
 * Function:        void USBCB_SOF_Handler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The USB host sends out a SOF packet to full-speed
 *                  devices every 1 ms. This interrupt may be useful
 *                  for isochronous pipes. End designers should
 *                  implement callback routine as necessary.
 *
 * Note:            None
 *******************************************************************/
void USBCB_SOF_Handler(void)
{
    // No need to clear UIRbits.SOFIF to 0 here.
    // Callback caller is already doing that.
}

/*******************************************************************
 * Function:        void USBCBErrorHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The purpose of this callback is mainly for
 *                  debugging during development. Check UEIR to see
 *                  which error causes the interrupt.
 *
 * Note:            None
 *******************************************************************/
void USBCBErrorHandler(void)
{
    // No need to clear UEIR to 0 here.
    // Callback caller is already doing that.

	// Typically, user firmware does not need to do anything special
	// if a USB error occurs.  For example, if the host sends an OUT
	// packet to your device, but the packet gets corrupted (ex:
	// because of a bad connection, or the user unplugs the
	// USB cable during the transmission) this will typically set
	// one or more USB error interrupt flags.  Nothing specific
	// needs to be done however, since the SIE will automatically
	// send a "NAK" packet to the host.  In response to this, the
	// host will normally retry to send the packet again, and no
	// data loss occurs.  The system will typically recover
	// automatically, without the need for application firmware
	// intervention.
	
	// Nevertheless, this callback function is provided, such as
	// for debugging purposes.
}


/*******************************************************************
 * Function:        void USBCBCheckOtherReq(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        When SETUP packets arrive from the host, some
 * 					firmware must process the request and respond
 *					appropriately to fulfill the request.  Some of
 *					the SETUP packets will be for standard
 *					USB "chapter 9" (as in, fulfilling chapter 9 of
 *					the official USB specifications) requests, while
 *					others may be specific to the USB device class
 *					that is being implemented.  For example, a HID
 *					class device needs to be able to respond to
 *					"GET REPORT" type of requests.  This
 *					is not a standard USB chapter 9 request, and 
 *					therefore not handled by usb_device.c.  Instead
 *					this request should be handled by class specific 
 *					firmware, such as that contained in usb_function_hid.c.
 *
 * Note:            None
 *****************************************************************************/
void USBCBCheckOtherReq(void)
{
}//end


/*******************************************************************
 * Function:        void USBCBStdSetDscHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The USBCBStdSetDscHandler() callback function is
 *					called when a SETUP, bRequest: SET_DESCRIPTOR request
 *					arrives.  Typically SET_DESCRIPTOR requests are
 *					not used in most applications, and it is
 *					optional to support this type of request.
 *
 * Note:            None
 *****************************************************************************/
void USBCBStdSetDscHandler(void)
{
    // Must claim session ownership if supporting this request
}//end


/******************************************************************************
 * Function:        void USBCBInitEP(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called when the device becomes
 *                  initialized, which occurs after the host sends a
 * 					SET_CONFIGURATION (wValue not = 0) request.  This 
 *					callback function should initialize the endpoints 
 *					for the device's usage according to the current 
 *					configuration.
 *
 * Note:            None
 *****************************************************************************/
void USBCBInitEP(void)
{
//    USBEnableEndpoint(USBGEN_EP_NUM,USB_OUT_ENABLED|USB_IN_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
    USBEnableEndpoint(USBINT_EP_NUM,USB_OUT_DISABLED|USB_IN_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
   USBEnableEndpoint(1,USB_OUT_ENABLED|USB_IN_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
	
	//Prepare the OUT endpoints to receive the first packets from the host.
//    USBGenericOutHandle = USBGenRead(USBGEN_EP_NUM,(BYTE*)&Packet,USBGEN_EP_SIZE);
	EP1OUTEvenHandle = USBTransferOnePacket(1, OUT_FROM_HOST,(BYTE*)&EP1OUTEvenBuffer,64);	//First 64-bytes of data sent to EP1 OUT will arrive in the even buffer.
	EP1OUTOddHandle = USBTransferOnePacket(1, OUT_FROM_HOST,(BYTE*)&EP1OUTOddBuffer,64);	//Second 64-bytes of data sent to EP1 OUT will arrive in the odd buffer.
    EP1OUTEvenNeedsServicingNext = TRUE;	//Used to keep track of which buffer will contain the next sequential data packet.


}

/********************************************************************
 * Function:        void USBCBSendResume(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The USB specifications allow some types of USB
 * 					peripheral devices to wake up a host PC (such
 *					as if it is in a low power suspend to RAM state).
 *					This can be a very useful feature in some
 *					USB applications, such as an Infrared remote
 *					control	receiver.  If a user presses the "power"
 *					button on a remote control, it is nice that the
 *					IR receiver can detect this signalling, and then
 *					send a USB "command" to the PC to wake up.
 *					
 *					The USBCBSendResume() "callback" function is used
 *					to send this special USB signalling which wakes 
 *					up the PC.  This function may be called by
 *					application firmware to wake up the PC.  This
 *					function should only be called when:
 *					
 *					1.  The USB driver used on the host PC supports
 *						the remote wakeup capability.
 *					2.  The USB configuration descriptor indicates
 *						the device is remote wakeup capable in the
 *						bmAttributes field.
 *					3.  The USB host PC is currently sleeping,
 *						and has previously sent your device a SET 
 *						FEATURE setup packet which "armed" the
 *						remote wakeup capability.   
 *
 *					This callback should send a RESUME signal that
 *                  has the period of 1-15ms.
 *
 * Note:            Interrupt vs. Polling
 *                  -Primary clock
 *                  -Secondary clock ***** MAKE NOTES ABOUT THIS *******
 *                   > Can switch to primary first by calling USBCBWakeFromSuspend()
 
 *                  The modifiable section in this routine should be changed
 *                  to meet the application needs. Current implementation
 *                  temporary blocks other functions from executing for a
 *                  period of 1-13 ms depending on the core frequency.
 *
 *                  According to USB 2.0 specification section 7.1.7.7,
 *                  "The remote wakeup device must hold the resume signaling
 *                  for at lest 1 ms but for no more than 15 ms."
 *                  The idea here is to use a delay counter loop, using a
 *                  common value that would work over a wide range of core
 *                  frequencies.
 *                  That value selected is 1800. See table below:
 *                  ==========================================================
 *                  Core Freq(MHz)      MIP         RESUME Signal Period (ms)
 *                  ==========================================================
 *                      48              12          1.05
 *                       4              1           12.6
 *                  ==========================================================
 *                  * These timing could be incorrect when using code
 *                    optimization or extended instruction mode,
 *                    or when having other interrupts enabled.
 *                    Make sure to verify using the MPLAB SIM's Stopwatch
 *                    and verify the actual signal on an oscilloscope.
 *******************************************************************/
void USBCBSendResume(void)
{
    static WORD delay_count;
    
    USBResumeControl = 1;                // Start RESUME signaling
    
    delay_count = 1800U;                // Set RESUME line for 1-13 ms
    do
    {
        delay_count--;
    }while(delay_count);
    USBResumeControl = 0;
}


/*******************************************************************
 * Function:        BOOL USER_USB_CALLBACK_EVENT_HANDLER(
 *                        USB_EVENT event, void *pdata, WORD size)
 *
 * PreCondition:    None
 *
 * Input:           USB_EVENT event - the type of event
 *                  void *pdata - pointer to the event data
 *                  WORD size - size of the event data
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called from the USB stack to
 *                  notify a user application that a USB event
 *                  occured.  This callback is in interrupt context
 *                  when the USB_INTERRUPT option is selected.
 *
 * Note:            None
 *******************************************************************/
BOOL USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, WORD size)
{
    switch(event)
    {
        case EVENT_CONFIGURED: 
            USBCBInitEP();
            break;
        case EVENT_SET_DESCRIPTOR:
            USBCBStdSetDscHandler();
            break;
        case EVENT_EP0_REQUEST:
            USBCBCheckOtherReq();
            break;
        case EVENT_SOF:
            USBCB_SOF_Handler();
            break;
        case EVENT_SUSPEND:
            USBCBSuspend();
            break;
        case EVENT_RESUME:
            USBCBWakeFromSuspend();
            break;
        case EVENT_BUS_ERROR:
            USBCBErrorHandler();
            break;
        case EVENT_TRANSFER:
            Nop();
            break;
        default:
            break;
    }      
    return TRUE; 
}
/** EOF main.c ***************************************************************/
