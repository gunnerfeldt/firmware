/* Compile options:  -ml (Large code model) */

//#include <stdio.h>
#include <p18f4520.h>
#include <adc.h>
#include <timers.h>
#include "typedefs.h"
#include <math.h>
// #pragma config WDT = ON
	
/*
 *  IO_card.h
 *  Test
 *
 *  Created by Pelle Gunnerfeldt on 2011-04-12.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

// allocate some resources in ACCESS RAM for speedy access in interrupt routines
// all locations in this section are volatile



#define SWITCH_DATA  			PORTCbits.RC0		// originally RC0. First card changed to RC4. Why didn't RC0 work?
#define SWITCH_LOAD  			LATCbits.LATC1
#define CLOCK_PIN  				LATCbits.LATC2
#define LED_MUTE_DATA  			LATCbits.LATC5
#define LED_LOAD  				LATCbits.LATC6
#define MUTE_LOAD  				LATCbits.LATC7

#define DAC_DATA  				LATBbits.LATB3
#define DAC_LOAD  				LATBbits.LATB4

#define MUTE_IN	  				PORTAbits.RA1		// originally RA1. First card changed to RC3. Why didn't RA1 work?

#define SSP_en          		!PORTBbits.RB0
#define SSP_clk          		PORTBbits.RB1
#define STROBE          		PORTBbits.RB2
#define SSP_write()         	TRISD = 0;
#define SSP_read()         		TRISD = 255;

#define STATUS_MASK				0x0C;
#define MUTE_MASK				0x10;

#define IO_CARD_ID				0x02				// bits 0b00110000 is free for check bits. 00 or 11 could be scrap data.
											// 01 or 10 is suitable

#define STOP_TMR_0				INTCONbits.TMR0IE=0
#define START_TMR_0				INTCONbits.TMR0IF=0;INTCONbits.TMR0IE=1

#define bit_set(var,bitno) ((var) |= 1 << (bitno))
#define bit_clr(var,bitno) ((var) &= ~(1 << (bitno)))
#define testbit_on(data,bitno) ((data>>bitno)&0x01)
#define testbitmask(data,bitmask) ((data&bitmask)==bitmask)

#define bits_on(var,mask) var |= mask
#define bits_off(var,mask) var &= ~0 ^ mask

#define hibyte(x)       (unsigned char)(x>>8)
#define lobyte(x)        (unsigned char)(x & 0xFF)


#pragma udata access volatile_access

union dacUnion {
	struct {
		unsigned fill:2;
		unsigned vca_lo:8;
		unsigned vca_hi:2;
		unsigned address:4;
	}channel[8];
	unsigned int data[8];
};

ram near struct shiftDataStruct {
	unsigned char trimLed;
	unsigned char absLed;
	unsigned char mute;
}shiftData;

union INdataUnion {
	unsigned char data[16];
	unsigned int word[8];
	struct{
		unsigned vca_lo:8;
		unsigned vca_hi:2;
		unsigned status:2;
		unsigned not_used:2;
		unsigned touchsense:1;
		unsigned mute:1;
		}channel[8];
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
};

ram near union INdataUnion INdata;
ram near union INdataUnion INbuffer;
ram near union OUTdataUnion OUTdata;
ram near unsigned int VCAout[8];
ram near unsigned int VCAoutOld[8];

#pragma udata

unsigned char LocalMuteBits = 0; 				// 8 mute bits.
unsigned char SwitchBits = 0; 					// 8 switch bits.
unsigned char StoredSwitchBits = 0; 			// 8 accumulated switch bits.

int VCAoutStep[8];
unsigned int VCAinOld[8];
unsigned int BlinkCnt = 0;
unsigned int status_bits;
unsigned int VCAPassThru[8];
byte BlinkLED = 1;

int adc;				// ADC int
byte adcMSB;			// ADC byte
byte adcLSB;			// ADC byte
byte adcchn = 0;
byte error;

const byte MANUAL =	0x00;
const byte AUTO = 0x04;
const byte TOUCH = 0x08;
const byte WRITE = 0x0C;

const unsigned char TICK_RATE = 8;

byte ShiftOut[5];		// Shift reg data out. LEDs and Motor Disable
						// byte 0 = MOTOR DISABLE
						// bytes 1-4:
						// bit 0 = AUTO LED	channel 7,5,3,1
						// bit 1 = TOUCH LED
						// bit 2 = WRITE LED
						// bit 3 = MUTE LED (inverted)
						// bit 4 = AUTO LED	channel 8,6,4,2
						// bit 5 = TOUCH LED
						// bit 6 = WRITE LED
						// bit 7 = MUTE LED (inverted)
byte ShiftIn;		// Shift reg data in. Switches



BOOL clk_flg = FALSE;

	unsigned long Ltimer;
	unsigned char clk_flag = 0; 
	unsigned char sw[8]; 
	unsigned char MUX[9];
//	unsigned char swbuf[40]; 
	unsigned long blinkcnt; 
	unsigned long cnt; 
	unsigned long Wcnt; 
	unsigned long wCntr; 
	unsigned long cnt1; 
	unsigned long cnt2;
	unsigned long cnt3; 
	unsigned int DACcnt;
	byte LEDword;
	unsigned int LEDcnt;
	unsigned int SWcnt;	
	short long DAClog;
	unsigned int DACval;
	unsigned int DACword;
	unsigned int DACaddr;
	unsigned char doOnce=0;


	unsigned int vca_in;
	unsigned int lo_adc;
	unsigned int hi_adc;
	byte LED_byte;
	unsigned char test=0;

	unsigned int TEST2=0;

	unsigned char WriteToDACflag = 0;
	unsigned char ParallelPortflag = 0;
	unsigned char Q_Frame_Flag = 1;

// *********************************** Prototypes ****************************************
void Init(void);
void Read_ADC(byte);
void Set_Get_VCA(unsigned char);
void Read_Switches(void);
void Set_Mutes_Leds(void);

int PGtoVCA(int);
int VCAtoPG(int);

#pragma code


// *********************************** Interrupts ****************************************

#pragma interrupt YourHighPriorityISRCode

	void YourHighPriorityISRCode()
	{
		unsigned char n, chn;
		unsigned char last_clk=0;
		unsigned char clk=0;
//		OUTdata.data[1]	= 0;
		if (INTCONbits.INT0IF)									// Interrupt flag for RB0
		{
			ClrWdt();
			cnt=0;	
			SSP_write();
			if (!ParallelPortflag)								// Interrupt flag for RB0
			{			

				LATD = OUTdata.data[0];				// Put byte on parallel port
				while(cnt<16)
				{
					while(SSP_clk==0){;}
					cnt++;
					LATD = OUTdata.data[(cnt)];				// Put byte on parallel port
//					LATD = 0;
					while(SSP_clk==1){;}
					if(!SSP_en)break;
				}
				SSP_read();
				while(cnt<32)
				{
					while(SSP_clk==0){;}
					INbuffer.data[cnt-16]=PORTD;			// read and store port in a buffer
					cnt++;
					while(SSP_clk==1){;}
					if(!SSP_en)break;
				}		
				if(cnt==32)ParallelPortflag=1;							// Flag for new data in
			}
			INTCONbits.INT0IF=0;											
		}
		if (INTCON3bits.INT2IF)									// Interrupt flag for RB1
		{
//			Q_Frame_Flag = 1;		
			INTCON3bits.INT2IF = 0;							// Clear interrupt on port RB1		
		}

	if (INTCONbits.TMR0IF)									// Timer base for creating slots in between transfers
		{			
			Q_Frame_Flag = 1;
			INTCONbits.TMR0IF = 0;
		}

	}
	#pragma interruptlow YourLowPriorityISRCode
	void YourLowPriorityISRCode()
	{
	
	}	//This return will be a "retfie", since this is in a #pragma interruptlow section 


#pragma code

// *********************************** Init ****************************************
void Init(void)
{
	ADCON1 = 0b00111110;
	T1CONbits.T1OSCEN=0; 			// Turn off OSC Timer 1 thing. Didn't effect anything after all.ö
	TRISA = 0x01;
	TRISB = 0x07;
	TRISC = 0x09; 	
	TRISD = 0x00;
	TRISE = 0x00;
	
	
    OpenADC(	ADC_FOSC_32     &
				ADC_RIGHT_JUST	&
				ADC_16_TAD,
				ADC_CH0		&
				ADC_INT_OFF		&
				ADC_VREFPLUS_EXT &
				ADC_VREFMINUS_EXT
				, 15 );


	CMCON = 0x07; /* Disable Comparator */

	INTCONbits.GIE = 1;	// Enables Low Prio interrupts
	INTCONbits.PEIE = 1;		// Enables High Prio 
//	RCONbits.IPEN = 1;		// Enables Priorites
	INTCONbits.GIEL = 1;	// Enables Low Prio interrupts
	INTCONbits.GIEH = 1;		// Enables High Prio 

	INTCON2bits.INTEDG0 = 0; // Chip Select is inverted
	INTCON2bits.INTEDG2 = 0; // Strobe too
	INTCONbits.INT0IE = 1; // Bank Select RB0 interrupt - Bank Select
	INTCON3bits.INT2IE = 1; ; // Clock RB2 interrupt - Strobe


	OpenTimer0( TIMER_INT_ON &
	T0_8BIT &
	T0_SOURCE_INT &
	T0_PS_1_128 );		// Frequency for writing to ADC/DAC


	MUX[0]=0x0;
	MUX[1]=0x1;
	MUX[2]=0x3;
	MUX[3]=0x5;
	MUX[4]=0x6;
	MUX[5]=0x7;
	MUX[6]=0x4;
	MUX[7]=0x2;
	MUX[8]=0x0;

}

// *********************************** MAIN ****************************************
void main (void)
{
	unsigned int loopCnt = 0;
	unsigned int addr;
	unsigned int word;
	unsigned char chn,n;
	unsigned char mux_cnt = 0;
	unsigned int ADC_value;
	Init();
 	for(wCntr=0;wCntr<30000;wCntr++)
		{
		;
		}
	while(1)
	{
		if(ParallelPortflag)							// New Data arrived
		{
			for(n=0;n<8;n++)							// loop thru channels
			{
				INdata.word[n]=INbuffer.word[n];		// Copy buffer
			}

			for(chn=0;chn<8;chn++)						// loop thru channels
			{
				VCAout[chn]=1023-(PGtoVCA(INdata.word[chn]&0x3FF));
				ADC_value = VCAtoPG(VCAinOld[chn]);			// convert to linear scale
				OUTdata.channel[chn].vca_lo = ADC_value&0xFF;	// split the WORD
				OUTdata.channel[chn].vca_hi = ADC_value>>8;
				OUTdata.channel[chn].card_id=IO_CARD_ID;
			}
			doOnce=1;									// flag for mute switch reads
			ParallelPortflag=0;							// Clear transfer flag. Buffer is safe to write to
			Read_Switches();
		}

		if(Q_Frame_Flag)						// New Data arrived
		{
			for(n=0;n<8;n++)						// loop thru channels
			{	
				Set_Get_VCA(n);							// Read fader and write to DAC
			}
			Q_Frame_Flag = 0;
			Set_Mutes_Leds();								// write mute and leds
			BlinkCnt++;
			if(BlinkCnt>30)
			{
				BlinkLED=!BlinkLED;
				BlinkCnt=0;
			}
		}

	}
}

// *********************************** Mute & Led out registers ****************************************

void Set_Mutes_Leds(void)
	{
	unsigned char i;

	DAC_LOAD=1;										// Clear all regs
	LED_LOAD=0;
	MUTE_LOAD=0;
	for(i=0;i<8;i++)								// First send Mute data
		{
		LED_MUTE_DATA=testbit_on(LocalMuteBits,i);
//		if(INdata.channel[i].status==0) {			// if Fader is in Manual Input MUTE > Output MUTE
//			LED_MUTE_DATA=OUTdata.channel[i].mute;
//		}
//		else {										// Else. System is in control. Latching
//			LED_MUTE_DATA=INdata.channel[i].mute;
//		}
		CLOCK_PIN=1;
		CLOCK_PIN=0;	
		}
	for(i=0;i<8;i++)	// ABS LED						
		{
		LED_MUTE_DATA=(INdata.channel[7-i].status==3);													// Write is lit only in WRITE STATE
		if(INdata.channel[7-i].touchsense)LED_MUTE_DATA=(BlinkLED&(INdata.channel[7-i].status!=0));		// Write blink when Touch sense is set and not in Manual
		CLOCK_PIN=1;
		CLOCK_PIN=0;	
		}
	for(i=0;i<8;i++) 	// TRIM LED							// Send LED data
		{
		LED_MUTE_DATA=(INdata.channel[7-i].status!=0);		// TRIM LED should lit for all states except manual
		CLOCK_PIN=1;
		CLOCK_PIN=0;	
		}
	MUTE_LOAD=1;																						// Strobe chips
	MUTE_LOAD=0;
	LED_LOAD=1;
	LED_LOAD=0;
	}

// *********************************** ADC and DAC ****************************************
void Set_Get_VCA(unsigned char ch){
	unsigned int loopCnt = 0;
	unsigned int word;
	unsigned int addr;
	unsigned int DACvalue;
	Read_ADC(ch);								// Read the ADC

//	INdata.channel[ch].status=1;				// !!!!!!!!!!!!!!

	if(INdata.channel[ch].status==0) {			// if Fader is in Manual state DAC should copy ADC
		DACvalue = VCAPassThru[ch];			// VCA data still in log form
	}
	else {
		DACvalue = (VCAout[ch]+(VCAoutOld[ch]))/2;	// VCA data from computer
		VCAoutOld[ch]=DACvalue;
	}


	addr = ch+1;								// address for the DAC ( 1 of 8)
	word = (addr<<12)+(DACvalue<<2);			// align the data right

	CLOCK_PIN = 0;								// prepare DAC chip
	DAC_LOAD = 0;
	for(loopCnt=0;loopCnt<16;loopCnt++){		// shift the DATA out
  		DAC_DATA=testbit_on(word,15-loopCnt);
		CLOCK_PIN = 1;
		CLOCK_PIN = 0;
	}
	DAC_LOAD = 1;								// Release the DAC chip

//	}
}

// *********************************** Read Status Switches ****************************************
void Read_Switches(void)
	{
	unsigned char n,m,SwitchXOR,PresSwitches,RelSwitches;
	SwitchBits=0;
	SWITCH_LOAD = 0;
	SWITCH_LOAD = 1;

	for (n=0;n<8;n++){
		OUTdata.channel[n].status_press = 0;					// clear event flag instead of waitloop
		if(SWITCH_DATA)bit_set(SwitchBits,n);					// Set a 1 if pin is 1
		CLOCK_PIN = 1;
		OUTdata.channel[n].status_release = 0;				// clear event flag instead of waitloop
		CLOCK_PIN = 0;
	}

	if(SwitchBits!=StoredSwitchBits) {							// If previous 8 bits are NOT equal with the current 8 bits:
		SwitchXOR=SwitchBits^StoredSwitchBits;					// Create a mask with all changed bits
		PresSwitches=SwitchBits&SwitchXOR;						// Mask out all Pressed switches
		RelSwitches=StoredSwitchBits&SwitchXOR;					// Mask out all Released Switches

		for (n=0;n<8;n++){
			OUTdata.channel[7-n].status_press	= PresSwitches & 1;		// Pack pressed switches in the Struct
			OUTdata.channel[7-n].status_release	= RelSwitches & 1;		// Pack released switches in the Struct
			PresSwitches>>=1;											// Shift right
			RelSwitches>>=1;											// Shift right
		}
	}
	StoredSwitchBits=SwitchBits;								// Copy Switch pins til next read

		
}

//********************************************************************
//
//	P&G to VCA
//	input: int PG
//	output: int VCA
//
//********************************************************************

int PGtoVCA(int PG)
	{
	unsigned int VCA;				//VCA fader value
	unsigned long groundlevel;		//VCA fader value as long
	unsigned long val;				//VCA fader value as long

	if(PG<157)
		{
		val=PG;
		groundlevel=0;
		val=val*3677;
		val=val/1000;
		}
	else
		{
		val=PG-157;
		groundlevel=577;
		val=val*515;
		val=val/1000;
		}
	VCA=val+groundlevel;
	return VCA;
	}

//********************************************************************
//
//	VCA to P&G
//	input: int VCA
//	output: int PG
//
//********************************************************************


int VCAtoPG(int VCA)
	{
	unsigned int PG=0;			//P&G fader value
	unsigned long groundlevel;		//VCA fader value as long
	unsigned long val;		//VCA fader value as long

	if(VCA<577)
		{
		val=VCA;
		groundlevel=0;
		val=val*271;
		val=val/1000;
		}
	else
		{
		val=VCA-577;
		groundlevel=157;
		val=val*1942;
		val=val/1000;
		}
	PG=val+groundlevel;
	return PG;
	}

// *********************************** Start ADC ****************************************
void Start_ADC(void)
	{
	ConvertADC();
	}

// *********************************** Read ADC *****************************************

void Read_ADC(unsigned char chn)
	{
	unsigned int ADC_value;											// Start conversion

/*
	if(doOnce)
	{
		if(OUTdata.channel[chn].mute != MUTE_IN)					// Check for MUTE change
		{
			if(MUTE_IN) OUTdata.channel[chn].mute_press = 1;		// Event flag for mute press
			else		OUTdata.channel[chn].mute_release = 1;		// Event flag for mute release
		}
		else
		{
			OUTdata.channel[chn].mute_press = 0;					// clear event flag
			OUTdata.channel[chn].mute_release = 0;					// clear event flag
		}
		doOnce=0;
	}
	
	OUTdata.channel[chn].mute = MUTE_IN;			// Check for MUTE threshold ( over 6 V )
*/
	while( BusyADC() );								// Wait til ready

	ADC_value = ADRESH;	
	ADC_value = (ADC_value<<8)+ADRESL;				// put the word together

	ADCON0bits.ADON=0;
	TRISAbits.TRISA0 = 0;

	VCAPassThru[chn] = ADC_value;					// Untouched value for manual fader state
	ADC_value = 1023-ADC_value;						// reverse scale
	ADC_value = (ADC_value + VCAinOld[chn])/2;
	VCAinOld[chn] = ADC_value;
	LATE = MUX[chn];
//	LATE = 0;
	TRISAbits.TRISA0 = 1;							// Channel !!!
	ADCON0bits.ADON=1;
	ConvertADC();

	}



