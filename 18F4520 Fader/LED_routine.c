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
	if(AttentionFlag)
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