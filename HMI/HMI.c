/*********************************/
/* Author   :   Spectrum         */
/* Date     :   21 Oct 2021      */
/* Version  :   V01              */
/*********************************/

#include "HMI.h"
#include "04-Keypad/keypad.h"
#include "05-LCD/LCD.h"
#include "05-UART/UART.h"
#include <avr/delay.h>

/*	Variables	*/
u8 key, cnt = 0;
u8 Password[5];
u8 Status;
u8 cntWrong = 0;

void Init_Modules(void) {
	/*Initialize the LCD.*/
	LCD_init();

	/*Initialize UART with Baud Rate 9600.*/
	UART_init(9600);
}

void Display_Menu(void) {
	/*Clear the Screen*/
	LCD_Clear();
	LCD_Displaystring("+: Open Door");

	/*Type in a fixed Position*/
	LCD_DispayStringRowColumn("-: Change Password", 1, 0);

	/*Select the Pressed key*/
	key = KEYPAD_getPressedKey();
	if (key == '+') {
		/*If + call the Open_Door function*/
		Status = Door;
	}

	else if (key == '-') {
		/*If - call the Change_Password function*/
		Status = Idle;
	}
	_delay_ms(500);
}

void Enter_Password(void) {
	if (cnt == 1)
	{
		LCD_Clear();
		LCD_Displaystring("Re-Enter Password");
		cnt = 0;
	}
	else
	{
		LCD_Clear();
		LCD_Displaystring("Enter Password");
		cnt++;
	}

	u8 i = 0;
	while (i < PasswordSize) {
		/*Select the Pressed key*/
		key = KEYPAD_getPressedKey();
		if (key >= 0 && key <= 9) {
			/*Display the Password as **/
			LCD_MoveCursor(1, i);
			LCD_DisplayCharacter('*');

			/*Send the Pressed Key to MC2 to save it*/
			UART_sendData(key);
			i++;
		}
		_delay_ms(500);
	}

	Status = Active;
}

void Check_Password(void) {

	Enter_Password();

	/*Wait to check if password is correct or wrong*/
	u8 CheckPassword = UART_recieveData();

	if (CheckPassword == Wrong) {
		/*if its wrong then number of tries decreased by one*/
		cntWrong++;
		LCD_Clear();

		/*Display Wrong Password*/
		LCD_Displaystring("Wrong Password");
		_delay_ms(500);
	}

	else if (CheckPassword == Correct) {
		cntWrong = 0;
		/*If Password is correct then send MC2 a message to open the door*/
		LCD_Clear();
		LCD_Displaystring("Welcome");

		_delay_ms(1000);

		/*Return to the Main Menu*/
		Status = MainMenu;
	}

	if (cntWrong == NO_OF_TRIAL)
		Status = Warning;
}

void Open_Door(void) {
	Enter_Password();

	/*Wait to check if password is correct or wrong*/
	u8 CheckPassword = UART_recieveData();

	if (CheckPassword == Wrong) {
		/*if its wrong then number of tries decreased by one*/
		cntWrong++;
		LCD_Clear();

		/*Display Wrong Password*/
		LCD_Displaystring("Wrong Password");
		_delay_ms(500);
	}

	else if (CheckPassword == Correct) {
		/*If Password is correct then send MC2 a message to open the door*/
		LCD_Clear();
		LCD_Displaystring("Opening...");

		_delay_ms(5500);

		/*Return to the Main Menu*/
		Status = MainMenu;
	}

	if (cntWrong == NO_OF_TRIAL)
		Status = Warning;
}

void Display_Thief(void) {

	/*If number of tries reaches its maximum then Display a message that system is locked*/
	LCD_Clear();
	LCD_Displaystring("System is Locked");
	_delay_ms(3000);
}
