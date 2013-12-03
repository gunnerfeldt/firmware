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
#include <USB/usb.h>
#include <USB/usb_function_generic.h>
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


#define ERROR_MASK_0	0b01010101
#define ERROR_MASK_1	0b10101010

struct packetStruct{
	unsigned char byte[64];
	};
struct mtcStruct{
	unsigned char PacketCntr;
	unsigned char Bank;
	unsigned char byte[6];
	};
struct sslFaderFromUSBStruct{
	unsigned vca_lo:8;
	unsigned vca_hi:2;
	unsigned status:2;
	unsigned not_used:1;
	unsigned event:1;
	unsigned not_used2:1;
	unsigned mute:1;
	};
struct sslFaderToUSBStruct{
	unsigned vca_lo:8;
	unsigned vca_hi:2;
	unsigned not_used:2;
	unsigned switch_press:1;
	unsigned event:1;
	unsigned not_used2:1;
	unsigned mute:1;
	};
struct motorFaderFromUSBStruct{
	unsigned vca_lo:8;
	unsigned vca_hi:2;
	unsigned status:2;
	unsigned motor_on:1;
	unsigned event:1;
	unsigned not_used:1;
	unsigned mute:1;
	};
struct motorFaderToUSBStruct{
	unsigned vca_lo:8;
	unsigned vca_hi:2;
	unsigned status:2;
	unsigned touch_sense:1;
	unsigned event:1;
	unsigned not_used:1;
	unsigned mute:1;
	};

struct dataOutStruct{
	struct mtcStruct MTCbytes;
	struct sslFaderFromUSBStruct sslFader[96];
	struct motorFaderFromUSBStruct motorFader[8];
	unsigned char motorFaderControl[8]; 
	unsigned char VCAcardControl[12]; 
	};	

struct dataInStruct{
	struct mtcStruct MTCbytes;
	struct sslFaderToUSBStruct sslFader[96];
	struct motorFaderToUSBStruct motorFader[8];
	unsigned char motorFaderControl[8]; 
	unsigned char VCAcardControl[12]; 
	};	

union USBdataOutUnion {
	unsigned char data[255];
	struct packetStruct packet[3];
	struct dataOutStruct Out;
	};

union USBdataInUnion {
	unsigned char data[255];
	struct packetStruct packet[3];
	struct dataInStruct In;
	};

/** VARIABLES ******************************************************/

#pragma udata USB_VARIABLES2=0x600

USB_VOLATILE union USBdataOutUnion USBdataOUT;

#pragma udata USB_VARIABLES3=0x700

USB_VOLATILE union USBdataInUnion USBdataIN;




#pragma udata USB_VARIABLES=0x500

USB_VOLATILE unsigned char tempData[16];
// USB_VOLATILE BYTE EP1OUTEvenBuffer[63];	//User buffer for receiving OUT packets sent from the host
// USB_VOLATILE BYTE EP1OUTOddBuffer[64];	//User buffer for receiving OUT packets sent from the host
unsigned char USBoutTimeOut = 0;
unsigned char mtc_array[6];
// unsigned char SSPpacketIn[15];
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
unsigned char USB_DONE_FLAG = 0;

unsigned char cnt2;




#pragma udata
BOOL blinkStatusValid;
USB_HANDLE USBGenericOutHandle;
USB_HANDLE USBGenericInHandle;
//USB_HANDLE USBIntInHandle[3];
//USB_HANDLE EP1OUTHandle[3];
USB_HANDLE USBIntInHandle;
USB_HANDLE EP1OUTHandle;

unsigned char USB_HANDLE_counter = 0;


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
void write_clock(void);
void read_clock(void);
void NoLatencyShuffle(void);
unsigned char ErrorCode(unsigned char, unsigned char);

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
 #define loop	          	8
 #define READ          		255
 #define WRITE          		0
 #define On          		1
 #define Off          		0

#define INT_OFF		INTCONbits.GIE = 0
#define INT_ON		INTCONbits.GIE = 1

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
	unsigned char devID;
    InitializeSystem();
	mLED_1_On();
    #if defined(USB_INTERRUPT)
        USBDeviceAttach();
    #endif


    while(1)
    {
       	ProcessIO(); 
		if(USB_DONE_FLAG)
			{
				mLED_2_Toggle();
				INT_OFF;
				data_comm(13);	// First read MTC
				INT_ON;
				INT_OFF;
				data_comm(12);	// Then read/write Motor Faders
				INT_ON;
			for(devID=0;devID<12;devID++)	// Last the VCA cards
				{
				INT_OFF;
				data_comm(devID);
				INT_ON;
				}	
			USB_DONE_FLAG = 0;
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

	TRISAbits.TRISA0 = 1;
	TRISAbits.TRISA1 = 1;
	TRISAbits.TRISA2 = 1;
	TRISC=0b00111001; 



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

//	if (USBoutTimeOut>1000) return;
	USBoutTimeOut++;

	USB_HANDLE_counter = 0;

	while(USB_HANDLE_counter<4) 
		{
//		if(!USBHandleBusy(EP1OUTHandle[USB_HANDLE_counter]))	//Check if the endpoint has received any data from the host.
		if(!USBHandleBusy(EP1OUTHandle))	//Check if the endpoint has received any data from the host.
			{  
			mLED_1_Toggle();
//		    EP1OUTHandle[USB_HANDLE_counter] = USBTransferOnePacket(1, OUT_FROM_HOST,(BYTE*)&USBdataOUT.packet[USB_HANDLE_counter].byte,64);
		    EP1OUTHandle = USBTransferOnePacket(1, OUT_FROM_HOST,(BYTE*)&USBdataOUT.packet[USB_HANDLE_counter].byte,64);
			USB_HANDLE_counter++;
			}

		}	


/*		PacketIn[0]=PacketInCntr+1;
		PacketIn[1] = MTC_fps;
		PacketIn[2] = MTC_frame;
		PacketIn[3] = MTC_second;
		PacketIn[4] = MTC_minute;
		PacketIn[5] = MTC_hour;
*/

		USB_HANDLE_counter = 0;
		while(USB_HANDLE_counter<4) 
			{			
			while(USBHandleBusy(USBIntInHandle))
				{
				;
				}
				USBIntInHandle = USBGenWrite(USBGEN_EP_NUM,(BYTE*)&USBdataIN.packet[USB_HANDLE_counter].byte,64);

			USB_HANDLE_counter++;
		//	if (USB_HANDLE_counter==3);// mLED_1 = !mLED_1;
			}
		USB_DONE_FLAG = 1;



}//end ProcessIO


void NoLatencyShuffle(void)
	{
	unsigned char n;
	unsigned char bank;
	unsigned char bank_add;
	bank = USBdataOUT.Out.MTCbytes.Bank;
	bank_add = bank * 8;
	for (n=0;n<8;n++){
		if(USBdataIN.In.motorFader[n].touch_sense == 1)
		{		
			if(USBdataIN.In.motorFaderControl[n] == 0xF1)
				{		
//				if(USBdataIN.In.motorFader[n].event)
					{
					USBdataOUT.Out.sslFader[n+bank_add].vca_lo = USBdataIN.In.motorFader[n].vca_lo;
					USBdataOUT.Out.sslFader[n+bank_add].vca_hi = USBdataIN.In.motorFader[n].vca_hi;
//					If mute is to be controlled it need to send latching info
//					USBdataOUT.Out.sslFader[n+bank_add].mute = USBdataIN.In.motorFader[n].mute;
					USBdataOUT.Out.sslFader[n+bank_add].event = USBdataIN.In.motorFader[n].event;
					USBdataOUT.Out.VCAcardControl[bank] = 0xF1;
					}
				}	
			}
		}			
	}
	



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
		USBdataIN.data[cnt] = PORTD;
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
	unsigned int err;
	unsigned char port;

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


		for(wCntr=0;wCntr<40;++wCntr) // 60
			{			
			;
			}

				
//	**********	Read operation

				SSP_rw = READ;
				for(wCntr=0;wCntr<60;++wCntr) //100
					{			
					;
					}
				for(cnt=0;cnt<16;cnt++)
					{
					USBdataIN.data[(PacketsCntr*16) + cnt + 8] = PORTD;
					SSP_clk= On;

					read_clock();

					}
				if(PacketsCntr==12)			// for Motor Fader Card, read 8 control bytes
					{
					for(cnt=0;cnt<8;cnt++)
						{
						USBdataIN.data[216 + cnt] = PORTD;	// store in 216 to 223

						read_clock();

						}
//	**********	Shuffle Real Time Stuff
					NoLatencyShuffle();
					}
				else		// for VCA cards, only one control byte. Store from 224
					{
					USBdataIN.data[PacketsCntr + 224] = PORTD;

					read_clock();
					}



//	**********	Write operation

				SSP_rw = WRITE;
				for(cnt=0;cnt<16;cnt++) // 16
					{

					LATD = USBdataOUT.data[(PacketsCntr*16) + cnt + 8];

					write_clock();

					}
				if(PacketsCntr==12)			// for Motor Fader Card, read 8 control bytes
					{
					for(cnt=0;cnt<8;cnt++)
						{
	
						LATD = USBdataOUT.data[216 + cnt];
						write_clock();
						}
					}
				else		// for VCA cards, only one control byte. Store from 224
					{
					LATD = USBdataOUT.data[PacketsCntr + 224];	// for VCA cards, only one control byte. Store from 224
					write_clock();
					}

//					Clear MUX
					MUX_en = 1;
					bus_transfer_flag = 1;

					SSP_rw = READ;


		}
		
//		}

}


void write_clock(void)
	{
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
void read_clock(void)
	{
	SSP_clk= On;
	for(wCntr=0;wCntr<loop;++wCntr)
		{
			;
		}
	SSP_clk= Off;
	for(wCntr=0;wCntr<loop;++wCntr)
		{
		;
		}
	}

unsigned char ErrorCode(unsigned char dataA, unsigned char dataB)
	{
	unsigned char checkA;
	unsigned char checkB;
	unsigned char check;
	checkA = dataA & ERROR_MASK_0;
	checkB = dataB & ERROR_MASK_1;
	check = checkA + checkB;
	return ~check;
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
//	EP1OUTHandle = USBTransferOnePacket(1, OUT_FROM_HOST,(BYTE*)&USBdataOUT.packet[0].byte,64);	//64-bytes of data sent to EP1 OUT will arrive in buffer.
//	EP1OUTHandle[0] = USBTransferOnePacket(1, OUT_FROM_HOST,(BYTE*)&USBdataOUT.packet[0].byte,64);	//First 64-bytes of data sent to EP1 OUT will arrive in the even buffer.
//	EP1OUTHandle[1] = USBTransferOnePacket(1, OUT_FROM_HOST,(BYTE*)&USBdataOUT.packet[1],64);	//Second 64-bytes of data sent to EP1 OUT will arrive in the odd buffer.
//	EP1OUTHandle[2] = USBTransferOnePacket(1, OUT_FROM_HOST,(BYTE*)&USBdataOUT.packet[2],64);	//Third 64-bytes of data sent to EP1 OUT will arrive in the even buffer.
//	EP1OUTHandle[3] = USBTransferOnePacket(1, OUT_FROM_HOST,(BYTE*)&USBdataOUT.packet[3],64);	//Fourth 64-bytes of data sent to EP1 OUT will arrive in the odd buffer.
//    EP1OUTEvenNeedsServicingNext = TRUE;	//Used to keep track of which buffer will contain the next sequential data packet.


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
