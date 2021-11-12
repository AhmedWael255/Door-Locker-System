/*********************************/
/* Author   :   Spectrum         */
/* Date     :   21 Oct 2021      */
/* Version  :   V01              */
/*********************************/

/****************************
 * 			CMU ECU			*
 ****************************/

#include "CMU.h"
#include "01-LIB/STD_Types.h"
#include "03-EEPROM_External/EEPROM.h"
#include "05-UART/UART.h"

u8 Status;

int main()
{


	/*Description:
	 * Initialize the Main Modules which are
	 * Buzzer, UART, DC Motor and EEPROM
	 * And Displays a Message after Initialization
	 */
	Init_Modules();

	/*Check the last saved Status of the ECU
	 * in the EEPROM and Send if to the HMI ECU
	 * */
	u8 Status_Address = EEPROM_STATUS_ADDRESS;
	EEPROM_ReadData(Status_Address, &Status);

	UART_sendData(Status);

	while(1)
	{
		/*Wait for checking the current status of the ECU*/
		Status = UART_recieveData();

		switch(Status)
		{
		/*If its the first time then save te Password in the EEPROM*/
		case Idle:
			Set_Password();
			break;

		/*If its not the first time then check the entered password*/
		case Active:
			Check_Password();
			break;

		/*If Password was entered three times wrong then Open Buzzer and mock the system*/
		case ActionBuzzer:
			/*If the Password is Wrong then Start Buzzer*/
			Start_Buzzer();
			break;

		/*If password was right then Open the door*/
		case ActionDoor:
			/*If the Password is correct then Open the Door*/
			Check_Password();
			break;
		}
	}

	return 0;
}
