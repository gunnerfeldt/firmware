/********************************************************************
 FileName:      main.c
 Dependencies:  See INCLUDES section
 Processor:     PIC18, PIC24, dsPIC, and PIC32 USB Microcontrollers
 Hardware:      This demo is natively intended to be used on Microchip USB demo
                boards supported by the MCHPFSUSB stack.  See release notes for
                support matrix.  This demo can be modified for use on other 
                hardware platforms.
 Complier:      Microchip C18 (for PIC18), XC16 (for PIC24/dsPIC), XC32 (for PIC32)
 Company:       Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the "Company") for its PIC(R) Microcontroller is intended and
 supplied to you, the Company's customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************
 File Description:

 Change History:
  Rev   Description
  ----  -----------------------------------------
  1.0   Initial release
  2.1   Updated for simplicity and to use common
                     coding style
  2.7b  Improvements to USBCBSendResume(), to make it easier to use.
  2.9f  Adding new part support
  2.9j  Updates to support new bootloader features (ex: app version 
        fetching).
********************************************************************/

#ifndef MAIN_C
#define MAIN_C

#define NIBBLE_MASK		0b01100000
#define MS_MASK			0b00010000
#define DATA_MASK		0b00001111
#define FPS_MASK		0b00000111
#define	COMM_CLOCK		LATBbits.LATB3
#define	MUX_ENABLE		LATBbits.LATB2
#define	COMM_STROBE		LATCbits.LATC2
#define COMM_READ		TRISD=255
#define COMM_WRITE		TRISD=0
#define SET_PORT		LATD
#define GET_PORT		PORTD

#define USB_LED              LATBbits.LATB0
#define MIDI_LED              LATBbits.LATB1

#define IDLE			0
#define PLAY			1
#define SKIP			2

#define IO_CARD_ID		0x20				// bits 0b00110000 is free for check bits. 00 or 11 could be scrap data.
											// 01 or 10 is suitable
#define DEBUG1			LATEbits.LATE0
#define DEBUG2			LATEbits.LATE1
#define DEBUG3			LATEbits.LATE2

/** INCLUDES *******************************************************/
#include "USB/usb.h"
#include "HardwareProfile.h"
#include "./USB/usb_function_hid.h"
#include <Usart.h>
#include <timers.h>


#include "GenericTypeDefs.h"
#include "Compiler.h"
#include "usb_config.h"
#include "./USB/usb_device.h"
#include "./USB/usb.h"

//#include "mtc.h"							// struct for MTC in data



/** CONFIGURATION **************************************************/
#if defined(PICDEM_FS_USB)      // Configuration bits for PICDEM FS USB Demo Board (based on PIC18F4550)
        #pragma config PLLDIV   = 5         // (20 MHz crystal on PICDEM FS USB board)
        #if (USB_SPEED_OPTION == USB_FULL_SPEED)
            #pragma config CPUDIV   = OSC1_PLL2  
        #else
            #pragma config CPUDIV   = OSC3_PLL4   
        #endif
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


#else
    #error No hardware board defined, see "HardwareProfile.h" and __FILE__
#endif

/** VARIABLES ******************************************************/
// #pragma udata

    //The ReceivedDataBuffer[] and ToSendDataBuffer[] arrays are used as
    //USB packet buffers in this firmware.  Therefore, they must be located in
    //a USB module accessible portion of microcontroller RAM.

//#pragma udata USB_VARIABLES=0x500
//
//#define IN_DATA_BUFFER_ADDRESS_TAG
//#define OUT_DATA_BUFFER_ADDRESS_TAG

//unsigned char hid_report_in[HID_INT_IN_EP_SIZE] IN_DATA_BUFFER_ADDRESS_TAG;

#pragma udata
#pragma udata USB_VARS

// ************************************************************************************************
// New Structs:
// ************************************************************************************************

typedef union {							// USB_OUT_BUF - Host to Device data struct
	struct {							// 
		struct {						// CMD - Command struct
			unsigned CMD_GROUP:4;		// Commands belongs to different groups
			unsigned CMD:4;				// Command
		}CMD;								// CMD ?

		struct {						// MTC_PROP	- MTC Properties struct
			unsigned ID:2;				// Quarter frame ID.
			unsigned FPS:2;				// Frames pper Second ID
			unsigned :4;				//
			unsigned long int POS;		// 32 bit integer with time code position
		}MTC_PROP;
										// Free bytes	
		unsigned char FREE_BYTE;		// Not used yet

		struct {						// SSL_PROP - SSL Properties struct
			unsigned BANK_ID:4;			// Current SSL 8 channel bank in focus
			unsigned BANK_ID_CHANGE:1;	// Flag for change of bank
			unsigned :3;				
		}SSL_PROP;

		unsigned char SSL_DATA[48];		// 2 bytes data for each channel. 24 channels in one packet
		unsigned char MF_DATA[8];		// 2 bytes data ffor each channel. 4 channels in one packet
		
	};
	unsigned char BYTES[64];			// 64 bytes raw data
}USB_OUT_BUF;


// ************************************************************************************************
typedef union {							// USB_IN_BUF - Device to Host data struct
	struct {							// 
		struct {						// CMD - Command struct
			unsigned CMD_GROUP:4;		// Commands belongs to different groups
			unsigned CMD:4;				// Command
		}CMD;								// CMD ?

		struct {						// MTC_PROP	- MTC Properties struct
			unsigned ID:2;				// Quarter frame ID.
			unsigned FPS:2;				// Frames per Second ID
			unsigned RUN:1;				// RUN event flag
			unsigned STOP:1;			// STOP event flag
			unsigned JUMP:1;			// JUMP event flag
			unsigned :1;				// 
			unsigned long int POS;		// 32 bit integer with time code position
		}MTC_PROP;

		struct {						// Free bytes	
		unsigned char FREE_BYTES[2];	// Not used yet
		}FREE;

		unsigned char SSL_DATA[48];		// 2 bytes data for each channel. 24 channels in one packet
		unsigned char MF_DATA[8];		// 2 bytes data for each channel. 4 channels in one packet
		
	};
	unsigned char BYTES[64];			// 64 bytes raw data
}USB_IN_BUF;

// ************************************************************************************************

struct {
	USB_IN_BUF SLOT[4];
}usb_in;


struct {
	USB_OUT_BUF SLOT[4];
}usb_out;

USB_OUT_BUF TEMP_BUF;
unsigned char TempIn[64];

#pragma udata

#pragma udata USB_BUFFER

#pragma udata

unsigned char DataSafe=0;
unsigned char HoldCardBus=0;
unsigned char MidiIn=0;
unsigned char Mode=0;
unsigned char MTC_q_frame = 0;
unsigned char MTC_flag = 0;
unsigned char F1_flag = 0;
unsigned char load_USB_flag = 0;
unsigned char armClock = 0;
unsigned char Clock = 0;
unsigned long MTClongEXT = 0;
unsigned long MTClongINT = 0;
unsigned char FPS = 25;
unsigned char FPScode = 1;
unsigned char OUT_BUFFER_FLIP = 0;
const unsigned char FPS_VAL[] = {24, 25 ,30, 30};
unsigned char appRunning=0;
unsigned char appTmr=0;
unsigned char blinkLED=0;


USB_HANDLE USBOutHandle = 0;
USB_HANDLE USBInHandle = 0;
BOOL blinkStatusValid = FALSE;



BYTE old_sw2,old_sw3;
BOOL emulate_mode;
BYTE movement_length;
BYTE vector = 0;
char buffer[3];
USB_VOLATILE USB_HANDLE lastTransmission = 0;

//The direction that the mouse will move in
ROM signed char dir_table[]={-4,-4,-4, 0, 4, 4, 4, 0};

/** PRIVATE PROTOTYPES *********************************************/
static void InitializeSystem(void);
void ProcessIO(unsigned char);
void UserInit(void);
void YourHighPriorityISRCode();
void YourLowPriorityISRCode();
void USBCBSendResume(void);

void MTC_machine (unsigned char);
void Backplane_Comm (unsigned char);
void Address_MUX (unsigned char);



/** VECTOR REMAPPING ***********************************************/
#if defined(__18CXX)
	//On PIC18 devices, addresses 0x00, 0x08, and 0x18 are used for
	//the reset, high priority interrupt, and low priority interrupt
	//vectors.  However, the Microchip HID bootloader occupies the
	//0x00-0xFFF program memory region.  Therefore, the bootloader code remaps 
	//these vectors to new locations as indicated below.  This remapping is 
	//only necessary if you wish to be able to (optionally) program the hex file 
	//generated from this project with the USB bootloader.  
	#define REMAPPED_RESET_VECTOR_ADDRESS			0x1000
	#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x1008
	#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x1018
	#define APP_VERSION_ADDRESS                     0x1016 //Fixed location, so the App FW image version can be read by the bootloader.
	#define APP_SIGNATURE_ADDRESS                   0x1006 //Signature location that must be kept at blaknk value (0xFFFF) in this project (has special purpose for bootloader).

    //--------------------------------------------------------------------------
    //Application firmware image version values, as reported to the bootloader
    //firmware.  These are useful so the bootloader can potentially know if the
    //user is trying to program an older firmware image onto a device that
    //has already been programmed with a with a newer firmware image.
    //Format is APP_FIRMWARE_VERSION_MAJOR.APP_FIRMWARE_VERSION_MINOR.
    //The valid minor version is from 00 to 99.  Example:
    //if APP_FIRMWARE_VERSION_MAJOR == 1, APP_FIRMWARE_VERSION_MINOR == 1,
    //then the version is "1.01"
    #define APP_FIRMWARE_VERSION_MAJOR  1   //valid values 0-255
    #define APP_FIRMWARE_VERSION_MINOR  0   //valid values 0-99
    //--------------------------------------------------------------------------
	
	#pragma romdata AppVersionAndSignatureSection = APP_VERSION_ADDRESS
	ROM unsigned char AppVersion[2] = {APP_FIRMWARE_VERSION_MINOR, APP_FIRMWARE_VERSION_MAJOR};
	#pragma romdata AppSignatureSection = APP_SIGNATURE_ADDRESS
	ROM unsigned short int SignaturePlaceholder = 0xFFFF;
	
	#pragma code HIGH_INTERRUPT_VECTOR = 0x08
	void High_ISR (void)
	{
	     _asm goto REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS _endasm
	}
	#pragma code LOW_INTERRUPT_VECTOR = 0x18
	void Low_ISR (void)
	{
	     _asm goto REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS _endasm
	}
	extern void _startup (void);        // See c018i.c in your C18 compiler dir
	#pragma code REMAPPED_RESET_VECTOR = REMAPPED_RESET_VECTOR_ADDRESS
	void _reset (void)
	{
	    _asm goto _startup _endasm
	}
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
	
	unsigned int timercnt;	
	unsigned int mtcIdleCntr=0;	
	unsigned char FakeTick=0;
	unsigned char RUN_STATUS = 0;
	unsigned char Idle=1;
	unsigned char IntClockRelease=0;
	unsigned char MTC_in_alert=0;
	unsigned char i=0;
	static unsigned char MidiState=0;
	static unsigned char RUNflag=0;
	
	//These are your actual interrupt handling routines.
	#pragma interrupt YourHighPriorityISRCode
	void YourHighPriorityISRCode()
	{
		static unsigned char LastMidiIn=0;
		static unsigned char FullMTCcntr=0;
													// timer overflow. When MTC in is idle. This is my clock.

	 if(PIR1bits.TMR1IF)
		{
//		MIDI_LED=1;
		mtcIdleCntr++;									// it waits a few clock ticks until it considers the MTC stopped
		if(mtcIdleCntr>3)			
		{
			HoldCardBus=0;
			// Don't know where this is used
			RUN_STATUS = 0;
			// Flag for main loop
			FakeTick=1;
			// lock the cntr
			mtcIdleCntr=3;
			// count Qframe
			MTC_q_frame++;							
			// only use 3 first bits
			MTC_q_frame &= 0x03;
			if(!MTC_q_frame)DataSafe=1;
		}
		else
		{
			if(mtcIdleCntr==3)			
			{
				DataSafe=0;
				// Will roll over to 0 further down
				MTC_q_frame=3;	
				// Flag a STOP Event
				usb_in.SLOT[0].MTC_PROP.STOP=1;
				Mode=IDLE;
				HoldCardBus=1;
				FullMTCcntr=0;
			}
		}
		PIR1bits.TMR1IF = 0;
		TMR1H = 0x40;
		TMR1L = 0x00;
//		MIDI_LED=0;
		}

/*

		0xFE			= Active Sense (Heart beat??)
		
	Full Frame MSG look like this:

		0xF0, 0x7F, = Full frame
		0x7F,		= All channels
		0x01, 0x01,	= Standard
		0bFFHHHHHH,	= F=FPS, H=Hour
		0xMM,		= Minute
		0xSS,		= Second
		0xFF,		= Frame
		0xF7,		= End Of Full Frame
	
		MIDI OX + Edirol MIDI interface starts with a full frame transfer
		then goes to quarter frames.

		Stop condition seem to overlap with active sense command
		Stop can be mad whenever in the Qframe sequence.
*/

	
	if(PIR1bits.RCIF)
	{                      
		MidiIn = ReadUSART();                            					// Read from the MIDI in buffer
/*
		if(MidiIn&0xF0==0xF0)
		{
						 	// Must be a 0xFx
			switch (MidiIn)
			case 0x
		}
		else
		{
		}
*/
		if(MidiState)			// if full frame sysex sequence started
		{	
			mtcIdleCntr=0;
			FakeTick=0;
			HoldCardBus=0;
			if(MidiState<6)
			{
				switch (MidiIn)
				{
					case 0x7F:													// 	0x7F	-> SysEx FullFrame 2nd byte 
						if(MidiState==1)										// Initial 0x7F = Real Time Uni Mess
						{
							MidiState=2;
						}
						if(MidiState==2)										// Second 0x7F = Global Broadcast
						{
							MidiState=3;
						}
						break;
					case 0x01:
						if(MidiState==3)										// Initial 0x01	= Time Code Mess
						{
							MidiState=4;
						}
						if(MidiState==5)										// Second 0x01 = Fullframe Mess
						{
							MidiState=6;
						}
						break;
					case 0xF7:													// 	0x7F	-> SysEx FullFrame 2nd byte 
						{
							MidiState=0;
						}
						break;
				}
			}
			else
			{
				if(MidiState==6)										// Hours
				{
					MidiState=7;
				//	FPScode=(MidiIn&0x60)>>5;
				//	FPScode=3;
				}
				if(MidiState==7)										// Mins
				{
					MidiState=8;
				}
				if(MidiState==8)										// Secs
				{
					MidiState=9;
				}
				if(MidiState==9)										// Frames
				{
					MidiState=10;
				}
				if(MidiIn&0xF0==0xF0)										// Break
				{
					MidiState=0;
				}
			}

		}
		else						// we're not in full frame sequence
		{
			switch (MidiIn)
			{
				case 0xF0:													// 	0xF0	-> SysEx FullFrame 1st byte
					MidiState=1;
					mtcIdleCntr=0;
					FakeTick=0;
					HoldCardBus=0;
					break;
	
				case 0xFE:													// 	0xFE	-> HeartBeat. Toggle LED
					if(Mode!=PLAY)MIDI_LED=0;
					break;
	
				case 0xF1:													// 	0xF1	-> MTC start byte. Data byte follows
					// Clear Idle timer
					mtcIdleCntr=0;
					FakeTick=0;
					load_USB_flag=0;
					//Increase Qframe.
					MTC_q_frame++;
					// only use 3 first bits
					MTC_q_frame &= 0x03;
	
					// Are we in PLAY mode?
					if(Mode==PLAY)
					{
						// Flag for USB in transfer. 
						MTC_flag=1;
						// when it rolls over, increase MTC frame and toggle LED
						if(MTC_q_frame==0)
						{
							MTClongINT++;
							MIDI_LED=!MIDI_LED;
						}
						if(MTC_q_frame==3)DataSafe=1;

						if(RUNflag)
						{
							// Flag a RUN Event
//							usb_in.SLOT[0].MTC_PROP.RUN=1;
//							usb_in.SLOT[1].MTC_PROP.RUN=1;
//							usb_in.SLOT[2].MTC_PROP.RUN=1;
//							usb_in.SLOT[3].MTC_PROP.RUN=1;
							RUNflag=0;
						}
					}
					// IDLE mode...
					else	
					{
						DataSafe=0;
						// IDLE mode. If it's the first start byte -> reset Qframe
						if(FullMTCcntr==0) 
						{
							MTC_q_frame=0;
							HoldCardBus=1; 
						}
						//	Stay in STOP mode
					}
					break;
	
				default:											// All other values
					if(LastMidiIn==0xF1)									// Was last MIDI msg 0xF1?
					{
						if(Mode==PLAY)
						{
							if(((MidiIn)&0x70)==0x70)
							{
							//	MTClongINT=MTClongEXT-1;
		FPScode=(MidiIn&0x06)>>1;
							}
						}
						else
						{
							MTC_machine(MidiIn);
							// Qframe and incomming Qframe match?
							if(FullMTCcntr==0)
							{
								MTC_q_frame=0;
							}
						//	if(MTC_q_frame==((MidiIn>>4)&0x03))
							{					
								// Extract the MIDI data and build the 4 byte word
								// We need 8 sequenced bytes to form a full SMPTE word
								FullMTCcntr++;
								if(FullMTCcntr>7)
								{
									// Go!
									Mode=PLAY;
									HoldCardBus=0;
									// Full word is here. Copy the position to our internal counter
									MTClongINT=MTClongEXT;
									// Flag a RUN Event. Not used !!!
									RUNflag=1;
									usb_in.SLOT[0].MTC_PROP.RUN=1;
								}
							}
							// No match. Reset all and wait for a new match
					//		else
							{
					//			FullMTCcntr=0;MTC_q_frame=0;Mode=IDLE;	// Reset All.
							}
						}
					}
					else 
					{
						FullMTCcntr=0;MTC_q_frame=0;Mode=IDLE;	// Reset All. No recognized message
					}
					break;

			}
		}
		LastMidiIn=MidiIn;
		if(RCSTAbits.OERR) RCSTAbits.CREN=0; 							// clear if error. USART standard stuff..
	} 


        #if defined(USB_INTERRUPT)
            USBDeviceTasks();
        #endif
    
    }   //This return will be a "retfie fast", since this is in a #pragma interrupt section 
    #pragma interruptlow YourLowPriorityISRCode
    void YourLowPriorityISRCode()
    {
        //Check which interrupt flag caused the interrupt.
        //Service the interrupt
        //Clear the interrupt flag
        //Etc.
    
    }   //This return will be a "retfie", since this is in a #pragma interruptlow section 
#elif defined(_PIC14E)
        //These are your actual interrupt handling routines.
    void interrupt ISRCode()
    {
        //Check which interrupt flag caused the interrupt.
        //Service the interrupt
        //Clear the interrupt flag
        //Etc.
            #if defined(USB_INTERRUPT)
                    USBDeviceTasks();
            #endif
    }
#endif





/** DECLARATIONS ***************************************************/
#if defined(__18CXX)
    #pragma code
#endif

/********************************************************************
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

void main(void)
{
    unsigned static char BACKPLANE_FLAG = 0;
	static unsigned char LEDcnt=0;
	unsigned char LockedQframe=0;
	unsigned i,j;
    InitializeSystem();
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB2 = 0;
    TRISCbits.TRISC7 = 1;
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC2 = 0;
    TRISD=0;
	TRISEbits.TRISE0=0;
	TRISEbits.TRISE1=0;
	TRISEbits.TRISE2=0;
    
    TRISB = 0x00;
	LATCbits.LATC2=0;				// Release Strobe !!!


			DEBUG1=0;
			DEBUG2=0;
			DEBUG3=0;

	for(i=0;i<4;i++)
		{
		for(j=0;j<64;j++)
			{
				usb_out.SLOT[i].BYTES[i]=0;              				 // Clear Buffers
				usb_in.SLOT[i].BYTES[i]=0;              				 // Clear Buffers
			}  
		}

    while(1)
    {
	LATCbits.LATC6=1;
	if(FakeTick) 								// when MTC in idle. This is my loop flag.
	{	
		LockedQframe=MTC_q_frame&0x03;
		FakeTick=0;
		BACKPLANE_FLAG=1;		
		load_USB_flag=1;				
		if(MIDI_LED==0)LEDcnt++;
		if(LEDcnt>3){MIDI_LED=1;LEDcnt=0;}
	}
		
	if(MTC_flag)								// when MTC runs. This is my loop flag.
	{
		LockedQframe=MTC_q_frame&0x03;
		MTC_machine(MidiIn);						// put the MTC data in the MTC machine (TradeMark Pelle Gunnerfeldt)
		MTC_flag =0;					
		BACKPLANE_FLAG=1;
		load_USB_flag=1;
/*		if(Clock)							// Frame flag
			{		
			LATBbits.LATB1=1;
				if (MTClongINT != MTClongEXT+1) 			// if not +1 frame. Report.
				{
					usb_in.SLOT[LockedQframe].MTC_PROP.JUMP=1;
	
					MTClongINT=MTClongEXT;				// and correct.
				}
				else
				{
				;
				}
				Clock = 0;
			}
*/
	}

	if(BACKPLANE_FLAG && !HoldCardBus)
	{	
		appTmr++;
		if(appTmr>5)
		{
			appRunning=0;
			appTmr=5;
				for(i=0;i<4;i++)
				{
				for(j=0;j<64;j++)
					{
						usb_out.SLOT[i].BYTES[j]=0;              				 // Clear Buffers
						usb_in.SLOT[i].BYTES[j]=0;              				 // Clear Buffers
					}  
				}
		}
		COMM_STROBE=1;				// Release Strobe !!!
		if(MTC_q_frame==0) blinkLED = !blinkLED;				// toogle LED every frame
		Backplane_Comm(LockedQframe);       // Do system communication
		COMM_STROBE=0;				// Strobe Cards for ACTION !!!
		BACKPLANE_FLAG=0;
	
	}
	

                                // Check bus status and service USB interrupts.
		;
        USBDeviceTasks();       // Interrupt or polling method.  If using polling, must call
                                // this function periodically.  This function will take care
                                // of processing and responding to SETUP transactions 
                                // (such as during the enumeration process when you first
                                // plug in).  USB hosts require that USB devices should accept
                                // and process SETUP packets in a timely fashion.  Therefore,
                                // when using polling, this function should be called 
                                // frequently (such as once about every 100 microseconds) at any
                                // time that a SETUP packet might reasonably be expected to
                                // be sent by the host to your device.  In most cases, the
                                // USBDeviceTasks() function does not take very long to
                                // execute (~50 instruction cycles) before it returns.


		ProcessIO(LockedQframe);				// system data is shuffled in Backplane_Comm() but
/*
	if(BACKPLANE_FLAG)
	{
		BACKPLANE_FLAG=0;			// MTC data is done as well as buffer switching is done in ProcessIO()
	}   
*/    
    }//end while
}//end main



	unsigned char test;

void Backplane_Comm(unsigned char LockedQframe) 
{
    unsigned char i,j,k,l;	
	unsigned char TempIn[64];
	unsigned char card_id=0;
	static unsigned char testCV=0;

// I2C CARD I2C CARD I2C CARD I2C CARD I2C CARD I2C CARD I2C CARD I2C CARD I2C CARD I2C CARD I2C CARD I2C CARD I2C CARD I2C CARD I2C CARD 
/*
	if(LockedQframe==0)
	{

        USBDeviceTasks();
        //MUX
		Address_MUX(12);
        
		MUX_ENABLE=0;                   // Set the MUX address
        COMM_READ;                      // Set parallel port to READ
        for(j=0;j<8;j++)
        {
            ;
        }


        for(i=0;i<4;i++)               // 2 bytes x 2 channels 
        {
      		//      Read PORT
        //    usb_in.SLOT[(MTC_q_frame>>1)+2].MF_DATA[i+((MTC_q_frame&1)<<2)]=GET_PORT;       // Place byte in the appropriate slot
            COMM_CLOCK = 1;      
            //Delay
            for(j=0;j<4;j++)
            {
                ;
            }
            COMM_CLOCK = 0;
        }


       	USBDeviceTasks();
        COMM_WRITE;                                                     // Set port to WRITE
		SET_PORT=MTC_q_frame;											// I2C card must channel no								
        for(j=0;j<2;j++)
        {
            ;
        }

        COMM_CLOCK = 1;                                             // Clock
        //Delay
        for(j=0;j<4;j++)
        {
            ;
        }
        COMM_CLOCK = 0;

       	USBDeviceTasks();
        for(i=0;i<4;i++)                                               // Write 2 x bytes to each card
        {
        //    SET_PORT=usb_out.SLOT[(MTC_q_frame>>1)+2].MF_DATA[i+((MTC_q_frame&1)<<2)];      // Take byte from the right slot 
            SET_PORT=0x55;
            //Delay
            for(j=0;j<2;j++)
            {
                ;
            }

            COMM_CLOCK = 1;                                             // Clock
            //Delay
            for(j=0;j<4;j++)
            {
                ;
            }
            COMM_CLOCK = 0;
        }

        COMM_READ;                      // Set parallel port to READ
        MUX_ENABLE=1;                                                   // Turn off MUX

	}
*/
	// SSL CARDS SSL CARD SSL CARDS SSL CARD SSL CARDS SSL CARD SSL CARDS SSL CARD SSL CARDS SSL CARD SSL CARDS SSL CARD SSL CARDS SSL CARD
	//
	// Called every quarter frame. 3 banks each time




    for(k=0;k<3;k++)													// Each USB packet has 48 bytes for 24 channels (3 banks).
    {
	
        USBDeviceTasks();												// Check USB pipe

																		//MUX the right bank
		Address_MUX((LockedQframe*3)+k);								// Qframe (0-3) * 3 + k(0-2)
        
		MUX_ENABLE=0;													// Strobe the MUX address
        COMM_READ;														// Set parallel port to READ
													
        for(j=0;j<8;j++)												// waitloop to ensure the bank is responding
        {
            ;
        }

        for(i=0;i<16;i++)												// 2 bytes x 8 channels from each card
        {
																		// Read PORT
			TempIn[(k*16)+i]=GET_PORT;									// Store parallel data in TempIn

            COMM_CLOCK = 1;												// Clock
            //Delay
            for(j=0;j<2;j++)											// Wait loop
            {
                ;
            }

            COMM_CLOCK = 0;	
            for(j=0;j<2;j++)											// Wait loop
            {
                ;
            }		
        }																// Repaet 2 x 8 bytes

        COMM_WRITE;                                                     // Set port to Write

        for(i=0;i<16;i++)                                               // Write 2 x bytes to each card
        {
           	SET_PORT=usb_out.SLOT[LockedQframe].BYTES[(k*16)+i+8];      // Take byte from the right slot 
            //Delay
            for(j=0;j<2;j++)
            {
                ;
            }

            COMM_CLOCK = 1;                                             // Clock
            //Delay
            for(j=0;j<4;j++)
            {
                ;
            }
            COMM_CLOCK = 0;
        }

        COMM_READ;																				// Set parallel port to READ

        MUX_ENABLE=1;																	     // Turn off MUX
    }

    for(k=0;k<3;k++)																			// Test for forbidden states to exclude empty ports
    {
        for(i=0;i<8;i++)                                             
		{
			card_id=(TempIn[((k*16)+(i*2)+1)]&0x30)>>4;											// Mask out  card ID and shift it to the end

			if((card_id>>1) == (card_id & 1))													// Bit 4 & 5 have to be either 01 or 10
			{
				usb_in.SLOT[LockedQframe].SSL_DATA[(k*16)+(i*2)]=0;								// clear data if forbidden state
				usb_in.SLOT[LockedQframe].SSL_DATA[(k*16)+(i*2)+1]=0;
			}
			else
			{
				usb_in.SLOT[LockedQframe].SSL_DATA[(k*16)+(i*2)]=TempIn[(k*16)+(i*2)];			// if everything ok, copy data
				usb_in.SLOT[LockedQframe].SSL_DATA[(k*16)+(i*2)+1]=TempIn[(k*16)+(i*2)+1];
			}
		}
	}
/*
			if(LockedQframe==3)			// Copy data to MF slots 1-8
			{
			    for(i=0;i<4;i++)      //                                   
				{
					if((TempIn[33+(i*2)]&0xC0)!=0xC0 && (TempIn[33+(i*2)]&0x30)!=0x30)
					{
						usb_in.SLOT[2].MF_DATA[(i*2)]=TempIn[32+(i*2)];
					//	usb_in.SLOT[3].SSL_DATA[(i*2)+32]=0;
						usb_in.SLOT[2].MF_DATA[(i*2)+1]=TempIn[33+(i*2)];
					//	usb_in.SLOT[3].SSL_DATA[(i*2)+33]=0;
					}
					if((TempIn[41+(i*2)]&0xC0)!=0xC0 && (TempIn[41+(i*2)]&0x30)!=0x30)
					{
						usb_in.SLOT[3].MF_DATA[(i*2)]=TempIn[40+(i*2)];
					//	usb_in.SLOT[3].SSL_DATA[(i*2)+40]=0;
						usb_in.SLOT[3].MF_DATA[(i*2)+1]=TempIn[41+(i*2)];
					//	usb_in.SLOT[3].SSL_DATA[(i*2)+41]=0;
					}
				}
			}
*/
}

                                                                        // MTC structs for unpacking MTC data
/*
union DIGIT_MASKS {
	unsigned char BYTES[5];
	struct {
		unsigned char FRAME_MASK;
		unsigned char SEC_MASK;
		unsigned char MIN_MASK;
		unsigned char HOUR_MASK;
		unsigned char FPS;
	};
}DIGIT_MASKS;
*/
union {
	unsigned char RAW_DATA;
	struct {
		unsigned DATA   :4;
		unsigned MSB    :1;
		unsigned DIGIT  :2;
		unsigned        :1;
	};
	struct {
		unsigned        :1;
		unsigned FPS    :2;
		unsigned        :5;
	};
}MIDI;

typedef struct {
	unsigned DATA		:4;
	unsigned 		:4;
} sLSB;

typedef struct {
	unsigned		:4;
	unsigned DATA 		:4;
} sMSB;

union {
	unsigned char BYTES[4];
	sLSB LSB[4];
	sMSB MSB[4];		
	struct {
		struct {
			unsigned DIGIT	:5;
			unsigned	:3;
		}FRAME;
		struct {
			unsigned DIGIT	:6;
			unsigned	:2;
		}SECOND;
		struct {
			unsigned DIGIT	:6;
			unsigned	:2;
		}MINUTE;
		struct {
			unsigned DIGIT	:5;
			unsigned FPS	:2;
			unsigned	:1;
		}HOUR;
	}DIGITS;
}mtcObject;

// ***********************************************
// *
// *    Function MTC_Machine
// *    IN: 1 byte raw MIDI data
// *    OUT: None
// *    GLOBAL: mtcObject - volatile object
// *            is affected. Holds complete 
// *            time code.
// * 
// ***********************************************

void MTC_machine (unsigned char raw_data)
{
	unsigned long Temp = 0;
	MIDI.RAW_DATA = raw_data;                                       // This struct will unpack MIDI data
	if(MIDI.MSB)                                                    // The MIDI is split into 2 bytes. Checks for MSB
	{
		mtcObject.MSB[MIDI.DIGIT].DATA = MIDI.DATA;             // Puts the data in the right slot in the struct
		if(MIDI.DIGIT==0x01)                                    // Digit=1 and MSB (4th byte)
		{
			MTClongEXT ++;                                  // Increase MTClongEXT (incomming MTC counter)
		}
		if(MIDI.DIGIT==0x03)                                    // on the last byte (8th)
		{
//			FPScode = MIDI.FPS;           // FPS is either 0,1,2 or 3
			MTClongEXT =  mtcObject.DIGITS.FRAME.DIGIT;     // build up the incomming MTC
			Temp = mtcObject.DIGITS.SECOND.DIGIT;                 
			Temp = Temp * FPS;
			MTClongEXT += Temp;
			Temp = mtcObject.DIGITS.MINUTE.DIGIT;
			Temp = Temp * FPS * 60;
			MTClongEXT += Temp;
			Temp = mtcObject.DIGITS.HOUR.DIGIT;
			Temp = Temp * FPS * 3600;
			MTClongEXT += Temp;                             // Full MTC position
			FPS = FPS_VAL[FPScode];       // FPS ?
/*			
			if(!RUN_STATUS)                                         // If not locked yet:
			{
				FPS = FPS_VAL[mtcObject.DIGITS.HOUR.FPS];       // FPS ?
				RUN_STATUS=1;                                   // lock
				MTClongINT=MTClongEXT;                          // sync INT and EXT
			}
*/
		}
	}
	else
	{
		mtcObject.LSB[MIDI.DIGIT].DATA = MIDI.DATA;             // every other byte (0,2,4,6)
	}
}


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

    ADCON1 |= 0x0F;                 // Default all pins to digital
/*
	DIGIT_MASKS.FRAME_MASK 	 = 0b00011111;
	DIGIT_MASKS.SEC_MASK	 = 0b00111111;
	DIGIT_MASKS.MIN_MASK	 = 0b00111111;
	DIGIT_MASKS.HOUR_MASK	 = 0b00011111;
	DIGIT_MASKS.FPS   		 = 0b00000110;
*/
//  The USB specifications require that USB peripheral devices must never source
//  current onto the Vbus pin.  Additionally, USB peripherals should not source
//  current on D+ or D- when the host/hub is not actively powering the Vbus line.
//  When designing a self powered (as opposed to bus powered) USB peripheral
//  device, the firmware should make sure not to turn on the USB module and D+
//  or D- pull up resistor unless Vbus is actively powered.  Therefore, the
//  firmware needs some means to detect when Vbus is being powered by the host.
//  A 5V tolerant I/O pin can be connected to Vbus (through a resistor), and
//  can be used to detect when Vbus is high (host actively powering), or low
//  (host is shut down or otherwise not supplying power).  The USB firmware
//  can then periodically poll this I/O pin to know when it is okay to turn on
//  the USB module/D+/D- pull up resistor.  When designing a purely bus powered
//  peripheral device, it is not possible to source current on D+ or D- when the
//  host is not actively providing power on Vbus. Therefore, implementing this
//  bus sense feature is optional.  This firmware can be made to use this bus
//  sense feature by making sure "USE_USB_BUS_SENSE_IO" has been defined in the
//  HardwareProfile.h file.    
    #if defined(USE_USB_BUS_SENSE_IO)
    tris_usb_bus_sense = INPUT_PIN; // See HardwareProfile.h
    #endif
    
//  If the host PC sends a GetStatus (device) request, the firmware must respond
//  and let the host know if the USB peripheral device is currently bus powered
//  or self powered.  See chapter 9 in the official USB specifications for details
//  regarding this request.  If the peripheral device is capable of being both
//  self and bus powered, it should not return a hard coded value for this request.
//  Instead, firmware should check if it is currently self or bus powered, and
//  respond accordingly.  If the hardware has been configured like demonstrated
//  on the PICDEM FS USB Demo Board, an I/O pin can be polled to determine the
//  currently selected power source.  On the PICDEM FS USB Demo Board, "RA2" 
//  is used for this purpose.  If using this feature, make sure "USE_SELF_POWER_SENSE_IO"
//  has been defined in HardwareProfile - (platform).h, and that an appropriate I/O pin 
//  has been mapped to it.
    #if defined(USE_SELF_POWER_SENSE_IO)
    tris_self_power = INPUT_PIN;    // See HardwareProfile.h
    #endif
    
    UserInit();

    USBDeviceInit();    //usb_device.c.  Initializes USB module SFRs and firmware
                        //variables to known states.
}//end InitializeSystem

/******************************************************************************
 * Function:        void UserInit(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine should take care of all of the demo code
 *                  initialization that is required.
 *
 * Note:            
 *
 *****************************************************************************/

void UserInit(void)
{
    //Initialize all of the LED pins
    mInitAllLEDs();

    // Clear USB handles
    USBOutHandle = 0;
    USBInHandle = 0;

    blinkStatusValid = TRUE;

    // Init MIDI in port with interrupts
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;

    OpenUSART(
        USART_TX_INT_OFF &
        USART_RX_INT_ON &
        USART_CONT_RX &
        USART_ASYNCH_MODE &
        USART_EIGHT_BIT &
        USART_BRGH_HIGH, 95);
    BAUDCONbits.BRG16 =0;

    // Init main Timer
    OpenTimer1(
        T1_16BIT_RW &
        T1_PS_1_2 &
        T1_SOURCE_INT &
        TIMER_INT_ON);

    // Init ports

 // TRISA = 0x40;
    TRISB = 0x00;
    TRISC = 0x00;
    TRISD = 0x00;

	USB_LED=1;
	MIDI_LED=1;

}//end UserInit


/********************************************************************
 * Function:        void ProcessIO(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is a place holder for other user
 *                  routines. It is a mixture of both USB and
 *                  non-USB tasks.
 *
 * Note:            None
 *******************************************************************/
//unsigned char fakeStatus=1;
//unsigned char fakeVca=0;

void ProcessIO(unsigned char LockedQframe)
{   
    unsigned char i, j;
	unsigned char slot;
	
    // USB tasks goes beneath this
/*
    if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) {USB_LED=1;return;}
	USB_LED=blinkLED>>(!appRunning);
*/
	if(load_USB_flag)                                                               // flag for new data to send to host
	{
	    if(!HIDTxHandleBusy(USBInHandle))                                           // if USB>Host buffer is empty
	    {

//			if(LockedQframe>1)
//			{
//			    for(i=0;i<8;i++)      //                                   
//				{
//					usb_in.SLOT[2].MF_DATA[i]=usb_in.SLOT[3].SSL_DATA[i+32];
//					usb_in.SLOT[3].SSL_DATA[i+32]=0;
//					usb_in.SLOT[3].MF_DATA[i]=usb_in.SLOT[3].SSL_DATA[i+40];
//					usb_in.SLOT[3].SSL_DATA[i+40]=0;
//				}
//			}
            usb_in.SLOT[LockedQframe].MTC_PROP.ID = LockedQframe;                        // MTC_q_frame is 2 bit indicator of subframe 4 per frame
            usb_in.SLOT[LockedQframe].MTC_PROP.POS = MTClongINT;                              // 4 x 64 bytes packets are sent to form complete transfer
 //           usb_in.SLOT[LockedQframe].MTC_PROP.FPS = mtcObject.DIGITS.HOUR.FPS;    
           usb_in.SLOT[LockedQframe].MTC_PROP.FPS = FPScode;  
			for(i=0;i<64;i++)
				{
					TempIn[i]=usb_in.SLOT[LockedQframe].BYTES[i];              				 // 
				} 
        	USBInHandle = HIDTxPacket(HID_EP,(BYTE*)&TempIn,64);  // Point to USB>Host buffer
			
			usb_in.SLOT[LockedQframe].MTC_PROP.STOP=0;
			usb_in.SLOT[LockedQframe].MTC_PROP.RUN=0;
			usb_in.SLOT[LockedQframe].MTC_PROP.JUMP=0;
               load_USB_flag=0;   
	    }
	}


    if(!HIDRxHandleBusy(USBOutHandle))                                                  // if guess Host>USB is only busy during transfer
    {   
		appTmr=0;
		slot = TEMP_BUF.BYTES[1]&0x03;													// 2 bits determing packet = 0,1,2 or 3
		appRunning=1;

		for(i=0;i<64;i++)
			{
				usb_out.SLOT[slot].BYTES[i]=TEMP_BUF.BYTES[i];              				 // TEMP_BUF is where Host>USB packets go
			}     
/*
		if(slot==3)
		{
		    for(i=0;i<8;i++)      //                                   
			{
				usb_out.SLOT[3].SSL_DATA[i+32]=usb_out.SLOT[2].MF_DATA[i];
				usb_out.SLOT[3].SSL_DATA[i+40]=usb_out.SLOT[3].MF_DATA[i];
			}
		}   
*/
        if(!HIDRxHandleBusy(USBOutHandle))                                              // Re-arm the OUT endpoint for the next packet
        {
            USBOutHandle = HIDRxPacket(HID_EP,(BYTE*)&TEMP_BUF.BYTES,64);               // Give Host>USB the pointer to TEMP_BUF
        }
    }
 
}//end ProcessIO


void Address_MUX (unsigned char bank)
{
	unsigned char addr_port = LATB & 0x0F;
	LATB = addr_port + (bank<<4);
//LATBbits.LATB4 = bank & 0x01;
//LATBbits.LATB5 = (bank>>1) & 0x01;
//LATBbits.LATB6 = (bank>>2) & 0x01;
//LATBbits.LATB7 = (bank>>3) & 0x01;



}



// ******************************************************************************************************
// ************** USB Callback Functions ****************************************************************
// ******************************************************************************************************
// The USB firmware stack will call the callback functions USBCBxxx() in response to certain USB related
// events.  For example, if the host PC is powering down, it will stop sending out Start of Frame (SOF)
// packets to your device.  In response to this, all USB devices are supposed to decrease their power
// consumption from the USB Vbus to <2.5mA* each.  The USB module detects this condition (which according
// to the USB specifications is 3+ms of no bus activity/SOF packets) and then calls the USBCBSuspend()
// function.  You should modify these callback functions to take appropriate actions for each of these
// conditions.  For example, in the USBCBSuspend(), you may wish to add code that will decrease power
// consumption from Vbus to <2.5mA (such as by clock switching, turning off LEDs, putting the
// microcontroller to sleep, etc.).  Then, in the USBCBWakeFromSuspend() function, you may then wish to
// add code that undoes the power saving things done in the USBCBSuspend() function.

// The USBCBSendResume() function is special, in that the USB stack will not automatically call this
// function.  This function is meant to be called from the application firmware instead.  See the
// additional comments near the function.

// Note *: The "usb_20.pdf" specs indicate 500uA or 2.5mA, depending upon device classification. However,
// the USB-IF has officially issued an ECN (engineering change notice) changing this to 2.5mA for all 
// devices.  Make sure to re-download the latest specifications to get all of the newest ECNs.

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
	

    #if defined(__C30__) || defined __XC16__
        //This function requires that the _IPL level be something other than 0.
        //  We can set it here to something other than 
        #ifndef DSPIC33E_USB_STARTER_KIT
        _IPL = 1;
        USBSleepOnSuspend();
        #endif
    #endif
}



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
	// 10+ milliseconds of wakeup time, after which the device must be 
	// fully back to normal, and capable of receiving and processing USB
	// packets.  In order to do this, the USB module must receive proper
	// clocking (IE: 48MHz clock must be available to SIE for full speed USB
	// operation).  
	// Make sure the selected oscillator settings are consistent with USB 
    // operation before returning from this function.
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
 *******************************************************************/
void USBCBCheckOtherReq(void)
{
    USBCheckHIDRequest();
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
 *******************************************************************/
void USBCBStdSetDscHandler(void)
{
    // Must claim session ownership if supporting this request
}//end


/*******************************************************************
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
 *******************************************************************/
void USBCBInitEP(void)
{
    //enable the HID endpoint
    USBEnableEndpoint(HID_EP,USB_IN_ENABLED|USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
    //Re-arm the OUT endpoint for the next packet
//    USBOutHandle = HIDRxPacket(HID_EP,(BYTE*)&ReceivedDataBuffer,64);
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
 *					function will only be able to wake up the host if
 *                  all of the below are true:
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
 *                  If the host has not armed the device to perform remote wakeup,
 *                  then this function will return without actually performing a
 *                  remote wakeup sequence.  This is the required behavior, 
 *                  as a USB device that has not been armed to perform remote 
 *                  wakeup must not drive remote wakeup signalling onto the bus;
 *                  doing so will cause USB compliance testing failure.
 *                  
 *					This callback should send a RESUME signal that
 *                  has the period of 1-15ms.
 *
 * Note:            This function does nothing and returns quickly, if the USB
 *                  bus and host are not in a suspended condition, or are 
 *                  otherwise not in a remote wakeup ready state.  Therefore, it
 *                  is safe to optionally call this function regularly, ex: 
 *                  anytime application stimulus occurs, as the function will
 *                  have no effect, until the bus really is in a state ready
 *                  to accept remote wakeup. 
 *
 *                  When this function executes, it may perform clock switching,
 *                  depending upon the application specific code in 
 *                  USBCBWakeFromSuspend().  This is needed, since the USB
 *                  bus will no longer be suspended by the time this function
 *                  returns.  Therefore, the USB module will need to be ready
 *                  to receive traffic from the host.
 *
 *                  The modifiable section in this routine may be changed
 *                  to meet the application needs. Current implementation
 *                  temporary blocks other functions from executing for a
 *                  period of ~3-15 ms depending on the core frequency.
 *
 *                  According to USB 2.0 specification section 7.1.7.7,
 *                  "The remote wakeup device must hold the resume signaling
 *                  for at least 1 ms but for no more than 15 ms."
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
    
    //First verify that the host has armed us to perform remote wakeup.
    //It does this by sending a SET_FEATURE request to enable remote wakeup,
    //usually just before the host goes to standby mode (note: it will only
    //send this SET_FEATURE request if the configuration descriptor declares
    //the device as remote wakeup capable, AND, if the feature is enabled
    //on the host (ex: on Windows based hosts, in the device manager 
    //properties page for the USB device, power management tab, the 
    //"Allow this device to bring the computer out of standby." checkbox 
    //should be checked).
    if(USBGetRemoteWakeupStatus() == TRUE) 
    {
        //Verify that the USB bus is in fact suspended, before we send
        //remote wakeup signalling.
        if(USBIsBusSuspended() == TRUE)
        {
            USBMaskInterrupts();
            
            //Clock switch to settings consistent with normal USB operation.
            USBCBWakeFromSuspend();
            USBSuspendControl = 0; 
            USBBusIsSuspended = FALSE;  //So we don't execute this code again, 
                                        //until a new suspend condition is detected.

            //Section 7.1.7.7 of the USB 2.0 specifications indicates a USB
            //device must continuously see 5ms+ of idle on the bus, before it sends
            //remote wakeup signalling.  One way to be certain that this parameter
            //gets met, is to add a 2ms+ blocking delay here (2ms plus at 
            //least 3ms from bus idle to USBIsBusSuspended() == TRUE, yeilds
            //5ms+ total delay since start of idle).
            delay_count = 3600U;        
            do
            {
                delay_count--;
            }while(delay_count);
            
            //Now drive the resume K-state signalling onto the USB bus.
            USBResumeControl = 1;       // Start RESUME signaling
            delay_count = 1800U;        // Set RESUME line for 1-13 ms
            do
            {
                delay_count--;
            }while(delay_count);
            USBResumeControl = 0;       //Finished driving resume signalling

            USBUnmaskInterrupts();
        }
    }
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
BOOL USER_USB_CALLBACK_EVENT_HANDLER(int event, void *pdata, WORD size)
{
    switch(event)
    {
        case EVENT_TRANSFER:
            //Add application specific callback task or callback function here if desired.
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
        case EVENT_CONFIGURED: 
            USBCBInitEP();
            break;
        case EVENT_SET_DESCRIPTOR:
            USBCBStdSetDscHandler();
            break;
        case EVENT_EP0_REQUEST:
            USBCBCheckOtherReq();
            break;
        case EVENT_BUS_ERROR:
            USBCBErrorHandler();
            break;
        case EVENT_TRANSFER_TERMINATED:
            //Add application specific callback task or callback function here if desired.
            //The EVENT_TRANSFER_TERMINATED event occurs when the host performs a CLEAR
            //FEATURE (endpoint halt) request on an application endpoint which was 
            //previously armed (UOWN was = 1).  Here would be a good place to:
            //1.  Determine which endpoint the transaction that just got terminated was 
            //      on, by checking the handle value in the *pdata.
            //2.  Re-arm the endpoint if desired (typically would be the case for OUT 
            //      endpoints).
            break;
        default:
            break;
    }      
    return TRUE; 
}

/** EOF main.c *************************************************/
#endif
