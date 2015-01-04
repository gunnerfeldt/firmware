

PORTA
	0	Fader ADC
	1	Fader Mute
	2	VREF-
	3	VREF+
	4	NC
	5	NC
	6	OSC
	7	---

PORTB
	0	BANK / CS / comm - inv
	1	CLOCK / comm
	2	NC
	3	DAC data
	4	DAC load
	5	PGM
	6	PGC
	7	PGD

PORTC
	0	SWITCH data
	1	SWITCH load
	2	CLOCK DAC / SWITCH / LED / MUTE
	3	NC
	4	NC
	5	LED / MUTE data
	6	LED load
	7	MUTE load

PORTD
		Comm	

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

unsigned int DAC_steps = 0;
unsigned int DAC_step_cntr = 0;

MUX[0]=0x2;
MUX[1]=0x0;
MUX[2]=0x1;
MUX[3]=0x3;
MUX[4]=0x5;
MUX[5]=0x6;
MUX[6]=0x7;
MUX[7]=0x4;
