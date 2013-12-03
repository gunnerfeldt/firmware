#line 1 "main.c"
#line 1 "main.c"









#line 1 "C:/MCC18/h/p18f25k22.h"

#line 5 "C:/MCC18/h/p18f25k22.h"
 


#line 9 "C:/MCC18/h/p18f25k22.h"

extern volatile far  unsigned char       ANSELA;
extern volatile far  struct {
  unsigned ANSA0:1;
  unsigned ANSA1:1;
  unsigned ANSA2:1;
  unsigned ANSA3:1;
  unsigned :1;
  unsigned ANSA5:1;
} ANSELAbits;
extern volatile far  unsigned char       ANSELB;
extern volatile far  struct {
  unsigned ANSB0:1;
  unsigned ANSB1:1;
  unsigned ANSB2:1;
  unsigned ANSB3:1;
  unsigned ANSB4:1;
  unsigned ANSB5:1;
} ANSELBbits;
extern volatile far  unsigned char       ANSELC;
extern volatile far  struct {
  unsigned :2;
  unsigned ANSC2:1;
  unsigned ANSC3:1;
  unsigned ANSC4:1;
  unsigned ANSC5:1;
  unsigned ANSC6:1;
  unsigned ANSC7:1;
} ANSELCbits;
extern volatile far  unsigned char       PMD2;
extern volatile far  struct {
  unsigned ADCMD:1;
  unsigned CMP1MD:1;
  unsigned CMP2MD:1;
  unsigned CTMUMD:1;
} PMD2bits;
extern volatile far  unsigned char       PMD1;
extern volatile far  struct {
  unsigned CCP1MD:1;
  unsigned CCP2MD:1;
  unsigned CCP3MD:1;
  unsigned CCP4MD:1;
  unsigned CCP5MD:1;
  unsigned :1;
  unsigned MSSP1MD:1;
  unsigned MSSP2MD:1;
} PMD1bits;
extern volatile far  unsigned char       PMD0;
extern volatile far  struct {
  unsigned TMR1MD:1;
  unsigned TMR2MD:1;
  unsigned TMR3MD:1;
  unsigned TMR4MD:1;
  unsigned TMR5MD:1;
  unsigned TMR6MD:1;
  unsigned UART1MD:1;
  unsigned UART2MD:1;
} PMD0bits;
extern volatile far  unsigned char       DACCON1;
extern volatile far  union {
  struct {
    unsigned DACR:5;
  };
  struct {
    unsigned DACR0:1;
    unsigned DACR1:1;
    unsigned DACR2:1;
    unsigned DACR3:1;
    unsigned DACR4:1;
  };
} DACCON1bits;
extern volatile far  unsigned char       VREFCON2;
extern volatile far  union {
  struct {
    unsigned DACR:5;
  };
  struct {
    unsigned DACR0:1;
    unsigned DACR1:1;
    unsigned DACR2:1;
    unsigned DACR3:1;
    unsigned DACR4:1;
  };
} VREFCON2bits;
extern volatile far  unsigned char       DACCON0;
extern volatile far  union {
  struct {
    unsigned DACNSS:1;
    unsigned :1;
    unsigned DACPSS:2;
    unsigned :1;
    unsigned DACOE:1;
    unsigned DACLPS:1;
    unsigned DACEN:1;
  };
  struct {
    unsigned :2;
    unsigned DACPSS0:1;
    unsigned DACPSS1:1;
  };
} DACCON0bits;
extern volatile far  unsigned char       VREFCON1;
extern volatile far  union {
  struct {
    unsigned DACNSS:1;
    unsigned :1;
    unsigned DACPSS:2;
    unsigned :1;
    unsigned DACOE:1;
    unsigned DACLPS:1;
    unsigned DACEN:1;
  };
  struct {
    unsigned :2;
    unsigned DACPSS0:1;
    unsigned DACPSS1:1;
  };
} VREFCON1bits;
extern volatile far  unsigned char       FVRCON;
extern volatile far  union {
  struct {
    unsigned :4;
    unsigned FVRS:2;
    unsigned FVRST:1;
    unsigned FVREN:1;
  };
  struct {
    unsigned :4;
    unsigned FVRS0:1;
    unsigned FVRS1:1;
  };
} FVRCONbits;
extern volatile far  unsigned char       VREFCON0;
extern volatile far  union {
  struct {
    unsigned :4;
    unsigned FVRS:2;
    unsigned FVRST:1;
    unsigned FVREN:1;
  };
  struct {
    unsigned :4;
    unsigned FVRS0:1;
    unsigned FVRS1:1;
  };
} VREFCON0bits;
extern volatile far  unsigned char       CTMUICON;
extern volatile far  union {
  struct {
    unsigned IRNG:2;
    unsigned ITRIM:6;
  };
  struct {
    unsigned IRNG0:1;
    unsigned IRNG1:1;
    unsigned ITRIM0:1;
    unsigned ITRIM1:1;
    unsigned ITRIM2:1;
    unsigned ITRIM3:1;
    unsigned ITRIM4:1;
    unsigned ITRIM5:1;
  };
} CTMUICONbits;
extern volatile far  unsigned char       CTMUICONH;
extern volatile far  union {
  struct {
    unsigned IRNG:2;
    unsigned ITRIM:6;
  };
  struct {
    unsigned IRNG0:1;
    unsigned IRNG1:1;
    unsigned ITRIM0:1;
    unsigned ITRIM1:1;
    unsigned ITRIM2:1;
    unsigned ITRIM3:1;
    unsigned ITRIM4:1;
    unsigned ITRIM5:1;
  };
} CTMUICONHbits;
extern volatile far  unsigned char       CTMUCON1;
extern volatile far  union {
  struct {
    unsigned EDG1STAT:1;
    unsigned EDG2STAT:1;
    unsigned EDG1SEL:2;
    unsigned EDG1POL:1;
    unsigned EDG2SEL:2;
    unsigned EDG2POL:1;
  };
  struct {
    unsigned :2;
    unsigned EDG1SEL0:1;
    unsigned EDG1SEL1:1;
    unsigned :1;
    unsigned EDG2SEL0:1;
    unsigned EDG2SEL1:1;
  };
} CTMUCON1bits;
extern volatile far  unsigned char       CTMUCONL;
extern volatile far  union {
  struct {
    unsigned EDG1STAT:1;
    unsigned EDG2STAT:1;
    unsigned EDG1SEL:2;
    unsigned EDG1POL:1;
    unsigned EDG2SEL:2;
    unsigned EDG2POL:1;
  };
  struct {
    unsigned :2;
    unsigned EDG1SEL0:1;
    unsigned EDG1SEL1:1;
    unsigned :1;
    unsigned EDG2SEL0:1;
    unsigned EDG2SEL1:1;
  };
} CTMUCONLbits;
extern volatile far  unsigned char       CTMUCON0;
extern volatile far  struct {
  unsigned CTTRIG:1;
  unsigned IDISSEN:1;
  unsigned EDGSEQEN:1;
  unsigned EDGEN:1;
  unsigned TGEN:1;
  unsigned CTMUSIDL:1;
  unsigned :1;
  unsigned CTMUEN:1;
} CTMUCON0bits;
extern volatile far  unsigned char       CTMUCONH;
extern volatile far  struct {
  unsigned CTTRIG:1;
  unsigned IDISSEN:1;
  unsigned EDGSEQEN:1;
  unsigned EDGEN:1;
  unsigned TGEN:1;
  unsigned CTMUSIDL:1;
  unsigned :1;
  unsigned CTMUEN:1;
} CTMUCONHbits;
extern volatile far  unsigned char       SRCON1;
extern volatile far  struct {
  unsigned SRRC1E:1;
  unsigned SRRC2E:1;
  unsigned SRRCKE:1;
  unsigned SRRPE:1;
  unsigned SRSC1E:1;
  unsigned SRSC2E:1;
  unsigned SRSCKE:1;
  unsigned SRSPE:1;
} SRCON1bits;
extern volatile far  unsigned char       SRCON0;
extern volatile far  union {
  struct {
    unsigned SRPR:1;
    unsigned SRPS:1;
    unsigned SRNQEN:1;
    unsigned SRQEN:1;
    unsigned SRCLK:3;
    unsigned SRLEN:1;
  };
  struct {
    unsigned :4;
    unsigned SRCLK0:1;
    unsigned SRCLK1:1;
    unsigned SRCLK2:1;
  };
} SRCON0bits;
extern volatile far  unsigned char       CCPTMRS1;
extern volatile far  union {
  struct {
    unsigned C4TSEL:2;
    unsigned C5TSEL:2;
  };
  struct {
    unsigned C4TSEL0:1;
    unsigned C4TSEL1:1;
    unsigned C5TSEL0:1;
    unsigned C5TSEL1:1;
  };
} CCPTMRS1bits;
extern volatile far  unsigned char       CCPTMRS0;
extern volatile far  union {
  struct {
    unsigned C1TSEL:2;
    unsigned :1;
    unsigned C2TSEL:2;
    unsigned :1;
    unsigned C3TSEL:2;
  };
  struct {
    unsigned C1TSEL0:1;
    unsigned C1TSEL1:1;
    unsigned :1;
    unsigned C2TSEL0:1;
    unsigned C2TSEL1:1;
    unsigned :1;
    unsigned C3TSEL0:1;
    unsigned C3TSEL1:1;
  };
} CCPTMRS0bits;
extern volatile far  unsigned char       T6CON;
extern volatile far  union {
  struct {
    unsigned T6CKPS:2;
    unsigned TMR6ON:1;
    unsigned T6OUTPS:4;
  };
  struct {
    unsigned T6CKPS0:1;
    unsigned T6CKPS1:1;
    unsigned :1;
    unsigned T6OUTPS0:1;
    unsigned T6OUTPS1:1;
    unsigned T6OUTPS2:1;
    unsigned T6OUTPS3:1;
  };
} T6CONbits;
extern volatile far  unsigned char       PR6;
extern volatile far  unsigned char       TMR6;
extern volatile far  unsigned char       T5GCON;
extern volatile far  union {
  struct {
    unsigned T5GSS:2;
    unsigned T5GVAL:1;
    unsigned T5GGO_NOT_DONE:1;
    unsigned T5GSPM:1;
    unsigned T5GTM:1;
    unsigned T5GPOL:1;
    unsigned TMR5GE:1;
  };
  struct {
    unsigned T5GSS0:1;
    unsigned T5GSS1:1;
    unsigned :1;
    unsigned T5GGO:1;
  };
  struct {
    unsigned :3;
    unsigned T5G_DONE:1;
  };
} T5GCONbits;
extern volatile far  unsigned char       T5CON;
extern volatile far  union {
  struct {
    unsigned TMR5ON:1;
    unsigned T5RD16:1;
    unsigned NOT_T5SYNC:1;
    unsigned T5SOSCEN:1;
    unsigned T5CKPS:2;
    unsigned TMR5CS:2;
  };
  struct {
    unsigned :2;
    unsigned T5SYNC:1;
    unsigned :1;
    unsigned T5CKPS0:1;
    unsigned T5CKPS1:1;
    unsigned TMR5CS0:1;
    unsigned TMR5CS1:1;
  };
} T5CONbits;
extern volatile far  unsigned char       TMR5L;
extern volatile far  unsigned char       TMR5H;
extern volatile far  unsigned char       T4CON;
extern volatile far  union {
  struct {
    unsigned T4CKPS:2;
    unsigned TMR4ON:1;
    unsigned T4OUTPS:4;
  };
  struct {
    unsigned T4CKPS0:1;
    unsigned T4CKPS1:1;
    unsigned :1;
    unsigned T4OUTPS0:1;
    unsigned T4OUTPS1:1;
    unsigned T4OUTPS2:1;
    unsigned T4OUTPS3:1;
  };
} T4CONbits;
extern volatile far  unsigned char       PR4;
extern volatile far  unsigned char       TMR4;
extern volatile far  unsigned char       CCP5CON;
extern volatile far  union {
  struct {
    unsigned CCP5M:4;
    unsigned DC5B:2;
  };
  struct {
    unsigned CCP5M0:1;
    unsigned CCP5M1:1;
    unsigned CCP5M2:1;
    unsigned CCP5M3:1;
    unsigned DC5B0:1;
    unsigned DC5B1:1;
  };
} CCP5CONbits;
extern volatile far  unsigned char       CCPR5;
extern volatile far  unsigned char       CCPR5L;
extern volatile far  unsigned char       CCPR5H;
extern volatile far  unsigned char       CCP4CON;
extern volatile far  union {
  struct {
    unsigned CCP4M:4;
    unsigned DC4B:2;
  };
  struct {
    unsigned CCP4M0:1;
    unsigned CCP4M1:1;
    unsigned CCP4M2:1;
    unsigned CCP4M3:1;
    unsigned DC4B0:1;
    unsigned DC4B1:1;
  };
} CCP4CONbits;
extern volatile far  unsigned char       CCPR4;
extern volatile far  unsigned char       CCPR4L;
extern volatile far  unsigned char       CCPR4H;
extern volatile far  unsigned char       PSTR3CON;
extern volatile far  struct {
  unsigned STR3A:1;
  unsigned STR3B:1;
  unsigned STR3C:1;
  unsigned STR3D:1;
  unsigned STR3SYNC:1;
} PSTR3CONbits;
extern volatile far  unsigned char       CCP3AS;
extern volatile far  union {
  struct {
    unsigned PSS3BD:2;
    unsigned PSS3AC:2;
    unsigned CCP3AS:3;
    unsigned CCP3ASE:1;
  };
  struct {
    unsigned PSS3BD0:1;
    unsigned PSS3BD1:1;
    unsigned PSS3AC0:1;
    unsigned PSS3AC1:1;
    unsigned CCP3AS0:1;
    unsigned CCP3AS1:1;
    unsigned CCP3AS2:1;
  };
} CCP3ASbits;
extern volatile far  unsigned char       ECCP3AS;
extern volatile far  union {
  struct {
    unsigned PSS3BD:2;
    unsigned PSS3AC:2;
    unsigned CCP3AS:3;
    unsigned CCP3ASE:1;
  };
  struct {
    unsigned PSS3BD0:1;
    unsigned PSS3BD1:1;
    unsigned PSS3AC0:1;
    unsigned PSS3AC1:1;
    unsigned CCP3AS0:1;
    unsigned CCP3AS1:1;
    unsigned CCP3AS2:1;
  };
} ECCP3ASbits;
extern volatile far  unsigned char       PWM3CON;
extern volatile far  union {
  struct {
    unsigned P3DC:7;
    unsigned P3RSEN:1;
  };
  struct {
    unsigned P3DC0:1;
    unsigned P3DC1:1;
    unsigned P3DC2:1;
    unsigned P3DC3:1;
    unsigned P3DC4:1;
    unsigned P3DC5:1;
    unsigned P3DC6:1;
  };
} PWM3CONbits;
extern volatile far  unsigned char       CCP3CON;
extern volatile far  union {
  struct {
    unsigned CCP3M:4;
    unsigned DC3B:2;
    unsigned P3M:2;
  };
  struct {
    unsigned CCP3M0:1;
    unsigned CCP3M1:1;
    unsigned CCP3M2:1;
    unsigned CCP3M3:1;
    unsigned DC3B0:1;
    unsigned DC3B1:1;
    unsigned P3M0:1;
    unsigned P3M1:1;
  };
} CCP3CONbits;
extern volatile far  unsigned char       CCPR3;
extern volatile far  unsigned char       CCPR3L;
extern volatile far  unsigned char       CCPR3H;
extern volatile near unsigned char       SLRCON;
extern volatile near struct {
  unsigned SLRA:1;
  unsigned SLRB:1;
  unsigned SLRC:1;
} SLRCONbits;
extern volatile near unsigned char       WPUB;
extern volatile near struct {
  unsigned WPUB0:1;
  unsigned WPUB1:1;
  unsigned WPUB2:1;
  unsigned WPUB3:1;
  unsigned WPUB4:1;
  unsigned WPUB5:1;
  unsigned WPUB6:1;
  unsigned WPUB7:1;
} WPUBbits;
extern volatile near unsigned char       IOCB;
extern volatile near struct {
  unsigned :4;
  unsigned IOCB4:1;
  unsigned IOCB5:1;
  unsigned IOCB6:1;
  unsigned IOCB7:1;
} IOCBbits;
extern volatile near unsigned char       PSTR2CON;
extern volatile near struct {
  unsigned STR2A:1;
  unsigned STR2B:1;
  unsigned STR2C:1;
  unsigned STR2D:1;
  unsigned STR2SYNC:1;
} PSTR2CONbits;
extern volatile near unsigned char       CCP2AS;
extern volatile near union {
  struct {
    unsigned PSS2BD:2;
    unsigned PSS2AC:2;
    unsigned CCP2AS:3;
    unsigned CCP2ASE:1;
  };
  struct {
    unsigned PSS2BD0:1;
    unsigned PSS2BD1:1;
    unsigned PSS2AC0:1;
    unsigned PSS2AC1:1;
    unsigned CCP2AS0:1;
    unsigned CCP2AS1:1;
    unsigned CCP2AS2:1;
  };
} CCP2ASbits;
extern volatile near unsigned char       ECCP2AS;
extern volatile near union {
  struct {
    unsigned PSS2BD:2;
    unsigned PSS2AC:2;
    unsigned CCP2AS:3;
    unsigned CCP2ASE:1;
  };
  struct {
    unsigned PSS2BD0:1;
    unsigned PSS2BD1:1;
    unsigned PSS2AC0:1;
    unsigned PSS2AC1:1;
    unsigned CCP2AS0:1;
    unsigned CCP2AS1:1;
    unsigned CCP2AS2:1;
  };
} ECCP2ASbits;
extern volatile near unsigned char       PWM2CON;
extern volatile near union {
  struct {
    unsigned P2DC:7;
    unsigned P2RSEN:1;
  };
  struct {
    unsigned P2DC0:1;
    unsigned P2DC1:1;
    unsigned P2DC2:1;
    unsigned P2DC3:1;
    unsigned P2DC4:1;
    unsigned P2DC5:1;
    unsigned P2DC6:1;
  };
} PWM2CONbits;
extern volatile near unsigned char       CCP2CON;
extern volatile near union {
  struct {
    unsigned CCP2M:4;
    unsigned DC2B:2;
    unsigned P2M0:1;
    unsigned P2M1:1;
  };
  struct {
    unsigned CCP2M0:1;
    unsigned CCP2M1:1;
    unsigned CCP2M2:1;
    unsigned CCP2M3:1;
    unsigned DC2B0:1;
    unsigned DC2B1:1;
  };
} CCP2CONbits;
extern volatile near unsigned            CCPR2;
extern volatile near unsigned char       CCPR2L;
extern volatile near unsigned char       CCPR2H;
extern volatile near unsigned char       SSP2CON3;
extern volatile near struct {
  unsigned DHEN:1;
  unsigned AHEN:1;
  unsigned SBCDE:1;
  unsigned SDAHT:1;
  unsigned BOEN:1;
  unsigned SCIE:1;
  unsigned PCIE:1;
  unsigned ACKTIM:1;
} SSP2CON3bits;
extern volatile near unsigned char       SSP2MSK;
extern volatile near struct {
  unsigned MSK0:1;
  unsigned MSK1:1;
  unsigned MSK2:1;
  unsigned MSK3:1;
  unsigned MSK4:1;
  unsigned MSK5:1;
  unsigned MSK6:1;
  unsigned MSK7:1;
} SSP2MSKbits;
extern volatile near unsigned char       SSP2CON2;
extern volatile near struct {
  unsigned SEN:1;
  unsigned RSEN:1;
  unsigned PEN:1;
  unsigned RCEN:1;
  unsigned ACKEN:1;
  unsigned ACKDT:1;
  unsigned ACKSTAT:1;
  unsigned GCEN:1;
} SSP2CON2bits;
extern volatile near unsigned char       SSP2CON1;
extern volatile near union {
  struct {
    unsigned SSPM:4;
    unsigned CKP:1;
    unsigned SSPEN:1;
    unsigned SSPOV:1;
    unsigned WCOL:1;
  };
  struct {
    unsigned SSPM0:1;
    unsigned SSPM1:1;
    unsigned SSPM2:1;
    unsigned SSPM3:1;
  };
} SSP2CON1bits;
extern volatile near unsigned char       SSP2STAT;
extern volatile near union {
  struct {
    unsigned BF:1;
    unsigned UA:1;
    unsigned R_NOT_W:1;
    unsigned S:1;
    unsigned P:1;
    unsigned D_NOT_A:1;
    unsigned CKE:1;
    unsigned SMP:1;
  };
  struct {
    unsigned :2;
    unsigned R:1;
    unsigned :2;
    unsigned D:1;
  };
  struct {
    unsigned :2;
    unsigned W:1;
    unsigned :2;
    unsigned A:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_W:1;
    unsigned :2;
    unsigned NOT_A:1;
  };
  struct {
    unsigned :2;
    unsigned R_W:1;
    unsigned :2;
    unsigned D_A:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_WRITE:1;
    unsigned :2;
    unsigned NOT_ADDRESS:1;
  };
} SSP2STATbits;
extern volatile near unsigned char       SSP2ADD;
extern volatile near unsigned char       SSP2BUF;
extern volatile near unsigned char       BAUD2CON;
extern volatile near union {
  struct {
    unsigned ABDEN:1;
    unsigned WUE:1;
    unsigned :1;
    unsigned BRG16:1;
    unsigned CKTXP:1;
    unsigned DTRXP:1;
    unsigned RCIDL:1;
    unsigned ABDOVF:1;
  };
  struct {
    unsigned :4;
    unsigned SCKP:1;
  };
} BAUD2CONbits;
extern volatile near unsigned char       BAUDCON2;
extern volatile near union {
  struct {
    unsigned ABDEN:1;
    unsigned WUE:1;
    unsigned :1;
    unsigned BRG16:1;
    unsigned CKTXP:1;
    unsigned DTRXP:1;
    unsigned RCIDL:1;
    unsigned ABDOVF:1;
  };
  struct {
    unsigned :4;
    unsigned SCKP:1;
  };
} BAUDCON2bits;
extern volatile near unsigned char       RC2STA;
extern volatile near union {
  struct {
    unsigned RX9D:1;
    unsigned OERR:1;
    unsigned FERR:1;
    unsigned ADDEN:1;
    unsigned CREN:1;
    unsigned SREN:1;
    unsigned RX9:1;
    unsigned SPEN:1;
  };
  struct {
    unsigned :3;
    unsigned ADEN:1;
  };
} RC2STAbits;
extern volatile near unsigned char       RCSTA2;
extern volatile near union {
  struct {
    unsigned RX9D:1;
    unsigned OERR:1;
    unsigned FERR:1;
    unsigned ADDEN:1;
    unsigned CREN:1;
    unsigned SREN:1;
    unsigned RX9:1;
    unsigned SPEN:1;
  };
  struct {
    unsigned :3;
    unsigned ADEN:1;
  };
} RCSTA2bits;
extern volatile near unsigned char       TX2STA;
extern volatile near struct {
  unsigned TX9D:1;
  unsigned TRMT:1;
  unsigned BRGH:1;
  unsigned SENDB:1;
  unsigned SYNC:1;
  unsigned TXEN:1;
  unsigned TX9:1;
  unsigned CSRC:1;
} TX2STAbits;
extern volatile near unsigned char       TXSTA2;
extern volatile near struct {
  unsigned TX9D:1;
  unsigned TRMT:1;
  unsigned BRGH:1;
  unsigned SENDB:1;
  unsigned SYNC:1;
  unsigned TXEN:1;
  unsigned TX9:1;
  unsigned CSRC:1;
} TXSTA2bits;
extern volatile near unsigned char       TX2REG;
extern volatile near unsigned char       TXREG2;
extern volatile near unsigned char       RC2REG;
extern volatile near unsigned char       RCREG2;
extern volatile near unsigned char       SP2BRG;
extern volatile near unsigned char       SPBRG2;
extern volatile near unsigned char       SP2BRGH;
extern volatile near unsigned char       SPBRGH2;
extern volatile near unsigned char       CM12CON;
extern volatile near struct {
  unsigned C2SYNC:1;
  unsigned C1SYNC:1;
  unsigned C2HYS:1;
  unsigned C1HYS:1;
  unsigned C2RSEL:1;
  unsigned C1RSEL:1;
  unsigned MC2OUT:1;
  unsigned MC1OUT:1;
} CM12CONbits;
extern volatile near unsigned char       CM2CON1;
extern volatile near struct {
  unsigned C2SYNC:1;
  unsigned C1SYNC:1;
  unsigned C2HYS:1;
  unsigned C1HYS:1;
  unsigned C2RSEL:1;
  unsigned C1RSEL:1;
  unsigned MC2OUT:1;
  unsigned MC1OUT:1;
} CM2CON1bits;
extern volatile near unsigned char       CM2CON;
extern volatile near union {
  struct {
    unsigned C2CH:2;
    unsigned C2R:1;
    unsigned C2SP:1;
    unsigned C2POL:1;
    unsigned C2OE:1;
    unsigned C2OUT:1;
    unsigned C2ON:1;
  };
  struct {
    unsigned C2CH0:1;
    unsigned C2CH1:1;
  };
} CM2CONbits;
extern volatile near unsigned char       CM2CON0;
extern volatile near union {
  struct {
    unsigned C2CH:2;
    unsigned C2R:1;
    unsigned C2SP:1;
    unsigned C2POL:1;
    unsigned C2OE:1;
    unsigned C2OUT:1;
    unsigned C2ON:1;
  };
  struct {
    unsigned C2CH0:1;
    unsigned C2CH1:1;
  };
} CM2CON0bits;
extern volatile near unsigned char       CM1CON;
extern volatile near union {
  struct {
    unsigned C1CH:2;
    unsigned C1R:1;
    unsigned C1SP:1;
    unsigned C1POL:1;
    unsigned C1OE:1;
    unsigned C1OUT:1;
    unsigned C1ON:1;
  };
  struct {
    unsigned C1CH0:1;
    unsigned C1CH1:1;
  };
} CM1CONbits;
extern volatile near unsigned char       CM1CON0;
extern volatile near union {
  struct {
    unsigned C1CH:2;
    unsigned C1R:1;
    unsigned C1SP:1;
    unsigned C1POL:1;
    unsigned C1OE:1;
    unsigned C1OUT:1;
    unsigned C1ON:1;
  };
  struct {
    unsigned C1CH0:1;
    unsigned C1CH1:1;
  };
} CM1CON0bits;
extern volatile near unsigned char       PIE4;
extern volatile near struct {
  unsigned CCP3IE:1;
  unsigned CCP4IE:1;
  unsigned CCP5IE:1;
} PIE4bits;
extern volatile near unsigned char       PIR4;
extern volatile near struct {
  unsigned CCP3IF:1;
  unsigned CCP4IF:1;
  unsigned CCP5IF:1;
} PIR4bits;
extern volatile near unsigned char       IPR4;
extern volatile near struct {
  unsigned CCP3IP:1;
  unsigned CCP4IP:1;
  unsigned CCP5IP:1;
} IPR4bits;
extern volatile near unsigned char       PIE5;
extern volatile near struct {
  unsigned TMR4IE:1;
  unsigned TMR5IE:1;
  unsigned TMR6IE:1;
} PIE5bits;
extern volatile near unsigned char       PIR5;
extern volatile near struct {
  unsigned TMR4IF:1;
  unsigned TMR5IF:1;
  unsigned TMR6IF:1;
} PIR5bits;
extern volatile near unsigned char       IPR5;
extern volatile near struct {
  unsigned TMR4IP:1;
  unsigned TMR5IP:1;
  unsigned TMR6IP:1;
} IPR5bits;
extern volatile near unsigned char       PORTA;
extern volatile near union {
  struct {
    unsigned RA0:1;
    unsigned RA1:1;
    unsigned RA2:1;
    unsigned RA3:1;
    unsigned RA4:1;
    unsigned RA5:1;
    unsigned RA6:1;
    unsigned RA7:1;
  };
  struct {
    unsigned AN0:1;
    unsigned AN1:1;
    unsigned AN2:1;
    unsigned AN3:1;
    unsigned :1;
    unsigned AN4:1;
  };
  struct {
    unsigned C12IN0M:1;
    unsigned C12IN1M:1;
    unsigned C2INP:1;
    unsigned C1INP:1;
    unsigned C1OUT:1;
    unsigned C2OUT:1;
  };
  struct {
    unsigned C12IN0N:1;
    unsigned C12IN1N:1;
    unsigned VREFM:1;
    unsigned VREFP:1;
    unsigned T0CKI:1;
    unsigned SS:1;
  };
  struct {
    unsigned :2;
    unsigned VREFN:1;
    unsigned :1;
    unsigned SRQ:1;
    unsigned NOT_SS:1;
  };
  struct {
    unsigned :2;
    unsigned CVREF:1;
    unsigned :1;
    unsigned CCP5:1;
    unsigned LVDIN:1;
  };
  struct {
    unsigned :2;
    unsigned DACOUT:1;
    unsigned :2;
    unsigned HLVDIN:1;
  };
  struct {
    unsigned :5;
    unsigned SS1:1;
  };
  struct {
    unsigned :5;
    unsigned NOT_SS1:1;
  };
  struct {
    unsigned :5;
    unsigned SRNQ:1;
  };
} PORTAbits;
extern volatile near unsigned char       PORTB;
extern volatile near union {
  struct {
    unsigned RB0:1;
    unsigned RB1:1;
    unsigned RB2:1;
    unsigned RB3:1;
    unsigned RB4:1;
    unsigned RB5:1;
    unsigned RB6:1;
    unsigned RB7:1;
  };
  struct {
    unsigned INT0:1;
    unsigned INT1:1;
    unsigned INT2:1;
    unsigned CCP2:1;
    unsigned KBI0:1;
    unsigned KBI1:1;
    unsigned KBI2:1;
    unsigned KBI3:1;
  };
  struct {
    unsigned AN12:1;
    unsigned AN10:1;
    unsigned AN8:1;
    unsigned AN9:1;
    unsigned AN11:1;
    unsigned AN13:1;
    unsigned TX2:1;
    unsigned RX2:1;
  };
  struct {
    unsigned FLT0:1;
    unsigned C12IN3M:1;
    unsigned P1B:1;
    unsigned C12IN2M:1;
    unsigned T5G:1;
    unsigned T1G:1;
    unsigned CK2:1;
    unsigned DT2:1;
  };
  struct {
    unsigned SRI:1;
    unsigned C12IN3N:1;
    unsigned CTED1:1;
    unsigned C12IN2N:1;
    unsigned P1D:1;
    unsigned CCP3:1;
    unsigned PGC:1;
    unsigned PGD:1;
  };
  struct {
    unsigned CCP4:1;
    unsigned P1C:1;
    unsigned SDA2:1;
    unsigned CTED2:1;
    unsigned :1;
    unsigned T3CKI:1;
  };
  struct {
    unsigned SS2:1;
    unsigned SCL2:1;
    unsigned SDI2:1;
    unsigned P2A:1;
    unsigned :1;
    unsigned P3A:1;
  };
  struct {
    unsigned NOT_SS2:1;
    unsigned SCK2:1;
    unsigned :1;
    unsigned SDO2:1;
    unsigned :1;
    unsigned P2B:1;
  };
} PORTBbits;
extern volatile near unsigned char       PORTC;
extern volatile near union {
  struct {
    unsigned RC0:1;
    unsigned RC1:1;
    unsigned RC2:1;
    unsigned RC3:1;
    unsigned RC4:1;
    unsigned RC5:1;
    unsigned RC6:1;
    unsigned RC7:1;
  };
  struct {
    unsigned T1OSO:1;
    unsigned T1OSI:1;
    unsigned T5CKI:1;
    unsigned SCK:1;
    unsigned SDI:1;
    unsigned SDO:1;
    unsigned TX:1;
    unsigned RX:1;
  };
  struct {
    unsigned P2B:1;
    unsigned P2A:1;
    unsigned P1A:1;
    unsigned SCL:1;
    unsigned SDA:1;
    unsigned :1;
    unsigned CK:1;
    unsigned DT:1;
  };
  struct {
    unsigned T1CKI:1;
    unsigned CCP2:1;
    unsigned CCP1:1;
    unsigned SCK1:1;
    unsigned SDI1:1;
    unsigned SDO1:1;
    unsigned TX1:1;
    unsigned RX1:1;
  };
  struct {
    unsigned T3CKI:1;
    unsigned :1;
    unsigned CTPLS:1;
    unsigned SCL1:1;
    unsigned SDA1:1;
    unsigned :1;
    unsigned CK1:1;
    unsigned DT1:1;
  };
  struct {
    unsigned T3G:1;
    unsigned :1;
    unsigned AN14:1;
    unsigned AN15:1;
    unsigned AN16:1;
    unsigned AN17:1;
    unsigned AN18:1;
    unsigned AN19:1;
  };
  struct {
    unsigned :6;
    unsigned CCP3:1;
    unsigned P3B:1;
  };
  struct {
    unsigned :6;
    unsigned P3A:1;
  };
} PORTCbits;
extern volatile near unsigned char       PORTE;
extern volatile near union {
  struct {
    unsigned :3;
    unsigned RE3:1;
  };
  struct {
    unsigned :3;
    unsigned MCLR:1;
  };
  struct {
    unsigned :3;
    unsigned NOT_MCLR:1;
  };
  struct {
    unsigned :3;
    unsigned VPP:1;
  };
} PORTEbits;
extern volatile near unsigned char       LATA;
extern volatile near struct {
  unsigned LATA0:1;
  unsigned LATA1:1;
  unsigned LATA2:1;
  unsigned LATA3:1;
  unsigned LATA4:1;
  unsigned LATA5:1;
  unsigned LATA6:1;
  unsigned LATA7:1;
} LATAbits;
extern volatile near unsigned char       LATB;
extern volatile near struct {
  unsigned LATB0:1;
  unsigned LATB1:1;
  unsigned LATB2:1;
  unsigned LATB3:1;
  unsigned LATB4:1;
  unsigned LATB5:1;
  unsigned LATB6:1;
  unsigned LATB7:1;
} LATBbits;
extern volatile near unsigned char       LATC;
extern volatile near struct {
  unsigned LATC0:1;
  unsigned LATC1:1;
  unsigned LATC2:1;
  unsigned LATC3:1;
  unsigned LATC4:1;
  unsigned LATC5:1;
  unsigned LATC6:1;
  unsigned LATC7:1;
} LATCbits;
extern volatile near unsigned char       DDRA;
extern volatile near union {
  struct {
    unsigned TRISA0:1;
    unsigned TRISA1:1;
    unsigned TRISA2:1;
    unsigned TRISA3:1;
    unsigned TRISA4:1;
    unsigned TRISA5:1;
    unsigned TRISA6:1;
    unsigned TRISA7:1;
  };
  struct {
    unsigned RA0:1;
    unsigned RA1:1;
    unsigned RA2:1;
    unsigned RA3:1;
    unsigned RA4:1;
    unsigned RA5:1;
    unsigned RA6:1;
    unsigned RA7:1;
  };
} DDRAbits;
extern volatile near unsigned char       TRISA;
extern volatile near union {
  struct {
    unsigned TRISA0:1;
    unsigned TRISA1:1;
    unsigned TRISA2:1;
    unsigned TRISA3:1;
    unsigned TRISA4:1;
    unsigned TRISA5:1;
    unsigned TRISA6:1;
    unsigned TRISA7:1;
  };
  struct {
    unsigned RA0:1;
    unsigned RA1:1;
    unsigned RA2:1;
    unsigned RA3:1;
    unsigned RA4:1;
    unsigned RA5:1;
    unsigned RA6:1;
    unsigned RA7:1;
  };
} TRISAbits;
extern volatile near unsigned char       DDRB;
extern volatile near union {
  struct {
    unsigned TRISB0:1;
    unsigned TRISB1:1;
    unsigned TRISB2:1;
    unsigned TRISB3:1;
    unsigned TRISB4:1;
    unsigned TRISB5:1;
    unsigned TRISB6:1;
    unsigned TRISB7:1;
  };
  struct {
    unsigned RB0:1;
    unsigned RB1:1;
    unsigned RB2:1;
    unsigned RB3:1;
    unsigned RB4:1;
    unsigned RB5:1;
    unsigned RB6:1;
    unsigned RB7:1;
  };
} DDRBbits;
extern volatile near unsigned char       TRISB;
extern volatile near union {
  struct {
    unsigned TRISB0:1;
    unsigned TRISB1:1;
    unsigned TRISB2:1;
    unsigned TRISB3:1;
    unsigned TRISB4:1;
    unsigned TRISB5:1;
    unsigned TRISB6:1;
    unsigned TRISB7:1;
  };
  struct {
    unsigned RB0:1;
    unsigned RB1:1;
    unsigned RB2:1;
    unsigned RB3:1;
    unsigned RB4:1;
    unsigned RB5:1;
    unsigned RB6:1;
    unsigned RB7:1;
  };
} TRISBbits;
extern volatile near unsigned char       DDRC;
extern volatile near union {
  struct {
    unsigned TRISC0:1;
    unsigned TRISC1:1;
    unsigned TRISC2:1;
    unsigned TRISC3:1;
    unsigned TRISC4:1;
    unsigned TRISC5:1;
    unsigned TRISC6:1;
    unsigned TRISC7:1;
  };
  struct {
    unsigned RC0:1;
    unsigned RC1:1;
    unsigned RC2:1;
    unsigned RC3:1;
    unsigned RC4:1;
    unsigned RC5:1;
    unsigned RC6:1;
    unsigned RC7:1;
  };
} DDRCbits;
extern volatile near unsigned char       TRISC;
extern volatile near union {
  struct {
    unsigned TRISC0:1;
    unsigned TRISC1:1;
    unsigned TRISC2:1;
    unsigned TRISC3:1;
    unsigned TRISC4:1;
    unsigned TRISC5:1;
    unsigned TRISC6:1;
    unsigned TRISC7:1;
  };
  struct {
    unsigned RC0:1;
    unsigned RC1:1;
    unsigned RC2:1;
    unsigned RC3:1;
    unsigned RC4:1;
    unsigned RC5:1;
    unsigned RC6:1;
    unsigned RC7:1;
  };
} TRISCbits;
extern volatile near unsigned char       TRISE;
extern volatile near struct {
  unsigned :7;
  unsigned WPUE3:1;
} TRISEbits;
extern volatile near unsigned char       OSCTUNE;
extern volatile near union {
  struct {
    unsigned TUN:6;
    unsigned PLLEN:1;
    unsigned INTSRC:1;
  };
  struct {
    unsigned TUN0:1;
    unsigned TUN1:1;
    unsigned TUN2:1;
    unsigned TUN3:1;
    unsigned TUN4:1;
    unsigned TUN5:1;
  };
} OSCTUNEbits;
extern volatile near unsigned char       HLVDCON;
extern volatile near union {
  struct {
    unsigned HLVDL:4;
    unsigned HLVDEN:1;
    unsigned IRVST:1;
    unsigned BGVST:1;
    unsigned VDIRMAG:1;
  };
  struct {
    unsigned HLVDL0:1;
    unsigned HLVDL1:1;
    unsigned HLVDL2:1;
    unsigned HLVDL3:1;
  };
  struct {
    unsigned LVDL0:1;
    unsigned LVDL1:1;
    unsigned LVDL2:1;
    unsigned LVDL3:1;
    unsigned LVDEN:1;
    unsigned IVRST:1;
  };
  struct {
    unsigned LVV0:1;
    unsigned LVV1:1;
    unsigned LVV2:1;
    unsigned LVV3:1;
    unsigned :1;
    unsigned BGST:1;
  };
} HLVDCONbits;
extern volatile near unsigned char       LVDCON;
extern volatile near union {
  struct {
    unsigned HLVDL:4;
    unsigned HLVDEN:1;
    unsigned IRVST:1;
    unsigned BGVST:1;
    unsigned VDIRMAG:1;
  };
  struct {
    unsigned HLVDL0:1;
    unsigned HLVDL1:1;
    unsigned HLVDL2:1;
    unsigned HLVDL3:1;
  };
  struct {
    unsigned LVDL0:1;
    unsigned LVDL1:1;
    unsigned LVDL2:1;
    unsigned LVDL3:1;
    unsigned LVDEN:1;
    unsigned IVRST:1;
  };
  struct {
    unsigned LVV0:1;
    unsigned LVV1:1;
    unsigned LVV2:1;
    unsigned LVV3:1;
    unsigned :1;
    unsigned BGST:1;
  };
} LVDCONbits;
extern volatile near unsigned char       PIE1;
extern volatile near union {
  struct {
    unsigned TMR1IE:1;
    unsigned TMR2IE:1;
    unsigned CCP1IE:1;
    unsigned SSP1IE:1;
    unsigned TX1IE:1;
    unsigned RC1IE:1;
    unsigned ADIE:1;
  };
  struct {
    unsigned :3;
    unsigned SSPIE:1;
    unsigned TXIE:1;
    unsigned RCIE:1;
  };
} PIE1bits;
extern volatile near unsigned char       PIR1;
extern volatile near union {
  struct {
    unsigned TMR1IF:1;
    unsigned TMR2IF:1;
    unsigned CCP1IF:1;
    unsigned SSP1IF:1;
    unsigned TX1IF:1;
    unsigned RC1IF:1;
    unsigned ADIF:1;
  };
  struct {
    unsigned :3;
    unsigned SSPIF:1;
    unsigned TXIF:1;
    unsigned RCIF:1;
  };
} PIR1bits;
extern volatile near unsigned char       IPR1;
extern volatile near union {
  struct {
    unsigned TMR1IP:1;
    unsigned TMR2IP:1;
    unsigned CCP1IP:1;
    unsigned SSP1IP:1;
    unsigned TX1IP:1;
    unsigned RC1IP:1;
    unsigned ADIP:1;
  };
  struct {
    unsigned :3;
    unsigned SSPIP:1;
    unsigned TXIP:1;
    unsigned RCIP:1;
  };
} IPR1bits;
extern volatile near unsigned char       PIE2;
extern volatile near union {
  struct {
    unsigned CCP2IE:1;
    unsigned TMR3IE:1;
    unsigned HLVDIE:1;
    unsigned BCL1IE:1;
    unsigned EEIE:1;
    unsigned C2IE:1;
    unsigned C1IE:1;
    unsigned OSCFIE:1;
  };
  struct {
    unsigned :2;
    unsigned LVDIE:1;
    unsigned BCLIE:1;
  };
} PIE2bits;
extern volatile near unsigned char       PIR2;
extern volatile near union {
  struct {
    unsigned CCP2IF:1;
    unsigned TMR3IF:1;
    unsigned HLVDIF:1;
    unsigned BCL1IF:1;
    unsigned EEIF:1;
    unsigned C2IF:1;
    unsigned C1IF:1;
    unsigned OSCFIF:1;
  };
  struct {
    unsigned :2;
    unsigned LVDIF:1;
    unsigned BCLIF:1;
  };
} PIR2bits;
extern volatile near unsigned char       IPR2;
extern volatile near union {
  struct {
    unsigned CCP2IP:1;
    unsigned TMR3IP:1;
    unsigned HLVDIP:1;
    unsigned BCL1IP:1;
    unsigned EEIP:1;
    unsigned C2IP:1;
    unsigned C1IP:1;
    unsigned OSCFIP:1;
  };
  struct {
    unsigned :2;
    unsigned LVDIP:1;
    unsigned BCLIP:1;
  };
} IPR2bits;
extern volatile near unsigned char       PIE3;
extern volatile near struct {
  unsigned TMR1GIE:1;
  unsigned TMR3GIE:1;
  unsigned TMR5GIE:1;
  unsigned CTMUIE:1;
  unsigned TX2IE:1;
  unsigned RC2IE:1;
  unsigned BCL2IE:1;
  unsigned SSP2IE:1;
} PIE3bits;
extern volatile near unsigned char       PIR3;
extern volatile near struct {
  unsigned TMR1GIF:1;
  unsigned TMR3GIF:1;
  unsigned TMR5GIF:1;
  unsigned CTMUIF:1;
  unsigned TX2IF:1;
  unsigned RC2IF:1;
  unsigned BCL2IF:1;
  unsigned SSP2IF:1;
} PIR3bits;
extern volatile near unsigned char       IPR3;
extern volatile near struct {
  unsigned TMR1GIP:1;
  unsigned TMR3GIP:1;
  unsigned TMR5GIP:1;
  unsigned CTMUIP:1;
  unsigned TX2IP:1;
  unsigned RC2IP:1;
  unsigned BCL2IP:1;
  unsigned SSP2IP:1;
} IPR3bits;
extern volatile near unsigned char       EECON1;
extern volatile near struct {
  unsigned RD:1;
  unsigned WR:1;
  unsigned WREN:1;
  unsigned WRERR:1;
  unsigned FREE:1;
  unsigned :1;
  unsigned CFGS:1;
  unsigned EEPGD:1;
} EECON1bits;
extern volatile near unsigned char       EECON2;
extern volatile near unsigned char       EEDATA;
extern volatile near unsigned char       EEADR;
extern volatile near union {
  struct {
    unsigned EEADR:8;
  };
  struct {
    unsigned EEADR0:1;
    unsigned EEADR1:1;
    unsigned EEADR2:1;
    unsigned EEADR3:1;
    unsigned EEADR4:1;
    unsigned EEADR5:1;
    unsigned EEADR6:1;
    unsigned EEADR7:1;
  };
} EEADRbits;
extern volatile near unsigned char       RC1STA;
extern volatile near union {
  struct {
    unsigned RX9D:1;
    unsigned OERR:1;
    unsigned FERR:1;
    unsigned ADDEN:1;
    unsigned CREN:1;
    unsigned SREN:1;
    unsigned RX9:1;
    unsigned SPEN:1;
  };
  struct {
    unsigned :3;
    unsigned ADEN:1;
  };
} RC1STAbits;
extern volatile near unsigned char       RCSTA;
extern volatile near union {
  struct {
    unsigned RX9D:1;
    unsigned OERR:1;
    unsigned FERR:1;
    unsigned ADDEN:1;
    unsigned CREN:1;
    unsigned SREN:1;
    unsigned RX9:1;
    unsigned SPEN:1;
  };
  struct {
    unsigned :3;
    unsigned ADEN:1;
  };
} RCSTAbits;
extern volatile near unsigned char       RCSTA1;
extern volatile near union {
  struct {
    unsigned RX9D:1;
    unsigned OERR:1;
    unsigned FERR:1;
    unsigned ADDEN:1;
    unsigned CREN:1;
    unsigned SREN:1;
    unsigned RX9:1;
    unsigned SPEN:1;
  };
  struct {
    unsigned :3;
    unsigned ADEN:1;
  };
} RCSTA1bits;
extern volatile near unsigned char       TX1STA;
extern volatile near struct {
  unsigned TX9D:1;
  unsigned TRMT:1;
  unsigned BRGH:1;
  unsigned SENDB:1;
  unsigned SYNC:1;
  unsigned TXEN:1;
  unsigned TX9:1;
  unsigned CSRC:1;
} TX1STAbits;
extern volatile near unsigned char       TXSTA;
extern volatile near struct {
  unsigned TX9D:1;
  unsigned TRMT:1;
  unsigned BRGH:1;
  unsigned SENDB:1;
  unsigned SYNC:1;
  unsigned TXEN:1;
  unsigned TX9:1;
  unsigned CSRC:1;
} TXSTAbits;
extern volatile near unsigned char       TXSTA1;
extern volatile near struct {
  unsigned TX9D:1;
  unsigned TRMT:1;
  unsigned BRGH:1;
  unsigned SENDB:1;
  unsigned SYNC:1;
  unsigned TXEN:1;
  unsigned TX9:1;
  unsigned CSRC:1;
} TXSTA1bits;
extern volatile near unsigned char       TX1REG;
extern volatile near union {
  struct {
    unsigned TX1REG:8;
  };
  struct {
    unsigned TXREG:8;
  };
} TX1REGbits;
extern volatile near unsigned char       TXREG;
extern volatile near union {
  struct {
    unsigned TX1REG:8;
  };
  struct {
    unsigned TXREG:8;
  };
} TXREGbits;
extern volatile near unsigned char       TXREG1;
extern volatile near union {
  struct {
    unsigned TX1REG:8;
  };
  struct {
    unsigned TXREG:8;
  };
} TXREG1bits;
extern volatile near unsigned char       RC1REG;
extern volatile near union {
  struct {
    unsigned RC1REG:8;
  };
  struct {
    unsigned RCREG:8;
  };
} RC1REGbits;
extern volatile near unsigned char       RCREG;
extern volatile near union {
  struct {
    unsigned RC1REG:8;
  };
  struct {
    unsigned RCREG:8;
  };
} RCREGbits;
extern volatile near unsigned char       RCREG1;
extern volatile near union {
  struct {
    unsigned RC1REG:8;
  };
  struct {
    unsigned RCREG:8;
  };
} RCREG1bits;
extern volatile near unsigned char       SP1BRG;
extern volatile near union {
  struct {
    unsigned SP1BRG:8;
  };
  struct {
    unsigned SPBRG:8;
  };
} SP1BRGbits;
extern volatile near unsigned char       SPBRG;
extern volatile near union {
  struct {
    unsigned SP1BRG:8;
  };
  struct {
    unsigned SPBRG:8;
  };
} SPBRGbits;
extern volatile near unsigned char       SPBRG1;
extern volatile near union {
  struct {
    unsigned SP1BRG:8;
  };
  struct {
    unsigned SPBRG:8;
  };
} SPBRG1bits;
extern volatile near unsigned char       SP1BRGH;
extern volatile near union {
  struct {
    unsigned SP1BRGH:8;
  };
  struct {
    unsigned SPBRGH:8;
  };
} SP1BRGHbits;
extern volatile near unsigned char       SPBRGH;
extern volatile near union {
  struct {
    unsigned SP1BRGH:8;
  };
  struct {
    unsigned SPBRGH:8;
  };
} SPBRGHbits;
extern volatile near unsigned char       SPBRGH1;
extern volatile near union {
  struct {
    unsigned SP1BRGH:8;
  };
  struct {
    unsigned SPBRGH:8;
  };
} SPBRGH1bits;
extern volatile near unsigned char       T3CON;
extern volatile near union {
  struct {
    unsigned TMR3ON:1;
    unsigned T3RD16:1;
    unsigned NOT_T3SYNC:1;
    unsigned T3SOSCEN:1;
    unsigned T3CKPS:2;
    unsigned TMR3CS:2;
  };
  struct {
    unsigned :3;
    unsigned T3OSCEN:1;
    unsigned T3CKPS0:1;
    unsigned T3CKPS1:1;
    unsigned TMR3CS0:1;
    unsigned TMR3CS1:1;
  };
} T3CONbits;
extern volatile near unsigned char       TMR3L;
extern volatile near unsigned char       TMR3H;
extern volatile near unsigned char       T3GCON;
extern volatile near union {
  struct {
    unsigned T3GSS:2;
    unsigned T3GVAL:1;
    unsigned T3GGO_NOT_DONE:1;
    unsigned T3GSPM:1;
    unsigned T3GTM:1;
    unsigned T3GPOL:1;
    unsigned TMR3GE:1;
  };
  struct {
    unsigned T3GSS0:1;
    unsigned T3GSS1:1;
    unsigned :1;
    unsigned T3G_DONE:1;
  };
  struct {
    unsigned :3;
    unsigned T3GGO:1;
  };
} T3GCONbits;
extern volatile near unsigned char       ECCP1AS;
extern volatile near union {
  struct {
    unsigned PSS1BD:2;
    unsigned PSS1AC:2;
    unsigned CCP1AS:3;
    unsigned CCP1ASE:1;
  };
  struct {
    unsigned PSS1BD0:1;
    unsigned PSS1BD1:1;
    unsigned PSS1AC0:1;
    unsigned PSS1AC1:1;
    unsigned CCP1AS0:1;
    unsigned CCP1AS1:1;
    unsigned CCP1AS2:1;
  };
  struct {
    unsigned PSSBD:2;
    unsigned PSSAC:2;
    unsigned ECCPAS:3;
    unsigned ECCPASE:1;
  };
  struct {
    unsigned PSSBD0:1;
    unsigned PSSBD1:1;
    unsigned PSSAC0:1;
    unsigned PSSAC1:1;
    unsigned ECCPAS0:1;
    unsigned ECCPAS1:1;
    unsigned ECCPAS2:1;
  };
} ECCP1ASbits;
extern volatile near unsigned char       ECCPAS;
extern volatile near union {
  struct {
    unsigned PSS1BD:2;
    unsigned PSS1AC:2;
    unsigned CCP1AS:3;
    unsigned CCP1ASE:1;
  };
  struct {
    unsigned PSS1BD0:1;
    unsigned PSS1BD1:1;
    unsigned PSS1AC0:1;
    unsigned PSS1AC1:1;
    unsigned CCP1AS0:1;
    unsigned CCP1AS1:1;
    unsigned CCP1AS2:1;
  };
  struct {
    unsigned PSSBD:2;
    unsigned PSSAC:2;
    unsigned ECCPAS:3;
    unsigned ECCPASE:1;
  };
  struct {
    unsigned PSSBD0:1;
    unsigned PSSBD1:1;
    unsigned PSSAC0:1;
    unsigned PSSAC1:1;
    unsigned ECCPAS0:1;
    unsigned ECCPAS1:1;
    unsigned ECCPAS2:1;
  };
} ECCPASbits;
extern volatile near unsigned char       PWM1CON;
extern volatile near union {
  struct {
    unsigned P1DC:7;
    unsigned P1RSEN:1;
  };
  struct {
    unsigned P1DC0:1;
    unsigned P1DC1:1;
    unsigned P1DC2:1;
    unsigned P1DC3:1;
    unsigned P1DC4:1;
    unsigned P1DC5:1;
    unsigned P1DC6:1;
  };
  struct {
    unsigned PDC:7;
    unsigned PRSEN:1;
  };
  struct {
    unsigned PDC0:1;
    unsigned PDC1:1;
    unsigned PDC2:1;
    unsigned PDC3:1;
    unsigned PDC4:1;
    unsigned PDC5:1;
    unsigned PDC6:1;
  };
} PWM1CONbits;
extern volatile near unsigned char       PWMCON;
extern volatile near union {
  struct {
    unsigned P1DC:7;
    unsigned P1RSEN:1;
  };
  struct {
    unsigned P1DC0:1;
    unsigned P1DC1:1;
    unsigned P1DC2:1;
    unsigned P1DC3:1;
    unsigned P1DC4:1;
    unsigned P1DC5:1;
    unsigned P1DC6:1;
  };
  struct {
    unsigned PDC:7;
    unsigned PRSEN:1;
  };
  struct {
    unsigned PDC0:1;
    unsigned PDC1:1;
    unsigned PDC2:1;
    unsigned PDC3:1;
    unsigned PDC4:1;
    unsigned PDC5:1;
    unsigned PDC6:1;
  };
} PWMCONbits;
extern volatile near unsigned char       BAUD1CON;
extern volatile near union {
  struct {
    unsigned ABDEN:1;
    unsigned WUE:1;
    unsigned :1;
    unsigned BRG16:1;
    unsigned CKTXP:1;
    unsigned DTRXP:1;
    unsigned RCIDL:1;
    unsigned ABDOVF:1;
  };
  struct {
    unsigned :4;
    unsigned SCKP:1;
  };
} BAUD1CONbits;
extern volatile near unsigned char       BAUDCON;
extern volatile near union {
  struct {
    unsigned ABDEN:1;
    unsigned WUE:1;
    unsigned :1;
    unsigned BRG16:1;
    unsigned CKTXP:1;
    unsigned DTRXP:1;
    unsigned RCIDL:1;
    unsigned ABDOVF:1;
  };
  struct {
    unsigned :4;
    unsigned SCKP:1;
  };
} BAUDCONbits;
extern volatile near unsigned char       BAUDCON1;
extern volatile near union {
  struct {
    unsigned ABDEN:1;
    unsigned WUE:1;
    unsigned :1;
    unsigned BRG16:1;
    unsigned CKTXP:1;
    unsigned DTRXP:1;
    unsigned RCIDL:1;
    unsigned ABDOVF:1;
  };
  struct {
    unsigned :4;
    unsigned SCKP:1;
  };
} BAUDCON1bits;
extern volatile near unsigned char       BAUDCTL;
extern volatile near union {
  struct {
    unsigned ABDEN:1;
    unsigned WUE:1;
    unsigned :1;
    unsigned BRG16:1;
    unsigned CKTXP:1;
    unsigned DTRXP:1;
    unsigned RCIDL:1;
    unsigned ABDOVF:1;
  };
  struct {
    unsigned :4;
    unsigned SCKP:1;
  };
} BAUDCTLbits;
extern volatile near unsigned char       PSTR1CON;
extern volatile near struct {
  unsigned STR1A:1;
  unsigned STR1B:1;
  unsigned STR1C:1;
  unsigned STR1D:1;
  unsigned STR1SYNC:1;
} PSTR1CONbits;
extern volatile near unsigned char       PSTRCON;
extern volatile near struct {
  unsigned STR1A:1;
  unsigned STR1B:1;
  unsigned STR1C:1;
  unsigned STR1D:1;
  unsigned STR1SYNC:1;
} PSTRCONbits;
extern volatile near unsigned char       T2CON;
extern volatile near union {
  struct {
    unsigned T2CKPS:2;
    unsigned TMR2ON:1;
    unsigned T2OUTPS:4;
  };
  struct {
    unsigned T2CKPS0:1;
    unsigned T2CKPS1:1;
    unsigned :1;
    unsigned T2OUTPS0:1;
    unsigned T2OUTPS1:1;
    unsigned T2OUTPS2:1;
    unsigned T2OUTPS3:1;
  };
} T2CONbits;
extern volatile near unsigned char       PR2;
extern volatile near unsigned char       TMR2;
extern volatile near unsigned char       CCP1CON;
extern volatile near union {
  struct {
    unsigned CCP1M:4;
    unsigned DC1B:2;
    unsigned P1M:2;
  };
  struct {
    unsigned CCP1M0:1;
    unsigned CCP1M1:1;
    unsigned CCP1M2:1;
    unsigned CCP1M3:1;
    unsigned DC1B0:1;
    unsigned DC1B1:1;
    unsigned P1M0:1;
    unsigned P1M1:1;
  };
} CCP1CONbits;
extern volatile near unsigned            CCPR1;
extern volatile near unsigned char       CCPR1L;
extern volatile near unsigned char       CCPR1H;
extern volatile near unsigned char       ADCON2;
extern volatile near union {
  struct {
    unsigned ADCS:3;
    unsigned ACQT:3;
    unsigned :1;
    unsigned ADFM:1;
  };
  struct {
    unsigned ADCS0:1;
    unsigned ADCS1:1;
    unsigned ADCS2:1;
    unsigned ACQT0:1;
    unsigned ACQT1:1;
    unsigned ACQT2:1;
  };
} ADCON2bits;
extern volatile near unsigned char       ADCON1;
extern volatile near union {
  struct {
    unsigned NVCFG:2;
    unsigned PVCFG:2;
    unsigned :3;
    unsigned TRIGSEL:1;
  };
  struct {
    unsigned NVCFG0:1;
    unsigned NVCFG1:1;
    unsigned PVCFG0:1;
    unsigned PVCFG1:1;
  };
} ADCON1bits;
extern volatile near unsigned char       ADCON0;
extern volatile near union {
  struct {
    unsigned ADON:1;
    unsigned GO_NOT_DONE:1;
    unsigned CHS:5;
  };
  struct {
    unsigned :1;
    unsigned GO:1;
    unsigned CHS0:1;
    unsigned CHS1:1;
    unsigned CHS2:1;
    unsigned CHS3:1;
    unsigned CHS4:1;
  };
  struct {
    unsigned :1;
    unsigned DONE:1;
  };
  struct {
    unsigned :1;
    unsigned NOT_DONE:1;
  };
  struct {
    unsigned :1;
    unsigned GO_DONE:1;
  };
} ADCON0bits;
extern volatile near unsigned            ADRES;
extern volatile near unsigned char       ADRESL;
extern volatile near unsigned char       ADRESH;
extern volatile near unsigned char       SSP1CON2;
extern volatile near struct {
  unsigned SEN:1;
  unsigned RSEN:1;
  unsigned PEN:1;
  unsigned RCEN:1;
  unsigned ACKEN:1;
  unsigned ACKDT:1;
  unsigned ACKSTAT:1;
  unsigned GCEN:1;
} SSP1CON2bits;
extern volatile near unsigned char       SSPCON2;
extern volatile near struct {
  unsigned SEN:1;
  unsigned RSEN:1;
  unsigned PEN:1;
  unsigned RCEN:1;
  unsigned ACKEN:1;
  unsigned ACKDT:1;
  unsigned ACKSTAT:1;
  unsigned GCEN:1;
} SSPCON2bits;
extern volatile near unsigned char       SSP1CON1;
extern volatile near union {
  struct {
    unsigned SSPM:4;
    unsigned CKP:1;
    unsigned SSPEN:1;
    unsigned SSPOV:1;
    unsigned WCOL:1;
  };
  struct {
    unsigned SSPM0:1;
    unsigned SSPM1:1;
    unsigned SSPM2:1;
    unsigned SSPM3:1;
  };
} SSP1CON1bits;
extern volatile near unsigned char       SSPCON1;
extern volatile near union {
  struct {
    unsigned SSPM:4;
    unsigned CKP:1;
    unsigned SSPEN:1;
    unsigned SSPOV:1;
    unsigned WCOL:1;
  };
  struct {
    unsigned SSPM0:1;
    unsigned SSPM1:1;
    unsigned SSPM2:1;
    unsigned SSPM3:1;
  };
} SSPCON1bits;
extern volatile near unsigned char       SSP1STAT;
extern volatile near union {
  struct {
    unsigned BF:1;
    unsigned UA:1;
    unsigned R_NOT_W:1;
    unsigned S:1;
    unsigned P:1;
    unsigned D_NOT_A:1;
    unsigned CKE:1;
    unsigned SMP:1;
  };
  struct {
    unsigned :2;
    unsigned R:1;
    unsigned :2;
    unsigned D:1;
  };
  struct {
    unsigned :2;
    unsigned W:1;
    unsigned :2;
    unsigned A:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_W:1;
    unsigned :2;
    unsigned NOT_A:1;
  };
  struct {
    unsigned :2;
    unsigned R_W:1;
    unsigned :2;
    unsigned D_A:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_WRITE:1;
    unsigned :2;
    unsigned NOT_ADDRESS:1;
  };
} SSP1STATbits;
extern volatile near unsigned char       SSPSTAT;
extern volatile near union {
  struct {
    unsigned BF:1;
    unsigned UA:1;
    unsigned R_NOT_W:1;
    unsigned S:1;
    unsigned P:1;
    unsigned D_NOT_A:1;
    unsigned CKE:1;
    unsigned SMP:1;
  };
  struct {
    unsigned :2;
    unsigned R:1;
    unsigned :2;
    unsigned D:1;
  };
  struct {
    unsigned :2;
    unsigned W:1;
    unsigned :2;
    unsigned A:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_W:1;
    unsigned :2;
    unsigned NOT_A:1;
  };
  struct {
    unsigned :2;
    unsigned R_W:1;
    unsigned :2;
    unsigned D_A:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_WRITE:1;
    unsigned :2;
    unsigned NOT_ADDRESS:1;
  };
} SSPSTATbits;
extern volatile near unsigned char       SSP1ADD;
extern volatile near union {
  struct {
    unsigned SSPADD:8;
  };
  struct {
    unsigned SSP1ADD:8;
  };
} SSP1ADDbits;
extern volatile near unsigned char       SSPADD;
extern volatile near union {
  struct {
    unsigned SSPADD:8;
  };
  struct {
    unsigned SSP1ADD:8;
  };
} SSPADDbits;
extern volatile near unsigned char       SSP1BUF;
extern volatile near union {
  struct {
    unsigned SSPBUF:8;
  };
  struct {
    unsigned SSP1BUF:8;
  };
} SSP1BUFbits;
extern volatile near unsigned char       SSPBUF;
extern volatile near union {
  struct {
    unsigned SSPBUF:8;
  };
  struct {
    unsigned SSP1BUF:8;
  };
} SSPBUFbits;
extern volatile near unsigned char       SSP1MSK;
extern volatile near struct {
  unsigned MSK0:1;
  unsigned MSK1:1;
  unsigned MSK2:1;
  unsigned MSK3:1;
  unsigned MSK4:1;
  unsigned MSK5:1;
  unsigned MSK6:1;
  unsigned MSK7:1;
} SSP1MSKbits;
extern volatile near unsigned char       SSPMSK;
extern volatile near struct {
  unsigned MSK0:1;
  unsigned MSK1:1;
  unsigned MSK2:1;
  unsigned MSK3:1;
  unsigned MSK4:1;
  unsigned MSK5:1;
  unsigned MSK6:1;
  unsigned MSK7:1;
} SSPMSKbits;
extern volatile near unsigned char       SSP1CON3;
extern volatile near struct {
  unsigned DHEN:1;
  unsigned AHEN:1;
  unsigned SBCDE:1;
  unsigned SDAHT:1;
  unsigned BOEN:1;
  unsigned SCIE:1;
  unsigned PCIE:1;
  unsigned ACKTIM:1;
} SSP1CON3bits;
extern volatile near unsigned char       SSPCON3;
extern volatile near struct {
  unsigned DHEN:1;
  unsigned AHEN:1;
  unsigned SBCDE:1;
  unsigned SDAHT:1;
  unsigned BOEN:1;
  unsigned SCIE:1;
  unsigned PCIE:1;
  unsigned ACKTIM:1;
} SSPCON3bits;
extern volatile near unsigned char       T1GCON;
extern volatile near union {
  struct {
    unsigned T1GSS:2;
    unsigned T1GVAL:1;
    unsigned T1GGO_NOT_DONE:1;
    unsigned T1GSPM:1;
    unsigned T1GTM:1;
    unsigned T1GPOL:1;
    unsigned TMR1GE:1;
  };
  struct {
    unsigned T1GSS0:1;
    unsigned T1GSS1:1;
    unsigned :1;
    unsigned T1G_DONE:1;
  };
  struct {
    unsigned :3;
    unsigned T1GGO:1;
  };
} T1GCONbits;
extern volatile near unsigned char       T1CON;
extern volatile near union {
  struct {
    unsigned TMR1ON:1;
    unsigned T1RD16:1;
    unsigned NOT_T1SYNC:1;
    unsigned T1SOSCEN:1;
    unsigned T1CKPS:2;
    unsigned TMR1CS:2;
  };
  struct {
    unsigned :1;
    unsigned RD16:1;
    unsigned T1SYNC:1;
    unsigned T1OSCEN:1;
    unsigned T1CKPS0:1;
    unsigned T1CKPS1:1;
    unsigned TMR1CS0:1;
    unsigned TMR1CS1:1;
  };
} T1CONbits;
extern volatile near unsigned char       TMR1L;
extern volatile near unsigned char       TMR1H;
extern volatile near unsigned char       RCON;
extern volatile near union {
  struct {
    unsigned NOT_BOR:1;
    unsigned NOT_POR:1;
    unsigned NOT_PD:1;
    unsigned NOT_TO:1;
    unsigned NOT_RI:1;
    unsigned :1;
    unsigned SBOREN:1;
    unsigned IPEN:1;
  };
  struct {
    unsigned BOR:1;
    unsigned POR:1;
    unsigned PD:1;
    unsigned TO:1;
    unsigned RI:1;
  };
} RCONbits;
extern volatile near unsigned char       WDTCON;
extern volatile near union {
  struct {
    unsigned SWDTEN:1;
  };
  struct {
    unsigned SWDTE:1;
  };
} WDTCONbits;
extern volatile near unsigned char       OSCCON2;
extern volatile near struct {
  unsigned LFIOFS:1;
  unsigned MFIOFS:1;
  unsigned PRISD:1;
  unsigned SOSCGO:1;
  unsigned MFIOSEL:1;
  unsigned :1;
  unsigned SOSCRUN:1;
  unsigned PLLRDY:1;
} OSCCON2bits;
extern volatile near unsigned char       OSCCON;
extern volatile near union {
  struct {
    unsigned SCS:2;
    unsigned HFIOFS:1;
    unsigned OSTS:1;
    unsigned IRCF:3;
    unsigned IDLEN:1;
  };
  struct {
    unsigned SCS0:1;
    unsigned SCS1:1;
    unsigned IOFS:1;
    unsigned :1;
    unsigned IRCF0:1;
    unsigned IRCF1:1;
    unsigned IRCF2:1;
  };
} OSCCONbits;
extern volatile near unsigned char       T0CON;
extern volatile near union {
  struct {
    unsigned T0PS:3;
    unsigned PSA:1;
    unsigned T0SE:1;
    unsigned T0CS:1;
    unsigned T08BIT:1;
    unsigned TMR0ON:1;
  };
  struct {
    unsigned T0PS0:1;
    unsigned T0PS1:1;
    unsigned T0PS2:1;
  };
} T0CONbits;
extern volatile near unsigned char       TMR0L;
extern volatile near unsigned char       TMR0H;
extern          near unsigned char       STATUS;
extern          near struct {
  unsigned C:1;
  unsigned DC:1;
  unsigned Z:1;
  unsigned OV:1;
  unsigned N:1;
} STATUSbits;
extern          near unsigned            FSR2;
extern          near unsigned char       FSR2L;
extern          near unsigned char       FSR2H;
extern volatile near unsigned char       PLUSW2;
extern volatile near unsigned char       PREINC2;
extern volatile near unsigned char       POSTDEC2;
extern volatile near unsigned char       POSTINC2;
extern          near unsigned char       INDF2;
extern          near unsigned char       BSR;
extern          near unsigned            FSR1;
extern          near unsigned char       FSR1L;
extern          near unsigned char       FSR1H;
extern volatile near unsigned char       PLUSW1;
extern volatile near unsigned char       PREINC1;
extern volatile near unsigned char       POSTDEC1;
extern volatile near unsigned char       POSTINC1;
extern          near unsigned char       INDF1;
extern          near unsigned char       W;
extern          near unsigned char       WREG;
extern          near unsigned            FSR0;
extern          near unsigned char       FSR0L;
extern          near unsigned char       FSR0H;
extern volatile near unsigned char       PLUSW0;
extern volatile near unsigned char       PREINC0;
extern volatile near unsigned char       POSTDEC0;
extern volatile near unsigned char       POSTINC0;
extern          near unsigned char       INDF0;
extern volatile near unsigned char       INTCON3;
extern volatile near union {
  struct {
    unsigned INT1IF:1;
    unsigned INT2IF:1;
    unsigned :1;
    unsigned INT1IE:1;
    unsigned INT2IE:1;
    unsigned :1;
    unsigned INT1IP:1;
    unsigned INT2IP:1;
  };
  struct {
    unsigned INT1F:1;
    unsigned INT2F:1;
    unsigned :1;
    unsigned INT1E:1;
    unsigned INT2E:1;
    unsigned :1;
    unsigned INT1P:1;
    unsigned INT2P:1;
  };
} INTCON3bits;
extern volatile near unsigned char       INTCON2;
extern volatile near union {
  struct {
    unsigned RBIP:1;
    unsigned :1;
    unsigned TMR0IP:1;
    unsigned :1;
    unsigned INTEDG2:1;
    unsigned INTEDG1:1;
    unsigned INTEDG0:1;
    unsigned NOT_RBPU:1;
  };
  struct {
    unsigned :7;
    unsigned RBPU:1;
  };
} INTCON2bits;
extern volatile near unsigned char       INTCON;
extern volatile near union {
  struct {
    unsigned RBIF:1;
    unsigned INT0IF:1;
    unsigned TMR0IF:1;
    unsigned RBIE:1;
    unsigned INT0IE:1;
    unsigned TMR0IE:1;
    unsigned PEIE_GIEL:1;
    unsigned GIE_GIEH:1;
  };
  struct {
    unsigned :1;
    unsigned INT0F:1;
    unsigned T0IF:1;
    unsigned :1;
    unsigned INT0E:1;
    unsigned T0IE:1;
    unsigned PEIE:1;
    unsigned GIE:1;
  };
  struct {
    unsigned :6;
    unsigned GIEL:1;
    unsigned GIEH:1;
  };
} INTCONbits;
extern          near unsigned            PROD;
extern          near unsigned char       PRODL;
extern          near unsigned char       PRODH;
extern volatile near unsigned char       TABLAT;
extern volatile near unsigned short long TBLPTR;
extern volatile near unsigned char       TBLPTRL;
extern volatile near unsigned char       TBLPTRH;
extern volatile near unsigned char       TBLPTRU;
extern volatile near struct {
  unsigned TBLPTRU:6;
} TBLPTRUbits;
extern volatile near unsigned short long PC;
extern volatile near unsigned char       PCL;
extern volatile near unsigned char       PCLATH;
extern volatile near unsigned char       PCLATU;
extern volatile near unsigned char       STKPTR;
extern volatile near union {
  struct {
    unsigned STKPTR:5;
    unsigned :1;
    unsigned STKUNF:1;
    unsigned STKFUL:1;
  };
  struct {
    unsigned SP0:1;
    unsigned SP1:1;
    unsigned SP2:1;
    unsigned SP3:1;
    unsigned SP4:1;
    unsigned :2;
    unsigned STKOVF:1;
  };
} STKPTRbits;
extern          near unsigned short long TOS;
extern          near unsigned char       TOSL;
extern          near unsigned char       TOSH;
extern          near unsigned char       TOSU;

#pragma varlocate 15 ANSELA
#pragma varlocate 15 ANSELAbits
#pragma varlocate 15 ANSELB
#pragma varlocate 15 ANSELBbits
#pragma varlocate 15 ANSELC
#pragma varlocate 15 ANSELCbits
#pragma varlocate 15 PMD2
#pragma varlocate 15 PMD2bits
#pragma varlocate 15 PMD1
#pragma varlocate 15 PMD1bits
#pragma varlocate 15 PMD0
#pragma varlocate 15 PMD0bits
#pragma varlocate 15 DACCON1
#pragma varlocate 15 DACCON1bits
#pragma varlocate 15 VREFCON2
#pragma varlocate 15 VREFCON2bits
#pragma varlocate 15 DACCON0
#pragma varlocate 15 DACCON0bits
#pragma varlocate 15 VREFCON1
#pragma varlocate 15 VREFCON1bits
#pragma varlocate 15 FVRCON
#pragma varlocate 15 FVRCONbits
#pragma varlocate 15 VREFCON0
#pragma varlocate 15 VREFCON0bits
#pragma varlocate 15 CTMUICON
#pragma varlocate 15 CTMUICONbits
#pragma varlocate 15 CTMUICONH
#pragma varlocate 15 CTMUICONHbits
#pragma varlocate 15 CTMUCON1
#pragma varlocate 15 CTMUCON1bits
#pragma varlocate 15 CTMUCONL
#pragma varlocate 15 CTMUCONLbits
#pragma varlocate 15 CTMUCON0
#pragma varlocate 15 CTMUCON0bits
#pragma varlocate 15 CTMUCONH
#pragma varlocate 15 CTMUCONHbits
#pragma varlocate 15 SRCON1
#pragma varlocate 15 SRCON1bits
#pragma varlocate 15 SRCON0
#pragma varlocate 15 SRCON0bits
#pragma varlocate 15 CCPTMRS1
#pragma varlocate 15 CCPTMRS1bits
#pragma varlocate 15 CCPTMRS0
#pragma varlocate 15 CCPTMRS0bits
#pragma varlocate 15 T6CON
#pragma varlocate 15 T6CONbits
#pragma varlocate 15 PR6
#pragma varlocate 15 TMR6
#pragma varlocate 15 T5GCON
#pragma varlocate 15 T5GCONbits
#pragma varlocate 15 T5CON
#pragma varlocate 15 T5CONbits
#pragma varlocate 15 TMR5L
#pragma varlocate 15 TMR5H
#pragma varlocate 15 T4CON
#pragma varlocate 15 T4CONbits
#pragma varlocate 15 PR4
#pragma varlocate 15 TMR4
#pragma varlocate 15 CCP5CON
#pragma varlocate 15 CCP5CONbits
#pragma varlocate 15 CCPR5
#pragma varlocate 15 CCPR5L
#pragma varlocate 15 CCPR5H
#pragma varlocate 15 CCP4CON
#pragma varlocate 15 CCP4CONbits
#pragma varlocate 15 CCPR4
#pragma varlocate 15 CCPR4L
#pragma varlocate 15 CCPR4H
#pragma varlocate 15 PSTR3CON
#pragma varlocate 15 PSTR3CONbits
#pragma varlocate 15 CCP3AS
#pragma varlocate 15 CCP3ASbits
#pragma varlocate 15 ECCP3AS
#pragma varlocate 15 ECCP3ASbits
#pragma varlocate 15 PWM3CON
#pragma varlocate 15 PWM3CONbits
#pragma varlocate 15 CCP3CON
#pragma varlocate 15 CCP3CONbits
#pragma varlocate 15 CCPR3
#pragma varlocate 15 CCPR3L
#pragma varlocate 15 CCPR3H


#line 2705 "C:/MCC18/h/p18f25k22.h"
 
#line 2707 "C:/MCC18/h/p18f25k22.h"
#line 2708 "C:/MCC18/h/p18f25k22.h"


#line 2711 "C:/MCC18/h/p18f25k22.h"
 
#line 2713 "C:/MCC18/h/p18f25k22.h"
#line 2714 "C:/MCC18/h/p18f25k22.h"
#line 2715 "C:/MCC18/h/p18f25k22.h"
#line 2716 "C:/MCC18/h/p18f25k22.h"

#line 2718 "C:/MCC18/h/p18f25k22.h"
#line 2719 "C:/MCC18/h/p18f25k22.h"
#line 2720 "C:/MCC18/h/p18f25k22.h"
#line 2721 "C:/MCC18/h/p18f25k22.h"
#line 2722 "C:/MCC18/h/p18f25k22.h"


#line 2726 "C:/MCC18/h/p18f25k22.h"
 
#line 2728 "C:/MCC18/h/p18f25k22.h"


#line 2731 "C:/MCC18/h/p18f25k22.h"
#line 10 "main.c"
    
#line 1 "C:/MCC18/h/adc.h"

#line 3 "C:/MCC18/h/adc.h"

#line 30 "C:/MCC18/h/adc.h"
 



#line 35 "C:/MCC18/h/adc.h"


#line 41 "C:/MCC18/h/adc.h"
 
#line 43 "C:/MCC18/h/adc.h"


#line 49 "C:/MCC18/h/adc.h"
 
#line 51 "C:/MCC18/h/adc.h"



#line 56 "C:/MCC18/h/adc.h"
#line 57 "C:/MCC18/h/adc.h"



#line 61 "C:/MCC18/h/adc.h"
#line 62 "C:/MCC18/h/adc.h"
#line 63 "C:/MCC18/h/adc.h"
#line 64 "C:/MCC18/h/adc.h"
#line 65 "C:/MCC18/h/adc.h"
#line 66 "C:/MCC18/h/adc.h"
#line 67 "C:/MCC18/h/adc.h"


#line 70 "C:/MCC18/h/adc.h"
#line 71 "C:/MCC18/h/adc.h"
#line 72 "C:/MCC18/h/adc.h"
#line 73 "C:/MCC18/h/adc.h"
#line 74 "C:/MCC18/h/adc.h"
#line 75 "C:/MCC18/h/adc.h"
#line 76 "C:/MCC18/h/adc.h"
#line 77 "C:/MCC18/h/adc.h"


#line 80 "C:/MCC18/h/adc.h"
#line 81 "C:/MCC18/h/adc.h"

#line 83 "C:/MCC18/h/adc.h"
#line 109 "C:/MCC18/h/adc.h"

#line 111 "C:/MCC18/h/adc.h"



#line 115 "C:/MCC18/h/adc.h"
#line 116 "C:/MCC18/h/adc.h"



#line 120 "C:/MCC18/h/adc.h"
#line 121 "C:/MCC18/h/adc.h"
#line 122 "C:/MCC18/h/adc.h"
#line 123 "C:/MCC18/h/adc.h"
#line 124 "C:/MCC18/h/adc.h"
#line 131 "C:/MCC18/h/adc.h"

#line 133 "C:/MCC18/h/adc.h"




#line 138 "C:/MCC18/h/adc.h"
#line 139 "C:/MCC18/h/adc.h"
#line 140 "C:/MCC18/h/adc.h"
#line 145 "C:/MCC18/h/adc.h"


#line 148 "C:/MCC18/h/adc.h"
#line 167 "C:/MCC18/h/adc.h"
#line 185 "C:/MCC18/h/adc.h"
#line 187 "C:/MCC18/h/adc.h"
#line 208 "C:/MCC18/h/adc.h"
#line 209 "C:/MCC18/h/adc.h"
#line 228 "C:/MCC18/h/adc.h"
#line 230 "C:/MCC18/h/adc.h"
#line 232 "C:/MCC18/h/adc.h"
#line 244 "C:/MCC18/h/adc.h"
#line 253 "C:/MCC18/h/adc.h"
#line 261 "C:/MCC18/h/adc.h"
#line 264 "C:/MCC18/h/adc.h"
#line 286 "C:/MCC18/h/adc.h"


#line 289 "C:/MCC18/h/adc.h"
#line 290 "C:/MCC18/h/adc.h"
#line 291 "C:/MCC18/h/adc.h"
#line 292 "C:/MCC18/h/adc.h"
#line 293 "C:/MCC18/h/adc.h"
#line 294 "C:/MCC18/h/adc.h"
#line 295 "C:/MCC18/h/adc.h"
#line 296 "C:/MCC18/h/adc.h"
#line 297 "C:/MCC18/h/adc.h"
#line 298 "C:/MCC18/h/adc.h"
#line 299 "C:/MCC18/h/adc.h"
#line 300 "C:/MCC18/h/adc.h"
#line 301 "C:/MCC18/h/adc.h"
#line 302 "C:/MCC18/h/adc.h"

#line 304 "C:/MCC18/h/adc.h"
#line 322 "C:/MCC18/h/adc.h"
#line 326 "C:/MCC18/h/adc.h"
#line 328 "C:/MCC18/h/adc.h"


#line 331 "C:/MCC18/h/adc.h"
#line 406 "C:/MCC18/h/adc.h"
#line 489 "C:/MCC18/h/adc.h"
#line 491 "C:/MCC18/h/adc.h"


#line 494 "C:/MCC18/h/adc.h"
#line 495 "C:/MCC18/h/adc.h"


#line 498 "C:/MCC18/h/adc.h"
#line 499 "C:/MCC18/h/adc.h"
#line 500 "C:/MCC18/h/adc.h"
#line 501 "C:/MCC18/h/adc.h"
#line 502 "C:/MCC18/h/adc.h"
#line 503 "C:/MCC18/h/adc.h"
#line 504 "C:/MCC18/h/adc.h"
#line 505 "C:/MCC18/h/adc.h"
#line 506 "C:/MCC18/h/adc.h"
#line 507 "C:/MCC18/h/adc.h"
#line 508 "C:/MCC18/h/adc.h"
#line 509 "C:/MCC18/h/adc.h"
#line 510 "C:/MCC18/h/adc.h"
#line 511 "C:/MCC18/h/adc.h"
#line 515 "C:/MCC18/h/adc.h"
#line 516 "C:/MCC18/h/adc.h"
#line 517 "C:/MCC18/h/adc.h"
#line 518 "C:/MCC18/h/adc.h"
#line 519 "C:/MCC18/h/adc.h"

#line 521 "C:/MCC18/h/adc.h"
#line 537 "C:/MCC18/h/adc.h"
#line 542 "C:/MCC18/h/adc.h"
#line 544 "C:/MCC18/h/adc.h"
#line 549 "C:/MCC18/h/adc.h"
#line 551 "C:/MCC18/h/adc.h"
#line 552 "C:/MCC18/h/adc.h"

#line 554 "C:/MCC18/h/adc.h"
#line 580 "C:/MCC18/h/adc.h"
#line 603 "C:/MCC18/h/adc.h"
#line 605 "C:/MCC18/h/adc.h"

#line 607 "C:/MCC18/h/adc.h"
#line 613 "C:/MCC18/h/adc.h"
#line 618 "C:/MCC18/h/adc.h"
#line 620 "C:/MCC18/h/adc.h"



#line 623 "C:/MCC18/h/adc.h"
#line 624 "C:/MCC18/h/adc.h"
#line 631 "C:/MCC18/h/adc.h"
#line 638 "C:/MCC18/h/adc.h"
#line 639 "C:/MCC18/h/adc.h"



#line 642 "C:/MCC18/h/adc.h"
#line 643 "C:/MCC18/h/adc.h"
#line 652 "C:/MCC18/h/adc.h"
#line 658 "C:/MCC18/h/adc.h"
#line 660 "C:/MCC18/h/adc.h"
#line 662 "C:/MCC18/h/adc.h"
#line 663 "C:/MCC18/h/adc.h"
#line 664 "C:/MCC18/h/adc.h"
#line 669 "C:/MCC18/h/adc.h"
#line 674 "C:/MCC18/h/adc.h"
#line 681 "C:/MCC18/h/adc.h"
#line 684 "C:/MCC18/h/adc.h"
#line 685 "C:/MCC18/h/adc.h"
#line 693 "C:/MCC18/h/adc.h"
#line 699 "C:/MCC18/h/adc.h"
#line 701 "C:/MCC18/h/adc.h"
#line 703 "C:/MCC18/h/adc.h"
#line 704 "C:/MCC18/h/adc.h"
#line 705 "C:/MCC18/h/adc.h"
#line 710 "C:/MCC18/h/adc.h"
#line 715 "C:/MCC18/h/adc.h"
#line 722 "C:/MCC18/h/adc.h"
#line 725 "C:/MCC18/h/adc.h"
#line 728 "C:/MCC18/h/adc.h"
#line 740 "C:/MCC18/h/adc.h"
#line 742 "C:/MCC18/h/adc.h"
#line 743 "C:/MCC18/h/adc.h"
#line 752 "C:/MCC18/h/adc.h"
#line 754 "C:/MCC18/h/adc.h"
#line 756 "C:/MCC18/h/adc.h"
#line 767 "C:/MCC18/h/adc.h"
#line 778 "C:/MCC18/h/adc.h"
#line 791 "C:/MCC18/h/adc.h"
#line 800 "C:/MCC18/h/adc.h"
#line 803 "C:/MCC18/h/adc.h"
#line 808 "C:/MCC18/h/adc.h"
#line 809 "C:/MCC18/h/adc.h"
#line 813 "C:/MCC18/h/adc.h"
#line 822 "C:/MCC18/h/adc.h"
#line 834 "C:/MCC18/h/adc.h"
#line 843 "C:/MCC18/h/adc.h"
#line 846 "C:/MCC18/h/adc.h"
#line 848 "C:/MCC18/h/adc.h"

 
union ADCResult
{
	int lr;			
 	char br[2];		
};

char BusyADC (void);

void ConvertADC (void);

int ReadADC(void);

void CloseADC(void);


#line 866 "C:/MCC18/h/adc.h"

#line 872 "C:/MCC18/h/adc.h"
#line 873 "C:/MCC18/h/adc.h"
#line 879 "C:/MCC18/h/adc.h"

void OpenADC ( unsigned char ,
               unsigned char ,
               unsigned int );

#line 885 "C:/MCC18/h/adc.h"
#line 892 "C:/MCC18/h/adc.h"
#line 897 "C:/MCC18/h/adc.h"

 

#line 903 "C:/MCC18/h/adc.h"
#line 904 "C:/MCC18/h/adc.h"
	
void SetChanADC(unsigned char );
#line 907 "C:/MCC18/h/adc.h"

void SelChanConvADC( unsigned char );




#line 914 "C:/MCC18/h/adc.h"

#line 920 "C:/MCC18/h/adc.h"

#line 928 "C:/MCC18/h/adc.h"
#line 932 "C:/MCC18/h/adc.h"


#line 935 "C:/MCC18/h/adc.h"

#line 941 "C:/MCC18/h/adc.h"

#line 949 "C:/MCC18/h/adc.h"
#line 954 "C:/MCC18/h/adc.h"

#line 960 "C:/MCC18/h/adc.h"

#line 968 "C:/MCC18/h/adc.h"
#line 972 "C:/MCC18/h/adc.h"

#line 978 "C:/MCC18/h/adc.h"

#line 986 "C:/MCC18/h/adc.h"
#line 990 "C:/MCC18/h/adc.h"


#line 993 "C:/MCC18/h/adc.h"

#line 1009 "C:/MCC18/h/adc.h"

#line 1017 "C:/MCC18/h/adc.h"

#line 1025 "C:/MCC18/h/adc.h"

#line 1033 "C:/MCC18/h/adc.h"

#line 1041 "C:/MCC18/h/adc.h"
#line 1045 "C:/MCC18/h/adc.h"

#line 1047 "C:/MCC18/h/adc.h"

#line 1061 "C:/MCC18/h/adc.h"

#line 1069 "C:/MCC18/h/adc.h"

#line 1077 "C:/MCC18/h/adc.h"

#line 1085 "C:/MCC18/h/adc.h"

#line 1093 "C:/MCC18/h/adc.h"
#line 1097 "C:/MCC18/h/adc.h"


  
#line 1101 "C:/MCC18/h/adc.h"

#line 1103 "C:/MCC18/h/adc.h"
#line 1104 "C:/MCC18/h/adc.h"
#line 1105 "C:/MCC18/h/adc.h"
#line 1106 "C:/MCC18/h/adc.h"
#line 1107 "C:/MCC18/h/adc.h"
#line 1108 "C:/MCC18/h/adc.h"
#line 1109 "C:/MCC18/h/adc.h"
#line 1110 "C:/MCC18/h/adc.h"
#line 1111 "C:/MCC18/h/adc.h"
#line 1112 "C:/MCC18/h/adc.h"
#line 1113 "C:/MCC18/h/adc.h"
#line 1114 "C:/MCC18/h/adc.h"
#line 1115 "C:/MCC18/h/adc.h"
#line 1116 "C:/MCC18/h/adc.h"
#line 1117 "C:/MCC18/h/adc.h"
#line 1118 "C:/MCC18/h/adc.h"

#line 1120 "C:/MCC18/h/adc.h"


#line 1124 "C:/MCC18/h/adc.h"
#line 1125 "C:/MCC18/h/adc.h"
#line 1126 "C:/MCC18/h/adc.h"
#line 1127 "C:/MCC18/h/adc.h"
#line 1128 "C:/MCC18/h/adc.h"
#line 1129 "C:/MCC18/h/adc.h"

#line 1131 "C:/MCC18/h/adc.h"
#line 1137 "C:/MCC18/h/adc.h"

#line 1139 "C:/MCC18/h/adc.h"
#line 11 "main.c"

#line 1 "C:/MCC18/h/delays.h"

#line 3 "C:/MCC18/h/delays.h"


#line 13 "C:/MCC18/h/delays.h"
 

 
#line 1 "C:/MCC18/h/p18cxxx.h"

#line 3 "C:/MCC18/h/p18cxxx.h"

#line 5 "C:/MCC18/h/p18cxxx.h"
#line 7 "C:/MCC18/h/p18cxxx.h"
#line 9 "C:/MCC18/h/p18cxxx.h"
#line 11 "C:/MCC18/h/p18cxxx.h"
#line 13 "C:/MCC18/h/p18cxxx.h"
#line 15 "C:/MCC18/h/p18cxxx.h"
#line 17 "C:/MCC18/h/p18cxxx.h"
#line 19 "C:/MCC18/h/p18cxxx.h"
#line 21 "C:/MCC18/h/p18cxxx.h"
#line 23 "C:/MCC18/h/p18cxxx.h"
#line 25 "C:/MCC18/h/p18cxxx.h"
#line 27 "C:/MCC18/h/p18cxxx.h"
#line 29 "C:/MCC18/h/p18cxxx.h"
#line 31 "C:/MCC18/h/p18cxxx.h"
#line 33 "C:/MCC18/h/p18cxxx.h"
#line 35 "C:/MCC18/h/p18cxxx.h"
#line 37 "C:/MCC18/h/p18cxxx.h"
#line 39 "C:/MCC18/h/p18cxxx.h"
#line 41 "C:/MCC18/h/p18cxxx.h"
#line 43 "C:/MCC18/h/p18cxxx.h"
#line 45 "C:/MCC18/h/p18cxxx.h"
#line 47 "C:/MCC18/h/p18cxxx.h"
#line 49 "C:/MCC18/h/p18cxxx.h"
#line 51 "C:/MCC18/h/p18cxxx.h"
#line 53 "C:/MCC18/h/p18cxxx.h"
#line 55 "C:/MCC18/h/p18cxxx.h"
#line 57 "C:/MCC18/h/p18cxxx.h"
#line 59 "C:/MCC18/h/p18cxxx.h"
#line 61 "C:/MCC18/h/p18cxxx.h"
#line 63 "C:/MCC18/h/p18cxxx.h"
#line 65 "C:/MCC18/h/p18cxxx.h"
#line 67 "C:/MCC18/h/p18cxxx.h"
#line 69 "C:/MCC18/h/p18cxxx.h"
#line 71 "C:/MCC18/h/p18cxxx.h"
#line 73 "C:/MCC18/h/p18cxxx.h"
#line 75 "C:/MCC18/h/p18cxxx.h"
#line 77 "C:/MCC18/h/p18cxxx.h"
#line 79 "C:/MCC18/h/p18cxxx.h"
#line 81 "C:/MCC18/h/p18cxxx.h"
#line 83 "C:/MCC18/h/p18cxxx.h"
#line 85 "C:/MCC18/h/p18cxxx.h"
#line 87 "C:/MCC18/h/p18cxxx.h"
#line 89 "C:/MCC18/h/p18cxxx.h"
#line 91 "C:/MCC18/h/p18cxxx.h"
#line 93 "C:/MCC18/h/p18cxxx.h"
#line 95 "C:/MCC18/h/p18cxxx.h"
#line 97 "C:/MCC18/h/p18cxxx.h"
#line 99 "C:/MCC18/h/p18cxxx.h"
#line 101 "C:/MCC18/h/p18cxxx.h"
#line 103 "C:/MCC18/h/p18cxxx.h"
#line 105 "C:/MCC18/h/p18cxxx.h"
#line 107 "C:/MCC18/h/p18cxxx.h"
#line 109 "C:/MCC18/h/p18cxxx.h"
#line 111 "C:/MCC18/h/p18cxxx.h"
#line 113 "C:/MCC18/h/p18cxxx.h"
#line 115 "C:/MCC18/h/p18cxxx.h"
#line 1 "C:/MCC18/h/p18f25k22.h"

#line 5 "C:/MCC18/h/p18f25k22.h"
 


#line 2705 "C:/MCC18/h/p18f25k22.h"

#line 2711 "C:/MCC18/h/p18f25k22.h"

#line 2726 "C:/MCC18/h/p18f25k22.h"
#line 2731 "C:/MCC18/h/p18f25k22.h"
#line 115 "C:/MCC18/h/p18cxxx.h"

#line 117 "C:/MCC18/h/p18cxxx.h"
#line 119 "C:/MCC18/h/p18cxxx.h"
#line 121 "C:/MCC18/h/p18cxxx.h"
#line 123 "C:/MCC18/h/p18cxxx.h"
#line 125 "C:/MCC18/h/p18cxxx.h"
#line 127 "C:/MCC18/h/p18cxxx.h"
#line 129 "C:/MCC18/h/p18cxxx.h"
#line 131 "C:/MCC18/h/p18cxxx.h"
#line 133 "C:/MCC18/h/p18cxxx.h"
#line 135 "C:/MCC18/h/p18cxxx.h"
#line 137 "C:/MCC18/h/p18cxxx.h"
#line 139 "C:/MCC18/h/p18cxxx.h"
#line 141 "C:/MCC18/h/p18cxxx.h"
#line 143 "C:/MCC18/h/p18cxxx.h"
#line 145 "C:/MCC18/h/p18cxxx.h"
#line 147 "C:/MCC18/h/p18cxxx.h"
#line 149 "C:/MCC18/h/p18cxxx.h"
#line 151 "C:/MCC18/h/p18cxxx.h"
#line 153 "C:/MCC18/h/p18cxxx.h"
#line 155 "C:/MCC18/h/p18cxxx.h"
#line 157 "C:/MCC18/h/p18cxxx.h"
#line 159 "C:/MCC18/h/p18cxxx.h"
#line 161 "C:/MCC18/h/p18cxxx.h"
#line 163 "C:/MCC18/h/p18cxxx.h"
#line 165 "C:/MCC18/h/p18cxxx.h"
#line 167 "C:/MCC18/h/p18cxxx.h"
#line 169 "C:/MCC18/h/p18cxxx.h"
#line 171 "C:/MCC18/h/p18cxxx.h"
#line 173 "C:/MCC18/h/p18cxxx.h"
#line 175 "C:/MCC18/h/p18cxxx.h"
#line 177 "C:/MCC18/h/p18cxxx.h"
#line 179 "C:/MCC18/h/p18cxxx.h"
#line 181 "C:/MCC18/h/p18cxxx.h"
#line 183 "C:/MCC18/h/p18cxxx.h"
#line 185 "C:/MCC18/h/p18cxxx.h"
#line 187 "C:/MCC18/h/p18cxxx.h"
#line 189 "C:/MCC18/h/p18cxxx.h"
#line 191 "C:/MCC18/h/p18cxxx.h"
#line 193 "C:/MCC18/h/p18cxxx.h"
#line 195 "C:/MCC18/h/p18cxxx.h"
#line 197 "C:/MCC18/h/p18cxxx.h"
#line 199 "C:/MCC18/h/p18cxxx.h"
#line 201 "C:/MCC18/h/p18cxxx.h"
#line 203 "C:/MCC18/h/p18cxxx.h"
#line 205 "C:/MCC18/h/p18cxxx.h"
#line 207 "C:/MCC18/h/p18cxxx.h"
#line 209 "C:/MCC18/h/p18cxxx.h"
#line 211 "C:/MCC18/h/p18cxxx.h"
#line 213 "C:/MCC18/h/p18cxxx.h"
#line 215 "C:/MCC18/h/p18cxxx.h"
#line 217 "C:/MCC18/h/p18cxxx.h"
#line 219 "C:/MCC18/h/p18cxxx.h"
#line 221 "C:/MCC18/h/p18cxxx.h"
#line 223 "C:/MCC18/h/p18cxxx.h"
#line 225 "C:/MCC18/h/p18cxxx.h"
#line 227 "C:/MCC18/h/p18cxxx.h"
#line 229 "C:/MCC18/h/p18cxxx.h"
#line 231 "C:/MCC18/h/p18cxxx.h"
#line 233 "C:/MCC18/h/p18cxxx.h"
#line 235 "C:/MCC18/h/p18cxxx.h"
#line 237 "C:/MCC18/h/p18cxxx.h"
#line 239 "C:/MCC18/h/p18cxxx.h"
#line 241 "C:/MCC18/h/p18cxxx.h"
#line 243 "C:/MCC18/h/p18cxxx.h"
#line 245 "C:/MCC18/h/p18cxxx.h"
#line 247 "C:/MCC18/h/p18cxxx.h"
#line 249 "C:/MCC18/h/p18cxxx.h"
#line 251 "C:/MCC18/h/p18cxxx.h"
#line 253 "C:/MCC18/h/p18cxxx.h"
#line 255 "C:/MCC18/h/p18cxxx.h"
#line 257 "C:/MCC18/h/p18cxxx.h"
#line 259 "C:/MCC18/h/p18cxxx.h"
#line 261 "C:/MCC18/h/p18cxxx.h"
#line 263 "C:/MCC18/h/p18cxxx.h"
#line 265 "C:/MCC18/h/p18cxxx.h"
#line 267 "C:/MCC18/h/p18cxxx.h"
#line 269 "C:/MCC18/h/p18cxxx.h"
#line 271 "C:/MCC18/h/p18cxxx.h"
#line 273 "C:/MCC18/h/p18cxxx.h"
#line 275 "C:/MCC18/h/p18cxxx.h"
#line 277 "C:/MCC18/h/p18cxxx.h"
#line 279 "C:/MCC18/h/p18cxxx.h"
#line 281 "C:/MCC18/h/p18cxxx.h"
#line 283 "C:/MCC18/h/p18cxxx.h"
#line 285 "C:/MCC18/h/p18cxxx.h"
#line 287 "C:/MCC18/h/p18cxxx.h"
#line 289 "C:/MCC18/h/p18cxxx.h"
#line 291 "C:/MCC18/h/p18cxxx.h"
#line 293 "C:/MCC18/h/p18cxxx.h"
#line 295 "C:/MCC18/h/p18cxxx.h"
#line 297 "C:/MCC18/h/p18cxxx.h"
#line 299 "C:/MCC18/h/p18cxxx.h"
#line 301 "C:/MCC18/h/p18cxxx.h"
#line 303 "C:/MCC18/h/p18cxxx.h"
#line 305 "C:/MCC18/h/p18cxxx.h"
#line 307 "C:/MCC18/h/p18cxxx.h"
#line 309 "C:/MCC18/h/p18cxxx.h"
#line 311 "C:/MCC18/h/p18cxxx.h"
#line 313 "C:/MCC18/h/p18cxxx.h"
#line 315 "C:/MCC18/h/p18cxxx.h"
#line 317 "C:/MCC18/h/p18cxxx.h"
#line 319 "C:/MCC18/h/p18cxxx.h"
#line 321 "C:/MCC18/h/p18cxxx.h"
#line 323 "C:/MCC18/h/p18cxxx.h"
#line 325 "C:/MCC18/h/p18cxxx.h"
#line 327 "C:/MCC18/h/p18cxxx.h"
#line 329 "C:/MCC18/h/p18cxxx.h"
#line 331 "C:/MCC18/h/p18cxxx.h"
#line 333 "C:/MCC18/h/p18cxxx.h"
#line 335 "C:/MCC18/h/p18cxxx.h"
#line 337 "C:/MCC18/h/p18cxxx.h"
#line 339 "C:/MCC18/h/p18cxxx.h"
#line 341 "C:/MCC18/h/p18cxxx.h"
#line 343 "C:/MCC18/h/p18cxxx.h"
#line 345 "C:/MCC18/h/p18cxxx.h"
#line 347 "C:/MCC18/h/p18cxxx.h"
#line 349 "C:/MCC18/h/p18cxxx.h"
#line 351 "C:/MCC18/h/p18cxxx.h"
#line 353 "C:/MCC18/h/p18cxxx.h"
#line 355 "C:/MCC18/h/p18cxxx.h"
#line 357 "C:/MCC18/h/p18cxxx.h"
#line 359 "C:/MCC18/h/p18cxxx.h"
#line 361 "C:/MCC18/h/p18cxxx.h"
#line 363 "C:/MCC18/h/p18cxxx.h"
#line 365 "C:/MCC18/h/p18cxxx.h"
#line 367 "C:/MCC18/h/p18cxxx.h"
#line 369 "C:/MCC18/h/p18cxxx.h"
#line 371 "C:/MCC18/h/p18cxxx.h"
#line 373 "C:/MCC18/h/p18cxxx.h"
#line 375 "C:/MCC18/h/p18cxxx.h"
#line 377 "C:/MCC18/h/p18cxxx.h"
#line 379 "C:/MCC18/h/p18cxxx.h"
#line 381 "C:/MCC18/h/p18cxxx.h"
#line 383 "C:/MCC18/h/p18cxxx.h"
#line 385 "C:/MCC18/h/p18cxxx.h"
#line 387 "C:/MCC18/h/p18cxxx.h"
#line 389 "C:/MCC18/h/p18cxxx.h"
#line 391 "C:/MCC18/h/p18cxxx.h"
#line 393 "C:/MCC18/h/p18cxxx.h"
#line 395 "C:/MCC18/h/p18cxxx.h"
#line 397 "C:/MCC18/h/p18cxxx.h"
#line 399 "C:/MCC18/h/p18cxxx.h"
#line 401 "C:/MCC18/h/p18cxxx.h"
#line 403 "C:/MCC18/h/p18cxxx.h"
#line 405 "C:/MCC18/h/p18cxxx.h"
#line 407 "C:/MCC18/h/p18cxxx.h"
#line 409 "C:/MCC18/h/p18cxxx.h"
#line 411 "C:/MCC18/h/p18cxxx.h"
#line 413 "C:/MCC18/h/p18cxxx.h"
#line 415 "C:/MCC18/h/p18cxxx.h"
#line 417 "C:/MCC18/h/p18cxxx.h"
#line 419 "C:/MCC18/h/p18cxxx.h"
#line 421 "C:/MCC18/h/p18cxxx.h"
#line 423 "C:/MCC18/h/p18cxxx.h"
#line 425 "C:/MCC18/h/p18cxxx.h"
#line 427 "C:/MCC18/h/p18cxxx.h"
#line 429 "C:/MCC18/h/p18cxxx.h"
#line 431 "C:/MCC18/h/p18cxxx.h"
#line 433 "C:/MCC18/h/p18cxxx.h"
#line 435 "C:/MCC18/h/p18cxxx.h"
#line 437 "C:/MCC18/h/p18cxxx.h"
#line 439 "C:/MCC18/h/p18cxxx.h"
#line 441 "C:/MCC18/h/p18cxxx.h"
#line 443 "C:/MCC18/h/p18cxxx.h"
#line 445 "C:/MCC18/h/p18cxxx.h"
#line 447 "C:/MCC18/h/p18cxxx.h"
#line 449 "C:/MCC18/h/p18cxxx.h"
#line 451 "C:/MCC18/h/p18cxxx.h"
#line 453 "C:/MCC18/h/p18cxxx.h"
#line 455 "C:/MCC18/h/p18cxxx.h"
#line 457 "C:/MCC18/h/p18cxxx.h"
#line 459 "C:/MCC18/h/p18cxxx.h"
#line 461 "C:/MCC18/h/p18cxxx.h"
#line 463 "C:/MCC18/h/p18cxxx.h"
#line 465 "C:/MCC18/h/p18cxxx.h"
#line 467 "C:/MCC18/h/p18cxxx.h"
#line 469 "C:/MCC18/h/p18cxxx.h"
#line 471 "C:/MCC18/h/p18cxxx.h"
#line 473 "C:/MCC18/h/p18cxxx.h"
#line 475 "C:/MCC18/h/p18cxxx.h"
#line 477 "C:/MCC18/h/p18cxxx.h"
#line 479 "C:/MCC18/h/p18cxxx.h"
#line 481 "C:/MCC18/h/p18cxxx.h"
#line 483 "C:/MCC18/h/p18cxxx.h"
#line 485 "C:/MCC18/h/p18cxxx.h"
#line 487 "C:/MCC18/h/p18cxxx.h"
#line 489 "C:/MCC18/h/p18cxxx.h"
#line 491 "C:/MCC18/h/p18cxxx.h"
#line 493 "C:/MCC18/h/p18cxxx.h"
#line 495 "C:/MCC18/h/p18cxxx.h"
#line 497 "C:/MCC18/h/p18cxxx.h"
#line 499 "C:/MCC18/h/p18cxxx.h"
#line 501 "C:/MCC18/h/p18cxxx.h"
#line 503 "C:/MCC18/h/p18cxxx.h"
#line 505 "C:/MCC18/h/p18cxxx.h"
#line 507 "C:/MCC18/h/p18cxxx.h"
#line 509 "C:/MCC18/h/p18cxxx.h"
#line 511 "C:/MCC18/h/p18cxxx.h"
#line 513 "C:/MCC18/h/p18cxxx.h"
#line 515 "C:/MCC18/h/p18cxxx.h"
#line 517 "C:/MCC18/h/p18cxxx.h"
#line 519 "C:/MCC18/h/p18cxxx.h"
#line 521 "C:/MCC18/h/p18cxxx.h"
#line 523 "C:/MCC18/h/p18cxxx.h"
#line 525 "C:/MCC18/h/p18cxxx.h"
#line 527 "C:/MCC18/h/p18cxxx.h"
#line 529 "C:/MCC18/h/p18cxxx.h"
#line 531 "C:/MCC18/h/p18cxxx.h"
#line 533 "C:/MCC18/h/p18cxxx.h"
#line 535 "C:/MCC18/h/p18cxxx.h"
#line 537 "C:/MCC18/h/p18cxxx.h"
#line 539 "C:/MCC18/h/p18cxxx.h"
#line 541 "C:/MCC18/h/p18cxxx.h"
#line 543 "C:/MCC18/h/p18cxxx.h"
#line 545 "C:/MCC18/h/p18cxxx.h"
#line 547 "C:/MCC18/h/p18cxxx.h"
#line 549 "C:/MCC18/h/p18cxxx.h"
#line 551 "C:/MCC18/h/p18cxxx.h"

#line 553 "C:/MCC18/h/p18cxxx.h"
#line 16 "C:/MCC18/h/delays.h"


 
#line 20 "C:/MCC18/h/delays.h"

#line 22 "C:/MCC18/h/delays.h"

 
#line 25 "C:/MCC18/h/delays.h"


#line 31 "C:/MCC18/h/delays.h"
 
void Delay10TCYx(auto  unsigned char);


#line 38 "C:/MCC18/h/delays.h"
 
void Delay100TCYx(auto  unsigned char);


#line 45 "C:/MCC18/h/delays.h"
 
void Delay1KTCYx(auto  unsigned char);


#line 52 "C:/MCC18/h/delays.h"
 
void Delay10KTCYx(auto  unsigned char);

#line 56 "C:/MCC18/h/delays.h"
#line 12 "main.c"
	    
#line 1 "C:/MCC18/h/usart.h"

#line 3 "C:/MCC18/h/usart.h"

#line 30 "C:/MCC18/h/usart.h"
 
 



 


#line 43 "C:/MCC18/h/usart.h"
 

 
#line 86 "C:/MCC18/h/usart.h"
 


#line 89 "C:/MCC18/h/usart.h"
 
#line 91 "C:/MCC18/h/usart.h"


#line 93 "C:/MCC18/h/usart.h"
 



#line 98 "C:/MCC18/h/usart.h"
#line 99 "C:/MCC18/h/usart.h"
#line 100 "C:/MCC18/h/usart.h"
#line 101 "C:/MCC18/h/usart.h"
#line 102 "C:/MCC18/h/usart.h"
#line 103 "C:/MCC18/h/usart.h"
#line 104 "C:/MCC18/h/usart.h"
#line 105 "C:/MCC18/h/usart.h"
#line 106 "C:/MCC18/h/usart.h"
#line 107 "C:/MCC18/h/usart.h"
#line 108 "C:/MCC18/h/usart.h"
#line 109 "C:/MCC18/h/usart.h"
#line 110 "C:/MCC18/h/usart.h"
#line 111 "C:/MCC18/h/usart.h"
#line 112 "C:/MCC18/h/usart.h"
#line 113 "C:/MCC18/h/usart.h"



#line 117 "C:/MCC18/h/usart.h"
#line 150 "C:/MCC18/h/usart.h"

 

#line 154 "C:/MCC18/h/usart.h"
#line 155 "C:/MCC18/h/usart.h"

#line 157 "C:/MCC18/h/usart.h"
#line 170 "C:/MCC18/h/usart.h"
#line 187 "C:/MCC18/h/usart.h"
#line 189 "C:/MCC18/h/usart.h"


 

#line 194 "C:/MCC18/h/usart.h"
#line 195 "C:/MCC18/h/usart.h"
#line 216 "C:/MCC18/h/usart.h"

#line 226 "C:/MCC18/h/usart.h"
#line 229 "C:/MCC18/h/usart.h"

#line 239 "C:/MCC18/h/usart.h"
#line 242 "C:/MCC18/h/usart.h"

#line 257 "C:/MCC18/h/usart.h"

#line 268 "C:/MCC18/h/usart.h"

#line 281 "C:/MCC18/h/usart.h"

#line 295 "C:/MCC18/h/usart.h"
#line 298 "C:/MCC18/h/usart.h"

 

#line 301 "C:/MCC18/h/usart.h"
#line 302 "C:/MCC18/h/usart.h"

#line 328 "C:/MCC18/h/usart.h"

#line 345 "C:/MCC18/h/usart.h"

#line 356 "C:/MCC18/h/usart.h"

#line 369 "C:/MCC18/h/usart.h"

#line 383 "C:/MCC18/h/usart.h"
#line 387 "C:/MCC18/h/usart.h"


#line 389 "C:/MCC18/h/usart.h"
#line 390 "C:/MCC18/h/usart.h"

#line 417 "C:/MCC18/h/usart.h"

#line 434 "C:/MCC18/h/usart.h"

#line 445 "C:/MCC18/h/usart.h"

#line 458 "C:/MCC18/h/usart.h"

#line 472 "C:/MCC18/h/usart.h"
#line 476 "C:/MCC18/h/usart.h"

#line 478 "C:/MCC18/h/usart.h"
#line 480 "C:/MCC18/h/usart.h"


#line 483 "C:/MCC18/h/usart.h"
#line 485 "C:/MCC18/h/usart.h"


#line 487 "C:/MCC18/h/usart.h"
#line 488 "C:/MCC18/h/usart.h"
#line 491 "C:/MCC18/h/usart.h"

 

	
#line 496 "C:/MCC18/h/usart.h"
#line 497 "C:/MCC18/h/usart.h"
#line 498 "C:/MCC18/h/usart.h"
#line 499 "C:/MCC18/h/usart.h"
	
#line 501 "C:/MCC18/h/usart.h"
#line 507 "C:/MCC18/h/usart.h"

#line 509 "C:/MCC18/h/usart.h"
#line 511 "C:/MCC18/h/usart.h"

#line 513 "C:/MCC18/h/usart.h"
#line 13 "main.c"
	    
#line 1 "C:/MCC18/h/i2c.h"

#line 3 "C:/MCC18/h/i2c.h"

#line 30 "C:/MCC18/h/i2c.h"
 
 


 
#line 36 "C:/MCC18/h/i2c.h"
#line 37 "C:/MCC18/h/i2c.h"
#line 38 "C:/MCC18/h/i2c.h"
#line 39 "C:/MCC18/h/i2c.h"
#line 40 "C:/MCC18/h/i2c.h"
#line 41 "C:/MCC18/h/i2c.h"
#line 42 "C:/MCC18/h/i2c.h"

 
#line 45 "C:/MCC18/h/i2c.h"
#line 46 "C:/MCC18/h/i2c.h"


#line 49 "C:/MCC18/h/i2c.h"

#line 62 "C:/MCC18/h/i2c.h"

#line 75 "C:/MCC18/h/i2c.h"

#line 89 "C:/MCC18/h/i2c.h"

#line 102 "C:/MCC18/h/i2c.h"

#line 115 "C:/MCC18/h/i2c.h"

#line 129 "C:/MCC18/h/i2c.h"

#line 145 "C:/MCC18/h/i2c.h"

#line 161 "C:/MCC18/h/i2c.h"

#line 178 "C:/MCC18/h/i2c.h"

#line 195 "C:/MCC18/h/i2c.h"

#line 216 "C:/MCC18/h/i2c.h"

#line 233 "C:/MCC18/h/i2c.h"

#line 253 "C:/MCC18/h/i2c.h"

#line 269 "C:/MCC18/h/i2c.h"

#line 284 "C:/MCC18/h/i2c.h"
#line 324 "C:/MCC18/h/i2c.h"



#line 328 "C:/MCC18/h/i2c.h"
#line 330 "C:/MCC18/h/i2c.h"

#line 340 "C:/MCC18/h/i2c.h"

#line 353 "C:/MCC18/h/i2c.h"

#line 367 "C:/MCC18/h/i2c.h"

#line 380 "C:/MCC18/h/i2c.h"

#line 393 "C:/MCC18/h/i2c.h"
#line 397 "C:/MCC18/h/i2c.h"

#line 408 "C:/MCC18/h/i2c.h"

#line 421 "C:/MCC18/h/i2c.h"

#line 435 "C:/MCC18/h/i2c.h"

#line 448 "C:/MCC18/h/i2c.h"

#line 461 "C:/MCC18/h/i2c.h"
#line 465 "C:/MCC18/h/i2c.h"

#line 477 "C:/MCC18/h/i2c.h"

#line 491 "C:/MCC18/h/i2c.h"

#line 505 "C:/MCC18/h/i2c.h"

#line 520 "C:/MCC18/h/i2c.h"

#line 535 "C:/MCC18/h/i2c.h"
#line 539 "C:/MCC18/h/i2c.h"

#line 555 "C:/MCC18/h/i2c.h"
#line 558 "C:/MCC18/h/i2c.h"

#line 574 "C:/MCC18/h/i2c.h"
#line 577 "C:/MCC18/h/i2c.h"

#line 591 "C:/MCC18/h/i2c.h"

#line 608 "C:/MCC18/h/i2c.h"

#line 621 "C:/MCC18/h/i2c.h"

#line 634 "C:/MCC18/h/i2c.h"
#line 664 "C:/MCC18/h/i2c.h"



#line 668 "C:/MCC18/h/i2c.h"

#line 681 "C:/MCC18/h/i2c.h"

#line 696 "C:/MCC18/h/i2c.h"

#line 712 "C:/MCC18/h/i2c.h"

#line 727 "C:/MCC18/h/i2c.h"

#line 742 "C:/MCC18/h/i2c.h"

#line 755 "C:/MCC18/h/i2c.h"

#line 766 "C:/MCC18/h/i2c.h"
#line 782 "C:/MCC18/h/i2c.h"

#line 784 "C:/MCC18/h/i2c.h"

#line 787 "C:/MCC18/h/i2c.h"

#line 792 "C:/MCC18/h/i2c.h"

#line 806 "C:/MCC18/h/i2c.h"

#line 820 "C:/MCC18/h/i2c.h"

#line 834 "C:/MCC18/h/i2c.h"

#line 849 "C:/MCC18/h/i2c.h"

#line 864 "C:/MCC18/h/i2c.h"

#line 879 "C:/MCC18/h/i2c.h"

#line 890 "C:/MCC18/h/i2c.h"
#line 921 "C:/MCC18/h/i2c.h"


#line 924 "C:/MCC18/h/i2c.h"
#line 927 "C:/MCC18/h/i2c.h"

#line 929 "C:/MCC18/h/i2c.h"
#line 932 "C:/MCC18/h/i2c.h"

#line 934 "C:/MCC18/h/i2c.h"
#line 937 "C:/MCC18/h/i2c.h"

#line 939 "C:/MCC18/h/i2c.h"
#line 943 "C:/MCC18/h/i2c.h"

#line 945 "C:/MCC18/h/i2c.h"
#line 948 "C:/MCC18/h/i2c.h"

#line 950 "C:/MCC18/h/i2c.h"
#line 953 "C:/MCC18/h/i2c.h"

#line 955 "C:/MCC18/h/i2c.h"
#line 958 "C:/MCC18/h/i2c.h"

#line 960 "C:/MCC18/h/i2c.h"

#line 14 "main.c"
	 	
#line 1 "C:/MCC18/h/timers.h"

#line 3 "C:/MCC18/h/timers.h"

#line 30 "C:/MCC18/h/timers.h"
 


 

 
union Timers
{
  unsigned int lt;
  char bt[2];
};



#line 44 "C:/MCC18/h/timers.h"
 


#line 48 "C:/MCC18/h/timers.h"
#line 49 "C:/MCC18/h/timers.h"

 

#line 52 "C:/MCC18/h/timers.h"
 
 
#line 55 "C:/MCC18/h/timers.h"
#line 56 "C:/MCC18/h/timers.h"

#line 58 "C:/MCC18/h/timers.h"
#line 59 "C:/MCC18/h/timers.h"

#line 61 "C:/MCC18/h/timers.h"
#line 62 "C:/MCC18/h/timers.h"

#line 64 "C:/MCC18/h/timers.h"
#line 65 "C:/MCC18/h/timers.h"
#line 66 "C:/MCC18/h/timers.h"
#line 67 "C:/MCC18/h/timers.h"
#line 68 "C:/MCC18/h/timers.h"
#line 69 "C:/MCC18/h/timers.h"
#line 70 "C:/MCC18/h/timers.h"
#line 71 "C:/MCC18/h/timers.h"
#line 72 "C:/MCC18/h/timers.h"

#line 74 "C:/MCC18/h/timers.h"

#line 81 "C:/MCC18/h/timers.h"
#line 109 "C:/MCC18/h/timers.h"

void OpenTimer0 ( unsigned char config);
void CloseTimer0 (void);
unsigned int ReadTimer0 (void);
void WriteTimer0 ( unsigned int timer0);

 


#line 118 "C:/MCC18/h/timers.h"
 
 
#line 121 "C:/MCC18/h/timers.h"
#line 143 "C:/MCC18/h/timers.h"
#line 168 "C:/MCC18/h/timers.h"
#line 176 "C:/MCC18/h/timers.h"




#line 181 "C:/MCC18/h/timers.h"
#line 182 "C:/MCC18/h/timers.h"
#line 183 "C:/MCC18/h/timers.h"
#line 184 "C:/MCC18/h/timers.h"
#line 185 "C:/MCC18/h/timers.h"
#line 186 "C:/MCC18/h/timers.h"
#line 187 "C:/MCC18/h/timers.h"
#line 188 "C:/MCC18/h/timers.h"
#line 189 "C:/MCC18/h/timers.h"
#line 190 "C:/MCC18/h/timers.h"
#line 191 "C:/MCC18/h/timers.h"
#line 192 "C:/MCC18/h/timers.h"

#line 194 "C:/MCC18/h/timers.h"
#line 220 "C:/MCC18/h/timers.h"

void OpenTimer1 ( unsigned char config);
void CloseTimer1 (void);
unsigned int ReadTimer1 (void);
void WriteTimer1 ( unsigned int timer1);
#line 226 "C:/MCC18/h/timers.h"


 

#line 231 "C:/MCC18/h/timers.h"
#line 232 "C:/MCC18/h/timers.h"

#line 233 "C:/MCC18/h/timers.h"
#line 258 "C:/MCC18/h/timers.h"
#line 283 "C:/MCC18/h/timers.h"

#line 294 "C:/MCC18/h/timers.h"

#line 307 "C:/MCC18/h/timers.h"
#line 314 "C:/MCC18/h/timers.h"
 

#line 317 "C:/MCC18/h/timers.h"

#line 319 "C:/MCC18/h/timers.h"
#line 335 "C:/MCC18/h/timers.h"
#line 356 "C:/MCC18/h/timers.h"

#line 363 "C:/MCC18/h/timers.h"

#line 371 "C:/MCC18/h/timers.h"
#line 382 "C:/MCC18/h/timers.h"
#line 404 "C:/MCC18/h/timers.h"
#line 429 "C:/MCC18/h/timers.h"
#line 435 "C:/MCC18/h/timers.h"

 

#line 439 "C:/MCC18/h/timers.h"

#line 441 "C:/MCC18/h/timers.h"
#line 466 "C:/MCC18/h/timers.h"
#line 491 "C:/MCC18/h/timers.h"

#line 502 "C:/MCC18/h/timers.h"

#line 515 "C:/MCC18/h/timers.h"
#line 523 "C:/MCC18/h/timers.h"


#line 526 "C:/MCC18/h/timers.h"
#line 545 "C:/MCC18/h/timers.h"
#line 573 "C:/MCC18/h/timers.h"
#line 580 "C:/MCC18/h/timers.h"
#line 602 "C:/MCC18/h/timers.h"
#line 627 "C:/MCC18/h/timers.h"
#line 634 "C:/MCC18/h/timers.h"



#line 638 "C:/MCC18/h/timers.h"

#line 640 "C:/MCC18/h/timers.h"
#line 665 "C:/MCC18/h/timers.h"
#line 690 "C:/MCC18/h/timers.h"

#line 701 "C:/MCC18/h/timers.h"

#line 714 "C:/MCC18/h/timers.h"
#line 722 "C:/MCC18/h/timers.h"


#line 725 "C:/MCC18/h/timers.h"
#line 747 "C:/MCC18/h/timers.h"
#line 772 "C:/MCC18/h/timers.h"
#line 779 "C:/MCC18/h/timers.h"




#line 784 "C:/MCC18/h/timers.h"

#line 786 "C:/MCC18/h/timers.h"
#line 811 "C:/MCC18/h/timers.h"
#line 836 "C:/MCC18/h/timers.h"

#line 847 "C:/MCC18/h/timers.h"

#line 860 "C:/MCC18/h/timers.h"
#line 868 "C:/MCC18/h/timers.h"


#line 871 "C:/MCC18/h/timers.h"

#line 873 "C:/MCC18/h/timers.h"
#line 898 "C:/MCC18/h/timers.h"
#line 923 "C:/MCC18/h/timers.h"

#line 934 "C:/MCC18/h/timers.h"

#line 947 "C:/MCC18/h/timers.h"
#line 955 "C:/MCC18/h/timers.h"



#line 959 "C:/MCC18/h/timers.h"

#line 961 "C:/MCC18/h/timers.h"
#line 986 "C:/MCC18/h/timers.h"
#line 1011 "C:/MCC18/h/timers.h"

#line 1022 "C:/MCC18/h/timers.h"

#line 1035 "C:/MCC18/h/timers.h"
#line 1043 "C:/MCC18/h/timers.h"





#line 1049 "C:/MCC18/h/timers.h"
#line 1067 "C:/MCC18/h/timers.h"
#line 1094 "C:/MCC18/h/timers.h"
#line 1095 "C:/MCC18/h/timers.h"

#line 1097 "C:/MCC18/h/timers.h"
#line 1104 "C:/MCC18/h/timers.h"
#line 1111 "C:/MCC18/h/timers.h"
#line 1113 "C:/MCC18/h/timers.h"
#line 1119 "C:/MCC18/h/timers.h"
#line 1124 "C:/MCC18/h/timers.h"
#line 1126 "C:/MCC18/h/timers.h"
#line 1132 "C:/MCC18/h/timers.h"
#line 1138 "C:/MCC18/h/timers.h"
#line 1139 "C:/MCC18/h/timers.h"

#line 1141 "C:/MCC18/h/timers.h"
#line 1143 "C:/MCC18/h/timers.h"

#line 1145 "C:/MCC18/h/timers.h"

#line 15 "main.c"

#line 1 "C:/MCC18/h/math.h"
 

#line 4 "C:/MCC18/h/math.h"

typedef float float_t;
typedef float double_t;

#line 9 "C:/MCC18/h/math.h"
#line 10 "C:/MCC18/h/math.h"
#line 11 "C:/MCC18/h/math.h"

float fabs (auto float x);
float ldexp (auto float x, auto int n);
float exp (auto float f);
float sqrt (auto float x);
float asin (auto float x);
float acos (auto float x);
float atan2 (auto float y, auto float x);
float atan (auto float x);
float sin (auto float x);
float cos (auto float x);
float tan (auto float x);
float sinh (auto float x);
float cosh (auto float x);
float tanh (auto float x);
float frexp (auto float x, auto int *pexp);
float log10 (auto float x);
float log (auto float x);
float pow (auto float x, auto float y);
float ceil (auto float x);
float floor (auto float x);
float modf (auto float x, auto float *ipart);
float fmod (auto float x, auto float y);

float mchptoieee (auto unsigned long v);
unsigned long ieeetomchp (auto float v);

#line 39 "C:/MCC18/h/math.h"
#line 16 "main.c"


#line 1 "C:/MCC18/h/pwm.h"

#line 3 "C:/MCC18/h/pwm.h"

#line 30 "C:/MCC18/h/pwm.h"
 
 



#line 48 "C:/MCC18/h/pwm.h"
 

 
#line 82 "C:/MCC18/h/pwm.h"
 

 
union PWMDC
{
    unsigned int lpwm;
    char bpwm[2];
};


 

#line 99 "C:/MCC18/h/pwm.h"
 
 
 

#line 106 "C:/MCC18/h/pwm.h"
#line 107 "C:/MCC18/h/pwm.h"
#line 116 "C:/MCC18/h/pwm.h"
#line 124 "C:/MCC18/h/pwm.h"

#line 129 "C:/MCC18/h/pwm.h"

#line 133 "C:/MCC18/h/pwm.h"
#line 142 "C:/MCC18/h/pwm.h"
#line 150 "C:/MCC18/h/pwm.h"
#line 152 "C:/MCC18/h/pwm.h"


#line 155 "C:/MCC18/h/pwm.h"
#line 181 "C:/MCC18/h/pwm.h"
#line 186 "C:/MCC18/h/pwm.h"
#line 191 "C:/MCC18/h/pwm.h"
#line 193 "C:/MCC18/h/pwm.h"
#line 201 "C:/MCC18/h/pwm.h"
#line 203 "C:/MCC18/h/pwm.h"
#line 229 "C:/MCC18/h/pwm.h"
#line 235 "C:/MCC18/h/pwm.h"
#line 241 "C:/MCC18/h/pwm.h"
#line 243 "C:/MCC18/h/pwm.h"
#line 253 "C:/MCC18/h/pwm.h"
#line 255 "C:/MCC18/h/pwm.h"
#line 256 "C:/MCC18/h/pwm.h"


#line 259 "C:/MCC18/h/pwm.h"
#line 267 "C:/MCC18/h/pwm.h"
#line 270 "C:/MCC18/h/pwm.h"
#line 277 "C:/MCC18/h/pwm.h"
#line 279 "C:/MCC18/h/pwm.h"
#line 288 "C:/MCC18/h/pwm.h"
#line 296 "C:/MCC18/h/pwm.h"
#line 299 "C:/MCC18/h/pwm.h"
#line 307 "C:/MCC18/h/pwm.h"
#line 309 "C:/MCC18/h/pwm.h"
#line 320 "C:/MCC18/h/pwm.h"
#line 321 "C:/MCC18/h/pwm.h"


#line 324 "C:/MCC18/h/pwm.h"
#line 341 "C:/MCC18/h/pwm.h"
#line 361 "C:/MCC18/h/pwm.h"
#line 362 "C:/MCC18/h/pwm.h"


void OpenPWM1 ( char period);
void SetDCPWM1 ( unsigned int duty_cycle);

#line 368 "C:/MCC18/h/pwm.h"
#line 369 "C:/MCC18/h/pwm.h"
#line 373 "C:/MCC18/h/pwm.h"
void ClosePWM1 (void);




#line 379 "C:/MCC18/h/pwm.h"
#line 380 "C:/MCC18/h/pwm.h"
#line 385 "C:/MCC18/h/pwm.h"
#line 388 "C:/MCC18/h/pwm.h"
#line 391 "C:/MCC18/h/pwm.h"



#line 395 "C:/MCC18/h/pwm.h"
#line 399 "C:/MCC18/h/pwm.h"
#line 402 "C:/MCC18/h/pwm.h"
#line 405 "C:/MCC18/h/pwm.h"



#line 409 "C:/MCC18/h/pwm.h"
#line 419 "C:/MCC18/h/pwm.h"

#line 421 "C:/MCC18/h/pwm.h"
#line 429 "C:/MCC18/h/pwm.h"

#line 431 "C:/MCC18/h/pwm.h"
#line 441 "C:/MCC18/h/pwm.h"
#line 454 "C:/MCC18/h/pwm.h"
#line 462 "C:/MCC18/h/pwm.h"
#line 463 "C:/MCC18/h/pwm.h"
#line 465 "C:/MCC18/h/pwm.h"


#line 468 "C:/MCC18/h/pwm.h"
#line 476 "C:/MCC18/h/pwm.h"

#line 478 "C:/MCC18/h/pwm.h"
#line 486 "C:/MCC18/h/pwm.h"
#line 499 "C:/MCC18/h/pwm.h"
#line 500 "C:/MCC18/h/pwm.h"


#line 503 "C:/MCC18/h/pwm.h"
#line 505 "C:/MCC18/h/pwm.h"
#line 507 "C:/MCC18/h/pwm.h"
#line 509 "C:/MCC18/h/pwm.h"
#line 511 "C:/MCC18/h/pwm.h"
#line 512 "C:/MCC18/h/pwm.h"
#line 513 "C:/MCC18/h/pwm.h"

#line 515 "C:/MCC18/h/pwm.h"
#line 517 "C:/MCC18/h/pwm.h"
#line 519 "C:/MCC18/h/pwm.h"
#line 521 "C:/MCC18/h/pwm.h"
#line 522 "C:/MCC18/h/pwm.h"
#line 523 "C:/MCC18/h/pwm.h"

#line 525 "C:/MCC18/h/pwm.h"
#line 527 "C:/MCC18/h/pwm.h"
#line 529 "C:/MCC18/h/pwm.h"
#line 531 "C:/MCC18/h/pwm.h"
#line 533 "C:/MCC18/h/pwm.h"
#line 534 "C:/MCC18/h/pwm.h"
#line 535 "C:/MCC18/h/pwm.h"

#line 537 "C:/MCC18/h/pwm.h"
#line 539 "C:/MCC18/h/pwm.h"
#line 541 "C:/MCC18/h/pwm.h"
#line 542 "C:/MCC18/h/pwm.h"
#line 543 "C:/MCC18/h/pwm.h"

#line 545 "C:/MCC18/h/pwm.h"
#line 547 "C:/MCC18/h/pwm.h"
#line 549 "C:/MCC18/h/pwm.h"
#line 551 "C:/MCC18/h/pwm.h"
#line 552 "C:/MCC18/h/pwm.h"
#line 553 "C:/MCC18/h/pwm.h"

#line 555 "C:/MCC18/h/pwm.h"
#line 557 "C:/MCC18/h/pwm.h"
#line 558 "C:/MCC18/h/pwm.h"
#line 559 "C:/MCC18/h/pwm.h"

#line 561 "C:/MCC18/h/pwm.h"
#line 563 "C:/MCC18/h/pwm.h"
#line 564 "C:/MCC18/h/pwm.h"
#line 565 "C:/MCC18/h/pwm.h"

#line 567 "C:/MCC18/h/pwm.h"
#line 569 "C:/MCC18/h/pwm.h"
#line 570 "C:/MCC18/h/pwm.h"
#line 571 "C:/MCC18/h/pwm.h"

#line 573 "C:/MCC18/h/pwm.h"
#line 575 "C:/MCC18/h/pwm.h"
#line 576 "C:/MCC18/h/pwm.h"
#line 577 "C:/MCC18/h/pwm.h"

#line 579 "C:/MCC18/h/pwm.h"
#line 581 "C:/MCC18/h/pwm.h"
#line 582 "C:/MCC18/h/pwm.h"
#line 583 "C:/MCC18/h/pwm.h"

#line 585 "C:/MCC18/h/pwm.h"
#line 18 "main.c"



#line 25 "main.c"
 




#line 31 "main.c"
#line 32 "main.c"
#line 33 "main.c"
#line 34 "main.c"
#line 35 "main.c"
#line 36 "main.c"
#line 37 "main.c"


#pragma udata access volatile_access

ram near unsigned char sspcon1copy;
ram near unsigned char address;
ram near unsigned char data;
ram near unsigned char rxbuf[2 ];
ram near unsigned char txbuf[2 ];
ram near unsigned char rxcount, txcount;
ram near int PWM;
ram near int rxinptr, rxoutptr, txinptr, txoutptr;

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
int last_cv;
int cv;
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
int speed;
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

#line 99 "main.c"

#line 101 "main.c"
#line 102 "main.c"
#line 103 "main.c"
#line 104 "main.c"

#line 106 "main.c"
#line 107 "main.c"
#line 108 "main.c"
#line 109 "main.c"

#line 111 "main.c"
#line 112 "main.c"
#line 113 "main.c"
#line 114 "main.c"

#line 116 "main.c"
#line 117 "main.c"

#line 119 "main.c"
#line 120 "main.c"

#line 122 "main.c"

void InterruptHandlerHigh (void); 
void InterruptHandlerLow (void); 
void Handle_I2C(void);		
void Handle_LEDs(void);		
void Handle_SWs(void);		
void Read_Pos(void);		
void Scan_Touch(void);		
void Calculate_PWM(void);		
void Run_Motor(void);		
void Init(void);				



#pragma code InterruptVectorHigh = 0x08
void
InterruptVectorHigh (void)
{
  _asm
    goto InterruptHandlerHigh 
  _endasm
}

#line 154 "main.c"
 




#pragma code
#pragma interrupt InterruptHandlerHigh

void
InterruptHandlerHigh () 
{
	INTCONbits.TMR0IE = 0;
	if (PIR1bits.SSPIF == 1)									
	{
		sspcon1copy = SSPCON1;
		sspcon1copy &= 0b00000110;
		if (sspcon1copy == 0b00000110)							
		{
			if (SSPSTATbits.R_W == 0)							
			{		
				if (SSPSTATbits.D_A == 0)						
				{				
					address = SSPBUF; 							
					rxcount = 0;
					txcount = 0;
				}
				else											
				{		
					if (SSPSTATbits.BF == 1)					
					{
						if (rxcount < 2 )
						{	
							rxbuf[rxcount] = SSPBUF;
							rxcount++;
							new_data = (rxcount==2);
						}
						else
						{
						SSPCON1bits.WCOL = 0;
						SSPCON1bits.SSPOV = 0;
						SSPCON1bits.CKP = 0;
						}
					}
				}
			}
			else												
			{

				data = SSPBUF; 
				if (txcount < 2 ) 								
				{
					SSPBUF = txbuf[txcount]; 				
					txcount++;
				}
				else
				{
					
						SSPCON1bits.WCOL = 0;
						SSPCON1bits.SSPOV = 0;
						SSPCON1bits.CKP = 0;
				}
			}
		}
		PIR1bits.SSPIF = 0; 
		SSPCON1bits.CKP = 1; 
		
	}

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

#line 239 "main.c"
 
#pragma code 

void main(void)
{
	int travel_distance = 0;
	double move_step = 0;
	unsigned char move_resolution = 30;
	unsigned char move_cnt = 0;

	Init();

	while (1) 
	{


	if (new_data)
		{
		Handle_SWs();
		Handle_I2C();
		Handle_LEDs();
		Scan_Touch();
		Read_Pos();




		}





		fader_dbl_goal = (fader_int_goal*0.8) + (fader_goal*0.2);
		fader_int_goal = fader_dbl_goal;
		Calculate_PWM();	
		Run_Motor();



	

	}
}
void Scan_Touch(void)
	{	
	unsigned int touch_adc;
	SetChanADC(0b11011111 );
	ConvertADC();
	while( BusyADC() );
	
	touch_adc = ADRESH;
	touch_adc = touch_adc << 8;
	touch_adc = touch_adc + ADRESL;
	if (touch_adc>(880+(fader_pos*0.07)))
		{
		fader_touch_sens = 1;
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
	SetChanADC(0b10000111 );
	ConvertADC();
	while( BusyADC() );
	
	fader_pos = ADRESH;
	fader_pos = fader_pos << 8;
	fader_pos = fader_pos + ADRESL;
	}	


void Calculate_PWM(void)
	{	
	SetChanADC(0b10001111 );
	ConvertADC();
	while( BusyADC() );
	
	fader_compare = ADRESH;
	fader_compare = fader_compare << 8;
	fader_compare = fader_compare + ADRESL;

			pError = fader_int_goal-fader_compare;
			iError += pError;
			iError *= intTime;
			if (iError>1000) iError =1000;
			if (iError<-1000) iError =-1000;
			dError = (lastpError - pError)*derTime/time_interval;

			fspeed = ((pK*pError)+(iK*iError)+(dK*dError))*gain;
			lastpError = pError;


			speed = fabs(fspeed);

	

			PWM=speed;
	
	}
	
void Handle_SWs(void)
	{
	local_fader_status = 0;	
	if(!PORTCbits.RC6 ) local_fader_status = 0x08;
	local_fader_status += (fader_touch_sens*0x10);
	}	
	
void Handle_LEDs(void)
	{
		LATBbits.LATB0  = (!((indata[1]&AUTO)==AUTO) );
		LATBbits.LATB1  = !((indata[1]&TOUCH)==TOUCH) ;
		LATBbits.LATB2  = !((indata[1]&WRITE)==WRITE) ;
		LATBbits.LATB3  = !((indata[1]&MUTE)==MUTE) ;

		if (fader_touch_sens) LATBbits.LATB2  = BlinkLED;
		if (fader_touch_sens) LATBbits.LATB0  = BlinkLED;

	}		
void Run_Motor(void)
	{
	
	if (fabs(fader_compare-fader_int_goal)>tol)
		{
		if (PWM<motorstart) PWM = motorstart;

			if(fspeed>0)
				{
				SetDCPWM2(PWM);
				SetDCPWM1(0);
				LATCbits.LATC0  = (!fader_touch_sens & soft_motor_on);
				}
			else
				{
				SetDCPWM2(0);
				SetDCPWM1(PWM);
				LATCbits.LATC0  = (!fader_touch_sens & soft_motor_on);
				}







		}	
	else
		{
		SetDCPWM2(0);
		SetDCPWM1(0);
		LATCbits.LATC0  = 0;
		}
	}	
		
void Handle_I2C(void)
	{
	

	INTCONbits.GIE = 0;
	if ((rxbuf[1]&ERROR_MASK)==ERROR_CHECK)			
		{
		indata[0] = rxbuf[0];
		indata[1] = rxbuf[1];
	
		fader_goal = (indata[1] & 0x03);
		fader_goal = fader_goal << 8;
		fader_goal =  fader_goal + indata[0];

		soft_motor_on = ((indata[1]&MOTOR_ENABLE)==MOTOR_ENABLE) ;
		}
		txbuf[0] = (unsigned char)(fader_pos & 0xFF) ;
		txbuf[1] = (unsigned char)(fader_pos>>8) +local_fader_status;
	new_data =0;
	INTCONbits.GIE = 1;
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
	
	rxinptr = rxoutptr = txinptr = txoutptr = 0;
	rxcount = txcount = 0;

	TRISA = 0xFF;
	TRISB = 0xF0;	
	TRISC = 0xF8;
	TRISCbits.TRISC1 =0;
	TRISCbits.TRISC2 =0;
	
	SSPCON1 = 0x36 + 0x00; 	
							
							
	
	fader_address = ((PORTA & 0b11100000)>>5) ;
	SSPADD = 0xE0 + fader_address; 

	
	INTCONbits.PEIE = 1;
	INTCONbits.GIE = 1;
	PIE1bits.SSPIE = 1; 
 	INTCONbits.TMR0IE=1; 

  	OpenTimer0 (0b11111111  & 0b11011111  & 0b11111111  & 0b11110111 );

	OpenADC(	0b10101111      &
				0b11111111 	&
				0b11110011 ,
				0b11100111 		&
				0b01111111 		&
				0b11111110  
				, 15 );
	
	ADCON1 = 0x0C;

	OpenTimer2(T2_PS_1_16 & 0b01111111 );
	OpenPWM1(2047);									
	SetDCPWM1(0); 

	OpenPWM2(2047);									
	SetDCPWM2(0);  

	motorstart =400;
	tol = 3;
	time_interval = 0.005;	

	intTime = 0.98;			
	derTime = 5;			

	gain = 500;				

	pK = 3;			

	iK = 0.02;					
	dK = -0.06;					

	}

