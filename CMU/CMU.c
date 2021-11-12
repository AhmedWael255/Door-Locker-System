/*********************************/
/* Author   :   Spectrum         */
/* Date     :   21 Oct 2021      */
/* Version  :   V01              */
/*********************************/

#include "CMU.h"
#include "01-LIB/STD_Types.h"
#include "02-DC Motor/DC_Motor.h"
#include "03-EEPROM_External/EEPROM.h"
#include "04-TMR0/TMR0.h"
#include "05-UART/UART.h"
#include "08-Buzzer/Buzzer.h"
#include <avr/delay.h>

u8 Status;

/*	Variables	*/
u8 Saved_Password, ChkRecievedData;
u16 EEPROM_Address = EEPROM_BASE_ADDRESS;
u8 Status_Address = EEPROM_STATUS_ADDRESS;

void Open_Door(void)
{
	  _delay_ms(500);
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

void Start_Buzzer(void)
{
	_delay_ms(300);

	/*Buzzer Start.*/
	Buzzer_ON();
	_delay_ms(2000);

	/*Buzzer Stop.*/
	Buzzer_OFF();
}

void Init_Modules(void)
{
	/*Initialize UART with Baud Rate 9600.*/
	UART_init(9600);

	/*Initialize Buzzer.*/
	Buzzer_Init();

	/*Initialize DC Motor.*/
	DC_Motor_Init();

	/*Initialize EEPROM.*/
	EEPROM_Init();
}

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
	  EEPROM_ReadData(EEPROM_Address, &Saved_Password);

	  /*If a Byte is wrong then Set flag to 1.*/
	  if(Saved_Password != ChkRecievedData)
		flag = 1;

	  /*Increase the Index of each byte.*/
	  i++;
	  EEPROM_Address++;
  }


  if(flag == 0)
  {
	  UART_sendData(Correct);
	  if(Status == ActionDoor)
		  Open_Door();
  }

  else
  {
	  UART_sendData(Wrong);
  }

}

void Set_Password(void)
{
  u8 i = 0;
  while(i < PasswordSize)
  {
	  /*Receive a Byte and Check it. */
	  Saved_Password = UART_recieveData();
	  /*Write this byte in the EEPROM*/
	  EEPROM_writeData(EEPROM_Address, Saved_Password);

	  /*Increase the Index of each byte.*/
	  i++;
	  EEPROM_Address++;
  }

  Status = Active;
  EEPROM_writeData(Status_Address, Active);
}








