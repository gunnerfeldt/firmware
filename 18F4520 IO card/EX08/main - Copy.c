/* Compile options:  -ml (Large code model) */

//#include <stdio.h>
#include <p18f4520.h>
#include <adc.h>
#include <timers.h>
#include "typedefs.h"
#include <math.h>
#pragma config WDT = OFF
	
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



#define SWITCH_DATA  			PORTCbits.RC0
#define SWITCH_LOAD  			LATCbits.LATC1
#define CLOCK_PIN  				LATCbits.LATC2
#define LED_MUTE_DATA  			LATCbits.LATC5
#define LED_LOAD  				LATCbits.LATC6
#define MUTE_LOAD  				LATCbits.LATC7

#define DAC_DATA  				LATBbits.LATB3
#define DAC_LOAD  				LATBbits.LATB4

#define MUTE_IN	  				PORTAbits.RA1
#define MUX_0	  				LATEbits.LATE0
#define MUX_1	  				LATEbits.LATE1
#define MUX_2	  				LATEbits.LATE2

#define SSP_en          		!PORTBbits.RB0
#define SSP_clk          		PORTBbits.RB1
#define SSP_write()         	TRISD = 0;
#define SSP_read()         		TRISD = 255;

#define STATUS_MASK				0x0C;
#define MUTE_MASK				0x10;



#define MANUAL_LED_EVEN			0b11011111;
#define AUTO_LED_EVEN 			0b11101111;
#define TOUCH_LED_EVEN 			0b11011111;
#define WRITE_LED_EVEN 			0b11011111;
#define MANUAL_LED_ODD			0b11111111;
#define AUTO_LED_ODD 			0b11111110;
#define TOUCH_LED_ODD 			0b11111101;
#define WRITE_LED_ODD 			0b11111011;


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

union IOdataUnion {
	unsigned char data[16];
	struct{
		unsigned vca_lo:8;
		unsigned vca_hi:2;
		unsigned status:2;
		unsigned not_used_1:1;
		unsigned event:1;
		unsigned blink:1;
		unsigned mute:1;
		}channel[8];
//		unsigned char check[8];
};

ram near union IOdataUnion INdata;
ram near union IOdataUnion OUTdata;
ram near unsigned int VCAout[7];
ram near unsigned int VCAoutStep[7];
#pragma udata
unsigned int BlinkCnt = 0;
unsigned int status_bits;
// unsigned char VCAPassThruLo[7];
// unsigned char VCAPassThruHi[7];
unsigned int VCAPassThru[7];
byte BlinkLED = 1;
unsigned int DAC_steps = 0;
unsigned int DAC_step_cntr = 0;
unsigned int clock_cntr = 0;
unsigned char DAC_update = 0;

int adc;				// ADC int
byte adcMSB;			// ADC byte
byte adcLSB;			// ADC byte
byte adcchn = 0;
byte error;

const byte MANUAL =	0x00;
const byte AUTO = 0x04;
const byte TOUCH = 0x08;
const byte WRITE = 0x0C;

const int GOAL_SHIFT = 3;
const unsigned char DAC_RATE = 8;

byte BankTemp[24];		// data to shuffle in/out
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
	unsigned char sw[7]; 
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

	float log_ratio;
	float exp1;
//	float vca;
	float linear;

	unsigned int vca_in;
	unsigned long adc_value;
	unsigned float adc_float;
	unsigned int lo_adc;
	unsigned int hi_adc;
	byte LED_byte;
	unsigned char test=0;

	unsigned char WriteToDACflag = 0;
	unsigned char ParallelPortflag = 0;

// Prototypes


void Scan_Parallell_Port(void);
void Init(void);
void mux(byte);
void Start_ADC(byte);
void Read_One_ADC(byte);
void Error(void);
void vca_in_out(unsigned char);
void switches_and_leds(void);
void mutes_leds(void);

int PGtoVCA(int);
int VCAtoPG(int);

#pragma code

	#pragma interrupt YourHighPriorityISRCode
	void YourHighPriorityISRCode()
	{
		unsigned char n;
		if (INTCONbits.INT0IF)	
		{
			cnt=0;											// reset counter
		//	clk_flag=0;										// flag for Lo/Hi trans
			SSP_write();
			while(cnt<32)									// 32 clock pulses
			{
				if(cnt<16)								// first 16 pulses = read
				{			
				//	if(cnt<1)SSP_write();						// write !!!!!!!!	
					
				//	LATD = OUTdata.data[cnt];
					LATD = INdata.data[cnt];
				//	LATD = test;

				}
				else
				{
					BankTemp[cnt-16]=PORTD;					// read and store port
				}

				if(SSP_clk == 1 && clk_flag == 0)			// Clock rise
					{
					clk_flag = 1;
					cnt++;									// count up
					if(cnt==16)SSP_read();
					}		
				if(SSP_clk == 0)						// clock hi to lo reset
					{
					clk_flag=0;
					}
			}

				SSP_read();
		
					error = 0;	
					
					for(cnt=0;cnt<16;cnt++)
						{
						INdata.data[cnt]=BankTemp[cnt];
						}
					for(n=0;n<8;n++)
						{		
						VCAout[n] = INdata.channel[n].vca_hi;
						VCAout[n] = (VCAout[n]<<8)+INdata.channel[n].vca_lo;
						}
		//			INTCONbits.GIE=1;
		//			test++;
					ParallelPortflag=1;
		
				INTCONbits.INT0IF = 0;
		}
	if (INTCONbits.TMR0IF)	
		{			
			clock_cntr++;
			DAC_step_cntr++;
			if(DAC_step_cntr>=(DAC_steps))
			{
				DAC_step_cntr=0;
				if(!SSP_en) DAC_update=1;
			}
			INTCONbits.TMR0IF = 0;
		}

	}
	#pragma interruptlow YourLowPriorityISRCode
	void YourLowPriorityISRCode()
	{
	
	}	//This return will be a "retfie", since this is in a #pragma interruptlow section 


void Init(void)
{
	TRISA = 0x0F;
	TRISB = 0x03;
	TRISC = 0x01; 	
	TRISD = 0x00;
	TRISE = 0x00;
	

    OpenADC(	ADC_FOSC_16     &
				ADC_RIGHT_JUST	&
				ADC_4_TAD,
				ADC_CH0		&
				ADC_INT_OFF		&
				ADC_VREFPLUS_EXT &
				ADC_VREFMINUS_EXT
				, 15 );

	INTCONbits.GIE = 1;	// Enables Low Prio interrupts
	INTCONbits.PEIE = 1;		// Enables High Prio 
//	RCONbits.IPEN = 1;		// Enables Priorites
	INTCONbits.GIEL = 1;	// Enables Low Prio interrupts
	INTCONbits.GIEH = 1;		// Enables High Prio 
//	INTCON2bits.TMR0IP = 0; // ADC/DAC timer i low prio

	INTCON2bits.INTEDG0 = 0; // Chip Select is inverted
	INTCONbits.INT0IE = 1; // parallell port interrupt


	OpenTimer0( TIMER_INT_ON &
	T0_8BIT &
	T0_SOURCE_INT &
	T0_PS_1_16 );		// Frequency for writing to ADC/DAC








}

void main (void)
	{
	unsigned int loopCnt = 0;
	unsigned int addr;
	unsigned int word;
	unsigned char n;
	unsigned char mux_cnt = 0;
	Init();
 	for(wCntr=0;wCntr<30000;wCntr++)
		{
		;
		}
	adcchn = 0;
	test=0;
	while(1)
		{

		if(ParallelPortflag == 1)
			{

			DAC_steps=(clock_cntr/DAC_RATE);			// Store steps to use in filter
			clock_cntr=0;					// reset counter
			DAC_step_cntr=6;
			ParallelPortflag=0;
//			switches_and_leds();

			for(n=0;n<8;n++)
				{	
				VCAout[n]=PGtoVCA(VCAout[n]);	
				vca_in_out(n);
				}
			mutes_leds();

			}

		if(DAC_update)
			{
				DAC_update=0;
			}

			// SET MUX !!!!!!!
//			mux(mux_cnt);		
//			mux_cnt++;
//			if(mux_cnt==8) mux_cnt = 0;

		}
	}

void mutes_leds(void)
	{
	unsigned char i;

//	SWITCH_LOAD=1;
	DAC_LOAD=1;
	LED_LOAD=0;
	MUTE_LOAD=0;

	for(i=0;i<8;i++)
		{
		LED_MUTE_DATA=INdata.channel[i].mute;
		CLOCK_PIN=1;
		CLOCK_PIN=0;	
		}
	for(i=0;i<16;i++)
		{
		LED_MUTE_DATA=0;
		CLOCK_PIN=1;
		CLOCK_PIN=0;	
		}
	LED_LOAD=1;
	MUTE_LOAD=1;
	MUTE_LOAD=0;
	}
void vca_in_out(unsigned char mux_cnt)
	{
	unsigned int loopCnt = 0;
	unsigned int word;
	unsigned int addr;
	unsigned int GOAL;

		if(INdata.channel[mux_cnt].status==0)
			{
			GOAL = VCAPassThru[mux_cnt];
			}
		else
			{
			// Low Pass For USB to FADER
			GOAL = VCAout[mux_cnt];
			}
			GOAL = VCAout[mux_cnt];
		addr = mux_cnt+1;	
		word = (addr<<12)+(GOAL<<2);
		CLOCK_PIN = 0;
		DAC_LOAD = 0;
		for(loopCnt=0;loopCnt<16;loopCnt++)
			{
   			DAC_DATA=testbit_on(word,15-loopCnt);
			CLOCK_PIN = 1;
			CLOCK_PIN = 0;
			}

		DAC_LOAD = 1;
//		Read_One_ADC(mux_cnt);		// read one ADC for each pass to speed up, all ADC is read anyway inbetween scans

//	}
			WriteToDACflag=0;
}
void switches_and_leds(void)
	{
	unsigned char n,o;
	unsigned int m;
//	local_mute[0] = 1;
	shiftData.trimLed = 0;
	shiftData.absLed = 0;
	shiftData.mute = 0;
	for(n=0;n<8;n++){
		// LEDs & MUTE
		shiftData.trimLed <<=1;
		shiftData.absLed <<=1;
		shiftData.mute <<=1;
		if(INdata.channel[n].status == 0x01)
			{
			shiftData.trimLed += 1;
			}
		if(INdata.channel[n].status == 0x02)
			{
			shiftData.trimLed += 1;
			}
		if(INdata.channel[n].status == 0x03)
			{
			shiftData.trimLed += 1;
			shiftData.absLed += 1;
			}
		if (INdata.channel[n].blink)
			{
			if(shiftData.absLed & 0x01)
				{shiftData.absLed = shiftData.absLed -1;}
			else
				{shiftData.absLed = shiftData.absLed +1;}
			}
		if (1)
			{
			shiftData.mute += OUTdata.channel[n].mute;
			}
	}
		shiftData.trimLed = ~shiftData.trimLed;
		shiftData.absLed = ~shiftData.absLed;
		shiftData.mute = shiftData.mute;	

	LED_LOAD = 0;
	m=0x01;
	for(n=0;n<8;n++){ 
//		LED_DATA = (shiftData.mute & m) == m;
		m <<=1;
		CLOCK_PIN = 1;
		CLOCK_PIN = 0;
	}
	m=0x01;
	for(n=0;n<8;n++){
//		LED_DATA = (shiftData.trimLed & m) == m;
		m <<=1;
		CLOCK_PIN = 1;
		CLOCK_PIN = 0;
	}
	m=0x01;
	for(n=0;n<8;n++){
//		LED_DATA = (shiftData.absLed & m) == m;
		m <<=1;
		CLOCK_PIN = 1;
		CLOCK_PIN = 0;
	}
	LED_LOAD = 1;	
	
	
	// Read SWITCH & MUTE
	SWITCH_LOAD = 0;
	SWITCH_LOAD = 1;
	for(n=0;n<8;n++){	
		OUTdata.channel[7-n].status = SWITCH_DATA;
		CLOCK_PIN = 1;
		CLOCK_PIN = 0;
	}	

	SWITCH_LOAD = 0;
		test++;
}

unsigned char test;
void Scan_Parallell_Port(void)
	{	
// 	INTCONbits.GIE=0;
	DAC_DATA=1;	

	cnt=0;											// reset counter
//	clk_flag=0;										// flag for Lo/Hi trans
	SSP_read();
	while(cnt<32)									// 32 clock pulses
		{
			if(cnt<16)								// first 16 pulses = read
				{				
				SSP_write();						// same, but write !!!!!!!!
			//	LATD = OUTdata.data[cnt];
				LATD = INdata.data[cnt];

//				while(SSP_clk==0)
//					{
//					;
//					}
				}
			else
				{
				SSP_read();

//				while(SSP_clk==0)
//					{
//					;
//					}
				BankTemp[cnt-16]=PORTD;					// read and store port
				}
//		if(SSP_clk == 1 && clk_flag == 0)			// Clock rise
//			{
//			clk_flag = 1;
			cnt++;									// count up
//			}
//
//		if(SSP_clk == 0)						// clock hi to lo reset
//			{
//			clk_flag=0;
//			}
		}
		SSP_read();


			error = 0;	
			

			for(cnt=0;cnt<16;cnt++)
				{
				INdata.data[cnt]=BankTemp[cnt];
				}
//			INTCONbits.GIE=1;
//			INdata.data[0]=test;
			test++;
			ParallelPortflag=1;

		DAC_DATA=0;	
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
	int VCA;		//VCA fader value
	double val;		//VCA fader value as double
	double BP1 = 818;	//breakpoint 1
	double BP2 = 921;	//breakpoint 2
	double mpl1 = 0.515;	//multiplier 1
	double mpl2 = 2.278;	//multiplier 2
	double mpl3 = 1.8;	//multiplier 3

	PG = 1024-PG;	// maybe this need to be down after conversion

	if(PG>BP1)		//if BP1 is passed
		{
		if(PG>BP2)	//if BP2 is passed
			{
			// function #3
			// start where #2 left off - add a new linear value
			val = 655.904 + ((PG-BP2)*mpl3);	
      			}
   		else
      			{
			// function #2
			// start where #1 left off - add a new linear value
			val = 421.27 + ((PG-BP1)*mpl2);
     			}
		}
	else
		{
		val = PG * mpl1;	// function #1	
		}
	// truncate down to int
	VCA = val;
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
	int PG;			//P&G fader value
	double val;		//VCA fader value as double
	double BP1 = 421;	//breakpoint 1
	double BP2 = 656;	//breakpoint 2
	double mpl1 = 1.942;	//multiplier 1
	double mpl2 = 0.456;	//multiplier 2
	double mpl3 = 0.277;	//multiplier 3

	if(VCA>BP1)		//if BP1 is passed
		{
		if(VCA>BP2)	//if BP2 is passed
			{
			// function #3
			// start where #2 left off - add a new linear value
			val = 925.772 + ((VCA-BP2)*mpl3);	
      			}
   		else
      			{
			// function #2
			// start where #1 left off - add a new linear value
			val = 819.524 + ((VCA-BP1)*mpl2);
     			}
		}	
	else
		{
		val = VCA * mpl1;	// function #1	
		}
	// truncate down to int
	PG= val;
	return PG;
	}


/*****************************************************************************/
void mux(byte chn)
	{
	switch (chn)
		{
		case 0:		//X7
			MUX_0 = 0;
			MUX_1 = 0;
			MUX_2 = 0;
		break;
		case 1:		//X5
			MUX_0 = 0;
			MUX_1 = 1;
			MUX_2 = 0;
		break;
		case 2:		//X4
			MUX_0 = 1;
			MUX_1 = 1;
			MUX_2 = 0;
		break;
		case 3:		//X6
			MUX_0 = 1;
			MUX_1 = 0;
			MUX_2 = 0;
		break;
		case 4:		//X1
			MUX_0 = 0;
			MUX_1 = 1;
			MUX_2 = 1;
		break;
		case 5:		//X2
			MUX_0 = 1;
			MUX_1 = 0;
			MUX_2 = 1;
		break;
		case 6:		//X3
			MUX_0 = 0;
			MUX_1 = 0;
			MUX_2 = 1;
		break;
		case 7:		//X0
			MUX_0 = 1;
			MUX_1 = 1;
			MUX_2 = 1;
		break;
		}
	}

void Start_ADC(byte chn)
	{
	SetChanADC(0);
	ConvertADC();
	}
void Read_One_ADC(byte chn)
	{
	unsigned char n;
	unsigned int DER_VALUE;
	for(n=0;n<4;n++)
		{
		Start_ADC(chn);
		while( BusyADC() );
		DER_VALUE = ADRESL;							// put the word together
		DER_VALUE = DER_VALUE + (256*(ADRESH));
		adc_value = (VCAPassThru[chn]*0.8) + (DER_VALUE*0.2);
		}
//	if(MUTE_DATA)
//		{
//		local_mute[chn] = 1;
//		}
//	else
//		{
//		local_mute[chn] = 0;
//		}
//	adc_value = DER_VALUE;

	VCAPassThru[chn] = adc_value;
	adc_value = 1023-VCAtoPG(adc_value);
//	adc_value = test;

	lo_adc = adc_value & 0xFF;					// expand it to two bytes
	hi_adc = adc_value >> 8;	


		OUTdata.channel[chn].vca_lo = lo_adc;
		OUTdata.channel[chn].vca_hi = hi_adc;

	OUTdata.channel[chn].mute = MUTE_IN;

	}



