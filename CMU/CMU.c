/*********************************/
/* Author   :   Spectrum         */
/* Date     :   21 Oct 2021      */
/* Version  :   V01              */
/*********************************/

#include "CMU.h"
#include "02-DC Motor/DC_Motor.h"
#include "03-I2C/I2C.h"
#include "03-EEPROM_External/EEPROM.h"
#include "04-TMR0/TMR0.h"
#include "05-UART/UART.h"
#include "08-Buzzer/Buzzer.h"
#include <avr/delay.h>

/*	Variables	*/
u8 RecievedData, ChkRecievedData;
u16 EEPROM_Address = EEPROM_BASE_ADDRESS;


/*Description:
 * Opens the Motor with 25% Clockwise for 1 Second then
 * Motor Stops for 3 Seconds then
 * Motor Starts with 25% Counter Clockwise for 1 Second.
 * */
void Open_Door(void)
{
	/*Start Motor Clockwise.*/
	  DC_Motor_Rotate(CW,25);
	  _delay_ms(1000);

	  /*Stop Motor.*/
	  DC_Motor_Stop();
	  _delay_ms(3000);

	  /*Start Motor Counter Clockwise.*/
	  DC_Motor_Rotate(CCW, 25);
	  _delay_ms(1000);

	  /*Stop Motor.*/
	  DC_Motor_Stop();
}

/*Description:
 *Buzzer start to alert for 2 seconds then stops.
 * */
void Start_Buzzer(void)
{
	_delay_ms(300);

	/*Buzzer Start.*/
	Buzzer_ON();
	_delay_ms(2000);

	/*Buzzer Stop.*/
	Buzzer_OFF();
}

/*Description:
 * Initialize the Main Modules which are
 * Buzzer, UART, DC Motor and I2C
 * And Displays a Message after Initialization.
 */
void Init_Modules(void)
{
	/*Initialize UART with Baud Rate 9600.*/
	UART_init(9600);

	/*Initialize Buzzer.*/
	Buzzer_Init();

	/*Initialize DC Motor.*/
	DC_Motor_Init();

	/*Initialize I2C with F_CPU/8 Clock.*/
	TWI_Init();
}

/*Description:
 * Receives Password from MC1 then Checks it with the
 * Password saved on the EEPROM and if its correct then
 * send a message which says its correct and if its
 * wrong then send a message which says its wrong.
 */
void Check_Password(void)
{
	/*Define EEPROM Address as the Base Address.*/
  EEPROM_Address = EEPROM_BASE_ADDRESS;
  u8 i = 0, flag = 0;

  while(i < PasswordSize)
  {
	  /*Receive a Byte and Check it. */
	  ChkRecievedData = UART_recieveData();

	  /*Read a Byte from EEPROM to check if its right.*/
	  EEPROM_ReadData(EEPROM_Address, RecievedData);

	  /*If a Byte is wrong then Set flag to 1.*/
	  if(RecievedData != ChkRecievedData)
		flag = 1;

	  /*Increase the Index of each byte.*/
	  i++;
	  EEPROM_Address++;
  }

  /*if flag is zero this indicates that no byte is different than the byte in EEPROM
   * then Send Correct message.
   * otherwise send Wrong Message.
   * */
  if(flag == 0)
  {
	  UART_sendData(Correct);
  }

  else
  {
	  UART_sendData(Wrong);
  }

}

/*Description:
 *Receives the Password from MC1 and Saves it in the EEPROM.
 */
void Set_Password(void)
{
  u8 i = 0;
  while(i < PasswordSize)
  {
	  /*Receive a Byte and Check it. */
	  RecievedData = UART_recieveData();
	  /*Write this byte in the EEPROM*/
	  EEPROM_writeData(EEPROM_Address, RecievedData);

	  /*Increase the Index of each byte.*/
	  i++;
	  EEPROM_Address++;
  }
}

/*Description:
 *Receives an action either to change password or open the door
 *this function send ACK in the two options which indicates that
 *UART is Ready for data.
 *If Status is to Change Password then Call the Set_Password Function.
 *If Status is to Open Door then if Password if Correct then it call Open_Door() Function.
 *If Password is Wrong for three times then Call Start_Buzzer() function.
 */
void Recieve_Action(void)
{
	/*Receive the needed Status*/
	u8 CheckStatus = UART_recieveData();

	if(CheckStatus == ChangePW)
	{
		/*if status is Change Password then Send ACK*/
		UART_sendData(Ready);

		/*Call the Set_Password Function to change password*/
		Set_Password();
	}

	else if(CheckStatus == DoorAction)
	{
		/*if status is Opening Door then Send ACK*/
		UART_sendData(Ready);

		/*Call the Check_Password Function to check password*/
		Check_Password();

		/*Receive the needed status for opening the door*/
		u8 CheckAction = UART_recieveData();

		if(CheckAction == OpenDoor)
		{
			/*If the Password is correct then Open the Door*/
			Open_Door();
		}

		else if(CheckAction == OpenBuzzer)
		{
			/*If the Password is Wrong then Start Buzzer*/
			Start_Buzzer();
		}
	}

}







