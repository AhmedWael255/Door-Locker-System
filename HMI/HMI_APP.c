/*********************************/
/* Author   :   Spectrum         */
/* Date     :   21 Oct 2021      */
/* Version  :   V01              */
/*********************************/


/********************************
 * 			HMI ECU				*
 ********************************/

#include "HMI.h"
#include "01-LIB/STD_Types.h"
#include "05-UART/UART.h"

u8 Status;

int main()
{

	/*Description:
	 * Initialize the Main Modules which are
	 * LCD and UART
	 */
	Init_Modules();

	/*Check the last status of the ECU */
	Status = UART_recieveData();

	while(1)
	{
		/*Check the First Status of the MCU then Apply Action*/
		switch(Status)
		{
		/*If its first time then Enter Password and save it*/
		case Idle:
			UART_sendData(Status);
			Enter_Password();
			break;

		/*If its not the first time then enter password to check it
		 * if its right then Display Main Menu
		 * if its wrong then enter again
		 * if its wrong for three times then Change Status to Warning*/
		case Active:
			UART_sendData(Status);
			Check_Password();
			break;

		/*If Status is Main Menu then Display it*/
		case MainMenu:
			Display_Menu();
			break;

		/*If Password is entered wrong for three times then Lock the System*/
		case Warning:
			UART_sendData(ActionBuzzer);
			Display_Thief();
			break;

		/*If Password is right then Open the Door*/
		case Door:
			UART_sendData(ActionDoor);
			Open_Door();
			break;

		}
	}
	return 0;
}
