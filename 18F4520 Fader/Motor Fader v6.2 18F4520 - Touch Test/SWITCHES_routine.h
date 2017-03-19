
extern unsigned char BlinkLED;
extern unsigned int BlinkCnt;
extern unsigned int SettleCnt;
extern unsigned char faderMode;
extern unsigned char touchThreshold;
extern unsigned int writeCntr;
extern unsigned char LocalStatus;
void Read_Switches(void);
void Scan_Touch(void) ;
void Start_Scan_Touch(void) ;

extern void WriteEEPROM(char address,char data);

