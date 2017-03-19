/* Compile options:  -ml (Large code model) */

//#include <stdio.h>
#include <p18f4520.h>
#include <adc.h>
#include <timers.h>
#include <typedefs.h>
#include <math.h>
#pragma config WDT = OFF
	

void Read_All_ADC(void);
void Scan_Parallell_Port(void);
void Sw_Test(void);
void LED_Test(void);
void DAC_Test(byte);
void Init(void);
void mux(byte);
void Start_ADC(byte);
void Read_One_ADC(byte);
void Error(void);
float Calc_Exp(unsigned int);

byte mask;
byte switch_flag = 0;
byte adc_flag = 0;
byte led_flag = 0;
byte dac_flag = 0;
byte engine_flag = 0;
unsigned int BlinkCnt = 0;
unsigned int status_bits;
byte BlinkLED = 1;

int adc;				// ADC int
byte adcMSB;			// ADC byte
byte adcLSB;			// ADC byte
byte adcchn = 0;
byte DACchn = 0;
byte error = 0;
byte OddEven = 0;

BOOL sw_flag;

unsigned char debounce_add;
unsigned char debounce_mute[7];
unsigned char debounce_sw[7];


byte FADER_STATUS[7];

byte FADER_SWITCH[7];


const byte MANUAL =	0x00;
const byte AUTO = 0x04;
const byte TOUCH = 0x08;
const byte WRITE = 0x0C;

/*
const byte MUTE_FLAG = 0b10000000;
const byte AUTO_FLAG = 0b00010000;
const byte TOUCH_FLAG = 0b00100000;
const byte WRITE_FLAG = 0b01000000;
*/

unsigned int FadersInPos[8];
unsigned char FadersInMute[8];
unsigned int Switch[8];
byte BankIn[16];		// data to shuffle in/out
byte BankOut[16];		// data to shuffle in/out
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



	#pragma interrupt YourHighPriorityISRCode
	void YourHighPriorityISRCode()
	{
		INTCONbits.TMR0IE = 0;
		if (INTCONbits.TMR0IF)		
			if(BlinkCnt>20)
				{
				BlinkLED = !BlinkLED;
				BlinkCnt = 0;
				}
			BlinkCnt++;
			INTCONbits.TMR0IF = 0;
			INTCONbits.TMR0IE = 1;
	}
	#pragma interruptlow YourLowPriorityISRCode
	void YourLowPriorityISRCode()
	{

	
	}	//This return will be a "retfie", since this is in a #pragma interruptlow section 

void Init(void)
{
	TRISA = 0x03;
	TRISB = 0xF8;
	TRISE = 0x00;
	

    OpenADC(	ADC_FOSC_16     &
				ADC_RIGHT_JUST	&
				ADC_4_TAD,
				ADC_CH0		&
				ADC_INT_OFF		&
				ADC_VREFPLUS_VDD
				, 15 );
//				ADC_VREFPLUS_EXT
	ADCON1 = 14;				// ref = VDD and ADC 0 to 7 activated

// INTCON=0;    //make sure interrupts are disable
// INTCONbits.GIE=1;  //enable global interrupts
// INTCONbits.PEIE=1;  //enable peripheral interrupts
// INTCONbits.TMR0IE=1; //enable TMR0 overflow interrupt enable bit



	TRISC = 0x01;
//  	OpenTimer0 (TIMER_INT_ON & T0_SOURCE_INT & T0_8BIT & T0_PS_1_256);

}

void main (void)
	{
	Init();
//	error = 0;					// error flag for par port failure
	LED1 = 1;
	LED2 = 1;

 for(wCntr=0;wCntr<30000;wCntr++)
	{
	;
	}
	LED1 = 0;
	LED2 = 0;


	adcchn = 0;
	TRISBbits.TRISB3 = 1;
	TRISBbits.TRISB4 = 1;
	TRISCbits.TRISC4 = 0;
	TRISCbits.TRISC6 = 0;
	TRISCbits.TRISC7 = 0;

	TRISDbits.TRISD2 = 1;
	mux_read_master = 1;
	mux_write_master = 1;


	while(1)
		{

		if(SSP_en != 1)						// always check if USB card is trying to communicate
			{
			if(adc_flag < 2)				// if there is adc's left to read. Until next cycle
				{	
				mux(adcchn);
					if(switch_flag < 10)
						{
						Sw_Test();	// scan switches 20 times per cycle
						switch_flag++;
						}
					else
						{				
						for(Wcnt=0;Wcnt<300;Wcnt++)
							{
							;
							}
						}
				Start_ADC(adcchn);
				while(BusyADC())
					{
					Sw_Test();	// scan switches 20 times per cycle
					switch_flag++;
					}

				Read_One_ADC(adcchn);		// read one ADC for each pass to speed up, all ADC is read anyway inbetween scans
				adcchn++;

				if (adcchn>7)											// when all adc's are scanned. raise flag. reset counter.
					{
					adcchn = 0;
					adc_flag++;
					}
				}
			}

		if(SSP_en != 1)
			{
			if(dac_flag==0)
				{
				for(cnt=0;cnt<8;cnt++)
					{
				DAC_Test(cnt);
					}
				dac_flag=1;
				}
			}	


		if( (SSP_en != 1) && (led_flag == 0) )LED_Test();		// update leds once per cycle
	
		if(SSP_en == 1)											// poll for parallel comm
			{

			Scan_Parallell_Port();								// communicate with USB card
			if (error == 1)	Error;									// Show the error
			}

		}

	}

void Error(void)
	{
	for(Wcnt=0;Wcnt<20000;Wcnt++)
		{
		;
		}
	for(blinkcnt=0;blinkcnt<10;blinkcnt++)
		{
		LED1=1;
		LED2=0;
		for(Wcnt=0;Wcnt<5000;Wcnt++)
			{
			;
			}
		LED1=0;
		LED2=1;
		for(Wcnt=0;Wcnt<5000;Wcnt++)
			{
			;
			}
		}
	error = 0;

	}

void Scan_Parallell_Port(void)
	{	
	INTCONbits.TMR0IE = 0;

//	SSP_write();
//	PORTD = 0xFF;
//	for(cnt=0;cnt<5;cnt++)
		{
		;
		}
	for (cnt=0;cnt<8;cnt++)
		{
		if (Switch[cnt] == 1) BankOut[1+(cnt*2)] |= 64;
		}


	cnt=0;											// reset counter
	clk_flag=0;										// flag for Lo/Hi trans

	SSP_read();
	while(cnt<48)									// 32 clock pulses
		{
		if(SSP_en == 0)								// check that USB card is still on
			{
			SSP_read();
//			BankOut[1] = 0x10;
//			BankOut[3] = 0x10;
//			BankOut[5] = 0x10;
//			BankOut[7] = 0x10;
//			BankOut[9] = 0x10;
//			BankOut[11] = 0x10;
//			BankOut[13] = 0x10;
//			BankOut[15] = 0x10;
			error=1;return;							// else break
			}
			
		if(cnt<24)								// first 16 pulses = read
			{
			SSP_read();
			BankIn[cnt]=PORTD;					// read and store port
			}
		else
			{
			SSP_write();						// same, but write

			LATD = BankOut[cnt-16];
//			LATD = 0;
//			BankOut[cnt-16] = 0;

			}

		if(SSP_clk == 1 && clk_flag == 0)			// Clock rise
			{
			clk_flag = 1;
			cnt++;									// count up
			}

		if(SSP_clk == 0)						// clock hi to lo reset
			{
			clk_flag=0;
			}


		}
	
			SSP_read();
			while(SSP_en == 1)						// hold til USB card releases CS
				{
				;
				}
			switch_flag = 0;
			led_flag = 0;
			adc_flag = 0;
			dac_flag=0;
			engine_flag = 0;
			LED1 = !LED1;
			BankOut[1] = 0x08;
			BankOut[3] = 0x08;
			BankOut[5] = 0x08;
			BankOut[7] = 0x08;
			BankOut[9] = 0x08;
			BankOut[11] = 0x08;
			BankOut[13] = 0x08;
			BankOut[15] = 0x08;

			INTCONbits.TMR0IE = 1;
	}



/******************************************************************************
 * Function:        void Sw_Test(void)
 *
 * PreCondition:    
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    
 *
 * Overview:        
 *
 * Note:            None
 *****************************************************************************/


void Sw_Test(void)
	{
		SWclk = 0;
		SWload = 0;
		SWload = 1;

			ShiftIn=0;
			for(SWcnt=0 ;SWcnt < 8; SWcnt++)
				{
				ShiftIn = ShiftIn << 1; 
				ShiftIn = ShiftIn + SWdata;
				SWclk = 1;
				SWclk = 0;
				}


		SWload = 0;	



		for(cnt=0;cnt<8;cnt++)
			{
//			BankOut[1+(cnt*2)] &= 131;
			sw_flag = 1;
			if (ShiftIn & 1) sw_flag=0;
			debounce_sw[cnt] = (debounce_sw[cnt]<<1)|sw_flag|0b11110000;
//			if (debounce_sw[cnt]  == 0b11110000) BankOut[1+(cnt*2)] |= 64;
			if (debounce_sw[cnt]  == 0b11110000) 
				{Switch[cnt] = 1;}
			else
				{Switch[cnt] = 0;}
			ShiftIn >>=1;
			}


	}

/******************************************************************************
 * Function:        void LED_Test(void)
 *
 * PreCondition:    
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    
 *
 * Overview:        
 *
 * Note:            None
 *****************************************************************************/

void LED_Test(void)
	{
	unsigned char error = 0;
		ShiftOut[0] = 0;	// ABS LED
		ShiftOut[1] = 0;	// TRIM LED
		ShiftOut[2] = 0;  // MUTE FUNCTION


//	LED_byte = 0xFF;
for (cnt=0;cnt<8;cnt++)	
	{
	if((BankIn[1+(cnt*2)]&0x60) == 0x40)
		{		
		ShiftOut[0] >>= 1;				// Make space for the bit to set
		ShiftOut[1] >>= 1;
		ShiftOut[2] >>= 1;
		
		status_bits = BankIn[1+(cnt*2)]&0x0C;
	
	
			if (status_bits == 0x00)					//MANUAL
				{
				ShiftOut[0] += 128;			// set the ABS LED bit
				ShiftOut[1] += 128;			// set the TRIM LED bit
				}
			if (status_bits == 0x04)					//AUTO
				{
				ShiftOut[1] += 128;			// set the TRIM LED bit
				}
			if (status_bits == 0x08)					//TOUCH
				{
				}
			if(status_bits == 0x0C)						//WRITE
				{
				ShiftOut[0] += 128;			// set the ABS LED bit
				}
	
		if (status_bits == 0x04)		// if not in manual status, set MUTE bit
			{
			if(BankIn[1+(cnt*2)]&128)		//MUTE
				{	
				ShiftOut[2] |= 128;
				}
			}
		else							// if manual, set mute bit if SSL mute is on
			{
			if (FadersInMute[cnt])
				{
				ShiftOut[2] |= 128;
				}
			}																					
		}
		else error = 1;
	}


// ********* shift out **************************'


// sätt in ordentlig mute. för online och offline.

	if (error == 0)
		{	
		LEDdata = 0;
		LEDclk = 0;
		LEDload = 0;
		for(cnt=0;cnt<3;cnt++)
			{
			mask = 128;
			for(LEDcnt=0 ;LEDcnt < 8; LEDcnt++)
				{		
				if(ShiftOut[cnt] & 128) 
				{LEDdata = 1;}
				else
				{LEDdata = 0;}

				ShiftOut[cnt] <<= 1;
				LEDclk = 1;

				LEDclk = 0;

				}
			}
		LEDload = 1;
		}	
		led_flag = 1;

	}

/******************************************************************************
 * Function:        void DAC_Test(void)
 *
 * PreCondition:    
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    
 *
 * Overview:        
 *
 * Note:            None
 *****************************************************************************/

void DAC_Test(byte chn)
	{
	if((BankIn[1+(chn*2)]&0x60) == 0x40)
		{
		DACaddr = 0x1000 + (0x1000 * chn);
	
		if ((BankIn[1+(chn*2)] & 0x0C) > 0x00)
			{
			DACval = (BankIn[1+(chn*2)]) & 3;			// unpack the DAC value from the incomming data
			DACval = DACval << 8;
			DACval = DACval + BankIn[0+(chn*2)];
			if (BankIn[1+(chn*2)]&128)					// check for mute
				{
				DACval = 1023;
				}										// if mute put fader to inf	//			
			else
				{
				DAClog = 1023-DACval;
				DACval = DAClog;
				}	
			}
		else											// if status is manual contol from fader(=outgoing data)
			{
			if (FadersInMute[chn])				// if muted set fader down
				{
				DACval = 1023;
				}
			else
				{
				DACval = FadersInPos[chn];			// unpack the DAC value from the outgoing data
				}
	
			}
	
	
			DACclk = 0;	
			DACload = 0;
	
	
			DACword = DACaddr + (DACval<<2);
			for (DACcnt=0;DACcnt<16;DACcnt++){
				if (0x8000 & DACword){DACdata=1;}
				else {DACdata=0;}
				DACword <<= 1;								// shift it out
				DACclk = 1;
				DACclk = 0;
				}
			}
		DACload = 1;	


	}





/******************************************************************************
 * Function:        void Read_All_ADC(void)
 *
 * PreCondition:    
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    Read and store 8 motor faders, 10 bit
 *
 * Overview:        Service loop for transfer to USB host.
 *
 * Note:            None
 *****************************************************************************/
void mux(byte chn)
	{
	switch (chn)
		{
		case 0:
			muxA = 1;
			muxB = 1;
			muxC = 1;
		break;
		case 1:
			muxA = 0;
			muxB = 1;
			muxC = 1;
		break;
		case 2:
			muxA = 1;
			muxB = 0;
			muxC = 1;
		break;
		case 3:
			muxA = 0;
			muxB = 0;
			muxC = 1;
		break;
		case 4:
			muxA = 1;
			muxB = 1;
			muxC = 0;
		break;
		case 5:
			muxA = 0;
			muxB = 1;
			muxC = 0;
		break;
		case 6:
			muxA = 1;
			muxB = 0;
			muxC = 0;
		break;
		case 7:
			muxA = 0;
			muxB = 0;
			muxC = 0;
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
//	SetChanADC(0);
//	ConvertADC();

	while( BusyADC() );
	adc_value = ADRESL;							// put the word together
	adc_value = adc_value + (256*(ADRESH));
	adc_value = (FadersInPos[chn] + adc_value)/ 2;
	FadersInPos[chn] = adc_value;

	lo_adc = adc_value & 0xFF;					// expand it to two bytes
	hi_adc = adc_value >> 8;	

	BankOut[chn *2] = lo_adc;
	BankOut[(chn *2)+1] &= 0x3C; 
	BankOut[(chn *2)+1] += hi_adc + (!mute * 128);
	FadersInMute[chn] = !mute;

	}



void Read_All_ADC(void)
			{

}


