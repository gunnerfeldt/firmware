#include "typedefs.h"
#include "I2C_routine.h"
#include <p18f4520.h>   /* for TRIS and PORT declarations */

#define AUTO_SW  !PORTCbits.RC5
#define TOUCH_SW  !PORTCbits.RC6
#define WRITE_SW  !PORTCbits.RC7
#define MUTE_SW  !PORTAbits.RA4

#pragma udata
unsigned char StoredSwitchBits=0;


#pragma code
//---------------------------------------------------------------------
// scan_switches
//---------------------------------------------------------------------
void Read_Switches(void)
{
	unsigned char SwitchXOR=0;
	Switches PresSwitches;
	Switches RelSwitches;
	Switches SwitchBits;

	SwitchBits.byte=0;
	PresSwitches.byte=0;
	RelSwitches.byte=0;

	SwitchBits.autoSW=AUTO_SW;
	SwitchBits.touchSW=TOUCH_SW;
	SwitchBits.writeSW=WRITE_SW;
	SwitchBits.muteSW=MUTE_SW;

	outbuffer.status=0;
	if(SwitchBits.byte!=StoredSwitchBits) {                            // If previous 8 bits are NOT equal with the current 8 bits:
	    SwitchXOR=SwitchBits.byte^StoredSwitchBits;                    // Create a mask with all changed bits
	    PresSwitches.byte=SwitchBits.byte&SwitchXOR;                        // Mask out all Pressed switches
	    RelSwitches.byte=StoredSwitchBits&SwitchXOR;                    // Mask out all Released Switches

	if(PresSwitches.autoSW)outbuffer.status=0x01;
	if(PresSwitches.touchSW)outbuffer.status=0x02;
	if(PresSwitches.writeSW)outbuffer.status=0x03;
	}
	StoredSwitchBits=SwitchBits.byte;                                // Copy Switch pins til next read
}