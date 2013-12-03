Hallå!!! !!! !!!


// ************************************************************************************************
// Old Structs:
// ************************************************************************************************

typedef struct {
	unsigned char BYTES[64];
}USB_BUF;

// ************************************************************************************************

typedef union {
	struct {
		struct {
			unsigned ID:2;
			unsigned MTC_ERR:1;
			unsigned MTC_FPS:2;
			unsigned CMD:3;
		}PROP;
		unsigned long int MTC;
		unsigned char FLAG[3];
		unsigned char DATA[48];
	};
	unsigned char BYTES[64];
}USB_IN_BUF;

// ************************************************************************************************
// New Structs:
// ************************************************************************************************

typedef union {							// USB_IN_BUF - Host to Device data struct
	struct {							// 
		struct {						// CMD - Command struct
			unsigned CMD_GROUP:4;		// Commands belongs to different groups
			unsigned CMD:4;				// Command
		};								// CMD ?

		struct {						// MTC_PROP	- MTC Properties struct
			unsigned ID:2;				// Quarter frame ID.
			unsigned FPS:2;				// Frames pper Second ID
			unsigned :4;				//
			unsigned long int POS;		// 32 bit integer with time code position
		}MTC_PROP;

		struct {						// SSL_PROP - SSL Properties struct
			unsigned BANK_ID:4;			// Current SSL 8 channel bank in focus
			unsigned BANK_ID_CHANGE:1;	// Flag for change of bank
			unsigned :3;				
		}SSL_PROP;

		unsigned char SSL_DATA[48];		// 2 bytes data for each channel. 24 channels in one packet
		unsigned char MF_DATA[8];		// 2 bytes data ffor each channel. 4 channels in one packet
		
	};
	unsigned char BYTES[64];			// 64 bytes raw data
}USB_OUT_BUF;

// ************************************************************************************************
typedef union {							// USB_IN_BUF - Device to Host data struct
	struct {							// 
		struct {						// CMD - Command struct
			unsigned CMD_GROUP:4;		// Commands belongs to different groups
			unsigned CMD:4;				// Command
		};								// CMD ?

		struct {						// MTC_PROP	- MTC Properties struct
			unsigned ID:2;				// Quarter frame ID.
			unsigned FPS:2;				// Frames per Second ID
			unsigned RUN:1;				// RUN event flag
			unsigned STOP:1;			// STOP event flag
			unsigned JUMP:1;			// JUMP event flag
			unsigned :1;				// 
			unsigned long int POS;		// 32 bit integer with time code position
		}MTC_PROP;

		struct {						// Free bytes	
		unsigned char FREE_BYTES[1];	// Not used yet
		}FREE;

		unsigned char SSL_DATA[48];		// 2 bytes data for each channel. 24 channels in one packet
		unsigned char MF_DATA[8];		// 2 bytes data ffor each channel. 4 channels in one packet
		
	};
	unsigned char BYTES[64];			// 64 bytes raw data
}USB_IN_BUF;

// ************************************************************************************************