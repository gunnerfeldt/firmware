///////////////////////////////////////////////////////////////
// PICJOESI2CSLAVE
//
// An I2C slave test program
// in 'C'
//
// (C) 2008 J.W.Brown
//
///////////////////////////////////////////////////////////////
#include <p18f4520.h>   /* for TRIS and PORT declarations */
#include <delays.h>	   /* Delays declarations */
#include <usart.h>	   /* Serial UART stuff */
#include <i2c.h>	/* Master Synchonous Serial I2C */	
#include <timers.h>
#include <adc.h>
#include <math.h>

#include <pwm.h>


/* Set configuration bits:
 *  - set HSPLL oscillator (10Mhz xtal, 40Mhz Osc
 *  - disable watchdog timer
 *  - disable low voltage programming
 *
 */
 
//#pragma config OSC= HSPLL
//#pragma config WDT=OFF
//#pragma config LVP=OFF

#define BUFSIZE 2
#define SW  !PORTCbits.RC6
// allocate some resources in ACCESS RAM for speedy access in interrupt routines
// all locations in this section are volatile
#pragma udata access volatile_access

ram near unsigned char sspcon1copy;
ram near unsigned char address;
ram near unsigned char data;
ram near unsigned char rxbuf[BUFSIZE];
ram near unsigned char txbuf[BUFSIZE];
ram near unsigned char rxcount, txcount;
ram near unsigned int PWM;

char PWMflag =0;
char I2Cflag =0;

const unsigned char MANUAL = 0x00;
const unsigned char AUTO = 0x04;
const unsigned char TOUCH = 0x08;
const unsigned char WRITE = 0x0C;
const unsigned char MUTE = 0x80;
const unsigned char MOTOR_ENABLE = 0x10;
const unsigned char ERROR_MASK = 0x60;
const unsigned char ERROR_CHECK = 0x40;
const unsigned char FADERSTATUS = 0x0C;
unsigned char indata[2];
float lastpError;
float lastiError;
float pError;
float iError;
float dError;
float pK;
float iK;
float dK;
float gain;
float time_interval;
float derTime;
float intTime;
int tol;

int motorstart;
unsigned int speed;
float fspeed;

double sim =0;

int fader_goal = 0;
int fader_int_goal = 0;
double fader_dbl_goal = 0;
int fader_compare = 0;
unsigned int fader_pos = 0;
unsigned char fader_address = 0;
unsigned char fader_status = 0;
unsigned char local_fader_status = 0;
unsigned char fader_touch_sens = 0;
unsigned double touch_acc;
unsigned char new_data = 0;
unsigned char soft_motor_on = 0;
unsigned char BlinkLED = 0;
unsigned char BlinkCnt = 0;
unsigned double acc_fader_pos;

#define motor_enable LATCbits.LATC0

#define AUTO_LED  LATBbits.LATB0
#define TOUCH_LED  LATBbits.LATB1
#define WRITE_LED  LATBbits.LATB2
#define MUTE_LED  LATBbits.LATB3

#define AUTO_SW  !PORTCbits.RC5
#define TOUCH_SW  !PORTCbits.RC6
#define WRITE_SW  !PORTCbits.RC7
#define MUTE_SW  !PORTAbits.RA4

#define COMP_ADC	ADC_CH1
#define CLEAN_ADC	ADC_CH0
#define TOUCH_ADC	ADC_CH11

unsigned char fader_adc;

#define bit_set(var,bitno) ((var) |= 1 << (bitno))
#define bit_clr(var,bitno) ((var) &= ~(1 << (bitno)))
#define testbit_on(data,bitno) ((data>>bitno)&0x01)
#define testbitmask(data,bitmask) ((data&bitmask)==bitmask)

#define bits_on(var,mask) var |= mask
#define bits_off(var,mask) var &= ~0 ^ mask

#define hibyte(x)       (unsigned char)(x>>8)
#define lobyte(x)        (unsigned char)(x & 0xFF)

#define fader_addr ((PORTA & 0b11100000)>>5)

void InterruptHandlerHigh (void); // prototype for int handler
void InterruptHandlerLow (void); // prototype for int handler
void Handle_I2C_1(void);		
void Handle_I2C_2(void);		
void Handle_LEDs(void);		
void Handle_SWs(void);		
void Read_Pos(void);		
void Scan_Touch(void);		
void Calculate_PWM(void);		
void Run_Motor(void);		
void Init(void);				

//----------------------------------------------------------------------------
// High priority interrupt vector (legacy interrupt)
#pragma code InterruptVectorHigh = 0x08
void
InterruptVectorHigh (void)
{
  _asm
    goto InterruptHandlerHigh //jump to interrupt routine
  _endasm
}
/*
// Low priority interrupt vector
#pragma code InterruptVectorLow = 0x18
void
InterruptVectorLow (void)
{
  _asm
    goto InterruptHandlerLow //jump to interrupt routine
  _endasm
}
*/

//----------------------------------------------------------------------------
// High priority interrupt routine (legacy interrupt)

#pragma code
#pragma interrupt InterruptHandlerHigh

void
InterruptHandlerHigh () 
{

	PIE1bits.TMR2IE = 0;

		if (PIR1bits.TMR2IF)	
			{			
			if(BlinkCnt>20)
				{
				BlinkLED = !BlinkLED;
				BlinkCnt = 0;
				}
			BlinkCnt++;
			PWMflag = 1;
			PIR1bits.TMR2IF = 0;
			}



	if (PIR1bits.SSPIF == 1)									// its an I2C interrupt
	{	
		sspcon1copy = SSPCON1;
		sspcon1copy &= 0b00000110;

		if (sspcon1copy == 0b00000110)							// its a master
			{
			if (SSPSTATbits.R_W == 0)							// its a WRITE from master
				{	
				if (SSPSTATbits.D_A == 0)						// its an ADDRESS - STATE 1:
					{				
					address = SSPBUF; 							// address not used in this test
					rxcount = 0;
					txcount = 0;
					}

				else											// its DATA - STATE 2:
					{
					if (SSPSTATbits.BF)					// there's DATA in the SSPBUF
						{	
						data = SSPBUF;	
						if (rxcount < 2)
							{	
							rxbuf[rxcount]=data;	
							if (SSPCON1bits.SSPOV)
								{
								SSPCON1bits.SSPOV = 0;
								}
							else
								{
								rxcount++;
								new_data = (rxcount==2);
			
								}
							}
						}				
					}
				}
			else												// its a READ by master
				{
				if (SSPSTATbits.D_A == 0)						// its an ADDRESS - STATE 3:
					{				
					address = SSPBUF; 							// address not used in this test
					rxcount = 0;
					txcount = 0;
					}
				else											// its DATA - STATE 2:
					{		
					data = SSPBUF; // dummy read
					if (txcount < 2) 								// is there a byte to transmit?
						{
						SSPBUF = txbuf[txcount]; 				// send byte
						if (SSPCON1bits.WCOL)
							{
							SSPCON1bits.WCOL = 0;
							}
						else
							{
							txcount++;	
							}		
						}
					}
						SSPCON1bits.WCOL = 0;
						SSPCON1bits.SSPOV = 0;

				}	
			}
		
		PIR1bits.SSPIF = 0; // clear interrupt flag
		SSPCON1bits.CKP = 1;
	}


		PIE1bits.TMR2IE = 1;
//		INTCONbits.TMR0IE = 1;
//		SSPCON1bits.CKP = 1; // release clock line
}
/*
#pragma interrupt InterruptHandlerLow

void InterruptHandlerLow(void)
{

}
*/
#pragma code 

void main(void)
{
	Init();

	while (1) // loop forever
	{

	if (new_data)
		{	
//		AUTO_LED = BlinkLED;
//		AUTO_LED =!AUTO_LED;
		INTCONbits.GIE = 0;
//		Handle_SWs();
		Handle_I2C_2();
		Handle_LEDs();
//		Scan_Touch();
//		Read_Pos();	
//		Run_Motor();
		new_data =0;

//			fader_goal = sim;
//			sim += 5;
//			if (sim>1023) sim =0;	

		INTCONbits.GIE = 1;
		}


		if (PWMflag ==1)
			if (PIR1bits.SSPIF == 0)
			{		
				{	
				fader_dbl_goal = (fader_int_goal*0.8) + (fader_goal*0.2);
				fader_int_goal = fader_dbl_goal;
	
	//				fader_int_goal = sim;
	//				sim = 512;
	//				if (sim>1023) sim =0;
					soft_motor_on = 1;
				
				Calculate_PWM();	
				Run_Motor();
//
//				SetDCPWM1(717);
//				motor_enable = 0;

				PWMflag=0;
				}
			}


	}
}
void Scan_Touch(void)
	{	
	unsigned int touch_adc;
	SetChanADC(ADC_CH11);
	ConvertADC();
	while( BusyADC() );
	
	touch_adc = ADRESH;
	touch_adc = touch_adc << 8;
	touch_adc = touch_adc + ADRESL;
	if (touch_adc>(890+(fader_pos*0.07)))
		{
//		fader_touch_sens = 1;
		touch_acc = (touch_acc+1)/2;
		}
	else
		{
		touch_acc = touch_acc*0.93;
		if (touch_acc<0.5)	
			{
			fader_touch_sens = 0;
			touch_acc = 0.5;
			}	
		}
	}	
void Read_Pos(void)
	{	
	SetChanADC(ADC_CH0);
	ConvertADC();
	while( BusyADC() );
	
	fader_pos = ADRESH;
	fader_pos = fader_pos << 8;
	fader_pos = fader_pos + ADRESL;
	}	


void Calculate_PWM(void)
	{	
	SetChanADC(fader_adc);
	ConvertADC();
	while( BusyADC() );
	
	fader_compare = ADRESH;
	fader_compare = fader_compare << 8;
	fader_compare = fader_compare + ADRESL;
	acc_fader_pos = (acc_fader_pos*0.4) + (fader_compare*0.6);
	fader_compare = acc_fader_pos;

			pError = fader_int_goal-fader_compare;
			iError += lastpError;
			iError *= intTime;

			if (fabs(pError)<tol+1) iError =0;
			if (iError>1023) iError =1023;
			if (iError<-1023) iError =-1023;

//			if (speed>1000)
				{dError = (lastpError - pError)*derTime/time_interval;}
//			else
//				{dError=0;}
				

			fspeed =fspeed + (((pK*pError)+(iK*iError)+(dK*dError))*gain);
			fspeed/=2;
			lastpError = pError;
//			lastiError = iError;


			speed = fabs(fspeed);

	
			if(speed>1023) speed = 1023;
			PWM=speed;
//			PWM =1023;
	}
	
void Handle_SWs(void)
	{
	local_fader_status = 0;	
	if(SW) local_fader_status = 0x08;
	local_fader_status += (fader_touch_sens*0x10);
	}	
	
void Handle_LEDs(void)
	{
		AUTO_LED = (!testbitmask(indata[1],AUTO));
		TOUCH_LED = !testbitmask(indata[1],TOUCH);
		WRITE_LED = !testbitmask(indata[1],WRITE);
		MUTE_LED = !testbitmask(indata[1],MUTE);

		if (fader_touch_sens) WRITE_LED = BlinkLED;
		if (fader_touch_sens) AUTO_LED = BlinkLED;

	}		
void Run_Motor(void)
	{
	unsigned int dutycycle ;
	INTCONbits.GIE = 0;
//	PWM *= PWM;PWM/=1023;
	dutycycle = PWM;

	INTCONbits.GIE = 1;	
	if (fabs(fader_compare-fader_int_goal)>tol)
		{
		if (dutycycle<motorstart) dutycycle = 0;
//			{
			if(fspeed>0)
				{
				SetDCPWM1(dutycycle);
				SetDCPWM2(0);
//				SetDCPWM2(1023-dutycycle);
//				motor_enable = (!fader_touch_sens & soft_motor_on);
				motor_enable = 1;

				}
			else
				{
				SetDCPWM2(dutycycle);
				SetDCPWM1(0);
//				SetDCPWM1(1023-dutycycle);
//				motor_enable = (!fader_touch_sens & soft_motor_on);
				motor_enable = 1;
				}

		}	
	else
		{

		SetDCPWM2(0);
		SetDCPWM1(0);
		motor_enable = 0;
		}
	}	
		
void Handle_I2C_1(void)
	{	

;
	}	
void Handle_I2C_2(void)
	{
	// Note disable interrupts while checking each volatile below



	if ((rxbuf[1]&ERROR_MASK)==ERROR_CHECK)			// check bit 5,6 for errors
		{
		indata[0] = rxbuf[0];
		indata[1] = rxbuf[1];
	
		fader_goal = (indata[1] & 0x03);
		fader_goal = fader_goal << 8;
		fader_goal =  fader_goal + indata[0];

		soft_motor_on = testbitmask(indata[1],MOTOR_ENABLE);
		}
		txbuf[0] = lobyte(fader_pos);
		txbuf[1] = hibyte(fader_pos)+local_fader_status;


	}

void Init(void)
	{
	OSCTUNEbits.TUN0 = 1;
	OSCTUNEbits.TUN1 = 1;
	OSCTUNEbits.TUN2 = 1;
	OSCTUNEbits.TUN3 = 1;
	OSCTUNEbits.TUN4 = 1;
	OSCCONbits.IRCF0 = 1;
	OSCCONbits.IRCF1 = 1;
	OSCCONbits.IRCF2 = 1;
	OSCTUNEbits.PLLEN = 1;
	// initialise buffer ptrs and counts to 0
	rxcount = txcount = 0;

	TRISA = 0xFF;
	TRISB = 0xF0;	
	TRISC = 0xF8;
	TRISCbits.TRISC1 =0;
	TRISCbits.TRISC2 =0;
	// setup I2C module
	SSPCON1 = 0x36 + 0x00; 	//  bit 5=1: enable I2C
							//  bit 4=1: release clock
							//  bits3:0: SSPM3:SSPM0; I2C Slave mode with 7bit address, no interrupts on start or stop bits
	
	fader_address = fader_addr;
//	SSPADD = 0xE0 + fader_address; // slave address
	SSPADD = 0xE0 + 0; // slave address

	// enable interrupts - legacy mode
	INTCONbits.PEIE = 1;
	INTCONbits.GIE = 1;
	PIE1bits.SSPIE = 1; // SSP interrupt enable
// 	INTCONbits.TMR0IE=1; //enable TMR0 overflow interrupt enable bit
 	PIE1bits.TMR2IE=1; //enable TMR0 overflow interrupt enable bit

//  	OpenTimer0 (TIMER_INT_ON & T0_SOURCE_INT & T0_8BIT & T0_PS_1_256);

	OpenADC(	ADC_FOSC_32     &
				ADC_RIGHT_JUST	&
				ADC_2_TAD,
				ADC_CH12		&
				ADC_INT_OFF		&
				ADC_VREFPLUS_EXT
				, 15 );
	//			ADC_VREFPLUS_EXT
	ADCON1 = 0x0C;
//	T2CON.TMR2ON = 1;
	OpenTimer2(T2_PS_1_16 & TIMER_INT_ON & T2_POST_1_8);

	


	fader_adc = COMP_ADC; 

	tol = 1;


	gain = 0.500;				// 1

	pK = 25;				
	iK = 7.000; // 10
	dK = 1.2;	// 0.20

	intTime = 1.0;			// 0.19

	derTime = -2;			// 1
	time_interval = 0.0015;	// 1

//	pK = 3;
//	iK = 3.000;
//	dK = 3.000;	
//	gain = 5;				// 1
	

//	gain = 0.500;				// 1
//
//	pK = 15;				
//	iK = 00.000;
//	dK = 0.00;	

	motorstart =0;

	OpenPWM1(255);									// Turn PWM on
	SetDCPWM1(0); 

	OpenPWM2(255);									// Turn PWM on
	SetDCPWM2(0);  
	}

