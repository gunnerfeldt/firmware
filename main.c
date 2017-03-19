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
  2.5   Initial release of this demo.
  2.7b  Improvements to USBCBSendResume(), to make it easier to use.
  2.9f  Adding new part support
  2.9j  Updates to support new bootloader features (ex: app version 
        fetching).
********************************************************************/

#ifndef MAIN_C
#define MAIN_C

/** INCLUDES *******************************************************/
#include "./USB/usb.h"
#include "HardwareProfile.h"
#include "./USB/usb_function_midi.h"


#include <spi.h>
#include <timers.h>

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
#pragma udata

//The ReceivedDataBuffer[] and ToSendDataBuffer[] arrays are used as
//USB packet buffers in this firmware.  Therefore, they must be located in
//a USB module accessible portion of microcontroller RAM.
#if defined(__18F14K50) || defined(__18F13K50) || defined(__18LF14K50) || defined(__18LF13K50) 
    #pragma udata usbram2
#elif defined(__18F2455) || defined(__18F2550) || defined(__18F4455) || defined(__18F4550)\
    || defined(__18F2458) || defined(__18F2553) || defined(__18F4458) || defined(__18F4553)\
    || defined(__18LF24K50) || defined(__18F24K50) || defined(__18LF25K50)\
    || defined(__18F25K50) || defined(__18LF45K50) || defined(__18F45K50)
    #pragma udata USB_VARIABLES=0x500
#elif defined(__18F4450) || defined(__18F2450)
    #pragma udata USB_VARIABLES=0x480
#else
    #pragma udata
#endif


union INdataUnion {
	unsigned char data[16];
	unsigned int word[8];
	struct{
		unsigned vca_lo:8;
		unsigned vca_hi:2;
		unsigned status:2;
		unsigned id_change_flag:1;
		unsigned blink_flag:1;
		unsigned touchsense:1;
		unsigned mute:1;
	}channel[8];
	struct{
		unsigned :8;
		unsigned cmd:4;
		unsigned flag:1;
		unsigned :3;
	}cmd[8];
	struct{
		unsigned lo_byte:8;
		unsigned :6;
		unsigned hi_byte:2;
	}vcaGroup[8];
};

union OUTdataUnion {
	unsigned char data[16];
	unsigned int word[8];
	struct{
		unsigned vca_lo:8;
		unsigned vca_hi:2;
		unsigned status_press:1;
		unsigned status_release:1;
		unsigned card_id:2;
		unsigned mute_press:1;
		unsigned mute_release:1;
		}channel[8];
	struct{
		unsigned vca_lo:8;
		unsigned vca_hi:2;
		unsigned status:2;
		unsigned touch_press:1;
		unsigned touch_release:1;
		unsigned mute_press:1;
		unsigned mute_release:1;
		}mf[8];
};
union INdataUnion dataToFader;
union OUTdataUnion dataFromFader;

unsigned char ReceivedDataBuffer[64];
unsigned char ToSendDataBuffer[64];

unsigned char flip=0;
USB_AUDIO_MIDI_EVENT_PACKET midiData;
//USB_CHUNK_ARRAY midiDataArray;


#if defined(__18CXX)
    #pragma udata
#endif

USB_HANDLE USBTxHandle = 0;
USB_HANDLE USBRxHandle = 0;


USB_VOLATILE BYTE msCounter;
int cnt=0x00;
int fader_out=0;
unsigned char midiOutFlag = 0;		// 1 when new data is in the midiOutBuffer
unsigned char midiPacketCntr=0;		// Pointer for midiOutBuffer (the buffer must split, only 3 bytes in each packet)
unsigned char midiOutBuffer[16];	// Large buffer to hold whatever needs to be sent.
unsigned char midiOutBufferLen=0;	// Size of midiOutBuffer
unsigned int faderLevel[8];

unsigned char midiTemp[64];


/** PRIVATE PROTOTYPES *********************************************/
void BlinkUSBStatus(void);
BOOL Switch2IsPressed(void);
BOOL Switch3IsPressed(void);
static void InitializeSystem(void);
void ProcessIO(void);
void UserInit(void);
void YourHighPriorityISRCode();
void YourLowPriorityISRCode();
void USBCBSendResume(void);
void parseMidiData(unsigned char, unsigned char, unsigned char, unsigned char);
WORD_VAL ReadPOT(void);

unsigned char * packSpiMessage(USB_AUDIO_MIDI_EVENT_PACKET * midiMessage);

/** VECTOR REMAPPING ***********************************************/
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
unsigned char cntr=0;
unsigned char spiCntr=0;
unsigned char spiFlag=0;

#pragma interrupt YourHighPriorityISRCode
void YourHighPriorityISRCode()
{

	if(PIR1bits.TMR2IF)
	{
		if(cntr==0)
		{
			cntr=252;
			spiFlag=1;
			spiCntr++;
			if(spiCntr>7)spiCntr=0;
		}
		cntr++;
		PIR1bits.TMR2IF=0;
	}
       #if defined(USB_INTERRUPT)
        USBDeviceTasks();
       #endif


}	
#pragma interruptlow YourLowPriorityISRCode
void YourLowPriorityISRCode()
{

}

/** DECLARATIONS ***************************************************/
#pragma code
#endif

unsigned char testArray[64];
unsigned char newFaderData=0;
unsigned char heartbeatFlag=1;
unsigned char heartbeatCntr=0;

unsigned char OutByte1 = 0;
unsigned char OutByte2 = 0;
unsigned char OutByte3 = 0;

unsigned char USBflag=0;
unsigned char channelState=0;
unsigned char currentChannel=0;

/*
				fader[channel_num] = hh; // put hh  hi order 7 bits into lsbs
				fader[channel_num] = fader[channel_num] << 7;  // shift up 7 bits to make room for 7 lsbs
				fader[channel_num] = fader[channel_num] + newchar; // put newchar = ll 7 bits into lsbs 
				fader[channel_num] = fader[channel_num] >>4; // shift back down 4 bits to make 10 bits R justified
*/


void parseMidiData(unsigned char bank, unsigned char data0, unsigned char data1, unsigned char data2)
{
    unsigned char channel;
    static unsigned int hibyte;
    unsigned int lobyte;
    unsigned char message[3];
	static unsigned char lastChannel=0;
    
   if(data0==0xB0)                           // Fader position
    {
        if((data1 & 0xF0) == 0x00 && (data1 & 0x0F) < 0x8)                 // First Fader byte
        {
            channel = (bank*8)+(data1 & 0x07);
            hibyte = data2 & 0x7F;
			faderLevel[channel] = (hibyte << 3);
        }
        if((data1 & 0xF0) == 0x20 && (data1 & 0x0F) < 0x8)             // Second Fader byte
        {
            channel = (bank*8)+(data1 & 0x07);  
            lobyte = data2 & 0x70;
			faderLevel[channel]+=(lobyte >> 4);
			faderLevel[channel]=faderLevel[channel]&0x3ff;
        }
    }
}

void main(void)
{
	static unsigned char testCntr=0;
	static unsigned int testPos=0;
	unsigned char midiFromHostIndex=0;
	unsigned char n=0;

    InitializeSystem();

    #if defined(USB_INTERRUPT)
        USBDeviceAttach();
    #endif

	TRISDbits.TRISD4=0;		// LED

	TRISCbits.TRISC7=0;		// SPI SDO
	TRISBbits.TRISB1=0;		// SPI CLK
	TRISBbits.TRISB0=1;		// SPI SDI

	INTCONbits.GIE = 1;	// Enables interrupts

	OpenTimer2( 	TIMER_INT_ON &
				T2_PS_1_4 &
				T2_POST_1_16 );

	OpenSPI(SPI_FOSC_TMR2, MODE_01, SMPEND); //initialize SPI
		// Frequency for writing to ADC/DAC


    while(1)
    {
        #if defined(USB_POLLING)
		// Check bus status and service USB interrupts.
        USBDeviceTasks(); // Interrupt or polling method.  If using polling, must call
        				  // this function periodically.  This function will take care
        				  // of processing and responding to SETUP transactions 
        				  // (such as during the enumeration process when you first
        				  // plug in).  USB hosts require that USB devices should accept
        				  // and process SETUP packets in a timely fashion.  Therefore,
        				  // when using polling, this function should be called 
        				  // regularly (such as once every 1.8ms or faster** [see 
        				  // inline code comments in usb_device.c for explanation when
        				  // "or faster" applies])  In most cases, the USBDeviceTasks() 
        				  // function does not take very long to execute (ex: <100 
        				  // instruction cycles) before it returns.
        #endif
	



		if(spiFlag)
		{

			switch(spiCntr)
			{
				case 0:		
				break;

				case 1:
					dataToFader.word[0]=faderLevel[0]&0x3ff;
					OutByte1 =dataToFader.data[0]&0b00111111;					// 6 bits from first byte
					OutByte1+=0b01000000;	

					OutByte2 =(dataToFader.data[0]&0b11000000)>>6;				// 2 bits from first byte, shift in place
					OutByte2+=(dataToFader.data[1]&0b00001111)<<2;		// 4 bits from second byte, shift in place
					OutByte2+=0b10000000;

					OutByte3=(dataToFader.data[1]&0b11110000)>>4;			// 4 bits from second byte, shift in place
					OutByte3+=0b11000000;

					WriteSPI(OutByte1);
				break;

				case 2:							
				break;
	
				case 3:							// add sync bits
					WriteSPI(OutByte2);	
				break;
	
				case 4:		
					dataFromFader.data[0]=SSPBUF;
				break;
		
				case 5:
					WriteSPI(OutByte3);
				break;
	
				case 6:				
					dataFromFader.data[1]=SSPBUF;
					newFaderData=1;				
				break;

				case 7:					
					heartbeatCntr++;
					if(heartbeatCntr>30)
					{
						heartbeatFlag=1;
						heartbeatCntr=0;
					}
				break;
			}

USBDeviceTasks();		
			spiFlag=0;
		}

		// Application-specific tasks.
		// Application related code may be added here, or in the ProcessIO() function.
        ProcessIO();
    }//end while
}//end main

static void InitializeSystem(void)
{
   	ADCON1 |= 0x0F;                 // Default all pins to digital

    #if defined(USE_USB_BUS_SENSE_IO)
    tris_usb_bus_sense = INPUT_PIN; // See HardwareProfile.h
    #endif

    #if defined(USE_SELF_POWER_SENSE_IO)
    tris_self_power = INPUT_PIN;	// See HardwareProfile.h
    #endif

    UserInit();

    USBDeviceInit();	//usb_device.c.  Initializes USB module SFRs and firmware
    					//variables to known states.
}//end InitializeSystem

void UserInit(void)
{


    //initialize the variable holding the handle for the last
    // transmission
    USBTxHandle = NULL;
    USBRxHandle = NULL;
}//end UserInit


void ProcessIO(void)
{
	static unsigned int cntr = 0;
	static unsigned char stateCntr = 0;
	int lobyte;
	int hibyte;
	unsigned char * arrayP;
	static unsigned int level=0;
	static unsigned int lastLevel=0;
	unsigned char index=0;
	unsigned char n=0;
	unsigned char channel=0;
	unsigned char midiFromHostIndex=0;


	level = dataFromFader.word[0] & 0x3ff;


	// No need to proceed if USB is not plugged
    if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) return;



    if(!USBHandleBusy(USBRxHandle))
    {
        // MIDI packet received
		mLED_2_Toggle();
	
		USBflag=1;
        //Get ready for next packet (this will overwrite the old data)

		USBRxHandle = USBRxOnePacket(MIDI_EP,(BYTE*)&ReceivedDataBuffer,64);

			mLED_2_Toggle();

			midiFromHostIndex=0;

			while(midiFromHostIndex<64)
			{
				if(ReceivedDataBuffer[midiFromHostIndex]==0x0b)
				{
				//	if(ReceivedDataBuffer[midiFromHostIndex+1]==0xb0)
					{
						if(ReceivedDataBuffer[midiFromHostIndex+2]==0x00)
						{
							parseMidiData(0,0xb0,ReceivedDataBuffer[midiFromHostIndex+2],ReceivedDataBuffer[midiFromHostIndex+3]);
						}
						if(ReceivedDataBuffer[midiFromHostIndex+2]==0x20)
						{
							parseMidiData(0,0xb0,ReceivedDataBuffer[midiFromHostIndex+2],ReceivedDataBuffer[midiFromHostIndex+3]);
						}
					}
				}
				midiFromHostIndex+=4;
			}
				
	}

	if(heartbeatFlag)
	{
		heartbeatFlag=0;
	    midiTemp[0] = 0x0B;
	    midiTemp[1] = 0x90;
	    midiTemp[2] = 0x00;
	    midiTemp[3] = 0x7F;
		index+=4;	
	}

	if(newFaderData)
	{
		newFaderData=0;
		if(dataFromFader.mf[0].touch_press)
		{
	
		    midiTemp[0+index] = 0x0B;
		    midiTemp[1+index] = 0xB0;
		    midiTemp[2+index] = 0x0F;
		    midiTemp[3+index] = 0x00;	//chn
		    midiTemp[4+index] = 0x0B;
		    midiTemp[5+index] = 0xB0;
		    midiTemp[6+index] = 0x2F;
		    midiTemp[7+index] = 0x40;	// touch on
			index+=8;
		}
	
		if(dataFromFader.mf[0].touch_release)
		{
		    midiTemp[0+index] = 0x0B;
		    midiTemp[1+index] = 0xB0;
		    midiTemp[2+index] = 0x0F;
		    midiTemp[3+index] = 0x00;	//chn
		    midiTemp[4+index] = 0x0B;
		    midiTemp[5+index] = 0xB0;
		    midiTemp[6+index] = 0x2F;
		    midiTemp[7+index] = 0x00;	// touch off
			index+=8;
		}

		if(level!=lastLevel)
		{
			dataToFader.word[0]=level;
			midiTemp[0+index] = 0x0B;
			midiTemp[1+index] = 0xB0;
			midiTemp[2+index] = 0x00;
			midiTemp[3+index] = (( level>>3 ) & 0x7F); // 7 msbits into <b6..b0> of hibyte
			midiTemp[4+index] = 0x0B;
			midiTemp[5+index] = 0xB0;
			midiTemp[6+index] = 0x20;
			midiTemp[7+index] = (( level<<4 ) & 0x70) >> 1; // 3 lsbits into b6,b5,b4 of lobyte
			lastLevel=level;
		}
	}


    	if(!USBHandleBusy(USBTxHandle) && midiTemp[0]!=0)
    	{
		for(n=0;n<64;n++)
		{
			ToSendDataBuffer[n]=midiTemp[n];
			midiTemp[n]=0;
		}
        	USBTxHandle = USBTxOnePacket(MIDI_EP,(BYTE*)&ToSendDataBuffer,64);
	}



}




void BlinkUSBStatus(void)
{
    static WORD led_count=0;

    if(led_count == 0)led_count = 10000U;
    led_count--;

    #define mLED_Both_Off()         {mLED_1_Off();mLED_2_Off();}
    #define mLED_Both_On()          {mLED_1_On();mLED_2_On();}
    #define mLED_Only_1_On()        {mLED_1_On();mLED_2_Off();}
    #define mLED_Only_2_On()        {mLED_1_Off();mLED_2_On();}

    if(USBSuspendControl == 1)
    {
        if(led_count==0)
        {
            mLED_1_Toggle();
            if(mGetLED_1())
            {
                mLED_2_On();
            }
            else
            {
                mLED_2_Off();
            }
        }//end if
    }
    else
    {
        if(USBDeviceState == DETACHED_STATE)
        {
            mLED_Both_Off();
        }
        else if(USBDeviceState == ATTACHED_STATE)
        {
            mLED_Both_On();
        }
        else if(USBDeviceState == POWERED_STATE)
        {
            mLED_Only_1_On();
        }
        else if(USBDeviceState == DEFAULT_STATE)
        {
            mLED_Only_2_On();
        }
        else if(USBDeviceState == ADDRESS_STATE)
        {
            if(led_count == 0)
            {
                mLED_1_Toggle();
                mLED_2_Off();
            }//end if
        }
        else if(USBDeviceState == CONFIGURED_STATE)
        {
            if(led_count==0)
            {
                mLED_1_Toggle();
                if(mGetLED_1())
                {
                    mLED_2_Off();
                }
                else
                {
                    mLED_2_On();
                }
            }//end if
        }//end if(...)
    }//end if(UCONbits.SUSPND...)

}//end BlinkUSBStatus




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

    if(msCounter != 0)
    {
        msCounter--;
    }
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
    USBEnableEndpoint(MIDI_EP,USB_OUT_ENABLED|USB_IN_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);

    //Re-arm the OUT endpoint for the next packet
    USBRxHandle = USBRxOnePacket(MIDI_EP,(BYTE*)&ReceivedDataBuffer,64);
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
 *                        int event, void *pdata, WORD size)
 *
 * PreCondition:    None
 *
 * Input:           int event - the type of event
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
    switch( event )
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

