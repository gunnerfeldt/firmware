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
 *  - disable watchdog timer
 *  - disable low voltage programming
 *
 */
 
//#pragma config WDT=OFF
//#pragma config LVP=OFF


// definitions, can be stripped
#define BUFSIZE 3
#define STATE_1 0b00001001 
#define STATE_2 0b00101001
#define STATE_3 0b00001100
#define STATE_4 0b00101100
#define STATE_5 0b00101000

#define motor_enable LATCbits.LATC0
#define AUTO_LED  LATBbits.LATB0
#define TOUCH_LED  LATBbits.LATB1
#define WRITE_LED  LATBbits.LATB2
#define MUTE_LED  LATBbits.LATB3

#define ON	0
#define OFF 1

#define AUTO_SW  !PORTCbits.RC5
#define TOUCH_SW  !PORTCbits.RC6
#define WRITE_SW  !PORTCbits.RC7
#define MUTE_SW  !PORTAbits.RA4

#define COMP_ADC		ADC_CH0
#define TEST_ADC		ADC_CH1
#define TOUCH_ADC		ADC_CH7
#define TOUCH_X_ADC		ADC_CH1
#define TOUCH_X_OUTPUT	TRISAbits.TRISA1 = 0
#define TOUCH_X_HIGH	LATAbits.LATA1 = 1

#define TOUCH_OUTPUT	TRISEbits.TRISE2 = 0
#define TOUCH_INPUT		TRISEbits.TRISE2 = 1
#define TOUCH_HI		LATEbits.LATE2 = 1
#define TOUCH_LOW		LATEbits.LATE2 = 0

#define LED_DRIVER_DATA		LATDbits.LATD0 = 0
#define LED_DRIVER_CLOCK	LATDbits.LATD1 = 0
#define LED_DRIVER_STROBE	LATDbits.LATD2 = 0
#define LED_DRIVER_ON		LATDbits.LATD3 = 0

#define big_plus  		0x0840		// hard code graphic for a plus sign
#define big_minus  		0x1008		// hard code graphic for a minus sign

#define ERROR_MASK_0	0b01010101
#define ERROR_MASK_1	0b10101010

#define bit_set(var,bitno) ((var) |= 1 << (bitno))
#define bit_clr(var,bitno) ((var) &= ~(1 << (bitno)))
#define testbit_on(data,bitno) ((data>>bitno)&0x01)
#define testbitmask(data,bitmask) ((data&bitmask)==bitmask)

#define bits_on(var,mask) var |= mask
#define bits_off(var,mask) var &= ~0 ^ mask

#define hibyte(x)       (unsigned char)(x>>8)
#define lobyte(x)        (unsigned char)(x & 0xFF)

#define fader_addr (~(PORTA & 0b11100000)>>5)

#define INT_OFF		INTCONbits.GIE = 0
#define INT_ON		INTCONbits.GIE = 1

#define TOUCH_SENSE 	210
#define TOUCH_RELEASE	90


// allocate some resources in ACCESS RAM for speedy access in interrupt routines
// all locations in this section are volatile
#pragma udata access volatile_access


volatile int FADER_PID = 0;
volatile int FADER_USB = 0;
volatile int PREV_FADER_USB = 0;
volatile unsigned int FADER_TOUCH = 0;
volatile unsigned char HARD_MOTOR_ON = 0;
unsigned char SET_FLASH = 0;
unsigned int SET_CNT = 0;
volatile near unsigned char       I2CSTAT;
struct {
    unsigned BF:1;
    unsigned UA:1;
    unsigned R_W:1;
    unsigned S:1;
    unsigned P:1;
    unsigned D_A:1;
    unsigned CKE:1;
    unsigned SMP:1;
}I2CSTATbits;

volatile near union INdataUnion {
unsigned char data[BUFSIZE];
struct  {
		unsigned vca_lo:8;
		unsigned vca_hi:2;
		unsigned status:2;
		unsigned not_used:2;
		unsigned motor_on:1;
		unsigned mute:1;
		};
}indata;

volatile near union OUTdataUnion {
unsigned char data[BUFSIZE];
struct  {

		unsigned vca_lo:8;
		unsigned vca_hi:2;
		unsigned status:2;
		unsigned touch_press:1;
		unsigned touch_release:1;
		unsigned mute_press:1;
		unsigned mute_release:1;

		};
}outdata;

// ram near unsigned int PWM;					// holds the PWM value
ram near unsigned int GOAL;
ram near unsigned int LAST_GOAL;
volatile unsigned int FADER_IN;
volatile unsigned char NEW_FADER_SET = 0;
volatile unsigned char PWMflag = 0;
volatile unsigned char I2Cflag = 0;
volatile signed long fspeed;
volatile unsigned char PWMCnt = 0;
volatile unsigned char SampleCnt = 0;
volatile unsigned char TouchCnt = 0;
volatile unsigned int I2CFakeCnt = 0;
volatile unsigned char I2CFakeTick = 0;

// fader in/out variables. Strip down please
volatile int touch = 0;
unsigned char fader_status = 0;
volatile unsigned char fader_address = 0;
unsigned char local_fader_status = 0;
unsigned char index;			// index counter for the I2C i/out buffer arrays
unsigned char address;		// where to store the dummy read. Might be used for general call

// funtion definitions
int HandleI2C(void);
void myWriteI2C(void);	
void scan_switches(void);
void InterruptHandlerHigh (void); // prototype for int handler
void InterruptHandlerLow (void);  // prototype for int handler
void Handle_LEDs(unsigned char);		
void Read_Pos(void);		
void Update_LED_Display(unsigned int);
void Update_LED_Display_Bits(unsigned int);
unsigned char Scan_Touch(void);
unsigned int Read_Fader(void);		
void CalcPWM1(int);		
void CalcPWM2(int);		
void Handle_Fader(void);		
void Init(void);
int Calculate_dB_Display(void);		// difference between fader and goal in dB

unsigned char ErrorCode(unsigned char, unsigned char);


#pragma udata


// Misc variables. Please redeem!!!
const unsigned char MANUAL = 0x00;
const unsigned char AUTO = 0x04;
const unsigned char TOUCH = 0x08;
const unsigned char WRITE = 0x0C;
const unsigned char MUTE = 0x80;
const unsigned char MOTOR_ENABLE = 0x10;
const unsigned char ERROR_MASK = 0x60;
const unsigned char ERROR_CHECK = 0x40;
const unsigned char FADERSTATUS = 0x0C;


signed int lastpError;
signed int lastiError;
signed long pError;
signed int iError;
signed int dError;


unsigned int GOAL_CNT;
unsigned int GOAL_MIN=35;
unsigned int GOAL_MAX=990;
const unsigned int SET_TIME = 3000;
const unsigned char TouchScanRate = 5;
const unsigned char SampleRate = 8;
const unsigned char PWMupdateRate = 24;
const unsigned int maxPWM =1023;

const signed long pK = 800;	//1000
const signed long iK = 6;	//3	
const signed long dK = 4000;	//1000
const long gain = 90;	//1
const long iKmult= 1;  // 1
const int TOL = 0;
const int iError_max = 1000; //500

const int ID = 1;		// motor fader channel !!!
const int DER_SPEED = 1; // 1.5

// Low Pass Constants
const int READ_SHIFT_PID = 0;
const int READ_SHIFT_USB = 2;
const int GOAL_SHIFT = 4;
const int DER_SHIFT = 0; //2

unsigned int touch_rel;
unsigned int touch_press;
unsigned char new_data = 0;
unsigned char soft_motor_on = 0;
unsigned char BlinkLED = 0;
unsigned int BlinkCnt = 0;
unsigned char DIG_TOGGLE;
unsigned char DIGIT[1];
unsigned int SEGMENTA[10];
unsigned int SEGMENTB[10];
unsigned char CHANNEL_NO = 1;
unsigned int displayint;
unsigned char fader_adc;
unsigned char trouble = 0;
unsigned char ScanFlag = 0;
unsigned char snapshot_flag = 0;
unsigned char DISPLAY;
unsigned char fader_ID;
unsigned char LOOP_CNTR = 1;
unsigned char LOOP_TIMES = 4;

/*

*/
//----------------------------------------------------------------------------
// High priority interrupt routine (legacy interrupt)

#pragma code
#pragma interrupt InterruptHandlerHigh

void InterruptHandlerHigh () 
{

// Move functions here:

	if(PIR1bits.SSPIF)					// if new I2C event occured
	{	
    	if (HandleI2C()==5)				// when I2C transfer is done (last state)	
    	{	
    	    I2Cflag = 1;				// flag for process	
    	}
	    PIR1bits.SSPIF = 0;				// reset	
	}


	if (PIR1bits.TMR2IF)	            // Timer base
		{			
		TouchCnt++;                     // Touch Timer
		SampleCnt++;                    // ADC Timer
		if(BlinkCnt>800)                // Blink Timer
			{
			if(SET_FLASH)               // Routine for flash delay
				{
				SET_CNT++;
				if(SET_CNT>50)          // Change this to a variable
					{ 
					SET_FLASH = 0;
					SET_CNT=0;	
					}
				}
			BlinkLED = !BlinkLED;       // Toggle Blink Value
			BlinkCnt = 0;
			}
		BlinkCnt++;
		PIR1bits.TMR2IF = 0;            // Reset Timer
		}
}


#pragma code

void main(void)
{	
	unsigned int temp_data;                 // ?
	int FADER_SET;                          // Fader ?
	int FADER_DIFF;                         // Difference ?
	int MOVE_STEP;                          // ?
	int FROM;                               // ?
	unsigned int USB_POS;                   // ?
	static long PID_FILTER_REG;             // ?
	static long USB_FILTER_REG;             // ?
	static long GOAL_FILTER_REG;            // ?
	static unsigned int USB_LSB_INT;        // ?
	static unsigned char USB_LSB = 0;       //
	unsigned int FADER_POSITION = 0;        //
	
	Init();                                                 // Initilialize Device
	Update_LED_Display(88);                                 // Reset Display
			
	while (1)                                               // loop forever
	{	
	if (I2Cflag)                                            // Move to ISR
		{
		I2Cflag = 0;                                        // Reset I2C flag

		if (1 == 1 && snapshot_flag == 0)					// control byte for read/write ???
			{
			FADER_SET = indata.data[1] & 3;                 // Fader CV to chase
			FADER_SET = (FADER_SET<<8)+indata.data[0];          
			LAST_GOAL = GOAL;                               // Last goal?
			NEW_FADER_SET=0;                                // ?
			if(FADER_SET!=FADER_IN)                         // ?
				{
				NEW_FADER_SET=1;                            // Test for new CV in
				}
			FADER_IN = FADER_SET;                           
			FADER_DIFF = FADER_SET - FADER_PID;             // Get difference from Chase CV and ??
			}

		if (indata.data[2] == 0xF3)					        // control byte for set switch flash
			{                                               // Change !!!!!!
			SET_FLASH = 1;
			}

		if ((indata.data[2]&0xF0) == 0xE0)					// Chnange !!!!!!
			{
			DISPLAY = ((indata.data[2] & 0x0F)*8) + fader_ID + 1 ;
			SET_FLASH = 0;
			}

			HARD_MOTOR_ON = indata.motor_on;                // Host software can turn off motors
			outdata.data[0] = lobyte(FADER_USB);            // Pack CV for outgoing
			outdata.data[1] = hibyte(FADER_USB);
			
		if (FADER_USB != PREV_FADER_USB && FADER_TOUCH)     // Used for what ??
			{
			PREV_FADER_USB = FADER_USB;
			}

//			DISPLAY = LOOP_CNTR;                            // determine loops. Change !!!! Do with timer
			LOOP_CNTR = 1;


		}	



		if(SampleCnt>SampleRate)                                                // ADC timer. Move ?
			{
			INT_OFF;                                                            // Turn off ISR. Not Good !!!!
			FADER_POSITION = Read_Fader();                                      // Sample Fader CV
			
			FADER_PID = FADER_POSITION;                                         // Shuffle around ???
			GOAL = (((30-LOOP_CNTR)*LAST_GOAL)+(LOOP_CNTR*FADER_SET))/30;       // all these filters. Sigh !!!!

			if(GOAL<GOAL_MIN)GOAL=GOAL_MIN;                                     // ?
			if(GOAL>GOAL_MAX)GOAL=GOAL_MAX;                                     // ?
			CalcPWM2(GOAL);                                                     // make out the PWM values
			Handle_Fader();                                                     // Update PWM 
			INT_ON;                                                             // Turn on  ISR. !!!!???!!!
			
			if(LOOP_CNTR<29)LOOP_CNTR++;                                        // determine loops. Change to timer
			

			USB_FILTER_REG = USB_FILTER_REG - (USB_FILTER_REG >> READ_SHIFT_USB) + FADER_POSITION;          // Filter for CV to Host
			FADER_USB = USB_FILTER_REG >> (READ_SHIFT_USB);                                                 // Filter

			SampleCnt = 0;                                                                                  // Reset ADC timer
			scan_switches();                                                                                // Read switches
			if (FADER_TOUCH)                                                                                // Update Led display
				{
				Update_LED_Display_Bits(Calculate_dB_Display());                                            // If Touch sense is true
				}
			else
				{                                                                                           // This shouldn't be done all the time
				Update_LED_Display(DISPLAY);
				}
			Handle_LEDs(indata.data[1]);                                                                    // Update status and mute LEDs
			}

		if(TouchCnt>TouchScanRate)                                                                          // determine touch sense
			{
			FADER_TOUCH = Scan_Touch();
			TouchCnt = 0;
			}
	
	}
}

/************************************************************************************************

    Calculate PWM values
    Input: Goal to chase. 10 bit value

*************************************************************************************************/
void CalcPWM2 (int FADER_GOAL)
	{
	int Scaled_Max;	
	static signed int D_REG;
	static signed int D_SPEED;
	static signed long lstP;




	pError = FADER_GOAL-FADER_PID;	                                                // Difference 

		if (pError != 0)                                                            // If it's a differnece
			{   
			iError += (pError*iKmult);                                              // Integral error ??
			Scaled_Max = iError_max; // *10;                                        // ??
			if (iError>Scaled_Max) iError =Scaled_Max;                              // ??
			if (iError<-Scaled_Max) iError =-Scaled_Max;

			dError = (pError-lstP);	                                                // Derivate error
			lstP = pError;		                                                    // Previous error
			fspeed = (((pK*pError)+(iK*iError)+(dK*dError))/(101-gain));            // Algorithm for PWM


			}
		else
			{                                                                       // if no error > clear all
			GOAL_CNT = SET_TIME;                                                    // Not good for over shoot
			iError = 0;
			pError = 0;
			dError = 0;
			D_REG = 0;
			lstP = 0;
			fspeed = 0;
			HARD_MOTOR_ON = 0;
			snapshot_flag = 0;
			}
	}

/************************************************************************************************

    Output PWM values

*************************************************************************************************/

void Handle_Fader(void)
	{
	unsigned int PWM1;
	unsigned int PWM2;


	if (HARD_MOTOR_ON == 0 || touch)                // If host motors off or touch. Check touch variable !!!
		{
		SetDCPWM2(0);                               // Clear PWM
		SetDCPWM1(0);                               
		motor_enable = 0;
		iError = 0;
		dError = 0;
		lastpError = 0;
		return;
		}




	if(fspeed<-1)                                   // Hmmm. -1. is fspeed without decimals
		{                                           // and should it not be 0 ?????
		PWM1=fabs(fspeed);
		if(PWM1>maxPWM) PWM1 = maxPWM;
		PWM2=0;
		motor_enable = 1;                           // This turns on motor driver
		SetDCPWM1(PWM1);
		SetDCPWM2(PWM2);
		}
	else if(fspeed>1)
		{
		PWM2=fabs(fspeed);
		if(PWM2>maxPWM) PWM2 = maxPWM;
		PWM1=0;
		motor_enable = 1;
		SetDCPWM1(PWM1);
		SetDCPWM2(PWM2);
		}
	else
		{
		SetDCPWM2(0);
		SetDCPWM1(0);
		motor_enable = 0;
		return;
		}
	}
	


//---------------------------------------------------------------------
// SSP_Handler
//---------------------------------------------------------------------
// The I2C code below checks for 5 states:
//---------------------------------------------------------------------
// State 1: I2C write operation, last byte was an address byte.
// SSPSTAT bits: S = 1, D_A = 0, R_W = 0, BF = 1
//
// State 2: I2C write operation, last byte was a data byte.
// SSPSTAT bits: S = 1, D_A = 1, R_W = 0, BF = 1
//
// State 3: I2C read operation, last byte was an address byte.
// SSPSTAT bits: S = 1, D_A = 0, R_W = 1 
//
// State 4: I2C read operation, last byte was a data byte.
// SSPSTAT bits: S = 1, D_A = 1, R_W = 1, BF = 0
//
// State 5: Slave I2C logic reset by NACK from master.
// SSPSTAT bits: S = 1, D_A = 1, BF = 0, CKP = 1 
//----------------------------------------------------------------------		

int HandleI2C(void)
	{	
															// copy status register		
		I2CSTAT = SSPSTAT & 0b00101101;						// mask out the used bits
															// decide the state
			if (I2CSTAT == STATE_1){						// address match, write
				index = 0;									// clear buffer index
				address = SSPBUF;							// dummy read to cear BF
				SSPCON1bits.CKP = 1; // release clock		
				return 1;}
			if (I2CSTAT == STATE_2){						// master write byte
				indata.data[index] = SSPBUF;				// read data and clear BF
				SSPCON1bits.CKP = 1; // release clock				
				index++;									// increment index
				if(index>BUFSIZE) index = 0;				// if buffer length exceeded, clear index
				return 2;}
			if ((I2CSTAT & 0b00101100) == STATE_3){			// address match, read (ignore BF bit)
				index = 0;									// clear buffer index
				myWriteI2C();								// a repeating function for writing
				index++;									// increment index
				return 3;}
			if (I2CSTAT == STATE_4){						// master read, buffer is empty. no need to read it.
				if(SSPCON1bits.CKP == 0){					// make sure the clock line hasn't been released
					if(index>BUFSIZE) index = 0;			// if buffer length exceeded, clear index
					myWriteI2C();							// a repeating function for writing
					index++;								// increment index
					return 4;}}
			if ((I2CSTAT & 0b00101000) == STATE_5){			// NACK received when sending data to the master		
			return 5;}										// Mask RW bit in SSPSTAT
		return -1;										    // if no state, return error code
		}

//---------------------------------------------------------------------
// myWriteI2C
//---------------------------------------------------------------------

void myWriteI2C(void)
	{
//	while(SSPSTATbits.BF)									// wait until bus is free
//		{													
//		;
//		}
	do 
		{							
		SSPCON1bits.WCOL = 0;								// clear collision bit
		SSPBUF = outdata.data[index];						// load hardware buffer
		}while(SSPCON1bits.WCOL);							// if there was a collision, try again
		SSPCON1bits.CKP = 1;								// release the clock stretch
	}


//---------------------------------------------------------------------
// scan_switches
//---------------------------------------------------------------------
unsigned char LastStatus=0;

void scan_switches()
{
	unsigned char SwitchBits=0;
	unsigned char PresSwitches=0;
	unsigned char RelSwitches=0;
	unsigned char SwitchXOR=0;

	outdata.data[1] &= 0x03;			// Clear all flags
//	if(AUTO_SW != LastSw) {
	outdata.status=AUTO_SW;
//	}
//	LastSw=AUTO_SW;
/*
	SwitchBits = AUTO_SW;
	SwitchBits = (SwitchBits<<1) + TOUCH_SW;
	SwitchBits = (SwitchBits<<1) + WRITE_SW;
	SwitchBits = (SwitchBits<<1) + MUTE_SW;
	SwitchBits = (SwitchBits<<1) + FADER_TOUCH;

	if(SwitchBits!=StoredSwitchBits) {                            // If previous 8 bits are NOT equal with the current 8 bits:
	    SwitchXOR=SwitchBits^StoredSwitchBits;                    // Create a mask with all changed bits
	    PresSwitches=SwitchBits&SwitchXOR;                        // Mask out all Pressed switches
	    RelSwitches=StoredSwitchBits&SwitchXOR;                    // Mask out all Released Switches

		outdata.touch_press = PresSwitches & 1;
		outdata.touch_release = RelSwitches & 1;
        PresSwitches>>=1;                                            // Shift right
        RelSwitches>>=1;

		outdata.mute_press = PresSwitches & 1;
		outdata.mute_release = RelSwitches & 1;
        PresSwitches>>=1;                                            // Shift right
        RelSwitches>>=1;
		
		if((PresSwitches & 0x01)==0x01)outdata.status=0x01;


	}
	StoredSwitchBits=SwitchBits;                                // Copy Switch pins til next read
*/
}




/************************************************************************************************

    Sample Fader

*************************************************************************************************/

unsigned int Read_Fader(void)
	{
	unsigned int FADER_POS;
	unsigned int AverageRead = 0;
	unsigned int cnt;
	
	SetChanADC(COMP_ADC);
	for (cnt=0;cnt<4;cnt++)                                     // 4 times ??? Nah !!
		{
		ConvertADC();                                           // This could be better. Start first
		while( BusyADC() );	                                    // Read later
		FADER_POS = ADRESH;
		FADER_POS = FADER_POS << 8;
		FADER_POS = FADER_POS + ADRESL;
		AverageRead += FADER_POS;
		}
		return AverageRead / 4;
	}





/************************************************************************************************

    Output PWM values

*************************************************************************************************/

unsigned char Scan_Touch(void)                                  
	{
	unsigned int fader_touch_sens;
	TOUCH_X_OUTPUT;
	TOUCH_X_HIGH;
	SetChanADC(TOUCH_X_ADC);
	TOUCH_OUTPUT;
	TOUCH_LOW;
	TOUCH_INPUT;

	SetChanADC(TOUCH_ADC);
	ConvertADC();
	while( BusyADC() );
	fader_touch_sens = ADRESH;
	fader_touch_sens = fader_touch_sens << 8;
	fader_touch_sens = fader_touch_sens + ADRESL;


	if (fader_touch_sens<TOUCH_SENSE) 
		{	
		if (touch_press > 0) 
			{touch = 1;
			touch_rel = 0;}
		else 
			{
			touch_press +=1;
			BlinkLED = 0;
			BlinkCnt = 0;
			}
		}
	else
		{
		if (touch_rel > 16) touch_press = 0;
		if (touch_rel > TOUCH_RELEASE) 
			{touch = 0;
			}
		else 
			{touch_rel +=1;}			
		}
	return touch;
	}	

void Update_LED_Display_Bits(unsigned int SHIFT_DIGITS)
	{
	unsigned int n;
	for(n=0;n<16;n++)
		{
		LATDbits.LATD0 = SHIFT_DIGITS & 1;
		SHIFT_DIGITS = SHIFT_DIGITS >> 1;
		LATDbits.LATD1 = 1;
		LATDbits.LATD1 = 0;
		}
	LATDbits.LATD2 = 1;
	LATDbits.LATD2 = 0;
	}


void Update_LED_Display(unsigned int displayint)
	{
	unsigned int SHIFT_DIGITS = 0;
	unsigned int n;
	if(displayint<10)
		{
		SHIFT_DIGITS = SEGMENTB[displayint];
		}
	else
		{
		SHIFT_DIGITS = SEGMENTA[displayint/10] + SEGMENTB[displayint%10];
		}
//	SHIFT_DIGITS = SEGMENTA[1];
	for(n=0;n<16;n++)
		{
		LATDbits.LATD0 = SHIFT_DIGITS & 1;
		SHIFT_DIGITS = SHIFT_DIGITS >> 1;
		LATDbits.LATD1 = 1;
		LATDbits.LATD1 = 0;
		}
	LATDbits.LATD2 = 1;
	LATDbits.LATD2 = 0;
	

	}
	

void Handle_LEDs(unsigned char status_bits)
	{
	static char NIBBLE_BUF;
	unsigned char nibble;
	nibble = status_bits&0x0C;
	if (nibble != NIBBLE_BUF) GOAL_CNT = 0;
	NIBBLE_BUF = nibble;
	MUTE_LED = !indata.mute;
	if(SET_FLASH)
		{		
		LATDbits.LATD3 = BlinkLED;                  // LED Display enable. Define !!!!

		}
	else
		{
		LATDbits.LATD3 = 0;
		}
		switch (nibble)
			{
			case 0x00:
			AUTO_LED = 1;
			TOUCH_LED = 1;
			WRITE_LED = 1 & !(BlinkLED & FADER_TOUCH) ;
			break;
			case 0x04:
			AUTO_LED = 0;
			TOUCH_LED = 1;
			WRITE_LED = 1 & !(BlinkLED & FADER_TOUCH) ;
			break;
			case 0x08:
			AUTO_LED = 0;
			TOUCH_LED = 0;
			WRITE_LED = 1 & !(BlinkLED & FADER_TOUCH) ;
			break;
			case 0x0C:
			AUTO_LED = 0;
			TOUCH_LED = 1;
			WRITE_LED = 1 & (BlinkLED & FADER_TOUCH) ;
			break;
			}
	}		
// function
int Calculate_dB_Display(void){
	signed double DIFF;															// variable for exact difference
	int DIFF_DISPLAY;													// variable for truncated difference
	DIFF = FADER_USB;
	DIFF = (DIFF - FADER_IN)*0.05; 							// difference in dB

	if(DIFF==0){															// spot on
		return SEGMENTB[0] & (BlinkLED * 0xFFFF);							// result: blinking zero
		}

	if(DIFF>0){															// if positive difference
		if(DIFF>=10){													// over 10dB +
			return big_plus;												// result: big plus
			}
		else{
			if(DIFF>=1){													// between 1 and 9 dB
				DIFF_DISPLAY = DIFF;									// truncate
				return SEGMENTB[DIFF_DISPLAY];						// result: difference, no sign
				}
			else{															//Â between 0.1 and 0.9 dB
				DIFF_DISPLAY = DIFF * 10;								// truncate and multiply
				return (0x4000 + SEGMENTB[DIFF_DISPLAY]);	// result: difference, with DP
				}		
			}
		}

	else	{																// if negative difference
		if(DIFF<=-10){													// under 10dB -
			return big_minus;												// result: big minus
			}
		else{
			if(DIFF<=-1){												// between -1 and -9 dB
				DIFF_DISPLAY = fabs(DIFF);								// truncate absolute
				return 0x0001 + SEGMENTB[DIFF_DISPLAY];		// result: difference, signed
				}
			else{															//Â between -0.1 and -0.9 dB
				DIFF_DISPLAY = fabs(DIFF * 10);							// truncate and multiply absolute
				return (0x4000 + SEGMENTB[DIFF_DISPLAY]
				+ 0x0001);										// result: difference, signed with DP
				}		
			}
		}
	}

void Init(void)
	{
	unsigned int A,B,C,D,E,F,G,DP;
	OSCTUNEbits.TUN0 = 1;
	OSCTUNEbits.TUN1 = 1;
	OSCTUNEbits.TUN2 = 1;
	OSCTUNEbits.TUN3 = 1;
	OSCTUNEbits.TUN4 = 1;
	OSCCONbits.IRCF0 = 1;
	OSCCONbits.IRCF1 = 1;
	OSCCONbits.IRCF2 = 1;
	OSCTUNEbits.PLLEN = 1;
	OSCTUNEbits.INTSRC = 0;


	TRISA = 0xFF;
	TRISB = 0xF0;	
	TRISC = 0xF8;
	TRISD = 0x00;
	TRISE = 0xFC;

	TRISEbits.PSPMODE = 0;

	TRISCbits.TRISC3 =1;
	TRISCbits.TRISC4 =1;
	OpenI2C (SLAVE_7, SLEW_ON);
	SSPCON2bits.SEN = 1;

		//		SEG 1
		A = 0x0800;			// 4
		B = 0x2000;			// 2
		C = 0x0020;			// 10
		D = 0x0008;			// 12
		E = 0x0004;			// 13
		F = 0x0200;			// 6
		G = 0x0001;			// 15
		DP = 0x4000;			// 1

		SEGMENTA[0] = A + B + C + D   + E + F;
		SEGMENTA[1] = B + C;
		SEGMENTA[2] = A + B + D + E + G;
		SEGMENTA[3] = A + B + C + D + G;
		SEGMENTA[4] = B + C + F + G;
		SEGMENTA[5] = A + C + D + F + G;
		SEGMENTA[6] = A + C + D + E + F + G;
		SEGMENTA[7] = A + B + C;
		SEGMENTA[8] = A + B + C + D + E + F + G;
		SEGMENTA[9] = A + B + C + D + F + G;
		// dots
		SEGMENTA[10] = DP;
		// big plus
		SEGMENTA[11] = A + A;
		// big minus
		SEGMENTA[12] = G;
		
		//		SEG 2
		A = 0x0040;			// 9
		B = 0x0080;			// 8
		C = 0x0400;			// 5
		D = 0x1000;			// 3
		E = 0x8000;			// 0
		F = 0x0010;			// 11
		G = 0x0002;			// 14
		DP = 0x0100;			// 7

		SEGMENTB[0] = A + B + C + D + E + F;
		SEGMENTB[1] = B + C;
		SEGMENTB[2] = A + B + D + E + G;
		SEGMENTB[3] = A + B + C + D + G;
		SEGMENTB[4] = B + C + F + G;
		SEGMENTB[5] = A + C + D + F + G;
		SEGMENTB[6] = A + C + D + E + F + G;
		SEGMENTB[7] = A + B + C;
		SEGMENTB[8] = A + B + C + D + E + F + G;
		SEGMENTB[9] = A + B + C + D + F + G;
		// dots
		SEGMENTB[10] = DP;
		// big plus
		SEGMENTB[11] = D + D;
		// big minus
		SEGMENTB[12] = G;




	// enable interrupts - legacy mode
	INTCONbits.PEIE = 1;
	INTCONbits.GIE = 1;
	PIE1bits.SSPIE = 1; // SSP interrupt enable


	OpenADC(	ADC_FOSC_32     	&
				ADC_RIGHT_JUST		&
				ADC_2_TAD,
				ADC_CH12			&
				ADC_INT_OFF			&
				ADC_VREFPLUS_EXT	&
				ADC_VREFMINUS_EXT
				, 15 );
	//			ADC_VREFPLUS_EXT

	ADCON1 = 0x0C;
	fader_adc = COMP_ADC; 
	OpenTimer2(T2_PS_1_1 & TIMER_INT_ON & T2_POST_1_4);	// 31.248 kHz

	
	// OpenPWM1(0 to 255)  PWM period value
	OpenPWM1(0xFF);									// Turn PWM on
	SetDCPWM1(0); 

	OpenPWM2(0xFF);									// Turn PWM on
	SetDCPWM2(0);  

	fader_ID = ID-1;

	fader_address = fader_ID*2;
	DISPLAY = ID;
	SSPADD = 0xE0 + fader_address; // slave address
	LATDbits.LATD3 = 0;
	}

