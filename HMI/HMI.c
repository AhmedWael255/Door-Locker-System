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
u8 key;
u8 Password[5];

/*Description:
 * Initialize the Main Modules which are
 * LCD and UART
 * And Displays a Message after Initialization.
 */
void Init_Modules(void)
{
	/*Initialize the LCD.*/
	LCD_init();

	/*Initialize UART with Baud Rate 9600.*/
	UART_init(9600);

	/*Display a String on the LCD.*/
	LCD_Displaystring("Enter Password:");
}

/*Description:
 * Function that Displays the Options Menu which is:
 * Open Door or Change Password.
 */
void Display_Menu(void)
{
	/*Clear the Screen*/
	LCD_Clear();
	LCD_Displaystring("+: Open Door");

	/*Type in a fixed Position*/
	LCD_MoveCursor(1,0);
	LCD_Displaystring("-: Change Password");

	/*Call the Mack Action Function to let user choose either + or -
	 * as displayed above.*/
	Make_Action();
}

/*Description:
 * Function that waits for writing the new password at the first
 * time then sends it to the MC2.
 */
void Enter_Password(void)
{
	u8 i = 0;
	while(i < PasswordSize)
	{
		/*Select the Pressed key*/
		key = KEYPAD_getPressedKey();
		if(key >= 0 && key <= 9)
		{
			/*Display the PAssword as **/
			LCD_MoveCursor(1,i);
			LCD_DisplayCharacter('*');

			/*Send the Pressed Key to MC2 to save it*/
			UART_sendData(key);
			i++;
		}
		_delay_ms(500);
	}
}

/*Description:
 * Get the Pressed key which is only + or - to take action,
 * Either + to Open the Door or - to Change Password.
 * */
void Make_Action(void)
{
	/*Select the Pressed key*/
	key = KEYPAD_getPressedKey();
	if(key == '+')
	{
		/*If + call the Open_Door function*/
		Open_Door();
	}

	else if (key == '-')
	{
		/*If - call the Change_Password function*/
		Change_Password();
	}
	_delay_ms(500);
}

/*Description:
 * Sends Message to MC2 to inform that user wants to change Password and wait for ACK,
 * then let user enters the new password then displays the Main Menu that display options.
 * */
void Change_Password(void)
{
	/*Informs MC2 that user will change Password*/
	UART_sendData(ChangePW);

	/*Waits for MC2 ACK*/
	while(UART_recieveData() != Ready);

	/*Let User enter the New Password*/
	LCD_Clear();
	LCD_Displaystring("Enter new Password:");
	Enter_Password();

	/*Display the Options Menu */
	Display_Menu();
}

/*Description:
 * Sends Message to MC2 to inform that user wants to Open the Door and wait for ACK,
 * then let user enters the password.
 * if password is correct then send MC2 message to open the door
 * if password is wrong then the user will try for another two times,
 * if its wrong for the three times then LCD displays message that System is Locked
 * */
void Open_Door(void)
{
	u8 j = 0, flag = 0;

	/*Informs MC2 that user will Open the Door*/
	UART_sendData(DoorAction);

	/*Waits for MC2 ACK*/
	while(UART_recieveData() != Ready);

	while(j < NO_OF_TRIAL && flag == 0)
	{
		/*Let User enter the Password*/
		LCD_Clear();
		LCD_Displaystring("Enter Password:");
		Enter_Password();

		/*Wait to check if password is correct or wrong*/
		u8 CheckPassword = UART_recieveData();

		if(CheckPassword == Wrong)
		{
			/*if its wrong then number of tries decreased by one*/
			j++;
			LCD_Clear();

			/*Display Wrong Password*/
			LCD_Displaystring("Wrong Password");
			_delay_ms(500);
		}

		else if(CheckPassword == Correct)
		{
			/*If Password is correct then send MC2 a message to open the door*/
			flag = 1;
			LCD_Clear();
			LCD_Displaystring("Opening...");

			/*Send message to open the door*/
			UART_sendData(OpenDoor);
			_delay_ms(5500);

			/*Return to the Main Menu*/
			Display_Menu();
		}
	}

	if(j == NO_OF_TRIAL && flag == 0)
	{
		/*If number of tries reaches its maximum then Display a message that system is locked*/
		LCD_Clear();
		LCD_Displaystring("System is Locked");
	}
}

