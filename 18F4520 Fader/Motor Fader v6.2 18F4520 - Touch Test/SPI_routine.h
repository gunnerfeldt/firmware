
unsigned char getQframe(void);
unsigned char getData(unsigned char);
void setData1(unsigned char);
void setData2(unsigned char);
char Read_SPI(void);
void Write_SPI(unsigned int data);

enum CMD {           /* typedef removed, */
    handshake,
	idChange
 };
union indata {
	unsigned char bytes[2];
	struct  {
		unsigned vca_lo:8;
		unsigned vca_hi:2;
		unsigned status:2;
		unsigned :2;
		unsigned motor_on:1;
		unsigned mute:1;
  };
  struct  {
    unsigned CHANNEL_ID:7;
    unsigned :1;
    unsigned CMD:4;				// This has 16 different commands when CMD_FLAG is 1
    unsigned CMD_FLAG:1;		// This means no Fader dat, only command
    unsigned BLINK_EVENT:1;		// This can be set with data
    unsigned :2;
  };
  struct  {
    unsigned LO_BYTE:8;
    unsigned :5;
    unsigned HI_BYTE:2;
    unsigned :1;
    };
	unsigned int word;
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
	unsigned int word;
};

extern ram near union indata inbuffer;
extern ram near union outdata outbuffer;

extern unsigned char BlinkLED;
extern unsigned char LocalTouch;

extern unsigned char xID;
