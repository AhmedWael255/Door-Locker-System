/*********************************/
/* Author   :   Spectrum         */
/* Date     :   13 Oct 2020      */
/* Version  :   V01              */
/*********************************/

#include "Keypad.h"
#include "../01-LIB/STD_Types.h"
#include "../01-GPIO/GPIO.h"

/*if required keypad is 4x4 then define Keypad_4x4Config function*/
#if KEYPAD_Columns == 4
	static u8 Keypad_4x4Config(u8 btn);

/*if required keypad is 4x3 then define Keypad_4x3Config function*/
#elif KEYPAD_Columns == 3
	static u8 Keypad_4x3Config(u8 btn);
#endif

u8 KEYPAD_getPressedKey(void)
{
	while(1)
	{
		for(u8 col = 0; col < KEYPAD_Columns; col++)
		{
			/*Each time the iteration occurs the Specified Column PIN
			 * will be output and all the rest pin are inputs*/
			GPIO_setPortDirection(KEYPAD_Port, INPUT_PORT);
			GPIO_setPinDirection(KEYPAD_Port, col+KEYPAD_FirstColPin, OUTPUT);

			/*Check if the Keypad is LOGIC LOW connected or LOGIC HIGH*/
			#if KEYPAD_BUTTON_PRESSED == Low
					u8 value = ~(1 << (col+KEYPAD_FirstColPin));
			#else
					u8 value =  (1 << (col+KEYPAD_FirstColPin));
			#endif
			/*Then write the value of Specified pin*/
			GPIO_writePort(KEYPAD_Port, value);

			/*Loop on each row to specify which input pin have zero logic then its the pressed key*/
			for(u8 row = 0; row < KEYPAD_Rows; row++)
			{
				if(GPIO_readPin(KEYPAD_Port, row+KEYPAD_FisrtRowPin) == KEYPAD_BUTTON_PRESSED)
				{
					/*Check weather keypad is 4x4 or 4x3 then convert its value correctly*/
					#if KEYPAD_Columns == 4
						return Keypad_4x4Config((row*KEYPAD_Columns)+col+1);
					#elif KEYPAD_Columns == 3
						return Keypad_4x3Config((row*KEYPAD_Columns)+col+1);
					#endif
				}
			}
		}
	}
}


/*Configure Keypad Output if it 4x3 */
#if KEYPAD_Columns == 3

	static u8 Keypad_4x3Config(u8 btn)
	{
		u8 replace_btn = 0;
		switch(btn)
		{
			case 10: replace_btn = '*'; // ASCII Code of *
					 break;
			case 11: replace_btn = 0;
					 break;
			case 12: replace_btn = '#'; // ASCII Code of #
					 break;
			default: replace_btn = btn;
					break;
		}
		return replace_btn;
	}

/*Configure Keypad Output if it 4x3 */
#elif KEYPAD_Columns == 4

	static u8 Keypad_4x4Config(u8 btn)
	{
		u8 replace_btn = 0;
		switch(btn)
		{
			case 1: replace_btn = 7;
					break;
			case 2: replace_btn = 8;
					break;
			case 3: replace_btn = 9;
					break;
			case 4: replace_btn = '%'; // ASCII Code of %
					break;
			case 5: replace_btn = 4;
					break;
			case 6: replace_btn = 5;
					break;
			case 7: replace_btn = 6;
					break;
			case 8: replace_btn = '*'; /* ASCII Code of '*' */
					break;
			case 9: replace_btn = 1;
					break;
			case 10: replace_btn = 2;
					break;
			case 11: replace_btn = 3;
					break;
			case 12: replace_btn = '-'; /* ASCII Code of '-' */
					break;
			case 13: replace_btn = 13;  /* ASCII of Enter */
					break;
			case 14: replace_btn = 0;
					break;
			case 15: replace_btn = '='; /* ASCII Code of '=' */
					break;
			case 16: replace_btn = '+'; /* ASCII Code of '+' */
					break;
			default: replace_btn = btn;
					break;
		}
		return replace_btn;
	}
#endif
