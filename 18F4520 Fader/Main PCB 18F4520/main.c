/* Compile options:  -ml (Large code model) */

//#include <stdio.h>
#include <p18f4520.h>
#include <timers.h>
#include <typedefs.h>
#include <i2c.h>
// #pragma config WDT = OFF
	

#define LED1  LATBbits.LATB3
#define LED2  LATBbits.LATB4


#define SSP_en          	!PORTBbits.RB0
#define SSP_clk          	PORTBbits.RB1
#define SSP_write()         TRISD = 0;
#define SSP_read()         	TRISD = 255;

#pragma udata access volatile_access

ram near unsigned char datain[2];

#pragma udata


void Scan_Parallell_Port(void);

void Init(void);
void Error(void);

byte mask;
byte switch_flag = 0;
byte adc_flag = 0;
byte led_flag = 0;
byte engine_flag = 0;
unsigned int BlinkCnt = 0;
byte BlinkLED = 0;

byte sim = 0;

byte error = 0;
byte OddEven = 0;
long cntr10 = 0;

byte BankTemp[24];		// data to shuffle in/out
byte BankIn[24];		// data to shuffle in/out
byte BankOut[24];		// data to shuffle in/out

BOOL clk_flg = FALSE;

	unsigned long Ltimer;
	unsigned long cnt; 
	unsigned char clk_flag = 0; 
	unsigned long Wcnt; 
	unsigned long cnt1; 
	unsigned long cnt2;
	unsigned long cnt3; 

	unsigned char fader_response = 0;


	#pragma interrupt YourHighPriorityISRCode
	void YourHighPriorityISRCode()
	{
	if (PIR1bits.SSPIF == 1)
		{
		PIR1bits.SSPIF = 0; // clear interrupt flag
		fader_response = 1;
		}
	}
	#pragma interruptlow YourLowPriorityISRCode
	void YourLowPriorityISRCode()
	{

	
	}	//This return will be a "retfie", since this is in a #pragma interruptlow section 


void Init(void)
{
	TRISA = 0x00;
	TRISB = 0x03;
	TRISC = 0x00;
	TRISE = 0x00;

 INTCON=0;    //make sure interrupts are disable


}

void main (void)
	{

	Init();
	TRISBbits.TRISB0 = 1;
	TRISBbits.TRISB1 = 1;
	TRISBbits.TRISB3 = 0;
	TRISBbits.TRISB4 = 0;

	TRISBbits.TRISB5 = 0;
	TRISBbits.TRISB6 = 0;
	TRISBbits.TRISB7 = 0;
	TRISCbits.TRISC3 = 1;
	TRISCbits.TRISC4 = 1;

	LED1 = 1;
	LED1 = 1;

	SSP_read();



	error = 0;					// error flag for par port failure


	OpenI2C (MASTER, SLEW_ON);
	SSPADD = 24; // for 400Khz // ( (Fosc/Bitrate)/4 ) - 1
	engine_flag = 1;
	INTCONbits.PEIE = 1;
//	INTCONbits.GIE = 1;
//	PIE1bits.SSPIE = 1; // SSP interrupt enable


/*
				IdleI2C();
			SSPCON2bits.SEN=1;
	while(SSPCON2bits.SEN==1)
		{
			LED1=0;
		}
	while(1)
		{
			LED1=1;
		}
*/





	while(1)
		{

		if(SSP_en == 1)											// poll for parallel comm
			{
			Scan_Parallell_Port();								// communicate with USB card
			}
		if (engine_flag == 0)
			{

	//		LED1 = !LED1;


			for(cnt=0;cnt<9;cnt++)			// Why 9?
				{
				
				IdleI2C();
				StartI2C();
				IdleI2C();


			if (WriteI2C(0xE0+(cnt*2))==0);  // LED2=!LED2 WRITE address. Must skip bit 0. Bit 0 is for READ!!!
				IdleI2C();
				WriteI2C(BankIn[cnt*2]);
				IdleI2C();
				WriteI2C(BankIn[1+(cnt*2)]);
				IdleI2C();
				WriteI2C(BankIn[16+cnt]);
				IdleI2C();
				StopI2C();
				BankIn[cnt*2]=0;
				BankIn[1+(cnt*2)]=0;
				BankIn[16+cnt]=0;
				}



			for(cnt=0;cnt<9;cnt++)
				{

				IdleI2C();
				StartI2C();

				IdleI2C();
				fader_response = 0;
//				WriteI2C(0xE1+(cnt*2));

//					IdleI2C();						// I need to read a dummy pass. WHY?
//					BankOut[cnt*2] = ReadI2C();
//					AckI2C();

//				if (fader_response)

				if (WriteI2C(0xE1+(cnt*2))==00) // READ address
					{
					IdleI2C();
	//				if(!SSPSTATbits.BF)
					{
						datain[0] = ReadI2C();	
						AckI2C();
						IdleI2C();
	
						datain[1] = ReadI2C();
						AckI2C();
						IdleI2C();
	
						datain[2] = ReadI2C();
						NotAckI2C();
						IdleI2C();
	
						BankOut[16+cnt] = datain[2];
						BankOut[cnt*2] = datain[0];
						BankOut[1+(cnt*2)] = datain[1];
//						if(datain[2]==0xF1) LED2=!LED2;
						ClrWdt();
						}
					}
				else 
					{
					;
					}

				IdleI2C();
				StopI2C();			
				}

			sim++;
			}	
		engine_flag = 1;
		}
	}

void Error(void)
	{

	}

void Scan_Parallell_Port(void)
	{	
// 	INTCONbits.GIE=0;


	cnt=0;											// reset counter
	clk_flag=0;										// flag for Lo/Hi trans
	SSP_read();
	while(cnt<48)									// 32 clock pulses
		{
		if(SSP_en == 0)								// check that USB card is still on
			{
			SSP_read();
			error=1;
			return;							// else break
			}
		
			if(cnt<24)								// first 24 pulses = read
				{
				SSP_write();						// same, but write !!!!!!!!
				LATD = BankOut[cnt];
				}
			else
				{				
				SSP_read();
				BankTemp[cnt-24]=PORTD;					// read and store port
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

			error = 0;	
			engine_flag = 0;
			
			for(cnt=0;cnt<24;cnt++)
				{
				BankIn[cnt]=BankTemp[cnt];
				}




//			INTCONbits.GIE=1;
	}












