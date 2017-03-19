#line 1 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"
#line 1 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"

#line 43 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"
 


#line 47 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"

 
#line 1 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/./USB/usb.h"


#line 7 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/./USB/usb.h"
 


#line 57 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/./USB/usb.h"
 

#line 85 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/./USB/usb.h"
 




#line 96 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/./USB/usb.h"
 



#line 101 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/./USB/usb.h"









#line 1 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/GenericTypeDefs.h"

#line 46 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/GenericTypeDefs.h"
 


#line 50 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/GenericTypeDefs.h"

 
#line 53 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/GenericTypeDefs.h"
#line 55 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/GenericTypeDefs.h"
#line 56 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/GenericTypeDefs.h"
#line 57 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/GenericTypeDefs.h"

#line 59 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/GenericTypeDefs.h"
#line 60 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/GenericTypeDefs.h"
#line 61 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/GenericTypeDefs.h"

 
#line 1 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stddef.h"
 

#line 4 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stddef.h"

typedef unsigned char wchar_t;


#line 10 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stddef.h"
 
typedef signed short int ptrdiff_t;
typedef signed short int ptrdiffram_t;
typedef signed short long int ptrdiffrom_t;


#line 20 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stddef.h"
 
typedef unsigned short int size_t;
typedef unsigned short int sizeram_t;
typedef unsigned short long int sizerom_t;


#line 34 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stddef.h"
 
#line 36 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stddef.h"


#line 41 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stddef.h"
 
#line 43 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stddef.h"

#line 45 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stddef.h"
#line 63 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/GenericTypeDefs.h"
 

typedef enum _BOOL { FALSE = 0, TRUE } BOOL;     
typedef enum _BIT { CLEAR = 0, SET } BIT;

#line 69 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/GenericTypeDefs.h"
#line 70 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/GenericTypeDefs.h"
#line 71 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/GenericTypeDefs.h"

 
typedef signed int          INT;
typedef signed char         INT8;
typedef signed short int    INT16;
typedef signed long int     INT32;

 
#line 80 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/GenericTypeDefs.h"
#line 82 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/GenericTypeDefs.h"

 
typedef unsigned int        UINT;
typedef unsigned char       UINT8;
typedef unsigned short int  UINT16;
 
#line 89 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/GenericTypeDefs.h"
typedef unsigned short long UINT24;
#line 91 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/GenericTypeDefs.h"
typedef unsigned long int   UINT32;      
 
#line 94 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/GenericTypeDefs.h"
#line 96 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/GenericTypeDefs.h"

typedef union
{
    UINT8 Val;
    struct
    {
         UINT8 b0:1;
         UINT8 b1:1;
         UINT8 b2:1;
         UINT8 b3:1;
         UINT8 b4:1;
         UINT8 b5:1;
         UINT8 b6:1;
         UINT8 b7:1;
    } bits;
} UINT8_VAL, UINT8_BITS;

typedef union 
{
    UINT16 Val;
    UINT8 v[2] ;
    struct 
    {
        UINT8 LB;
        UINT8 HB;
    } byte;
    struct 
    {
         UINT8 b0:1;
         UINT8 b1:1;
         UINT8 b2:1;
         UINT8 b3:1;
         UINT8 b4:1;
         UINT8 b5:1;
         UINT8 b6:1;
         UINT8 b7:1;
         UINT8 b8:1;
         UINT8 b9:1;
         UINT8 b10:1;
         UINT8 b11:1;
         UINT8 b12:1;
         UINT8 b13:1;
         UINT8 b14:1;
         UINT8 b15:1;
    } bits;
} UINT16_VAL, UINT16_BITS;

 
#line 145 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/GenericTypeDefs.h"
typedef union
{
    UINT24 Val;
    UINT8 v[3] ;
    struct 
    {
        UINT8 LB;
        UINT8 HB;
        UINT8 UB;
    } byte;
    struct 
    {
         UINT8 b0:1;
         UINT8 b1:1;
         UINT8 b2:1;
         UINT8 b3:1;
         UINT8 b4:1;
         UINT8 b5:1;
         UINT8 b6:1;
         UINT8 b7:1;
         UINT8 b8:1;
         UINT8 b9:1;
         UINT8 b10:1;
         UINT8 b11:1;
         UINT8 b12:1;
         UINT8 b13:1;
         UINT8 b14:1;
         UINT8 b15:1;
         UINT8 b16:1;
         UINT8 b17:1;
         UINT8 b18:1;
         UINT8 b19:1;
         UINT8 b20:1;
         UINT8 b21:1;
         UINT8 b22:1;
         UINT8 b23:1;
    } bits;
} UINT24_VAL, UINT24_BITS;
#line 184 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/GenericTypeDefs.h"

typedef union
{
    UINT32 Val;
    UINT16 w[2] ;
    UINT8  v[4] ;
    struct 
    {
        UINT16 LW;
        UINT16 HW;
    } word;
    struct 
    {
        UINT8 LB;
        UINT8 HB;
        UINT8 UB;
        UINT8 MB;
    } byte;
    struct 
    {
        UINT16_VAL low;
        UINT16_VAL high;
    }wordUnion;
    struct 
    {
         UINT8 b0:1;
         UINT8 b1:1;
         UINT8 b2:1;
         UINT8 b3:1;
         UINT8 b4:1;
         UINT8 b5:1;
         UINT8 b6:1;
         UINT8 b7:1;
         UINT8 b8:1;
         UINT8 b9:1;
         UINT8 b10:1;
         UINT8 b11:1;
         UINT8 b12:1;
         UINT8 b13:1;
         UINT8 b14:1;
         UINT8 b15:1;
         UINT8 b16:1;
         UINT8 b17:1;
         UINT8 b18:1;
         UINT8 b19:1;
         UINT8 b20:1;
         UINT8 b21:1;
         UINT8 b22:1;
         UINT8 b23:1;
         UINT8 b24:1;
         UINT8 b25:1;
         UINT8 b26:1;
         UINT8 b27:1;
         UINT8 b28:1;
         UINT8 b29:1;
         UINT8 b30:1;
         UINT8 b31:1;
    } bits;
} UINT32_VAL;

 
#line 246 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/GenericTypeDefs.h"
#line 333 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/GenericTypeDefs.h"

 

 
typedef void                    VOID;

typedef char                    CHAR8;
typedef unsigned char           UCHAR8;

typedef unsigned char           BYTE;                            
typedef unsigned short int      WORD;                            
typedef unsigned long           DWORD;                           
 

typedef unsigned long long      QWORD;                           
typedef signed char             CHAR;                            
typedef signed short int        SHORT;                           
typedef signed long             LONG;                            
 

typedef signed long long        LONGLONG;                        
typedef union
{
    BYTE Val;
    struct 
    {
         BYTE b0:1;
         BYTE b1:1;
         BYTE b2:1;
         BYTE b3:1;
         BYTE b4:1;
         BYTE b5:1;
         BYTE b6:1;
         BYTE b7:1;
    } bits;
} BYTE_VAL, BYTE_BITS;

typedef union
{
    WORD Val;
    BYTE v[2] ;
    struct 
    {
        BYTE LB;
        BYTE HB;
    } byte;
    struct 
    {
         BYTE b0:1;
         BYTE b1:1;
         BYTE b2:1;
         BYTE b3:1;
         BYTE b4:1;
         BYTE b5:1;
         BYTE b6:1;
         BYTE b7:1;
         BYTE b8:1;
         BYTE b9:1;
         BYTE b10:1;
         BYTE b11:1;
         BYTE b12:1;
         BYTE b13:1;
         BYTE b14:1;
         BYTE b15:1;
    } bits;
} WORD_VAL, WORD_BITS;

typedef union
{
    DWORD Val;
    WORD w[2] ;
    BYTE v[4] ;
    struct 
    {
        WORD LW;
        WORD HW;
    } word;
    struct 
    {
        BYTE LB;
        BYTE HB;
        BYTE UB;
        BYTE MB;
    } byte;
    struct 
    {
        WORD_VAL low;
        WORD_VAL high;
    }wordUnion;
    struct 
    {
         BYTE b0:1;
         BYTE b1:1;
         BYTE b2:1;
         BYTE b3:1;
         BYTE b4:1;
         BYTE b5:1;
         BYTE b6:1;
         BYTE b7:1;
         BYTE b8:1;
         BYTE b9:1;
         BYTE b10:1;
         BYTE b11:1;
         BYTE b12:1;
         BYTE b13:1;
         BYTE b14:1;
         BYTE b15:1;
         BYTE b16:1;
         BYTE b17:1;
         BYTE b18:1;
         BYTE b19:1;
         BYTE b20:1;
         BYTE b21:1;
         BYTE b22:1;
         BYTE b23:1;
         BYTE b24:1;
         BYTE b25:1;
         BYTE b26:1;
         BYTE b27:1;
         BYTE b28:1;
         BYTE b29:1;
         BYTE b30:1;
         BYTE b31:1;
    } bits;
} DWORD_VAL;

 
typedef union
{
    QWORD Val;
    DWORD d[2] ;
    WORD w[4] ;
    BYTE v[8] ;
    struct 
    {
        DWORD LD;
        DWORD HD;
    } dword;
    struct 
    {
        WORD LW;
        WORD HW;
        WORD UW;
        WORD MW;
    } word;
    struct 
    {
         BYTE b0:1;
         BYTE b1:1;
         BYTE b2:1;
         BYTE b3:1;
         BYTE b4:1;
         BYTE b5:1;
         BYTE b6:1;
         BYTE b7:1;
         BYTE b8:1;
         BYTE b9:1;
         BYTE b10:1;
         BYTE b11:1;
         BYTE b12:1;
         BYTE b13:1;
         BYTE b14:1;
         BYTE b15:1;
         BYTE b16:1;
         BYTE b17:1;
         BYTE b18:1;
         BYTE b19:1;
         BYTE b20:1;
         BYTE b21:1;
         BYTE b22:1;
         BYTE b23:1;
         BYTE b24:1;
         BYTE b25:1;
         BYTE b26:1;
         BYTE b27:1;
         BYTE b28:1;
         BYTE b29:1;
         BYTE b30:1;
         BYTE b31:1;
         BYTE b32:1;
         BYTE b33:1;
         BYTE b34:1;
         BYTE b35:1;
         BYTE b36:1;
         BYTE b37:1;
         BYTE b38:1;
         BYTE b39:1;
         BYTE b40:1;
         BYTE b41:1;
         BYTE b42:1;
         BYTE b43:1;
         BYTE b44:1;
         BYTE b45:1;
         BYTE b46:1;
         BYTE b47:1;
         BYTE b48:1;
         BYTE b49:1;
         BYTE b50:1;
         BYTE b51:1;
         BYTE b52:1;
         BYTE b53:1;
         BYTE b54:1;
         BYTE b55:1;
         BYTE b56:1;
         BYTE b57:1;
         BYTE b58:1;
         BYTE b59:1;
         BYTE b60:1;
         BYTE b61:1;
         BYTE b62:1;
         BYTE b63:1;
    } bits;
} QWORD_VAL;

#line 548 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/GenericTypeDefs.h"

#line 550 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/GenericTypeDefs.h"
#line 110 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/./USB/usb.h"

#line 1 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"

#line 56 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
 

#line 59 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"


#line 62 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
	
#line 64 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 1 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"

#line 3 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"

#line 5 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 7 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 9 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 11 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 13 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 15 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 17 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 19 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 21 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 23 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 25 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 27 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 29 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 31 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 33 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 35 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 37 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 39 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 41 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 43 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 45 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 47 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 49 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 51 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 53 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 55 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 57 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 59 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 61 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 63 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 65 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 67 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 69 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 71 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 73 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 75 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 77 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 79 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 81 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 83 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 85 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 87 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 89 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 91 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 93 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 95 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 97 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 99 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 101 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 103 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 105 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 107 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 109 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 111 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 113 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 115 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 117 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 119 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 121 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 123 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 125 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 127 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 129 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 131 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 133 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 135 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 137 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 139 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 141 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 143 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 145 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 147 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 149 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 151 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 153 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 155 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 157 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 159 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 161 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 163 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 165 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 167 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 169 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 171 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 173 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 175 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 177 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 179 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 181 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 183 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 185 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 187 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 189 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 191 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 193 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 195 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 197 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 199 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 201 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 203 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 205 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 207 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 209 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 211 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 213 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 1 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18f4550.h"

#line 33 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18f4550.h"
 


#line 37 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18f4550.h"

extern volatile near unsigned char       SPPDATA;
extern volatile near unsigned char       SPPCFG;
extern volatile near union {
  struct {
    unsigned WS:4;
    unsigned CLK1EN:1;
    unsigned CSEN:1;
    unsigned CLKCFG:2;
  };
  struct {
    unsigned WS0:1;
    unsigned WS1:1;
    unsigned WS2:1;
    unsigned WS3:1;
    unsigned :2;
    unsigned CLKCFG0:1;
    unsigned CLKCFG1:1;
  };
} SPPCFGbits;
extern volatile near unsigned char       SPPEPS;
extern volatile near union {
  struct {
    unsigned ADDR:4;
    unsigned SPPBUSY:1;
    unsigned :1;
    unsigned WRSPP:1;
    unsigned RDSPP:1;
  };
  struct {
    unsigned ADDR0:1;
    unsigned ADDR1:1;
    unsigned ADDR2:1;
    unsigned ADDR3:1;
  };
} SPPEPSbits;
extern volatile near unsigned char       SPPCON;
extern volatile near struct {
  unsigned SPPEN:1;
  unsigned SPPOWN:1;
} SPPCONbits;
extern volatile near unsigned            UFRM;
extern volatile near unsigned char       UFRML;
extern volatile near union {
  struct {
    unsigned FRM:8;
  };
  struct {
    unsigned FRM0:1;
    unsigned FRM1:1;
    unsigned FRM2:1;
    unsigned FRM3:1;
    unsigned FRM4:1;
    unsigned FRM5:1;
    unsigned FRM6:1;
    unsigned FRM7:1;
  };
} UFRMLbits;
extern volatile near unsigned char       UFRMH;
extern volatile near union {
  struct {
    unsigned FRM:3;
  };
  struct {
    unsigned FRM8:1;
    unsigned FRM9:1;
    unsigned FRM10:1;
  };
} UFRMHbits;
extern volatile near unsigned char       UIR;
extern volatile near struct {
  unsigned URSTIF:1;
  unsigned UERRIF:1;
  unsigned ACTVIF:1;
  unsigned TRNIF:1;
  unsigned IDLEIF:1;
  unsigned STALLIF:1;
  unsigned SOFIF:1;
} UIRbits;
extern volatile near unsigned char       UIE;
extern volatile near struct {
  unsigned URSTIE:1;
  unsigned UERRIE:1;
  unsigned ACTVIE:1;
  unsigned TRNIE:1;
  unsigned IDLEIE:1;
  unsigned STALLIE:1;
  unsigned SOFIE:1;
} UIEbits;
extern volatile near unsigned char       UEIR;
extern volatile near struct {
  unsigned PIDEF:1;
  unsigned CRC5EF:1;
  unsigned CRC16EF:1;
  unsigned DFN8EF:1;
  unsigned BTOEF:1;
  unsigned :2;
  unsigned BTSEF:1;
} UEIRbits;
extern volatile near unsigned char       UEIE;
extern volatile near struct {
  unsigned PIDEE:1;
  unsigned CRC5EE:1;
  unsigned CRC16EE:1;
  unsigned DFN8EE:1;
  unsigned BTOEE:1;
  unsigned :2;
  unsigned BTSEE:1;
} UEIEbits;
extern volatile near unsigned char       USTAT;
extern volatile near union {
  struct {
    unsigned :1;
    unsigned PPBI:1;
    unsigned DIR:1;
    unsigned ENDP:4;
  };
  struct {
    unsigned :3;
    unsigned ENDP0:1;
    unsigned ENDP1:1;
    unsigned ENDP2:1;
    unsigned ENDP3:1;
  };
} USTATbits;
extern volatile near unsigned char       UCON;
extern volatile near struct {
  unsigned :1;
  unsigned SUSPND:1;
  unsigned RESUME:1;
  unsigned USBEN:1;
  unsigned PKTDIS:1;
  unsigned SE0:1;
  unsigned PPBRST:1;
} UCONbits;
extern volatile near unsigned char       UADDR;
extern volatile near union {
  struct {
    unsigned ADDR:7;
  };
  struct {
    unsigned ADDR0:1;
    unsigned ADDR1:1;
    unsigned ADDR2:1;
    unsigned ADDR3:1;
    unsigned ADDR4:1;
    unsigned ADDR5:1;
    unsigned ADDR6:1;
  };
} UADDRbits;
extern volatile near unsigned char       UCFG;
extern volatile near union {
  struct {
    unsigned PPB:2;
    unsigned FSEN:1;
    unsigned UTRDIS:1;
    unsigned UPUEN:1;
    unsigned :1;
    unsigned UOEMON:1;
    unsigned UTEYE:1;
  };
  struct {
    unsigned PPB0:1;
    unsigned PPB1:1;
  };
} UCFGbits;
extern volatile near unsigned char       UEP0;
extern volatile near struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP0bits;
extern volatile near unsigned char       UEP1;
extern volatile near struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP1bits;
extern volatile near unsigned char       UEP2;
extern volatile near struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP2bits;
extern volatile near unsigned char       UEP3;
extern volatile near struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP3bits;
extern volatile near unsigned char       UEP4;
extern volatile near struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP4bits;
extern volatile near unsigned char       UEP5;
extern volatile near struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP5bits;
extern volatile near unsigned char       UEP6;
extern volatile near struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP6bits;
extern volatile near unsigned char       UEP7;
extern volatile near struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP7bits;
extern volatile near unsigned char       UEP8;
extern volatile near struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP8bits;
extern volatile near unsigned char       UEP9;
extern volatile near struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP9bits;
extern volatile near unsigned char       UEP10;
extern volatile near struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP10bits;
extern volatile near unsigned char       UEP11;
extern volatile near struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP11bits;
extern volatile near unsigned char       UEP12;
extern volatile near struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP12bits;
extern volatile near unsigned char       UEP13;
extern volatile near struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP13bits;
extern volatile near unsigned char       UEP14;
extern volatile near struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP14bits;
extern volatile near unsigned char       UEP15;
extern volatile near struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP15bits;
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
  };
  struct {
    unsigned AN0:1;
    unsigned AN1:1;
    unsigned AN2:1;
    unsigned AN3:1;
    unsigned T0CKI:1;
    unsigned AN4:1;
    unsigned OSC2:1;
  };
  struct {
    unsigned :2;
    unsigned VREFM:1;
    unsigned VREFP:1;
    unsigned :1;
    unsigned LVDIN:1;
  };
  struct {
    unsigned :5;
    unsigned HLVDIN:1;
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
    unsigned :2;
    unsigned PGM:1;
    unsigned PGC:1;
    unsigned PGD:1;
  };
} PORTBbits;
extern volatile near unsigned char       PORTC;
extern volatile near union {
  struct {
    unsigned RC0:1;
    unsigned RC1:1;
    unsigned RC2:1;
    unsigned :1;
    unsigned RC4:1;
    unsigned RC5:1;
    unsigned RC6:1;
    unsigned RC7:1;
  };
  struct {
    unsigned T1OSO:1;
    unsigned T1OSI:1;
    unsigned CCP1:1;
    unsigned :3;
    unsigned TX:1;
    unsigned RX:1;
  };
  struct {
    unsigned T13CKI:1;
    unsigned :1;
    unsigned P1A:1;
    unsigned :3;
    unsigned CK:1;
    unsigned DT:1;
  };
} PORTCbits;
extern volatile near unsigned char       PORTD;
extern volatile near union {
  struct {
    unsigned RD0:1;
    unsigned RD1:1;
    unsigned RD2:1;
    unsigned RD3:1;
    unsigned RD4:1;
    unsigned RD5:1;
    unsigned RD6:1;
    unsigned RD7:1;
  };
  struct {
    unsigned SPP0:1;
    unsigned SPP1:1;
    unsigned SPP2:1;
    unsigned SPP3:1;
    unsigned SPP4:1;
    unsigned SPP5:1;
    unsigned SPP6:1;
    unsigned SPP7:1;
  };
} PORTDbits;
extern volatile near unsigned char       PORTE;
extern volatile near union {
  struct {
    unsigned RE0:1;
    unsigned RE1:1;
    unsigned RE2:1;
    unsigned RE3:1;
    unsigned :3;
    unsigned RDPU:1;
  };
  struct {
    unsigned CK1SPP:1;
    unsigned CK2SPP:1;
    unsigned OESPP:1;
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
  unsigned :3;
  unsigned LATC6:1;
  unsigned LATC7:1;
} LATCbits;
extern volatile near unsigned char       LATD;
extern volatile near struct {
  unsigned LATD0:1;
  unsigned LATD1:1;
  unsigned LATD2:1;
  unsigned LATD3:1;
  unsigned LATD4:1;
  unsigned LATD5:1;
  unsigned LATD6:1;
  unsigned LATD7:1;
} LATDbits;
extern volatile near unsigned char       LATE;
extern volatile near struct {
  unsigned LATE0:1;
  unsigned LATE1:1;
  unsigned LATE2:1;
} LATEbits;
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
  };
  struct {
    unsigned RA0:1;
    unsigned RA1:1;
    unsigned RA2:1;
    unsigned RA3:1;
    unsigned RA4:1;
    unsigned RA5:1;
    unsigned RA6:1;
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
  };
  struct {
    unsigned RA0:1;
    unsigned RA1:1;
    unsigned RA2:1;
    unsigned RA3:1;
    unsigned RA4:1;
    unsigned RA5:1;
    unsigned RA6:1;
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
    unsigned :3;
    unsigned TRISC6:1;
    unsigned TRISC7:1;
  };
  struct {
    unsigned RC0:1;
    unsigned RC1:1;
    unsigned RC2:1;
    unsigned :3;
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
    unsigned :3;
    unsigned TRISC6:1;
    unsigned TRISC7:1;
  };
  struct {
    unsigned RC0:1;
    unsigned RC1:1;
    unsigned RC2:1;
    unsigned :3;
    unsigned RC6:1;
    unsigned RC7:1;
  };
} TRISCbits;
extern volatile near unsigned char       DDRD;
extern volatile near union {
  struct {
    unsigned TRISD0:1;
    unsigned TRISD1:1;
    unsigned TRISD2:1;
    unsigned TRISD3:1;
    unsigned TRISD4:1;
    unsigned TRISD5:1;
    unsigned TRISD6:1;
    unsigned TRISD7:1;
  };
  struct {
    unsigned RD0:1;
    unsigned RD1:1;
    unsigned RD2:1;
    unsigned RD3:1;
    unsigned RD4:1;
    unsigned RD5:1;
    unsigned RD6:1;
    unsigned RD7:1;
  };
} DDRDbits;
extern volatile near unsigned char       TRISD;
extern volatile near union {
  struct {
    unsigned TRISD0:1;
    unsigned TRISD1:1;
    unsigned TRISD2:1;
    unsigned TRISD3:1;
    unsigned TRISD4:1;
    unsigned TRISD5:1;
    unsigned TRISD6:1;
    unsigned TRISD7:1;
  };
  struct {
    unsigned RD0:1;
    unsigned RD1:1;
    unsigned RD2:1;
    unsigned RD3:1;
    unsigned RD4:1;
    unsigned RD5:1;
    unsigned RD6:1;
    unsigned RD7:1;
  };
} TRISDbits;
extern volatile near unsigned char       DDRE;
extern volatile near union {
  struct {
    unsigned TRISE0:1;
    unsigned TRISE1:1;
    unsigned TRISE2:1;
  };
  struct {
    unsigned RE0:1;
    unsigned RE1:1;
    unsigned RE2:1;
  };
} DDREbits;
extern volatile near unsigned char       TRISE;
extern volatile near union {
  struct {
    unsigned TRISE0:1;
    unsigned TRISE1:1;
    unsigned TRISE2:1;
  };
  struct {
    unsigned RE0:1;
    unsigned RE1:1;
    unsigned RE2:1;
  };
} TRISEbits;
extern volatile near unsigned char       OSCTUNE;
extern volatile near union {
  struct {
    unsigned TUN:5;
    unsigned :2;
    unsigned INTSRC:1;
  };
  struct {
    unsigned TUN0:1;
    unsigned TUN1:1;
    unsigned TUN2:1;
    unsigned TUN3:1;
    unsigned TUN4:1;
  };
} OSCTUNEbits;
extern volatile near unsigned char       PIE1;
extern volatile near struct {
  unsigned TMR1IE:1;
  unsigned TMR2IE:1;
  unsigned CCP1IE:1;
  unsigned SSPIE:1;
  unsigned TXIE:1;
  unsigned RCIE:1;
  unsigned ADIE:1;
  unsigned SPPIE:1;
} PIE1bits;
extern volatile near unsigned char       PIR1;
extern volatile near struct {
  unsigned TMR1IF:1;
  unsigned TMR2IF:1;
  unsigned CCP1IF:1;
  unsigned SSPIF:1;
  unsigned TXIF:1;
  unsigned RCIF:1;
  unsigned ADIF:1;
  unsigned SPPIF:1;
} PIR1bits;
extern volatile near unsigned char       IPR1;
extern volatile near struct {
  unsigned TMR1IP:1;
  unsigned TMR2IP:1;
  unsigned CCP1IP:1;
  unsigned SSPIP:1;
  unsigned TXIP:1;
  unsigned RCIP:1;
  unsigned ADIP:1;
  unsigned SPPIP:1;
} IPR1bits;
extern volatile near unsigned char       PIE2;
extern volatile near union {
  struct {
    unsigned CCP2IE:1;
    unsigned TMR3IE:1;
    unsigned HLVDIE:1;
    unsigned BCLIE:1;
    unsigned EEIE:1;
    unsigned USBIE:1;
    unsigned CMIE:1;
    unsigned OSCFIE:1;
  };
  struct {
    unsigned :2;
    unsigned LVDIE:1;
  };
} PIE2bits;
extern volatile near unsigned char       PIR2;
extern volatile near union {
  struct {
    unsigned CCP2IF:1;
    unsigned TMR3IF:1;
    unsigned HLVDIF:1;
    unsigned BCLIF:1;
    unsigned EEIF:1;
    unsigned USBIF:1;
    unsigned CMIF:1;
    unsigned OSCFIF:1;
  };
  struct {
    unsigned :2;
    unsigned LVDIF:1;
  };
} PIR2bits;
extern volatile near unsigned char       IPR2;
extern volatile near union {
  struct {
    unsigned CCP2IP:1;
    unsigned TMR3IP:1;
    unsigned HLVDIP:1;
    unsigned BCLIP:1;
    unsigned EEIP:1;
    unsigned USBIP:1;
    unsigned CMIP:1;
    unsigned OSCFIP:1;
  };
  struct {
    unsigned :2;
    unsigned LVDIP:1;
  };
} IPR2bits;
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
extern volatile near unsigned char       TXREG;
extern volatile near unsigned char       RCREG;
extern volatile near unsigned char       SPBRG;
extern volatile near unsigned char       SPBRGH;
extern volatile near unsigned char       T3CON;
extern volatile near union {
  struct {
    unsigned TMR3ON:1;
    unsigned TMR3CS:1;
    unsigned NOT_T3SYNC:1;
    unsigned T3CCP1:1;
    unsigned T3CKPS:2;
    unsigned T3CCP2:1;
    unsigned RD16:1;
  };
  struct {
    unsigned :2;
    unsigned T3SYNC:1;
    unsigned :1;
    unsigned T3CKPS0:1;
    unsigned T3CKPS1:1;
  };
  struct {
    unsigned :2;
    unsigned T3NSYNC:1;
  };
} T3CONbits;
extern volatile near unsigned char       TMR3L;
extern volatile near unsigned char       TMR3H;
extern volatile near unsigned char       CMCON;
extern volatile near union {
  struct {
    unsigned CM:3;
    unsigned CIS:1;
    unsigned C1INV:1;
    unsigned C2INV:1;
    unsigned C1OUT:1;
    unsigned C2OUT:1;
  };
  struct {
    unsigned CM0:1;
    unsigned CM1:1;
    unsigned CM2:1;
  };
} CMCONbits;
extern volatile near unsigned char       CVRCON;
extern volatile near union {
  struct {
    unsigned CVR:4;
    unsigned CVRSS:1;
    unsigned CVRR:1;
    unsigned CVROE:1;
    unsigned CVREN:1;
  };
  struct {
    unsigned CVR0:1;
    unsigned CVR1:1;
    unsigned CVR2:1;
    unsigned CVR3:1;
    unsigned CVREF:1;
  };
} CVRCONbits;
extern volatile near unsigned char       CCP1AS;
extern volatile near union {
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
} CCP1ASbits;
extern volatile near unsigned char       ECCP1AS;
extern volatile near union {
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
extern volatile near unsigned char       CCP1DEL;
extern volatile near union {
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
} CCP1DELbits;
extern volatile near unsigned char       ECCP1DEL;
extern volatile near union {
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
} ECCP1DELbits;
extern volatile near unsigned char       BAUDCON;
extern volatile near union {
  struct {
    unsigned ABDEN:1;
    unsigned WUE:1;
    unsigned :1;
    unsigned BRG16:1;
    unsigned TXCKP:1;
    unsigned RXDTP:1;
    unsigned RCIDL:1;
    unsigned ABDOVF:1;
  };
  struct {
    unsigned :4;
    unsigned SCKP:1;
    unsigned :1;
    unsigned RCMT:1;
  };
} BAUDCONbits;
extern volatile near unsigned char       BAUDCTL;
extern volatile near union {
  struct {
    unsigned ABDEN:1;
    unsigned WUE:1;
    unsigned :1;
    unsigned BRG16:1;
    unsigned TXCKP:1;
    unsigned RXDTP:1;
    unsigned RCIDL:1;
    unsigned ABDOVF:1;
  };
  struct {
    unsigned :4;
    unsigned SCKP:1;
    unsigned :1;
    unsigned RCMT:1;
  };
} BAUDCTLbits;
extern volatile near unsigned char       CCP2CON;
extern volatile near union {
  struct {
    unsigned CCP2M:4;
    unsigned DC2B:2;
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
extern volatile near unsigned char       ECCP1CON;
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
} ECCP1CONbits;
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
    unsigned PCFG:4;
    unsigned VCFG:2;
  };
  struct {
    unsigned PCFG0:1;
    unsigned PCFG1:1;
    unsigned PCFG2:1;
    unsigned PCFG3:1;
    unsigned VCFG0:1;
    unsigned VCFG1:1;
  };
} ADCON1bits;
extern volatile near unsigned char       ADCON0;
extern volatile near union {
  struct {
    unsigned ADON:1;
    unsigned GO_NOT_DONE:1;
    unsigned CHS:4;
  };
  struct {
    unsigned :1;
    unsigned GO_DONE:1;
    unsigned CHS0:1;
    unsigned CHS1:1;
    unsigned CHS2:1;
    unsigned CHS3:1;
  };
  struct {
    unsigned :1;
    unsigned DONE:1;
  };
  struct {
    unsigned :1;
    unsigned GO:1;
  };
  struct {
    unsigned :1;
    unsigned NOT_DONE:1;
  };
} ADCON0bits;
extern volatile near unsigned            ADRES;
extern volatile near unsigned char       ADRESL;
extern volatile near unsigned char       ADRESH;
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
    unsigned R_W:1;
    unsigned :2;
    unsigned D_A:1;
  };
  struct {
    unsigned :2;
    unsigned I2C_READ:1;
    unsigned I2C_START:1;
    unsigned I2C_STOP:1;
    unsigned I2C_DAT:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_W:1;
    unsigned :2;
    unsigned NOT_A:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_WRITE:1;
    unsigned :2;
    unsigned NOT_ADDRESS:1;
  };
  struct {
    unsigned :2;
    unsigned READ_WRITE:1;
    unsigned :2;
    unsigned DATA_ADDRESS:1;
  };
  struct {
    unsigned :2;
    unsigned R:1;
    unsigned :2;
    unsigned D:1;
  };
} SSPSTATbits;
extern volatile near unsigned char       SSPADD;
extern volatile near unsigned char       SSPBUF;
extern volatile near unsigned char       T2CON;
extern volatile near union {
  struct {
    unsigned T2CKPS:2;
    unsigned TMR2ON:1;
    unsigned TOUTPS:4;
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
  struct {
    unsigned :3;
    unsigned TOUTPS0:1;
    unsigned TOUTPS1:1;
    unsigned TOUTPS2:1;
    unsigned TOUTPS3:1;
  };
} T2CONbits;
extern volatile near unsigned char       PR2;
extern volatile near unsigned char       TMR2;
extern volatile near unsigned char       T1CON;
extern volatile near union {
  struct {
    unsigned TMR1ON:1;
    unsigned TMR1CS:1;
    unsigned NOT_T1SYNC:1;
    unsigned T1OSCEN:1;
    unsigned T1CKPS:2;
    unsigned T1RUN:1;
    unsigned RD16:1;
  };
  struct {
    unsigned :2;
    unsigned T1SYNC:1;
    unsigned :1;
    unsigned T1CKPS0:1;
    unsigned T1CKPS1:1;
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
    unsigned :2;
    unsigned NOT_IPEN:1;
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
extern volatile near unsigned char       HLVDCON;
extern volatile near union {
  struct {
    unsigned HLVDL:4;
    unsigned HLVDEN:1;
    unsigned IRVST:1;
    unsigned :1;
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
    unsigned :1;
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
extern volatile near unsigned char       OSCCON;
extern volatile near union {
  struct {
    unsigned SCS:2;
    unsigned IOFS:1;
    unsigned OSTS:1;
    unsigned IRCF:3;
    unsigned IDLEN:1;
  };
  struct {
    unsigned SCS0:1;
    unsigned SCS1:1;
    unsigned FLTS:1;
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
    unsigned :2;
    unsigned T0IP:1;
    unsigned :4;
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
    unsigned STKPTR0:1;
    unsigned STKPTR1:1;
    unsigned STKPTR2:1;
    unsigned STKPTR3:1;
    unsigned STKPTR4:1;
  };
  struct {
    unsigned :7;
    unsigned STKOVF:1;
  };
} STKPTRbits;
extern          near unsigned short long TOS;
extern          near unsigned char       TOSL;
extern          near unsigned char       TOSH;
extern          near unsigned char       TOSU;



#line 1529 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18f4550.h"
 
#line 1531 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18f4550.h"
#line 1532 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18f4550.h"


#line 1535 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18f4550.h"
 
#line 1537 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18f4550.h"
#line 1538 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18f4550.h"
#line 1539 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18f4550.h"
#line 1540 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18f4550.h"

#line 1542 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18f4550.h"
#line 1543 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18f4550.h"
#line 1544 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18f4550.h"
#line 1545 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18f4550.h"
#line 1546 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18f4550.h"


#line 1550 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18f4550.h"
 
#line 1552 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18f4550.h"


#line 1555 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18f4550.h"
#line 213 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"

#line 215 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 217 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 219 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 221 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 223 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 225 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 227 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 229 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 231 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 233 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 235 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 237 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 239 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 241 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 243 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 245 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 247 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 249 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 251 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 253 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 255 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 257 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 259 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 261 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 263 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 265 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 267 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 269 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 271 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 273 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 275 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 277 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 279 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 281 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 283 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 285 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 287 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 289 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 291 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 293 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 295 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 297 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 299 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 301 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 303 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 305 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 307 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 309 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 311 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 313 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 315 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 317 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 319 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 321 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 323 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 325 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 327 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 329 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 331 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 333 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 335 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 337 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 339 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 341 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 343 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 345 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 347 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 349 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 351 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 353 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 355 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 357 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 359 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 361 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 363 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 365 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 367 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 369 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 371 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 373 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 375 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 377 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 379 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 381 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 383 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 385 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 387 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 389 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 391 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 393 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 395 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 397 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 399 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 401 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 403 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 405 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 407 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 409 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 411 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 413 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 415 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 417 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 419 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 421 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 423 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 425 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 427 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 429 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 431 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 433 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 435 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 437 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 439 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 441 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 443 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 445 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 447 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 449 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 451 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 453 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 455 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 457 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 459 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 461 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 463 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 465 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 467 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 469 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 471 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 473 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 475 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 477 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 479 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 481 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 483 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 485 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 487 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 489 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 491 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 493 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 495 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 497 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 499 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 501 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 503 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 505 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 507 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 509 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 511 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 513 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 515 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 517 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 519 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 521 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 523 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 525 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 527 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 529 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 531 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 533 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 535 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 537 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 539 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 541 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 543 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 545 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 547 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 549 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 551 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 553 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 555 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 557 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 559 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 561 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 563 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 565 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 567 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 569 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 571 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 573 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 575 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 577 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 579 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 581 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 583 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 585 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 587 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 589 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 591 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 593 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 595 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 597 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"

#line 599 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 64 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"

#line 66 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 68 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 70 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 73 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 77 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 81 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 85 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 89 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 93 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 97 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 101 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 106 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 111 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 112 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 113 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 115 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 119 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 121 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"

#line 1 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdio.h"

#line 3 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdio.h"

#line 1 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdarg.h"
 


#line 5 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdarg.h"

typedef void* va_list;
#line 8 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdarg.h"
#line 9 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdarg.h"
#line 10 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdarg.h"
#line 11 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdarg.h"
#line 12 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdarg.h"
#line 4 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdio.h"

#line 1 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stddef.h"
 

#line 10 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stddef.h"

#line 20 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stddef.h"

#line 34 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stddef.h"

#line 41 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stddef.h"
#line 45 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stddef.h"
#line 5 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdio.h"



#line 9 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdio.h"
 
#line 11 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdio.h"

#line 13 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdio.h"


typedef unsigned char FILE;

 
#line 19 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdio.h"
#line 20 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdio.h"

extern FILE *stderr;
extern FILE *stdout;


int putc (auto char c, auto FILE *f);
int vsprintf (auto char *buf, auto const far  rom char *fmt, auto va_list ap);
int vprintf (auto const far  rom char *fmt, auto va_list ap);
int sprintf (auto char *buf, auto const far  rom char *fmt, ...);
int printf (auto const far  rom char *fmt, ...);
int fprintf (auto FILE *f, auto const far  rom char *fmt, ...);
int vfprintf (auto FILE *f, auto const far  rom char *fmt, auto va_list ap);
int puts (auto const far  rom char *s);
int fputs (auto const far  rom char *s, auto FILE *f);

#line 36 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdio.h"
#line 122 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"

#line 1 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdlib.h"
 

#line 4 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdlib.h"

#line 6 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdlib.h"

#line 9 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdlib.h"
 
 

#line 16 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdlib.h"
 
double atof (const auto char *s);

#line 28 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdlib.h"
 
signed char atob (const auto char *s);


#line 39 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdlib.h"
 
int atoi (const auto char *s);

#line 47 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdlib.h"
 
long atol (const auto char *s);

#line 58 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdlib.h"
 
unsigned long atoul (const auto char *s);


#line 71 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdlib.h"
 
char *btoa (auto signed char value, auto char *s);

#line 83 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdlib.h"
 
char *itoa (auto int value, auto char *s);

#line 95 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdlib.h"
 
char *ltoa (auto long value, auto char *s);

#line 107 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdlib.h"
 
char *ultoa (auto unsigned long value, auto char *s);
 


#line 112 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdlib.h"
 
 

#line 116 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdlib.h"
 
#line 118 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdlib.h"


#line 124 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdlib.h"
 
int rand (void);

#line 136 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdlib.h"
 
void srand (auto unsigned int seed);
 
#line 140 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdlib.h"
#line 149 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdlib.h"

#line 151 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/stdlib.h"
#line 123 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"

#line 1 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"

#line 3 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"

#line 7 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"


#line 20 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
#line 22 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"


#line 25 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
#line 27 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"

 

#line 39 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
void *memcpy (auto void *s1, auto const void *s2, auto size_t n);


#line 55 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
void *memmove (auto void *s1, auto const void *s2, auto size_t n);


#line 67 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
char *strcpy (auto char *s1, auto const char *s2);


#line 83 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
char *strncpy (auto char *s1, auto const char *s2, auto size_t n);


#line 97 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
char *strcat (auto char *s1, auto const char *s2);


#line 113 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
char *strncat (auto char *s1, auto const char *s2, auto size_t n);


#line 128 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
signed char memcmp (auto const void *s1, auto const void *s2, auto size_t n);


#line 141 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
signed char strcmp (auto const char *s1, auto const char *s2);


#line 147 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 


#line 161 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
signed char strncmp (auto const char *s1, auto const char *s2, auto size_t n);


#line 167 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 


#line 183 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
void *memchr (auto const void *s, auto unsigned char c, auto size_t n);


#line 199 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
char *strchr (auto const char *s, auto unsigned char c);


#line 210 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
size_t strcspn (auto const char *s1, auto const char *s2);


#line 222 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
char *strpbrk (auto const char *s1, auto const char *s2);


#line 238 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
char *strrchr (auto const char *s, auto unsigned char c);


#line 249 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
size_t strspn (auto const char *s1, auto const char *s2);


#line 262 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
char *strstr (auto const char *s1, auto const char *s2);


#line 305 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
char *strtok (auto char *s1, auto const char *s2);


#line 321 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
void *memset (auto void *s, auto unsigned char c, auto size_t n);


#line 339 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
#line 341 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"


#line 349 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
size_t strlen (auto const char *s);


#line 358 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
char *strupr (auto char *s);


#line 367 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
char *strlwr (auto char *s);



 

#line 379 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
far  rom void *memcpypgm (auto far  rom void *s1, auto const far  rom void *s2, auto sizerom_t n);


#line 389 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
void *memcpypgm2ram (auto void *s1, auto const far  rom void *s2, auto sizeram_t n);


#line 398 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
far  rom void *memcpyram2pgm (auto far  rom void *s1, auto const void *s2, auto sizeram_t n);


#line 407 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
far  rom void *memmovepgm (auto far  rom void *s1, auto const far  rom void *s2, auto sizerom_t n);


#line 417 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
void *memmovepgm2ram (auto void *s1, auto const far  rom void *s2, auto sizeram_t n);


#line 426 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
far  rom void *memmoveram2pgm (auto far  rom void *s1, auto const void *s2, auto sizeram_t n);


#line 434 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
far  rom char *strcpypgm (auto far  rom char *s1, auto const far  rom char *s2);


#line 443 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
char *strcpypgm2ram (auto char *s1, auto const far  rom char *s2);


#line 451 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
far  rom char *strcpyram2pgm (auto far  rom char *s1, auto const char *s2);


#line 460 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
far  rom char *strncpypgm (auto far  rom char *s1, auto const far  rom char *s2, auto sizerom_t n);


#line 470 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
char *strncpypgm2ram (auto char *s1, auto const far  rom char *s2, auto sizeram_t n);


#line 479 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
far  rom char *strncpyram2pgm (auto far  rom char *s1, auto const char *s2, auto sizeram_t n);


#line 487 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
far  rom char *strcatpgm (auto far  rom char *s1, auto const far  rom char *s2);


#line 496 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
char *strcatpgm2ram (auto char *s1, auto const far  rom char *s2);


#line 504 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
far  rom char *strcatram2pgm (auto far  rom char *s1, auto const char *s2);


#line 513 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
far  rom char *strncatpgm (auto far  rom char *s1, auto const far  rom char *s2, auto sizerom_t n);


#line 523 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
char *strncatpgm2ram (auto char *s1, auto const far  rom char *s2, auto sizeram_t n);


#line 532 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
far  rom char *strncatram2pgm (auto far  rom char *s1, auto const char *s2, auto sizeram_t n);


#line 541 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
signed char memcmppgm (auto far  rom void *s1, auto const far  rom void *s2, auto sizerom_t n);


#line 551 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
signed char memcmppgm2ram (auto void *s1, auto const far  rom void *s2, auto sizeram_t n);


#line 560 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
signed char memcmpram2pgm (auto far  rom void *s1, auto const void *s2, auto sizeram_t n);


#line 568 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
signed char strcmppgm (auto const far  rom char *s1, auto const far  rom char *s2);


#line 577 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
signed char strcmppgm2ram (auto const char *s1, auto const far  rom char *s2);


#line 585 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
signed char strcmpram2pgm (auto const far  rom char *s1, auto const char *s2);


#line 594 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
signed char strncmppgm (auto const far  rom char *s1, auto const far  rom char *s2, auto sizerom_t n);


#line 604 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
signed char strncmppgm2ram (auto char *s1, auto const far  rom char *s2, auto sizeram_t n);


#line 613 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
signed char strncmpram2pgm (auto far  rom char *s1, auto const char *s2, auto sizeram_t n);


#line 622 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
far  rom char *memchrpgm (auto const far  rom char *s, auto const unsigned char c, auto sizerom_t n);


#line 631 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
far  rom char *strchrpgm (auto const far  rom char *s, auto unsigned char c);


#line 639 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
sizerom_t strcspnpgm (auto const far  rom char *s1, auto const far  rom char *s2);


#line 647 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
sizerom_t strcspnpgmram (auto const far  rom char *s1, auto const char *s2);


#line 655 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
sizeram_t strcspnrampgm (auto const char *s1, auto const far  rom char *s2);


#line 663 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
far  rom char *strpbrkpgm (auto const far  rom char *s1, auto const far  rom char *s2);


#line 671 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
far  rom char *strpbrkpgmram (auto const far  rom char *s1, auto const char *s2);


#line 679 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
char *strpbrkrampgm (auto const char *s1, auto const far  rom char *s2);


#line 688 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
 


#line 696 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
sizerom_t strspnpgm (auto const far  rom char *s1, auto const far  rom char *s2);


#line 704 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
sizerom_t strspnpgmram (auto const far  rom char *s1, auto const char *s2);


#line 712 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
sizeram_t strspnrampgm (auto const char *s1, auto const far  rom char *s2);


#line 720 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
far  rom char *strstrpgm (auto const far  rom char *s1, auto const far  rom char *s2);


#line 729 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
far  rom char *strstrpgmram (auto const far  rom char *s1, auto const char *s2);


#line 737 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
char *strstrrampgm (auto const char *s1, auto const far  rom char *s2);


#line 745 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
far  rom char *strtokpgm (auto far  rom char *s1, auto const far  rom char *s2);


#line 754 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
char *strtokpgmram (auto char *s1, auto const far  rom char *s2);


#line 762 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
far  rom char *strtokrampgm (auto far  rom char *s1, auto const char *s2);


#line 771 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
far  rom void *memsetpgm (auto far  rom void *s, auto unsigned char c, auto sizerom_t n);


#line 778 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
far  rom char *struprpgm (auto far  rom char *s);


#line 785 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
far  rom char *strlwrpgm (auto far  rom char *s);


#line 792 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
 
sizerom_t strlenpgm (auto const far  rom char *s);

#line 796 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"

#line 798 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"

#line 805 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
#line 814 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"

#line 816 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/string.h"
#line 124 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"




#line 129 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 132 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 135 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 136 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 137 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 138 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 141 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"



#line 145 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 155 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"




#line 160 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 161 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"

#line 163 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"

	
#line 166 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 167 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 168 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
	
	
#line 171 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 176 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 179 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 182 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 185 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 186 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
    


#line 190 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 194 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 197 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 200 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 201 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 203 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 211 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 213 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 214 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 215 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"



#line 219 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 111 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/./USB/usb.h"


#line 1 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/usb_config.h"

#line 43 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/usb_config.h"
 


#line 47 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/usb_config.h"
 


#line 51 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/usb_config.h"

 
#line 54 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/usb_config.h"
								
								
								
								
								
									
#line 61 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/usb_config.h"
#line 62 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/usb_config.h"




#line 67 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/usb_config.h"
#line 68 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/usb_config.h"



#line 72 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/usb_config.h"
#line 73 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/usb_config.h"




#line 78 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/usb_config.h"





#line 84 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/usb_config.h"

 
#line 87 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/usb_config.h"


#line 90 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/usb_config.h"





#line 96 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/usb_config.h"























#line 120 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/usb_config.h"















#line 136 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/usb_config.h"
                                                
                                                



#line 142 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/usb_config.h"

#line 144 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/usb_config.h"

 
#line 147 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/usb_config.h"

 
#line 150 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/usb_config.h"

 

#line 154 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/usb_config.h"
#line 113 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/./USB/usb.h"
             

#line 1 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"

#line 36 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
 


#line 66 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
 




#line 77 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
 





#line 84 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"


#line 1 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/limits.h"

#line 9 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/limits.h"
 


#line 13 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/limits.h"

#line 15 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/limits.h"
#line 16 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/limits.h"

#line 18 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/limits.h"
#line 19 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/limits.h"
#line 20 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/limits.h"

 
#line 23 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/limits.h"
#line 26 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/limits.h"
#line 27 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/limits.h"
#line 28 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/limits.h"
#line 29 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/limits.h"

#line 31 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/limits.h"
#line 32 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/limits.h"
#line 33 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/limits.h"

#line 35 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/limits.h"
#line 36 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/limits.h"
#line 37 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/limits.h"

#line 39 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/limits.h"
#line 40 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/limits.h"
#line 41 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/limits.h"

 
#line 44 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/limits.h"
#line 45 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/limits.h"
#line 46 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/limits.h"

 
#line 49 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/limits.h"
#line 50 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/limits.h"

#line 52 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/limits.h"











#line 86 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"










#line 97 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 98 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 99 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 100 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 101 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 102 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 103 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 104 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 105 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 106 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 107 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 108 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 109 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 110 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 111 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"

#line 113 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 114 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 115 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 116 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 117 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 118 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 119 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 120 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 121 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 122 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 123 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 124 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"



#line 128 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 129 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 130 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 131 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 132 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 133 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 134 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 135 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 136 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 137 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 138 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 139 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"

#line 141 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"

#line 143 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"










#line 168 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
 

typedef union
{
    BYTE    bitmap;
    struct
    {
        BYTE ep_num:    4;
        BYTE zero_pkt:  1;
        BYTE dts:       1;
        BYTE force_dts: 1;
        BYTE direction: 1;
    }field;

} TRANSFER_FLAGS;



#line 189 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
 
#line 191 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 192 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 193 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 194 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 195 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 196 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 197 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 198 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 199 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 200 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 201 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 202 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 203 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 204 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 205 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 206 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"



#line 212 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
 
#line 214 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 215 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 216 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 217 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 218 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 219 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 220 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 221 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 222 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 223 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 224 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"



#line 231 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
 
#line 233 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"




#line 242 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
 

typedef enum
{
    
    EVENT_NONE = 0,

    EVENT_DEVICE_STACK_BASE = 1,

    EVENT_HOST_STACK_BASE = 100,

    
    EVENT_HUB_ATTACH,           
    
    
    EVENT_STALL,                  
    
    
    EVENT_VBUS_SES_REQUEST,     
    
    
    
    
    EVENT_VBUS_OVERCURRENT,     
    
    
    
    
    
    EVENT_VBUS_REQUEST_POWER,   
    
    
    
    
    EVENT_VBUS_RELEASE_POWER,   
    
    
    
    
    
    
    
    
    EVENT_VBUS_POWER_AVAILABLE, 
    
    
    
    EVENT_UNSUPPORTED_DEVICE,   
    
    
    
    EVENT_CANNOT_ENUMERATE,     
    
    
    
    EVENT_CLIENT_INIT_ERROR,    
    
    
    
    
    
    EVENT_OUT_OF_MEMORY,        
    
    
    EVENT_UNSPECIFIED_ERROR,     
             
    
    
    EVENT_DETACH, 
     
    
    
    
    EVENT_TRANSFER,
    
    
    
    EVENT_SOF,                  
    
    
    EVENT_RESUME,
    
    
    
    EVENT_SUSPEND,
                  
    
    
    EVENT_RESET,  
    
    
    
    
    
    EVENT_DATA_ISOC_READ,
    
    
    
    
    
    EVENT_DATA_ISOC_WRITE,
    
    
    
    
    
    
    
    
    
    EVENT_OVERRIDE_CLIENT_DRIVER_SELECTION,

    
    
    
    
    
    
    EVENT_1MS,

    
    EVENT_GENERIC_BASE  = 400,      

    EVENT_MSD_BASE      = 500,      

    EVENT_HID_BASE      = 600,      

    EVENT_PRINTER_BASE  = 700,      
    
    EVENT_CDC_BASE      = 800,      

    EVENT_CHARGER_BASE  = 900,      

    EVENT_AUDIO_BASE    = 1000,      
        
	EVENT_USER_BASE     = 10000,    
                                    

    
    
    EVENT_BUS_ERROR     = 32767    

} USB_EVENT;




#line 394 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
 

typedef struct _transfer_event_data
{
    TRANSFER_FLAGS  flags;          
    UINT32          size;           
    BYTE            pid;            

} USB_TRANSFER_EVENT_DATA;




#line 411 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
 

typedef struct _vbus_power_data
{
    BYTE            port;           
    BYTE            current;        
} USB_VBUS_POWER_EVENT_DATA;




#line 425 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
 
typedef struct _override_client_driver_data
{        
    WORD idVendor;              
    WORD idProduct;             
    BYTE bDeviceClass;          
    BYTE bDeviceSubClass;       
    BYTE bDeviceProtocol;       
} USB_OVERRIDE_CLIENT_DRIVER_EVENT_DATA;




#line 442 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
 









#line 486 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
 

typedef BOOL (*USB_EVENT_HANDLER) ( USB_EVENT event, void *data, unsigned int size );









#line 521 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
 

   
#line 525 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 526 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 527 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 529 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"

#line 531 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 533 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 534 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 535 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 536 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 537 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 538 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 540 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 542 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 543 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 544 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"



#line 570 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
 

    
#line 574 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 575 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 576 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 578 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 580 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 581 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 582 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 583 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 584 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 585 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 587 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 589 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 590 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 591 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"

#line 593 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 594 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 595 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
#line 596 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"

#line 598 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"

#line 600 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_common.h"
 

#line 115 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/./USB/usb.h"
         
#line 1 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"

#line 39 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
 


#line 72 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
 




#line 82 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
 




#line 88 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"









#line 98 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 99 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 100 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 101 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 102 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 103 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 104 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 105 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 106 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"



#line 113 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
 
typedef struct   _USB_DEVICE_DESCRIPTOR
{
    BYTE bLength;               
    BYTE bDescriptorType;       
    WORD bcdUSB;                
    BYTE bDeviceClass;          
    BYTE bDeviceSubClass;       
    BYTE bDeviceProtocol;       
    BYTE bMaxPacketSize0;       
    WORD idVendor;              
    WORD idProduct;             
    WORD bcdDevice;             
    BYTE iManufacturer;         
    BYTE iProduct;              
    BYTE iSerialNumber;         
    BYTE bNumConfigurations;    
} USB_DEVICE_DESCRIPTOR;




#line 139 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
 
typedef struct   _USB_CONFIGURATION_DESCRIPTOR
{
    BYTE bLength;               
    BYTE bDescriptorType;       
    WORD wTotalLength;          
    BYTE bNumInterfaces;        
    BYTE bConfigurationValue;   
    BYTE iConfiguration;        
    BYTE bmAttributes;          
    BYTE bMaxPower;             
} USB_CONFIGURATION_DESCRIPTOR;


#line 154 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 155 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 156 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"




#line 164 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
 
typedef struct   _USB_INTERFACE_DESCRIPTOR
{
    BYTE bLength;               
    BYTE bDescriptorType;       
    BYTE bInterfaceNumber;      
    BYTE bAlternateSetting;     
    BYTE bNumEndpoints;         
    BYTE bInterfaceClass;       
    BYTE bInterfaceSubClass;    
    BYTE bInterfaceProtocol;    
    BYTE iInterface;            
} USB_INTERFACE_DESCRIPTOR;




#line 185 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
 
typedef struct   _USB_ENDPOINT_DESCRIPTOR
{
    BYTE bLength;               
    BYTE bDescriptorType;       
    BYTE bEndpointAddress;      
    BYTE bmAttributes;          
    WORD wMaxPacketSize;        
    BYTE bInterval;             
} USB_ENDPOINT_DESCRIPTOR;



#line 199 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 200 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"







#line 208 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 209 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 210 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 211 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"


#line 214 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 215 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 216 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 217 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"


#line 220 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 221 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 222 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"


#line 225 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 226 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 227 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 228 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 229 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 230 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 231 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"


#line 235 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
 
typedef struct
{
    BYTE    index;
    BYTE    type;
    UINT16  language_id;

} DESCRIPTOR_ID;



#line 250 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
 
typedef struct   _USB_OTG_DESCRIPTOR
{
    BYTE bLength;               
    BYTE bDescriptorType;       
    BYTE bmAttributes;          
} USB_OTG_DESCRIPTOR;


















typedef struct   _USB_STRING_DSC
{
    BYTE   bLength;             
    BYTE   bDescriptorType;     

} USB_STRING_DESCRIPTOR;













typedef struct   _USB_DEVICE_QUALIFIER_DESCRIPTOR
{
    BYTE bLength;               
    BYTE bType;                 
    WORD bcdUSB;                
    BYTE bDeviceClass;          
    BYTE bDeviceSubClass;       
    BYTE bDeviceProtocol;       
    BYTE bMaxPacketSize0;       
    BYTE bNumConfigurations;    
    BYTE bReserved;             

} USB_DEVICE_QUALIFIER_DESCRIPTOR;










typedef union  
{
     
    struct  
    {
        BYTE bmRequestType; 
        BYTE bRequest; 
        WORD wValue; 
        WORD wIndex; 
        WORD wLength; 
    };
    struct  
    {
        unsigned :8;
        unsigned :8;
        WORD_VAL W_Value; 
        WORD_VAL W_Index; 
        WORD_VAL W_Length; 
    };
    struct  
    {
        unsigned Recipient:5;   
        unsigned RequestType:2; 
        unsigned DataDir:1;     
        unsigned :8;
        BYTE bFeature;          
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;
    };
    struct  
    {
        union                           
        {                               
            BYTE bmRequestType;         
            struct
            {
                BYTE    recipient:  5;  
                BYTE    type:       2;  
                BYTE    direction:  1;  
            };
        }requestInfo;
    };
    struct  
    {
        unsigned :8;
        unsigned :8;
        BYTE bDscIndex;         
        BYTE bDescriptorType;          
        WORD wLangID;           
        unsigned :8;
        unsigned :8;
    };
    struct  
    {
        unsigned :8;
        unsigned :8;
        BYTE_VAL bDevADR;       
        BYTE bDevADRH;          
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;
    };
    struct  
    {
        unsigned :8;
        unsigned :8;
        BYTE bConfigurationValue;         
        BYTE bCfgRSD;           
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;
    };
    struct  
    {
        unsigned :8;
        unsigned :8;
        BYTE bAltID;            
        BYTE bAltID_H;          
        BYTE bIntfID;           
        BYTE bIntfID_H;         
        unsigned :8;
        unsigned :8;
    };
    struct  
    {
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;
        BYTE bEPID;             
        BYTE bEPID_H;           
        unsigned :8;
        unsigned :8;
    };
    struct  
    {
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned EPNum:4;       
        unsigned :3;
        unsigned EPDir:1;       
        unsigned :8;
        unsigned :8;
        unsigned :8;
    };

     

} CTRL_TRF_SETUP, SETUP_PKT, *PSETUP_PKT;










#line 444 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 445 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 446 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 447 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 448 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 449 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 450 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 451 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 452 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 453 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 454 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 455 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 456 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 457 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 458 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 459 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"

#line 461 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 462 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"




#line 467 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 468 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 469 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"




#line 474 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 475 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"



#line 479 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 480 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"



#line 484 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 485 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 486 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 487 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 488 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 489 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 490 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 491 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 492 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 493 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 494 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"

#line 496 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 497 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 498 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"



#line 502 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 503 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 504 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 505 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 506 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 507 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 508 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 509 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 510 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"

#line 512 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 513 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 514 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 515 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 516 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 517 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 518 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 519 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 520 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"



#line 524 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 525 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 526 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"



#line 530 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 531 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 532 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 533 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"


#line 536 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 537 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 538 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"



#line 542 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"


#line 547 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
 
#line 549 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 550 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 551 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 552 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 553 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 554 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 555 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 556 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 557 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 558 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 559 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 560 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 561 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 562 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 563 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 564 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 565 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 566 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 567 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 568 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 569 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 570 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 571 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 572 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 573 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 574 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 575 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 576 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 577 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 578 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 579 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 580 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"

 
#line 583 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 584 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 585 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 586 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 587 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"

 
#line 590 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 591 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 592 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"

#line 594 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 595 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 596 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 597 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"

 
#line 600 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 601 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 602 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 603 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"

 
#line 606 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 607 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 608 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"



#line 612 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
#line 613 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"

#line 615 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"

#line 617 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_ch9.h"
 

#line 116 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/./USB/usb.h"
            

#line 119 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/./USB/usb.h"
#line 1 "USB/usb_device.h"

#line 42 "USB/usb_device.h"
 


#line 74 "USB/usb_device.h"
 


#line 101 "USB/usb_device.h"
 


#line 105 "USB/usb_device.h"


 





#line 114 "USB/usb_device.h"

#line 116 "USB/usb_device.h"
#line 117 "USB/usb_device.h"
#line 118 "USB/usb_device.h"
#line 119 "USB/usb_device.h"
#line 120 "USB/usb_device.h"
#line 121 "USB/usb_device.h"


#line 125 "USB/usb_device.h"
 


#line 129 "USB/usb_device.h"
 
typedef enum
{
    
#line 134 "USB/usb_device.h"
 
    DETACHED_STATE 
         = 0x00                          ,
    
#line 138 "USB/usb_device.h"
 
    ATTACHED_STATE
         = 0x01                          ,
    
#line 142 "USB/usb_device.h"
 
    POWERED_STATE
         = 0x02                          ,
    
#line 146 "USB/usb_device.h"
 
    DEFAULT_STATE
         = 0x04                          ,
    
#line 153 "USB/usb_device.h"
 
    ADR_PENDING_STATE
         = 0x08                          ,
    
#line 157 "USB/usb_device.h"
 
    ADDRESS_STATE
         = 0x10                          ,
    
#line 164 "USB/usb_device.h"
 
    CONFIGURED_STATE
         = 0x20                         
} USB_DEVICE_STATE;


 
typedef enum
{
    
    EVENT_CONFIGURED
         = EVENT_DEVICE_STACK_BASE         ,

    
    EVENT_SET_DESCRIPTOR,

    
    
    
    
    EVENT_EP0_REQUEST,




















    




    
    
    
    EVENT_ATTACH,

    
    
    
    EVENT_TRANSFER_TERMINATED

} USB_DEVICE_STACK_EVENTS;

 


 
 
 


#line 251 "USB/usb_device.h"
 
void USBDeviceInit(void);


#line 356 "USB/usb_device.h"
 
void USBDeviceTasks(void);



#line 408 "USB/usb_device.h"
 
void USBEnableEndpoint(BYTE ep, BYTE options);



#line 501 "USB/usb_device.h"
 
void*  USBTransferOnePacket(BYTE ep,BYTE dir,BYTE* data,BYTE len);


#line 526 "USB/usb_device.h"
 
void USBStallEndpoint(BYTE ep, BYTE dir);

#line 550 "USB/usb_device.h"
 
void USBCancelIO(BYTE endpoint);


#line 647 "USB/usb_device.h"
 
void USBDeviceDetach(void);

 
#line 652 "USB/usb_device.h"
#line 654 "USB/usb_device.h"
 


#line 692 "USB/usb_device.h"
 
void USBDeviceAttach(void);

 
#line 697 "USB/usb_device.h"
#line 699 "USB/usb_device.h"
 



#line 731 "USB/usb_device.h"
 
void USBCtrlEPAllowStatusStage(void);




#line 761 "USB/usb_device.h"
 
void USBCtrlEPAllowDataStage(void);



#line 837 "USB/usb_device.h"
 
void USBDeferOUTDataStage(void);
extern volatile BOOL USBDeferOUTDataStagePackets;
 
#line 842 "USB/usb_device.h"
 


#line 907 "USB/usb_device.h"
 
void USBDeferStatusStage(void);
extern volatile BOOL USBDeferStatusStagePacket;
 
#line 912 "USB/usb_device.h"
 



#line 959 "USB/usb_device.h"
 
BOOL USBOUTDataStageDeferred(void);
 
#line 963 "USB/usb_device.h"
 


#line 1042 "USB/usb_device.h"
 
void USBDeferINDataStage(void);
extern volatile BOOL USBDeferINDataStagePackets;
 
#line 1047 "USB/usb_device.h"
 




#line 1096 "USB/usb_device.h"
 
BOOL USBINDataStageDeferred(void);
 
#line 1100 "USB/usb_device.h"
 




#line 1166 "USB/usb_device.h"
 
BOOL USBGetRemoteWakeupStatus(void);
 
#line 1170 "USB/usb_device.h"
 


#line 1223 "USB/usb_device.h"
 
USB_DEVICE_STATE USBGetDeviceState(void);
 
#line 1227 "USB/usb_device.h"
 




#line 1279 "USB/usb_device.h"
 
BOOL USBGetSuspendState(void);
 
#line 1283 "USB/usb_device.h"
 


#line 1314 "USB/usb_device.h"
 
BOOL USBIsDeviceSuspended(void);
 
#line 1318 "USB/usb_device.h"
 



#line 1357 "USB/usb_device.h"
 
BOOL USBIsBusSuspended(void);
 
#line 1361 "USB/usb_device.h"
 


#line 1383 "USB/usb_device.h"
 
void USBSoftDetach(void);
 
#line 1387 "USB/usb_device.h"
 



#line 1421 "USB/usb_device.h"
 
BOOL USBHandleBusy(void*  handle);
 
#line 1425 "USB/usb_device.h"
 


#line 1455 "USB/usb_device.h"
 
WORD USBHandleGetLength(void*  handle);
 
#line 1459 "USB/usb_device.h"
 


#line 1487 "USB/usb_device.h"
 
WORD USBHandleGetAddr(void* );
 
#line 1491 "USB/usb_device.h"
 



#line 1587 "USB/usb_device.h"
 
void*  USBGetNextHandle(BYTE ep_num, BYTE ep_dir);
 
#line 1591 "USB/usb_device.h"
 


#line 1620 "USB/usb_device.h"
 
void USBEP0Transmit(BYTE options);
 
#line 1624 "USB/usb_device.h"
 


#line 1648 "USB/usb_device.h"
 
void USBEP0SendRAMPtr(BYTE* src, WORD size, BYTE Options);
 

#line 1655 "USB/usb_device.h"
#line 1656 "USB/usb_device.h"
 


#line 1680 "USB/usb_device.h"
 
void USBEP0SendROMPtr(BYTE* src, WORD size, BYTE Options);
 

#line 1687 "USB/usb_device.h"
#line 1688 "USB/usb_device.h"
 


#line 1708 "USB/usb_device.h"
 
void USBEP0Receive(BYTE* dest, WORD size, void (*function));
 
#line 1712 "USB/usb_device.h"
 


#line 1743 "USB/usb_device.h"
 
void*  USBTxOnePacket(BYTE ep, BYTE* data, WORD len);
 
#line 1747 "USB/usb_device.h"
 


#line 1780 "USB/usb_device.h"
 
void*  USBRxOnePacket(BYTE ep, BYTE* data, WORD len);
 
#line 1784 "USB/usb_device.h"
 


#line 1812 "USB/usb_device.h"
 
BOOL USB_APPLICATION_EVENT_HANDLER(BYTE address, USB_EVENT event, void *pdata, WORD size);


#line 1844 "USB/usb_device.h"
 
void *USBDeviceCBGetDescriptor (    UINT16 *length, 
                                    UINT8 *ptr_type,
                                    DESCRIPTOR_ID *id);



 


#line 1864 "USB/usb_device.h"
 
#line 1866 "USB/usb_device.h"


#line 1871 "USB/usb_device.h"
 
#line 1873 "USB/usb_device.h"


#line 1878 "USB/usb_device.h"
 
#line 1880 "USB/usb_device.h"
















 

#line 1905 "USB/usb_device.h"
 

#line 1908 "USB/usb_device.h"
#line 1910 "USB/usb_device.h"
#line 1911 "USB/usb_device.h"
#line 1912 "USB/usb_device.h"

#line 1914 "USB/usb_device.h"
#line 1915 "USB/usb_device.h"




typedef struct  
{
    union  
    {
        
        
        BYTE *bRam;
        rom  BYTE *bRom;
        WORD *wRam;
        rom  WORD *wRom;
    }pSrc;
    union  
    {
        struct  
        {
            
            BYTE ctrl_trf_mem          :1;
            BYTE reserved              :5;
            
            
            BYTE includeZero           :1;
            
            BYTE busy                  :1;
        }bits;
        BYTE Val;
    }info;
    WORD_VAL   wCount;
}IN_PIPE;

extern volatile  IN_PIPE inPipes[];

typedef struct  
{
    union  
    {
        
        
        BYTE *bRam;
        WORD *wRam;
    }pDst;
    union  
    {
        struct  
        {
            BYTE reserved              :7;
            
            BYTE busy                  :1;
        }bits;
        BYTE Val;
    }info;
    WORD_VAL wCount;
    void  (*pFunc)(void );
}OUT_PIPE;

 







extern volatile  BOOL RemoteWakeup;
extern volatile  BOOL USBBusIsSuspended;
extern volatile  USB_DEVICE_STATE USBDeviceState;
extern volatile  BYTE USBActiveConfiguration;
 
 

#line 1989 "USB/usb_device.h"
#line 119 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/./USB/usb.h"
     
#line 121 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/./USB/usb.h"

#line 123 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/./USB/usb.h"
#line 125 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/./USB/usb.h"

#line 127 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/./USB/usb.h"
#line 129 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/./USB/usb.h"

#line 1 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"

#line 34 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
 


#line 74 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
 


#line 87 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
 


#line 91 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"


#line 94 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 1 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"

#line 49 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
 


#line 85 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
 



#line 108 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
 



#line 113 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"

 
 
 

#line 1 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"

#line 56 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
 
#line 62 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 66 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 68 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 70 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 73 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 77 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 81 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 85 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 89 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 93 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 97 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 101 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 106 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 111 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 112 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 113 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 115 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 119 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 121 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 129 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 132 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 135 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 138 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 141 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 145 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 155 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 160 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 166 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 168 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 171 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 176 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 179 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 182 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 185 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 186 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 190 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 194 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 197 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 200 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 201 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 203 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 211 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 213 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 214 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 215 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 219 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/Compiler.h"
#line 118 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"

#line 1 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/usb_config.h"

#line 43 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/usb_config.h"
 


#line 47 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/usb_config.h"
 

#line 154 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/usb_config.h"
#line 119 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"


 
 
 


#line 127 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 128 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"

#line 130 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 131 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"

#line 133 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 134 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"

#line 136 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 137 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"

#line 139 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"


#line 142 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 143 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"

#line 145 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 146 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"

#line 148 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 149 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"


#line 152 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 153 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 154 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 155 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"

#line 157 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 158 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 159 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 160 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"

#line 162 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 163 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 164 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 165 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"

#line 167 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 168 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 169 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 170 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"

#line 172 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 173 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 174 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 175 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"

#line 177 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 178 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 179 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 180 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"

#line 182 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 183 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 184 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 185 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"


#line 188 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 190 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 191 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 192 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"

#line 194 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 196 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 197 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 198 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"


#line 201 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 202 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 203 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 204 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 205 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"


#line 208 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 209 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 210 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 211 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 212 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 213 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 214 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 215 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 216 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 217 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"

#line 219 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 220 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 221 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 222 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 223 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 224 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 225 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 226 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"

#line 228 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"


#line 231 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"

 
#line 234 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 235 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 236 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 237 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"


#line 240 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 241 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 242 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 243 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 244 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 245 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 246 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 247 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 248 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 249 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 250 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 251 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"


#line 254 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 255 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 257 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 259 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 261 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 262 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 263 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 264 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"

#line 266 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 267 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 268 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"



#line 272 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 273 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 274 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 275 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 276 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 277 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"

 
 
 


typedef union _BD_STAT
{
    BYTE Val;
    struct{
        
        unsigned BC8:1;         
        unsigned BC9:1;         
        unsigned BSTALL:1;      
        unsigned DTSEN:1;       
        unsigned INCDIS:1;      
        unsigned KEN:1;         
        unsigned DTS:1;         
        unsigned UOWN:1;        
    };
    struct{
        
        
        unsigned :2;
        unsigned PID0:1;        
        unsigned PID1:1;
        unsigned PID2:1;
        unsigned PID3:1;
        unsigned :1;
    };
    struct{
        unsigned :2;
        unsigned PID:4;         
        unsigned :2;
    };
} BD_STAT;                      


typedef union __BDT
{
    struct
    {
        BD_STAT STAT;
        BYTE CNT;
        BYTE ADRL;                      
        BYTE ADRH;                      
    };
    struct
    {
        unsigned :8;
        unsigned :8;
        WORD     ADR;                      
    };
    DWORD Val;
    BYTE v[4];
} BDT_ENTRY;


typedef union __USTAT
{
    struct
    {
        unsigned char filler1:1;
        unsigned char ping_pong:1;
        unsigned char direction:1;
        unsigned char endpoint_number:4;
    };
    BYTE Val;
} USTAT_FIELDS;


#line 349 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 350 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 351 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"


typedef union _POINTER
{
    struct
    {
        BYTE bLow;
        BYTE bHigh;
        
    };
    WORD _word;                         
    
    

    BYTE* bRam;                         
                                        
    WORD* wRam;                         
                                        

    rom  BYTE* bRom;                     
    rom  WORD* wRom;
    
    
    
    
} POINTER;

 
 
 

#line 383 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 384 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"





#line 390 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 392 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 395 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 398 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 403 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 405 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 407 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"

#line 414 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 416 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"



#line 420 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 421 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 422 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 423 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 424 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 427 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
    
#line 429 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
    
    
#line 432 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 433 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 434 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 436 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
    
#line 438 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
    

#line 443 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 444 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 445 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"




#line 466 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
 
#line 468 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"


#line 485 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
 

#line 490 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 491 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"


#line 508 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
 
#line 510 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"


#line 529 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
 
#line 531 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"


#line 551 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
 
#line 553 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"


#line 574 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
 
#line 576 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"

 
 
 


#line 585 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"

 
 
 

#line 591 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
    
    extern volatile  BYTE USBActiveConfiguration;
    extern volatile  IN_PIPE inPipes[1];
    extern volatile  OUT_PIPE outPipes[1];
#line 596 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"

extern volatile BDT_ENTRY* pBDTEntryOut[4 +1];
extern volatile BDT_ENTRY* pBDTEntryIn[4 +1];

#line 601 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal_pic18.h"
#line 94 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"

#line 96 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 97 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 99 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 101 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 103 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 104 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 106 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 108 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 110 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
    


#line 114 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
 


#line 145 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
 

#line 148 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
 

#line 151 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"

void OTGCORE_SetDeviceAddr ( BYTE addr );



#line 182 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
 


#line 186 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
 
#line 188 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
    void USBHALControlUsbResistors( BYTE flags );
#line 190 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 193 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"

 
#line 196 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 197 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 198 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 199 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"

#line 201 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
 
#line 203 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 204 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 205 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"



#line 209 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
 



#line 233 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
 

BOOL USBHALSessionIsValid( void );



#line 259 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
 

BOOL USBHALControlBusPower( BYTE cmd );

 
#line 265 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 266 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 267 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 268 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"

#line 271 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
 



#line 300 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
 

unsigned long USBHALGetLastError( void );


#line 306 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
 
#line 308 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 309 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 310 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 311 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 312 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 313 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 314 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 315 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 316 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 317 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 318 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"



#line 346 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
 

void USBHALHandleBusEvent ( void );



#line 381 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
 

#line 385 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
 

#line 388 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"

BOOL OTGCORE_StallPipe ( TRANSFER_FLAGS pipe );



#line 418 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
 

#line 422 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
 

#line 425 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"

BOOL OTGCORE_UnstallPipe ( TRANSFER_FLAGS pipe );



#line 451 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
 


#line 456 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
 

#line 459 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"

UINT16 OTGCORE_GetStalledEndpoints  ( void );



#line 495 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
 

BOOL USBHALFlushPipe( TRANSFER_FLAGS pipe );



#line 555 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
 

BOOL USBHALTransferData ( TRANSFER_FLAGS    flags,
                          void             *buffer,
                          unsigned int      size      );



#line 595 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
 

BOOL USBHALSetEpConfiguration ( BYTE ep_num, UINT16 max_pkt_size, UINT16 flags );

 
#line 601 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 602 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 603 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 604 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"

#line 606 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 607 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 608 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"

#line 615 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
#line 619 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"



#line 645 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
 

BOOL USBHALInitialize ( unsigned long flags );

#line 650 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"

#line 652 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/USB/usb_hal.h"
 

#line 130 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/./USB/usb.h"
            







#line 139 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/./USB/usb.h"
#line 140 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/./USB/usb.h"
#line 141 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/./USB/usb.h"

#line 143 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/./USB/usb.h"

#line 145 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/./USB/usb.h"
 

#line 49 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"

#line 1 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"

#line 34 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
 


#line 38 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"



#line 42 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 43 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 44 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 45 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 47 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 49 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 50 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 51 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 53 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 56 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 57 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 58 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"

#line 60 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 61 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 63 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 65 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 67 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 69 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 71 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 73 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 74 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 76 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 78 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 79 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 80 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 82 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 83 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 84 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"

#line 86 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 87 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 1 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"

#line 39 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
 


#line 43 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"

     
     
     
    
    
    
    
    
    
    
    

    
    
    
    
#line 61 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 62 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 64 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 65 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 66 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"

    
#line 69 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 70 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 72 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 73 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 74 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"


    
    
    
	
    
    
#line 83 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"

     
     
     
     
     
     
     

     
    
    
    
    
    
    
#line 100 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 101 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 102 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"


     
#line 106 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
    
#line 108 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 109 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 110 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 111 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
    
#line 113 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 114 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 115 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 116 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"

#line 118 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 119 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 120 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 121 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
    
#line 123 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 124 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 125 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 126 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
    
#line 128 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 129 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 130 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 131 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
    
     
#line 134 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 135 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 136 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 137 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 138 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
    
     
#line 141 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 142 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 143 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 144 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 145 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 146 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
    
#line 148 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
    
     
#line 151 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 152 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"

#line 154 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile - PICDEM FSUSB.h"
#line 87 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"

#line 89 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 91 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 93 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 95 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 97 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 99 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 100 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 102 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 104 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 105 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 107 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 108 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"

#line 110 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 111 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 113 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 114 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 115 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"

#line 117 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 119 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"

#line 121 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware/HardwareProfile.h"
#line 50 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"




#line 1 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"

#line 3 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"

#line 30 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"
 
 
#line 1 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"



#line 5 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 11 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
 



#line 1 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 5 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 7 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 9 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 11 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 13 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 15 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 17 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 19 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 21 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 23 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 25 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 27 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 29 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 31 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 33 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 35 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 37 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 39 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 41 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 43 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 45 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 47 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 49 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 51 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 53 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 55 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 57 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 59 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 61 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 63 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 65 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 67 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 69 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 71 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 73 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 75 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 77 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 79 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 81 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 83 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 85 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 87 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 89 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 91 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 93 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 95 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 97 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 99 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 101 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 103 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 105 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 107 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 109 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 111 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 113 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 115 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 117 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 119 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 121 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 123 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 125 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 127 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 129 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 131 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 133 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 135 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 137 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 139 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 141 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 143 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 145 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 147 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 149 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 151 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 153 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 155 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 157 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 159 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 161 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 163 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 165 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 167 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 169 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 171 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 173 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 175 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 177 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 179 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 181 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 183 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 185 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 187 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 189 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 191 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 193 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 195 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 197 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 199 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 201 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 203 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 205 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 207 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 209 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 211 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 213 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 215 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 217 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 219 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 221 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 223 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 225 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 227 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 229 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 231 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 233 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 235 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 237 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 239 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 241 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 243 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 245 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 247 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 249 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 251 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 253 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 255 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 257 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 259 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 261 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 263 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 265 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 267 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 269 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 271 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 273 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 275 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 277 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 279 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 281 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 283 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 285 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 287 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 289 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 291 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 293 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 295 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 297 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 299 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 301 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 303 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 305 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 307 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 309 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 311 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 313 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 315 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 317 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 319 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 321 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 323 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 325 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 327 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 329 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 331 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 333 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 335 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 337 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 339 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 341 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 343 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 345 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 347 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 349 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 351 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 353 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 355 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 357 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 359 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 361 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 363 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 365 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 367 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 369 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 371 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 373 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 375 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 377 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 379 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 381 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 383 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 385 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 387 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 389 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 391 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 393 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 395 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 397 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 399 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 401 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 403 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 405 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 407 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 409 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 411 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 413 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 415 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 417 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 419 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 421 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 423 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 425 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 427 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 429 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 431 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 433 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 435 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 437 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 439 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 441 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 443 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 445 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 447 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 449 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 451 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 453 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 455 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 457 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 459 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 461 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 463 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 465 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 467 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 469 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 471 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 473 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 475 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 477 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 479 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 481 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 483 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 485 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 487 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 489 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 491 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 493 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 495 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 497 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 499 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 501 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 503 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 505 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 507 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 509 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 511 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 513 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 515 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 517 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 519 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 521 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 523 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 525 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 527 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 529 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 531 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 533 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 535 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 537 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 539 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 541 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 543 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 545 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 547 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 549 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 551 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 553 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 555 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 557 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 559 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 561 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 563 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 565 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 567 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 569 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 571 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 573 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 575 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 577 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 579 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 581 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 583 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 585 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 587 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 589 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 591 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 593 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 595 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 597 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 599 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h"
#line 15 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"



#line 84 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 150 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 216 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 282 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 348 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 414 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 480 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 546 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 612 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 678 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 744 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 810 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 876 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 942 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 1008 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 1074 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 1140 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 1206 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 1272 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 1338 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 1404 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 1470 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 1536 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 1602 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 1668 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 1734 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 1800 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 1866 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 1932 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 1998 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 2064 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 2130 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 2196 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 2262 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 2328 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 2394 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 2460 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 2526 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 2592 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 2658 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 2724 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 2790 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 2856 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 2922 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 2988 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 3054 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 3120 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

 
 
 

 
#line 3127 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

 
 

 
#line 3133 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

 
#line 3136 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

 
#line 3139 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

 
 

 
#line 3145 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

 
#line 3148 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

 
#line 3151 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

 
#line 3154 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

 
#line 3157 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

 
#line 3160 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

 
#line 3163 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

 
#line 3166 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

 
 

 
 

 
 

 
 

 
 

 
#line 3184 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 3186 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 3252 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 3318 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 3384 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 3450 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 3516 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 3582 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 3648 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 3714 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 3780 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 3846 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 3912 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 3978 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 4044 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 4110 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 4176 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 4242 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 4308 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 4374 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 4440 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 4506 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 4572 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 4638 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 4704 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 4770 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 4836 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 4902 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 4968 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 5034 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 5100 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 5166 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 5232 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 5298 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 5364 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 5430 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 5496 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 5562 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 5628 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 5694 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 5760 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 5826 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 5892 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 5958 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 6024 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 6090 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 6156 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 6222 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 6288 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 6354 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 6420 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 6486 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 6552 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 6618 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 6684 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 6750 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 6816 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 6882 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 6948 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 7014 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 7080 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 7146 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 7212 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 7278 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 7344 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 7410 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 7476 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 7542 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 7608 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 7674 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 7740 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 7806 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 7872 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 7938 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 8004 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 8070 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 8136 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 8202 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 8268 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 8334 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 8400 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 8466 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 8532 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 8598 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 8664 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 8730 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 8796 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 8862 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 8928 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 8994 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 9060 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 9126 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 9192 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 9258 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 9324 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 9390 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 9456 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 9522 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 9588 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 9654 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 9720 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 9786 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 9852 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 9918 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 9984 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 10050 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 10116 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 10182 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 10248 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 10314 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 10380 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 10446 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 10512 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 10578 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 10644 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 10710 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 10776 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 10842 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 10908 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 10974 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 11040 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 11106 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 11172 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 11238 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 11304 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 11370 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 11436 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 11502 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 11568 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 11634 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 11700 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 11766 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 11832 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 11898 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 11964 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 12030 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 12096 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 12162 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 12228 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 12294 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 12360 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 12426 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 12492 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 12558 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 12624 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 12690 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 12756 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 12822 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 12888 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 12954 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 13020 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 13086 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 13152 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 13218 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 13284 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 13350 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 13416 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 13482 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 13548 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 13614 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 13680 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 13746 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 13812 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 13878 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 13944 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 14010 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 14076 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 14142 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 14208 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 14274 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 14340 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 14406 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 14472 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 14538 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 14604 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 14670 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 14736 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 14802 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 14868 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 14934 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 15000 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 15066 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 15132 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 15198 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 15264 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 15330 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 15396 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 15462 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 15528 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 15594 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 15660 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 15726 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 15792 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 15858 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 15924 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 15990 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 16056 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 16122 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 16188 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 16254 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 16320 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 16386 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 16452 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 16518 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 16584 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 16650 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 16716 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 16782 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 16848 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 16914 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 16980 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 17046 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 17112 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 17178 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 17244 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 17310 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 17376 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 17442 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 17508 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 17574 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 17640 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 17706 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 17772 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 17838 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 17904 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 17970 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 18036 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 18102 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 18168 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 18234 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 18300 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 18366 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 18432 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 18498 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 18564 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 18630 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 18696 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 18762 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 18828 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 18894 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 18960 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19026 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19092 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19158 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19224 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19290 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19356 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19422 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19424 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"




 
 
 

#line 19458 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
 
 


#line 19463 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19465 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19466 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19467 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"


#line 19479 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19480 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19481 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19482 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"


#line 19503 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19504 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19505 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19510 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19511 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19513 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19514 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19516 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19521 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19523 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19526 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19528 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19533 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19535 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19539 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"


#line 19547 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19548 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19553 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"


#line 19555 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19556 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19560 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"


#line 19562 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19563 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19570 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19572 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19577 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"


#line 19584 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19585 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19588 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19589 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19591 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19592 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"


#line 19600 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19601 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19608 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19609 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19611 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19612 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19614 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19615 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19617 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19620 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19621 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19623 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"


#line 19625 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19626 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19628 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19629 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19630 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19632 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"


#line 19636 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19637 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19639 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19641 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19643 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19645 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19646 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19648 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"


#line 19653 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19654 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19660 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"


#line 19662 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19663 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19664 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19665 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19666 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19667 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19668 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19669 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19670 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19671 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19673 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19682 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19684 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19691 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19693 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19701 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"


#line 19703 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19704 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19714 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19716 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19722 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19724 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19729 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"


#line 19733 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19734 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19744 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19746 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19747 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19748 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19750 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19751 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19753 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19764 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"


#line 19766 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19767 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19770 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"


#line 19778 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19779 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19784 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"


#line 19786 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19787 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19790 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"


#line 19792 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19793 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19798 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19801 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19802 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"


#line 19804 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19805 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19812 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19814 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19815 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19816 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19820 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19821 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"


#line 19826 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19827 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19837 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19839 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19845 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19847 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19854 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19856 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19864 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19866 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19876 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"


#line 19881 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19882 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19884 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"


#line 19887 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19888 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19896 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19897 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19899 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19900 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"


#line 19903 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19904 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19911 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"


#line 19917 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19918 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19923 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19924 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19926 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19927 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19928 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19930 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19931 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"


#line 19934 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19935 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19940 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"


#line 19944 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19945 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19948 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"


#line 19951 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19952 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19956 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"


#line 19960 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19961 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19971 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19972 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19975 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19976 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19979 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19980 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"


#line 19983 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19984 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19990 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19991 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19994 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19996 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19997 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19998 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 20000 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 20007 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 20009 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 20010 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 20012 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 20013 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 32 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"
#line 33 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"


 


 



#line 43 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"
#line 44 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"


#line 47 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"



#line 51 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"



#line 55 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"



#line 59 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"



 
#line 64 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"

#line 66 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"
#line 67 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"
#line 68 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"
#line 69 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"
#line 70 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"
#line 71 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"


 
#line 75 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"
#line 76 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"
#line 77 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"
#line 78 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"
#line 79 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"
#line 80 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"

 
#line 83 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"
#line 84 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"
#line 85 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"
#line 86 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"


 

 
#line 92 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"

#line 111 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"

#line 123 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"

#line 136 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"

#line 147 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"

#line 158 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"

#line 169 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"

#line 184 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"

#line 199 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"

#line 210 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"

#line 226 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"
#line 249 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"
 

#line 252 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"
#line 254 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"

#line 263 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"

#line 275 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"

#line 288 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"

#line 299 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"

#line 310 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"
#line 314 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"

#line 324 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"

#line 336 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"

#line 349 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"

#line 360 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"

#line 371 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"
#line 375 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"

#line 385 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"

#line 400 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"

#line 415 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"

#line 426 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"

#line 437 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"
#line 454 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"

#line 456 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"

 


#line 468 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"
  
#line 470 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"


#line 480 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"
  
#line 482 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"


#line 493 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"
 
#line 495 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"


#line 504 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"
 
#line 506 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"


#line 515 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"
 
#line 517 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"


#line 526 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"
 
#line 528 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"




#line 543 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"
 
#line 545 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"


#line 558 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"
 
#line 560 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"


#line 569 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"
 
#line 571 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"


#line 580 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"
 
#line 582 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"


void OpenSPI(  unsigned char sync_mode,
               unsigned char bus_mode,
               unsigned char smp_phase );

signed char WriteSPI(  unsigned char data_out );

void getsSPI(  unsigned char *rdptr,  unsigned char length );

void putsSPI(  unsigned char *wrptr );

unsigned char ReadSPI( void );

#line 597 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"


#line 600 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/spi.h"

#line 54 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"

#line 1 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

#line 3 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

#line 30 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
 
#line 1 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"



#line 11 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 84 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 150 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 216 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 282 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 348 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 414 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 480 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 546 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 612 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 678 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 744 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 810 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 876 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 942 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 1008 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 1074 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 1140 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 1206 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 1272 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 1338 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 1404 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 1470 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 1536 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 1602 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 1668 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 1734 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 1800 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 1866 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 1932 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 1998 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 2064 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 2130 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 2196 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 2262 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 2328 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 2394 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 2460 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 2526 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 2592 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 2658 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 2724 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 2790 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 2856 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 2922 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 2988 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 3054 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 3120 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 3186 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 3252 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 3318 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 3384 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 3450 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 3516 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 3582 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 3648 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 3714 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 3780 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 3846 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 3912 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 3978 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 4044 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 4110 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 4176 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 4242 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 4308 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 4374 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 4440 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 4506 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 4572 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 4638 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 4704 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 4770 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 4836 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 4902 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 4968 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 5034 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 5100 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 5166 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 5232 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 5298 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 5364 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 5430 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 5496 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 5562 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 5628 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 5694 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 5760 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 5826 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 5892 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 5958 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 6024 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 6090 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 6156 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 6222 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 6288 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 6354 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 6420 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 6486 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 6552 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 6618 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 6684 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 6750 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 6816 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 6882 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 6948 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 7014 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 7080 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 7146 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 7212 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 7278 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 7344 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 7410 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 7476 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 7542 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 7608 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 7674 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 7740 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 7806 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 7872 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 7938 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 8004 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 8070 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 8136 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 8202 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 8268 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 8334 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 8400 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 8466 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 8532 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 8598 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 8664 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 8730 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 8796 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 8862 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 8928 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 8994 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 9060 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 9126 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 9192 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 9258 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 9324 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 9390 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 9456 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 9522 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 9588 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 9654 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 9720 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 9786 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 9852 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 9918 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 9984 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 10050 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 10116 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 10182 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 10248 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 10314 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 10380 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 10446 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 10512 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 10578 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 10644 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 10710 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 10776 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 10842 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 10908 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 10974 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 11040 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 11106 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 11172 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 11238 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 11304 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 11370 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 11436 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 11502 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 11568 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 11634 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 11700 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 11766 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 11832 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 11898 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 11964 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 12030 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 12096 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 12162 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 12228 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 12294 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 12360 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 12426 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 12492 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 12558 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 12624 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 12690 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 12756 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 12822 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 12888 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 12954 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 13020 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 13086 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 13152 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 13218 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 13284 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 13350 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 13416 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 13482 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 13548 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 13614 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 13680 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 13746 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 13812 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 13878 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 13944 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 14010 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 14076 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 14142 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 14208 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 14274 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 14340 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 14406 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 14472 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 14538 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 14604 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 14670 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 14736 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 14802 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 14868 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 14934 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 15000 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 15066 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 15132 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 15198 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 15264 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 15330 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 15396 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 15462 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 15528 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 15594 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 15660 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 15726 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 15792 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 15858 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 15924 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 15990 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 16056 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 16122 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 16188 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 16254 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 16320 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 16386 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 16452 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 16518 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 16584 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 16650 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 16716 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 16782 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 16848 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 16914 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 16980 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 17046 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 17112 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 17178 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 17244 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 17310 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 17376 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 17442 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 17508 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 17574 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 17640 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 17706 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 17772 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 17838 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 17904 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 17970 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 18036 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 18102 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 18168 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 18234 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 18300 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 18366 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 18432 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 18498 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 18564 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 18630 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 18696 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 18762 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 18828 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 18894 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 18960 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19026 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19092 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19158 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19224 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19290 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19356 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19422 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19424 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"




 
 
 

#line 19458 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
 
 

#line 19465 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19467 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19479 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19480 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19482 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19503 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19504 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19510 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19511 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19513 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19514 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19516 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19521 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19523 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19526 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19528 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19533 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19535 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19539 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19547 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19548 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19553 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19555 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19556 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19560 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19562 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19563 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19570 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19572 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19577 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19584 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19585 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19588 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19589 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19591 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19592 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19600 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19601 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19608 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19609 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19611 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19612 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19614 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19615 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19617 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19620 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19621 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19623 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19625 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19626 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19628 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19629 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19630 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19632 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19636 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19637 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19639 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19641 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19643 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19645 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19646 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19648 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19653 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19654 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19660 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19662 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19663 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19671 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19673 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19682 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19684 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19691 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19693 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19701 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19703 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19704 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19714 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19716 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19722 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19724 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19729 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19733 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19734 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19744 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19746 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19747 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19748 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19750 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19751 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19753 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19764 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19766 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19767 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19770 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19778 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19779 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19784 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19786 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19787 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19790 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19792 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19793 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19798 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19801 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19802 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19804 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19805 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19812 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19814 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19815 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19816 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19820 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19821 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19826 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19827 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19837 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19839 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19845 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19847 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19854 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19856 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19864 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19866 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19876 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19881 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19882 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19884 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19887 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19888 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19896 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19897 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19899 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19900 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19903 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19904 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19911 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19917 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19918 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19923 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19924 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19926 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19927 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19928 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19930 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19931 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19934 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19935 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19940 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19944 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19945 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19948 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19951 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19952 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19956 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19960 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19961 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19971 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19972 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19975 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19976 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19979 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19980 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19983 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19984 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"

#line 19990 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19991 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19994 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19996 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19997 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 19998 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 20000 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 20007 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 20009 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 20010 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 20012 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 20013 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/pconfig.h"
#line 31 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 32 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

 

 
union Timers
{
  unsigned int lt;
  char bt[2];
};



#line 44 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
 


#line 48 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 49 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

 

#line 52 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
 
 
#line 55 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 56 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

#line 58 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 59 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 61 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 62 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 63 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

#line 65 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 66 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

#line 68 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 69 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 70 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 71 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 72 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 73 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 74 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 75 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 76 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

#line 78 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

#line 85 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 93 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 95 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 97 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 117 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

void OpenTimer0 ( unsigned char config);
void CloseTimer0 (void);
unsigned int ReadTimer0 (void);
void WriteTimer0 ( unsigned int timer0);

 


#line 126 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
 
 

#line 129 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 130 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 134 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 136 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 155 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 157 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 159 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 183 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 191 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"




#line 196 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 197 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 198 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 199 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 200 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 201 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 202 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 203 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 204 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 205 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 206 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 207 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

#line 209 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 235 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

void OpenTimer1 ( unsigned char config);
void CloseTimer1 (void);
unsigned int ReadTimer1 (void);
void WriteTimer1 ( unsigned int timer1);
#line 241 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"


 

#line 246 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 247 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

#line 248 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
 



#line 253 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 254 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 255 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 256 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 257 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 258 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 259 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 260 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 261 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 262 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 263 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 264 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 265 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 266 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 267 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 268 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 269 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 270 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 271 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

#line 273 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 298 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"


#line 309 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
 
#line 311 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"


#line 322 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
 
#line 324 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

void OpenTimer2 ( unsigned char config);
void CloseTimer2 (void);

#line 329 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
 

#line 332 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"


#line 334 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
 
 


#line 339 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 340 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 341 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 342 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 343 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 344 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 345 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 346 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 347 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 348 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

#line 350 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 371 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"



#line 378 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
  
#line 380 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"


#line 386 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
  
#line 388 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"



void OpenTimer3 ( unsigned char config);
void CloseTimer3 (void);
unsigned int ReadTimer3 (void);
void WriteTimer3 ( unsigned int timer3);


#line 397 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 398 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 402 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 404 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 423 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 425 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 427 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 451 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 457 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

 


#line 461 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 462 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

#line 464 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 489 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 514 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

#line 525 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

#line 538 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 546 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"


#line 549 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 568 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 596 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 603 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 607 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 609 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 628 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 630 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 632 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 656 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 663 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"



#line 667 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

#line 669 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 694 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 719 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

#line 730 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

#line 743 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 751 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"


#line 754 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 776 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 801 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 808 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"




#line 813 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

#line 815 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 840 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 865 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

#line 876 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

#line 889 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 897 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"


#line 900 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

#line 902 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 927 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 952 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

#line 963 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

#line 976 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 984 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"



#line 988 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

#line 990 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 1015 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 1040 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

#line 1051 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

#line 1064 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 1072 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"


#line 1075 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 1088 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 1092 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 1095 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 1099 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 1118 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 1122 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 1125 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 1132 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 1133 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

#line 1135 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 1142 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 1149 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 1151 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"


#line 1154 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 1155 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 1156 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 1157 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 1162 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

#line 1164 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 1170 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 1176 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
#line 1177 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

#line 1179 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"
void SetTmrCCPSrc(  unsigned char );
#line 1181 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

#line 1183 "C:/Program Files (x86)/Microchip/mplabc18/v3.46/h/timers.h"

#line 55 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"


 
#pragma config PLLDIV   = 5         
#pragma config CPUDIV   = OSC1_PLL2
#pragma config USBDIV   = 2         
#pragma config FOSC     = HSPLL_HS
#pragma config FCMEN    = OFF
#pragma config IESO     = OFF
#pragma config PWRT     = OFF
#pragma config BOR      = ON
#pragma config BORV     = 3
#pragma config VREGEN   = ON      
#pragma config WDT      = OFF
#pragma config WDTPS    = 32768
#pragma config MCLRE    = ON
#pragma config LPT1OSC  = OFF
#pragma config PBADEN   = OFF

#pragma config STVREN   = ON
#pragma config LVP      = OFF

#pragma config XINST    = OFF       
#pragma config CP0      = OFF
#pragma config CP1      = OFF


#pragma config CPB      = OFF

#pragma config WRT0     = OFF
#pragma config WRT1     = OFF


#pragma config WRTB     = OFF       
#pragma config WRTC     = OFF

#pragma config EBTR0    = OFF
#pragma config EBTR1    = OFF


#pragma config EBTRB    = OFF

 
#pragma udata




#line 104 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"

#line 108 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"
#line 109 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"
    #pragma udata USB_VARIABLES=0x500
#line 111 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"
#line 113 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"
#line 115 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"


union INdataUnion {
	unsigned char data[16];
	unsigned int word[8];
	struct{
		unsigned vca_lo:8;
		unsigned vca_hi:2;
		unsigned status:2;
		unsigned id_change_flag:1;
		unsigned blink_flag:1;
		unsigned touchsense:1;
		unsigned mute:1;
	}channel[8];
	struct{
		unsigned :8;
		unsigned cmd:4;
		unsigned flag:1;
		unsigned :3;
	}cmd[8];
	struct{
		unsigned lo_byte:8;
		unsigned :6;
		unsigned hi_byte:2;
	}vcaGroup[8];
};

union OUTdataUnion {
	unsigned char data[16];
	unsigned int word[8];
	struct{
		unsigned vca_lo:8;
		unsigned vca_hi:2;
		unsigned status_press:1;
		unsigned status_release:1;
		unsigned card_id:2;
		unsigned mute_press:1;
		unsigned mute_release:1;
		}channel[8];
	struct{
		unsigned vca_lo:8;
		unsigned vca_hi:2;
		unsigned status:2;
		unsigned touch_press:1;
		unsigned touch_release:1;
		unsigned mute_press:1;
		unsigned mute_release:1;
		}mf[8];
};
union INdataUnion dataToFader;
union OUTdataUnion dataFromFader;

unsigned char ReceivedDataBuffer[64];
unsigned char ToSendDataBuffer[64];

unsigned char flip=0;
USB_AUDIO_MIDI_EVENT_PACKET midiData;



#line 176 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"
    #pragma udata
#line 178 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"

void*  USBTxHandle = 0;
void*  USBRxHandle = 0;


volatile  BYTE msCounter;
int cnt=0x00;
int fader_out=0;
unsigned char midiOutFlag = 0;		
unsigned char midiPacketCntr=0;		
unsigned char midiOutBuffer[16];	
unsigned char midiOutBufferLen=0;	
unsigned int faderLevel[8];

unsigned char midiTemp[64];


 
void BlinkUSBStatus(void);
BOOL Switch2IsPressed(void);
BOOL Switch3IsPressed(void);
static void InitializeSystem(void);
void ProcessIO(void);
void UserInit(void);
void YourHighPriorityISRCode();
void YourLowPriorityISRCode();
void USBCBSendResume(void);
void parseMidiData(unsigned char, unsigned char, unsigned char, unsigned char);
WORD_VAL ReadPOT(void);

unsigned char * packSpiMessage(USB_AUDIO_MIDI_EVENT_PACKET * midiMessage);

 







#line 219 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"
#line 220 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"
#line 221 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"
#line 222 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"
#line 223 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"

   
   
   
   
   
   
   
   
   
#line 234 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"
#line 235 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"
   

#pragma romdata AppVersionAndSignatureSection = 0x1016 
rom  unsigned char AppVersion[2] = {0 , 1 };
#pragma romdata AppSignatureSection = 0x1006 
rom  unsigned short int SignaturePlaceholder = 0xFFFF;

#pragma code HIGH_INTERRUPT_VECTOR = 0x08
void High_ISR (void)
{
     _asm goto 0x1008  _endasm
}
#pragma code LOW_INTERRUPT_VECTOR = 0x18
void Low_ISR (void)
{
     _asm goto 0x1018  _endasm
}
extern void _startup (void);        
#pragma code REMAPPED_RESET_VECTOR = 0x1000 
void _reset (void)
{
    _asm goto _startup _endasm
}
#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = 0x1008 
void Remapped_High_ISR (void)
{
     _asm goto YourHighPriorityISRCode _endasm
}
#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = 0x1018 
void Remapped_Low_ISR (void)
{
     _asm goto YourLowPriorityISRCode _endasm
}
#pragma code
unsigned char cntr=0;
unsigned char spiCntr=0;
unsigned char spiFlag=0;

#pragma interrupt YourHighPriorityISRCode
void YourHighPriorityISRCode()
{

	if(PIR1bits.TMR2IF)
	{
		if(cntr==0)
		{
			cntr=252;
			spiFlag=1;
			spiCntr++;
			if(spiCntr>7)spiCntr=0;
		}
		cntr++;
		PIR1bits.TMR2IF=0;
	}
#line 290 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"
        USBDeviceTasks();
#line 292 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"


}	
#pragma interruptlow YourLowPriorityISRCode
void YourLowPriorityISRCode()
{

}

 
#pragma code
#line 304 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"

unsigned char testArray[64];
unsigned char newFaderData=0;
unsigned char heartbeatFlag=1;
unsigned char heartbeatCntr=0;

unsigned char OutByte1 = 0;
unsigned char OutByte2 = 0;
unsigned char OutByte3 = 0;

unsigned char USBflag=0;
unsigned char channelState=0;
unsigned char currentChannel=0;


#line 323 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"
 


void parseMidiData(unsigned char bank, unsigned char data0, unsigned char data1, unsigned char data2)
{
    unsigned char channel;
    static unsigned int hibyte;
    unsigned int lobyte;
    unsigned char message[3];
	static unsigned char lastChannel=0;
    
   if(data0==0xB0)                           
    {
        if((data1 & 0xF0) == 0x00 && (data1 & 0x0F) < 0x8)                 
        {
            channel = (bank*8)+(data1 & 0x07);
            hibyte = data2 & 0x7F;
			faderLevel[channel] = (hibyte << 3);
        }
        if((data1 & 0xF0) == 0x20 && (data1 & 0x0F) < 0x8)             
        {
            channel = (bank*8)+(data1 & 0x07);  
            lobyte = data2 & 0x70;
			faderLevel[channel]+=(lobyte >> 4);
			faderLevel[channel]=faderLevel[channel]&0x3ff;
        }
    }
}

void main(void)
{
	static unsigned char testCntr=0;
	static unsigned int testPos=0;
	unsigned char midiFromHostIndex=0;
	unsigned char n=0;

    InitializeSystem();

#line 362 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"
        USBDeviceAttach();
#line 364 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"

	TRISDbits.TRISD4=0;		

	TRISCbits.TRISC7=0;		
	TRISBbits.TRISB1=0;		
	TRISBbits.TRISB0=1;		

	INTCONbits.GIE = 1;	

	OpenTimer2( 	0b11111111  &
				0b11111101  &
				0b11111111  );

	OpenSPI(0b00000011 , 0b00000001 , 0b10000000 ); 
		


    while(1)
    {
#line 384 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"
#line 398 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"
	



		if(spiFlag)
		{

			switch(spiCntr)
			{
				case 0:		
				break;

				case 1:
					dataToFader.word[0]=faderLevel[0]&0x3ff;
					OutByte1 =dataToFader.data[0]&0b00111111;					
					OutByte1+=0b01000000;	

					OutByte2 =(dataToFader.data[0]&0b11000000)>>6;				
					OutByte2+=(dataToFader.data[1]&0b00001111)<<2;		
					OutByte2+=0b10000000;

					OutByte3=(dataToFader.data[1]&0b11110000)>>4;			
					OutByte3+=0b11000000;

					WriteSPI(OutByte1);
				break;

				case 2:							
				break;
	
				case 3:							
					WriteSPI(OutByte2);	
				break;
	
				case 4:		
					dataFromFader.data[0]=SSPBUF;
				break;
		
				case 5:
					WriteSPI(OutByte3);
				break;
	
				case 6:				
					dataFromFader.data[1]=SSPBUF;
					newFaderData=1;				
				break;

				case 7:					
					heartbeatCntr++;
					if(heartbeatCntr>30)
					{
						heartbeatFlag=1;
						heartbeatCntr=0;
					}
				break;
			}

USBDeviceTasks();		
			spiFlag=0;
		}

		
		
        ProcessIO();
    }
}

static void InitializeSystem(void)
{
   	ADCON1 |= 0x0F;                 

#line 470 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"
#line 472 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"

#line 474 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"
#line 476 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"

    UserInit();

    USBDeviceInit();	
    					
}

void UserInit(void)
{


    
    
    USBTxHandle = 0 ;
    USBRxHandle = 0 ;
}


void ProcessIO(void)
{
	static unsigned int cntr = 0;
	static unsigned char stateCntr = 0;
	int lobyte;
	int hibyte;
	unsigned char * arrayP;
	static unsigned int level=0;
	static unsigned int lastLevel=0;
	unsigned char index=0;
	unsigned char n=0;
	unsigned char channel=0;
	unsigned char midiFromHostIndex=0;


	level = dataFromFader.word[0] & 0x3ff;


	
    if((USBDeviceState < CONFIGURED_STATE)||(UCONbits.SUSPND ==1)) return;



    if(!(USBRxHandle==0?0:((volatile BDT_ENTRY*)USBRxHandle)->STAT.UOWN) )
    {
        
		LATDbits.LATD4  = !LATDbits.LATD4 ; ;
	
		USBflag=1;
        

		USBRxHandle = USBTransferOnePacket(1 ,0 ,(BYTE*)&ReceivedDataBuffer,64) ;

			LATDbits.LATD4  = !LATDbits.LATD4 ; ;

			midiFromHostIndex=0;

			while(midiFromHostIndex<64)
			{
				if(ReceivedDataBuffer[midiFromHostIndex]==0x0b)
				{
				
					{
						if(ReceivedDataBuffer[midiFromHostIndex+2]==0x00)
						{
							parseMidiData(0,0xb0,ReceivedDataBuffer[midiFromHostIndex+2],ReceivedDataBuffer[midiFromHostIndex+3]);
						}
						if(ReceivedDataBuffer[midiFromHostIndex+2]==0x20)
						{
							parseMidiData(0,0xb0,ReceivedDataBuffer[midiFromHostIndex+2],ReceivedDataBuffer[midiFromHostIndex+3]);
						}
					}
				}
				midiFromHostIndex+=4;
			}
				
	}

	if(heartbeatFlag)
	{
		heartbeatFlag=0;
	    midiTemp[0] = 0x0B;
	    midiTemp[1] = 0x90;
	    midiTemp[2] = 0x00;
	    midiTemp[3] = 0x7F;
		index+=4;	
	}

	if(newFaderData)
	{
		newFaderData=0;
		if(dataFromFader.mf[0].touch_press)
		{
	
		    midiTemp[0+index] = 0x0B;
		    midiTemp[1+index] = 0xB0;
		    midiTemp[2+index] = 0x0F;
		    midiTemp[3+index] = 0x00;	
		    midiTemp[4+index] = 0x0B;
		    midiTemp[5+index] = 0xB0;
		    midiTemp[6+index] = 0x2F;
		    midiTemp[7+index] = 0x40;	
			index+=8;
		}
	
		if(dataFromFader.mf[0].touch_release)
		{
		    midiTemp[0+index] = 0x0B;
		    midiTemp[1+index] = 0xB0;
		    midiTemp[2+index] = 0x0F;
		    midiTemp[3+index] = 0x00;	
		    midiTemp[4+index] = 0x0B;
		    midiTemp[5+index] = 0xB0;
		    midiTemp[6+index] = 0x2F;
		    midiTemp[7+index] = 0x00;	
			index+=8;
		}

		if(level!=lastLevel)
		{
			dataToFader.word[0]=level;
			midiTemp[0+index] = 0x0B;
			midiTemp[1+index] = 0xB0;
			midiTemp[2+index] = 0x00;
			midiTemp[3+index] = (( level>>3 ) & 0x7F); 
			midiTemp[4+index] = 0x0B;
			midiTemp[5+index] = 0xB0;
			midiTemp[6+index] = 0x20;
			midiTemp[7+index] = (( level<<4 ) & 0x70) >> 1; 
			lastLevel=level;
		}
	}


    	if(!(USBTxHandle==0?0:((volatile BDT_ENTRY*)USBTxHandle)->STAT.UOWN)  && midiTemp[0]!=0)
    	{
		for(n=0;n<64;n++)
		{
			ToSendDataBuffer[n]=midiTemp[n];
			midiTemp[n]=0;
		}
        	USBTxHandle = USBTransferOnePacket(1 ,1 ,(BYTE*)&ToSendDataBuffer,64) ;
	}



}




void BlinkUSBStatus(void)
{
    static WORD led_count=0;

    if(led_count == 0)led_count = 10000U;
    led_count--;

#line 633 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"
#line 634 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"
#line 635 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"
#line 636 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"

    if(UCONbits.SUSPND  == 1)
    {
        if(led_count==0)
        {
            LATBbits.LATB0  = !LATBbits.LATB0 ; ;
            if(LATBbits.LATB0  )
            {
                LATDbits.LATD4  = 1; ;
            }
            else
            {
                LATDbits.LATD4  = 0; ;
            }
        }
    }
    else
    {
        if(USBDeviceState == DETACHED_STATE)
        {
            {LATBbits.LATB0  = 0; ;LATDbits.LATD4  = 0; ;} ;
        }
        else if(USBDeviceState == ATTACHED_STATE)
        {
            {LATBbits.LATB0  = 1; ;LATDbits.LATD4  = 1; ;} ;
        }
        else if(USBDeviceState == POWERED_STATE)
        {
            {LATBbits.LATB0  = 1; ;LATDbits.LATD4  = 0; ;} ;
        }
        else if(USBDeviceState == DEFAULT_STATE)
        {
            {LATBbits.LATB0  = 0; ;LATDbits.LATD4  = 1; ;} ;
        }
        else if(USBDeviceState == ADDRESS_STATE)
        {
            if(led_count == 0)
            {
                LATBbits.LATB0  = !LATBbits.LATB0 ; ;
                LATDbits.LATD4  = 0; ;
            }
        }
        else if(USBDeviceState == CONFIGURED_STATE)
        {
            if(led_count==0)
            {
                LATBbits.LATB0  = !LATBbits.LATB0 ; ;
                if(LATBbits.LATB0  )
                {
                    LATDbits.LATD4  = 0; ;
                }
                else
                {
                    LATDbits.LATD4  = 1; ;
                }
            }
        }
    }

}



























#line 736 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"
 
void USBCBSuspend(void)
{
	
	
	

	
	
	
	
	
	
	

	
	
	


   
}




#line 781 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"
 
void USBCBWakeFromSuspend(void)
{
	
	
	
	
	
	
	
	
	
    
}


#line 813 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"
 
void USBCB_SOF_Handler(void)
{
    
    

    if(msCounter != 0)
    {
        msCounter--;
    }
}


#line 841 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"
 
void USBCBErrorHandler(void)
{
    
    

	
	
	
	
	
	
	
	
	
	
	
	

	
	
}



#line 892 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"
 
void USBCBCheckOtherReq(void)
{
}



#line 916 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"
 
void USBCBStdSetDscHandler(void)
{
    
}



#line 942 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"
 
void USBCBInitEP(void)
{
    
    USBEnableEndpoint(1 ,0x04 |0x02 |0x10 |0x08 );

    
    USBRxHandle = USBTransferOnePacket(1 ,0 ,(BYTE*)&ReceivedDataBuffer,64) ;
}


#line 1038 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"
 
void USBCBSendResume(void)
{
    static WORD delay_count;
    
    
    
    
    
    
    
    
    
    
    if(RemoteWakeup  == TRUE) 
    {
        
        
        if(USBBusIsSuspended  == TRUE)
        {
            {PIE2bits.USBIE = 0;} ;
            
            
            USBCBWakeFromSuspend();
            UCONbits.SUSPND  = 0; 
            USBBusIsSuspended = FALSE;  
                                        

            
            
            
            
            
            
            delay_count = 3600U;        
            do
            {
                delay_count--;
            }while(delay_count);
            
            
            UCONbits.RESUME  = 1;       
            delay_count = 1800U;        
            do
            {
                delay_count--;
            }while(delay_count);
            UCONbits.RESUME  = 0;       

            {PIE2bits.USBIE = 1;} ;
        }
    }
}



#line 1113 "C:\Users\Pelle\Documents\Docus\Automan\Automation Project\Firmware\main.c"
 
BOOL USER_USB_CALLBACK_EVENT_HANDLER(int event, void *pdata, WORD size)
{
    switch( event )
    {
        case EVENT_TRANSFER:
            
            break;
        case EVENT_SOF:
            USBCB_SOF_Handler();
            break;
        case EVENT_SUSPEND:
            USBCBSuspend();
            break;
        case EVENT_RESUME:
            USBCBWakeFromSuspend();
            break;
        case EVENT_CONFIGURED:
            USBCBInitEP();
            break;
        case EVENT_SET_DESCRIPTOR:
            USBCBStdSetDscHandler();
            break;
        case EVENT_EP0_REQUEST:
            USBCBCheckOtherReq();
            break;
        case EVENT_BUS_ERROR:
            USBCBErrorHandler();
            break;
        case EVENT_TRANSFER_TERMINATED:
            
            
            
            
            
            
            
            
            break;
        default:
            break;
    }
    return TRUE;
}

