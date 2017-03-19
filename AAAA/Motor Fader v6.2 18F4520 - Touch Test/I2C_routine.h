char HandleI2C(void);
void myWriteI2C(unsigned int data);
unsigned char getQframe(void);
unsigned char getData(unsigned char);
void setData1(unsigned char);
void setData2(unsigned char);

extern union indata {
	unsigned char bytes[2];
	struct  {
		unsigned vca_lo:8;
		unsigned vca_hi:2;
		unsigned status:2;
		unsigned not_used:2;
		unsigned motor_on:1;
		unsigned mute:1;
		};
};
extern union outdata{
	unsigned char bytes[2];
	struct  {
		unsigned vca_lo:8;
		unsigned vca_hi:2;
		unsigned status:2;
		unsigned touch_press:1;
		unsigned touch_release:1;
		unsigned mute_press:1;
		unsigned mute_release:1;
		};
};

extern ram near volatile union indata inbuffer;
extern ram near volatile union outdata outbuffer;

extern unsigned char BlinkLED;
extern unsigned char localTouchSense;



