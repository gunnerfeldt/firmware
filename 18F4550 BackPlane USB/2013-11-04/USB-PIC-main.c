/********************************************************************
 FileName:     main.c
 Dependencies: See INCLUDES section
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
  Rev   Date         Description
  1.0   11/19/2004   Initial release
  2.1   02/26/2007   Updated for simplicity and to use common
                     coding style
********************************************************************/

#ifndef USBMOUSE_C
#define USBMOUSE_C

#define NIBBLE_MASK		0b01100000
#define MS_MASK			0b00010000
#define DATA_MASK		0b00001111
#define FPS_MASK		0b00000111
#define	COMM_DIR		LATCbits.LATC6
#define	COMM_CLOCK		LATBbits.LATB3
#define	MUX_ENABLE		LATBbits.LATB2
#define	COMM_STROBE		LATCbits.LATC2
#define COMM_READ		TRISB=1
#define COMM_WRITE		TRISB=0
#define SET_PORT		LATD
#define GET_PORT		PORTD

/** INCLUDES *******************************************************/
#include "GenericTypeDefs.h"
#include "Compiler.h"
#include "usb_config.h"
#include "./USB/usb_device.h"
#include "./USB/usb.h"
#include <Usart.h>
//#include "mtc.h"							// struct for MTC in data
#include <timers.h>

#include "HardwareProfile.h"

#include "./USB/usb_function_hid.h"

/** CONFIGURATION **************************************************/
     // Configuration bits for PICDEM FS USB Demo Board (based on PIC18F4550)
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
#pragma udata
BYTE old_sw2,old_sw3;
BOOL emulate_mode;
BYTE movement_length;
BYTE vector = 0;


#pragma udata USB_VARS


/*******************************************************************************************************
*
* 	Host -> Device. 64 bytes USB buffer Struct 'USB_BUF'
*
* 	Struct 'PROP' - Misc bits
* 	ID 		= 2 bits 	= Quarter frame counter
*	MTC_ERR		= 1 bit		= Error Flag
*	MTC_FPS		= 2 bits	= FPS rate. 0=24, 25, 30D, 30ND
*	CMD		= 3 bits	= Command bits
*
* 	MTC 		= 4 INT32 	= Timecode value. Frame resolution.
*	FLAG		= 3 bytes	= Channel flags for the data. (see note)
*	DATA		= 48 bytes	= Data. 2 bytes for each channel. Only relevant data
*
*	When the data reached it's destination it's used like this. 
*	Similar structure for VCA and motorfaders.
*
*	struct 'DATA' - 2 bytes per channel
*	VCA		= 10 bits	= CV for VCA or the motorfaders
*	STATUS		= 2 bits	= Fader status. Manual, Auto, Touch & Write. Latched values.
*	MOTOR_ON	= 1 bit		= Only used for motor faders. Bypassing motors from software.
*	EVENT		= 1 bit		= Was used to tell a new value was sent. Maybe not used anymore.
*	NOT_USED	= 1 bit
*	MUTE		= 1 bit		= Mute. For both motorfaders and VCA cards, latching 1 = mute. 0 = open.
*
********************************************************************************************************/

typedef struct {
	unsigned char BYTES[64];
}USB_BUF;

/*******************************************************************************************************
* 	Device -> Host. 64 bytes USB buffer Union 'USB_IN_BUF'
*
* 	Struct 'PROP' - Misc bits
* 	ID		= 2 bits 	= Quarter frame counter
*	NOT_USED	= 3 bit	
*	CMD		= 3 bits	= Command bits
*
* 	MTC 		= 4 INT32 	= Timecode value. Frame resolution. Not used. Yet.
*	FLAG		= 3 bytes	= Channel flags for the data. (see note)
*	DATA		= 48 bytes	= Data. 2 bytes for each channel. Only relevant data
*
*	How the data is packed from VCA cards & motor fader card. 
*	Similar structure for VCA and motorfaders.
*
*	struct 'DATA' - 2 bytes per channel
*	VCA		= 10 bits	= CV for VCA or the motorfaders
*	STATUS		= 2 bits	= Status switches momentary. Idle, Auto, Touch & Write buttons.
*							  For the SSL channels just the first bit is used. Only one button there.
*	TOUCH_SENSE	= 1 bit		= Only used for motor faders. Fader knob touch sensor.
*	EVENT		= 1 bit		= Was used to tell a new value was sent. Maybe not used anymore.
*	NOT_USED	= 1 bit
*	MUTE		= 1 bit		= Mute. Latched value from SSL. Momentary from motorfaders.
*
********************************************************************************************************/


/*******************************************************************************************************
*
*	note: FLAG
*	3 bytes holding an array of 24 flags representing channels on the SSL.
*	An idea for optimizing data flow. Let me explain:
*	If channel '1' on the SSL is sending data it will FLAG bit 0 in the array. And
*	only fill the first two bytes with data. 
*	So my encoder/decoder scan thru the bits and shuffle the data accordingly.
*	Maybe overkill but ...
*
********************************************************************************************************/




typedef union {
	struct {
		struct {
			unsigned ID:2;
			unsigned MTC_ERR:1;
			unsigned MTC_FPS:2;
			unsigned CMD:3;
		}PROP;
		unsigned long int MTC;
		unsigned char FLAG[3];
		unsigned char DATA[48];
	};
	unsigned char BYTES[64];
}USB_IN_BUF;


struct {
	USB_IN_BUF SLOT[4];
}usb_in;


struct {
	USB_BUF SLOT[4];
}usb_out;
	USB_BUF TEMP_BUF;

#pragma udata

#pragma udata USB_BUFFER

#pragma udata

unsigned char MTC_q_frame = 0;
unsigned char MTC;
unsigned char MTC_flag = 0;
unsigned char F1_flag = 0;
unsigned char load_USB_flag = 0;
unsigned char armClock = 0;
unsigned char Clock = 0;
unsigned long MTClongEXT = 0;
unsigned long MTClongINT = 0;
unsigned char FPS = 30;
unsigned char OUT_BUFFER_FLIP = 0;
const unsigned char FPS_VAL[] = {24, 25 ,30, 30};


USB_HANDLE USBOutHandle = 0;
USB_HANDLE USBInHandle = 0;
BOOL blinkStatusValid = TRUE;

/** PRIVATE PROTOTYPES *********************************************/

static void InitializeSystem(void);
void ProcessIO(void);
void UserInit(void);
void YourHighPriorityISRCode();
void YourLowPriorityISRCode();
void MTC_machine (unsigned char);
void Backplane_Comm (void);

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
	
	#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)
		#define REMAPPED_RESET_VECTOR_ADDRESS			0x1000
		#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x1008
		#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x1018
	#elif defined(PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER)	
		#define REMAPPED_RESET_VECTOR_ADDRESS			0x800
		#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x808
		#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x818
	#else	
		#define REMAPPED_RESET_VECTOR_ADDRESS			0x00
		#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x08
		#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x18
	#endif
	
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
	
	#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)||defined(PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER)
	//Note: If this project is built while one of the bootloaders has
	//been defined, but then the output hex file is not programmed with
	//the bootloader, addresses 0x08 and 0x18 would end up programmed with 0xFFFF.
	//As a result, if an actual interrupt was enabled and occured, the PC would jump
	//to 0x08 (or 0x18) and would begin executing "0xFFFF" (unprogrammed space).  This
	//executes as nop instructions, but the PC would eventually reach the REMAPPED_RESET_VECTOR_ADDRESS
	//(0x1000 or 0x800, depending upon bootloader), and would execute the "goto _startup".  This
	//would effective reset the application.
	
	//To fix this situation, we should always deliberately place a 
	//"goto REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS" at address 0x08, and a
	//"goto REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS" at address 0x18.  When the output
	//hex file of this project is programmed with the bootloader, these sections do not
	//get bootloaded (as they overlap the bootloader space).  If the output hex file is not
	//programmed using the bootloader, then the below goto instructions do get programmed,
	//and the hex file still works like normal.  The below section is only required to fix this
	//scenario.
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
	#endif	//end of "#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)||defined(PROGRAMMABLE_WITH_USB_LEGACY_CUSTOM_CLASS_BOOTLOADER)"

	#pragma code
	
	unsigned int timercnt;	
	unsigned int mtcIdleCntr=0;	
	unsigned char FakeTick=0;
	unsigned char RUN_STATUS = 0;


	//These are your actual interrupt handling routines.
	#pragma interrupt YourHighPriorityISRCode
	

	
	void YourHighPriorityISRCode()
	{
													// timer overflow. When MTC in is idle. This is my clock.

	 if(PIR1bits.TMR1IF)
		{
		mtcIdleCntr++;									// it waits a few clock ticks until it considers the MTC stopped
		if(mtcIdleCntr>7)
		{
			RUN_STATUS = 0;
			FakeTick=1;
			mtcIdleCntr=7;
			MTC_q_frame++;								// still count the quarter frame ID
			if(MTC_q_frame>3) MTC_q_frame=0;
		}
		PIR1bits.TMR1IF = 0;
		TMR1H = 0x40;
		TMR1L = 0x00;
		}


														// if new MIDI data
	 if(PIR1bits.RCIF)
		{
                                                    	// Read from the MIDI in buffer
			MTC = ReadUSART();
                                                    	// Look for MTC status byte (0xF1 = MTC standard)
			if (MTC==0xF1)
			{                                           // reset the idle timer threshold counter.
				mtcIdleCntr = 0;
                                                    	// I want to flag the clock on the first byte on the first quarter frame
				if(armClock)                        	// If the Previous byte was the last in a 4 byte sequence
                {                   					// I arm the clock then
					armClock=0;
					MTClongINT++;                   	// I have an internal MTC counting so I don't need to evaluate
					Clock=1;                        	// the MTC data here in my interrupt code
					MTC_q_frame = 0;
				}
				F1_flag=1;                          	// Status byte flag is set.
			}
			else
			{
														// if last byte was the MTC status byte. Probably was. But other MIDI
				if(F1_flag)								// could be mixed in as well
				{
														// check for the fourth quarter byte to arm the clock pulse
					if((MTC & 0x30) == 0x30)armClock = 1;
														// flag for MTC decoder (to be able to turn of modules
					MTC_flag = 1;						// when debugging)
														// Increase Quarter Frame Counter
					MTC_q_frame++;
				}
			F1_flag = 0;								// reset F1 status byte
			}

		if(RCSTAbits.OERR) RCSTAbits.CREN=0; 			// clear if error. USART standard stuff..
		}                                               // This is the over flow bit
	
	}	//This return will be a "retfie fast", since this is in a #pragma interrupt section 
	#pragma interruptlow YourLowPriorityISRCode
	void YourLowPriorityISRCode()
	{

	
	}	//This return will be a "retfie", since this is in a #pragma interruptlow section 


#endif //of "#if defined(__18CXX)"




/** DECLARATIONS ***************************************************/
#pragma code

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
    unsigned char BACKPLANE_FLAG = 0;
    InitializeSystem();
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB2 = 0;
    TRISCbits.TRISC7 = 1;
    TRISD=0;
    
    while(1)
    {

	if(FakeTick) 								// when MTC in idle. This is my loop flag.
	{	
		FakeTick=0;
		if(MTC_q_frame==0) mLED_1_Toggle();				// toogle LED every frame
		load_USB_flag=1;						// debugging
		BACKPLANE_FLAG=1;						// debugging
	}
		
	if(MTC_flag)								// when MTC runs. This is my loop flag.
	{
		MTC_machine(MTC);						// put the MTC data in the MTC machine (TradeMark Pelle Gunnerfeldt)
		MTC_flag =0;
		load_USB_flag=1;									
		BACKPLANE_FLAG=1;
		if(Clock)							// Frame flag
		{	
			mLED_1_Toggle();					// Toggle LED
			if (MTClongINT != MTClongEXT+1) 			// if not +1 frame. Report.
			{
				usb_in.SLOT[MTC_q_frame].PROP.MTC_ERR=1;

				MTClongINT=MTClongEXT;				// and correct.
//				mLED_1_On();
			}
			else
			{
				usb_in.SLOT[MTC_q_frame].PROP.MTC_ERR=0;
//				mLED_1_Off();
			}
			Clock = 0;
		}
	}
	if(BACKPLANE_FLAG)
	{
		Backplane_Comm();       // Do system communication
	}
	

                                // Check bus status and service USB interrupts.

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


	if(BACKPLANE_FLAG)
	{
		ProcessIO();				// system data is shuffled in Backplane_Comm() but
		BACKPLANE_FLAG=0;			// MTC data is done as well as buffer switching is done in ProcessIO()
	}


//        ProcessIO();       
    }//end while
}//end main


void Backplane_Comm(void) {

    unsigned char i,j,k,l;	
    for(k=0;k<3;k++)                        // USB Packets are 64 bytes. 4 x 64 bytes.
    {
        //MUX
        MUX_ENABLE=1;                   // Set the MUX address
        COMM_READ;                      // Set parallel port to READ
        COMM_DIR=1;                     // This is not used (yet)
        for(i=0;i<16;i++)               // 2 bytes x 8 channels from each card
        {
            //Read PORT
            usb_in.SLOT[MTC_q_frame].BYTES[(k*16)+i+16]=GET_PORT;       // Place byte in the appropriate slot
            usb_in.SLOT[MTC_q_frame].BYTES[(k*16)+i+16]=(k*16)+i+16;    // Dummy thing. Debugging
            COMM_CLOCK = 1;                                             // Clock
            //Delay
            for(j=0;j<5;j++)
            {
                ;
            }
            COMM_CLOCK = 0;
        }
        COMM_WRITE;                                                     // Set port to WRITE
        COMM_DIR=0;                                                     // Not used
        for(i=0;i<16;i++)                                               // Write 2 x bytes to each card
        {
            SET_PORT=usb_out.SLOT[MTC_q_frame].BYTES[(k*16)+i+16];      // Take byte from the right slot
            COMM_CLOCK = 1;                                             // Clock
            //Delay
            for(j=0;j<5;j++)
            {
                ;
            }
            COMM_CLOCK = 0;
        }
        MUX_ENABLE=0;                                                   // Turn off MUX
    }

}

                                                                        // MTC structs for unpacking MTC data

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
			mtcObject.DIGITS.HOUR.FPS = MIDI.FPS;           // FPS is either 0,1,2 or 3
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
			
			if(!RUN_STATUS)                                         // If not locked yet:
			{
				FPS = FPS_VAL[mtcObject.DIGITS.HOUR.FPS];       // FPS ?
				RUN_STATUS=1;                                   // lock
				MTClongINT=MTClongEXT;                          // sync INT and EXT
			}
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

	DIGIT_MASKS.FRAME_MASK 	 = 0b00011111;
	DIGIT_MASKS.SEC_MASK	 = 0b00111111;
	DIGIT_MASKS.MIN_MASK	 = 0b00111111;
	DIGIT_MASKS.HOUR_MASK	 = 0b00011111;
	DIGIT_MASKS.FPS   		 = 0b01100000;
    
//	The USB specifications require that USB peripheral devices must never source
//	current onto the Vbus pin.  Additionally, USB peripherals should not source
//	current on D+ or D- when the host/hub is not actively powering the Vbus line.
//	When designing a self powered (as opposed to bus powered) USB peripheral
//	device, the firmware should make sure not to turn on the USB module and D+
//	or D- pull up resistor unless Vbus is actively powered.  Therefore, the
//	firmware needs some means to detect when Vbus is being powered by the host.
//	A 5V tolerant I/O pin can be connected to Vbus (through a resistor), and
// 	can be used to detect when Vbus is high (host actively powering), or low
//	(host is shut down or otherwise not supplying power).  The USB firmware
// 	can then periodically poll this I/O pin to know when it is okay to turn on
//	the USB module/D+/D- pull up resistor.  When designing a purely bus powered
//	peripheral device, it is not possible to source current on D+ or D- when the
//	host is not actively providing power on Vbus. Therefore, implementing this
//	bus sense feature is optional.  This firmware can be made to use this bus
//	sense feature by making sure "USE_USB_BUS_SENSE_IO" has been defined in the
//	HardwareProfile.h file.    
    #if defined(USE_USB_BUS_SENSE_IO)
    tris_usb_bus_sense = INPUT_PIN; // See HardwareProfile.h
    #endif
    
//	If the host PC sends a GetStatus (device) request, the firmware must respond
//	and let the host know if the USB peripheral device is currently bus powered
//	or self powered.  See chapter 9 in the official USB specifications for details
//	regarding this request.  If the peripheral device is capable of being both
//	self and bus powered, it should not return a hard coded value for this request.
//	Instead, firmware should check if it is currently self or bus powered, and
//	respond accordingly.  If the hardware has been configured like demonstrated
//	on the PICDEM FS USB Demo Board, an I/O pin can be polled to determine the
//	currently selected power source.  On the PICDEM FS USB Demo Board, "RA2" 
//	is used for	this purpose.  If using this feature, make sure "USE_SELF_POWER_SENSE_IO"
//	has been defined in HardwareProfile.h, and that an appropriate I/O pin has been mapped
//	to it in HardwareProfile.h.
    #if defined(USE_SELF_POWER_SENSE_IO)
    tris_self_power = INPUT_PIN;	// See HardwareProfile.h
    #endif
    
    USBDeviceInit();	//usb_device.c.  Initializes USB module SFRs and firmware
    					//variables to known states.
    UserInit();

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
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB3 = 0;
    TRISCbits.TRISC2 = 0;
    TRISCbits.TRISC6 = 0;


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
void ProcessIO(void)
{   
    unsigned char i, j;
	
    // USB tasks goes beneath this
    if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) return;

	if(load_USB_flag)                                                               // flag for new data to send to host
	{
	    if(!HIDTxHandleBusy(USBInHandle))                                           // if USB>Host buffer is empty
	    {
                usb_in.SLOT[MTC_q_frame].PROP.ID = MTC_q_frame;                         // MTC_q_frame is 2 bit indicator of subframe 4 per frame
                usb_in.SLOT[MTC_q_frame].MTC = MTClongINT;                              // 4 x 64 bytes packets are sent to form complete transfer
                usb_in.SLOT[MTC_q_frame].PROP.MTC_FPS = FPS;                            
	        USBInHandle = HIDTxPacket(HID_EP,(BYTE*)&usb_in.SLOT[MTC_q_frame],64);  // Point to USB>Host buffer
                load_USB_flag=0;                                                        // Clear flag
//              mLED_1_Toggle();
	    }
	}

    if(!HIDRxHandleBusy(USBOutHandle))                                                  // if guess Host>USB is only busy during transfer
    {   
        usb_out.SLOT[TEMP_BUF.BYTES[0]]=TEMP_BUF;                                       // TEMP_BUF is where Host>USB packets go
        if(!HIDRxHandleBusy(USBOutHandle))                                              // Re-arm the OUT endpoint for the next packet
        {
            USBOutHandle = HIDRxPacket(HID_EP,(BYTE*)&TEMP_BUF.BYTES,64);               // Give Host>USB the pointer to TEMP_BUF
        }
    }
 
}//end ProcessIO




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
        TRISA &= 0xFF3F;
        LATAbits.LATA6 = 1;
        Sleep();
        LATAbits.LATA6 = 0;
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
            LATAbits.LATA7 = 1;
        
            IEC5bits.USB1IE = 0;
            U1OTGIEbits.ACTVIE = 0;
            IFS5bits.USB1IF = 0;
        
            //USBClearInterruptFlag(USBActivityIFReg,USBActivityIFBitNum);
            USBClearInterruptFlag(USBIdleIFReg,USBIdleIFBitNum);
            //USBSuspendControl = 0;
            LATAbits.LATA7 = 0;
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
    USBOutHandle = HIDRxPacket(HID_EP,(BYTE*)&TEMP_BUF.BYTES,64);
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


/** EOF main.c *************************************************/
#endif
