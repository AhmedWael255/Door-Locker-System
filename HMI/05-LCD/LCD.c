/*********************************/
/* Author   :   Spectrum         */
/* Date     :   13 Oct 2020      */
/* Version  :   V01              */
/*********************************/

#include "LCD.h"

#include <avr/delay.h>

#include "../01-GPIO/GPIO.h"


void LCD_init()
{
	GPIO_setPinDirection(ControlPort, RS, OUTPUT);
	GPIO_setPinDirection(ControlPort, RW, OUTPUT);
	GPIO_setPinDirection(ControlPort, EN, OUTPUT);

#if Data_Bit_Mode == 8
	GPIO_setPortDirection(DataPort,OUTPUT);
	LCD_sendCommand(LCD_8bit);

#elif Data_Bit_Mode == 4
	LCD_sendCommand(LCD_4bit);
	GPIO_setPinDirection(DataPort, DataPin, OUTPUT);
	GPIO_setPinDirection(DataPort, DataPin+1, OUTPUT);
	GPIO_setPinDirection(DataPort, DataPin+2, OUTPUT);
	GPIO_setPinDirection(DataPort, DataPin+3, OUTPUT);

	LCD_sendCommand(LCD_GO_TO_HOME);
#endif
	LCD_sendCommand(LCD_CURSOR_OFF);
	LCD_sendCommand(LCD_ClearScreen);
}

void LCD_sendCommand(u8 cmd)
{
	GPIO_writePin(ControlPort, RS, Low);
	GPIO_writePin(ControlPort, RW, Low);
	_delay_ms(1);
	GPIO_writePin(ControlPort, EN, High);
	_delay_ms(1);
	GPIO_writePort(DataPort, cmd);
	_delay_ms(1);
	GPIO_writePin(ControlPort, EN, Low);
	_delay_ms(1);
}

void LCD_DisplayCharacter(u8 ch)
{
	GPIO_writePin(ControlPort, RS, High);
	GPIO_writePin(ControlPort, RW, Low);
	_delay_ms(1);
	GPIO_writePin(ControlPort, EN, High);
	_delay_ms(1);
	GPIO_writePort(DataPort, ch);
	_delay_ms(1);
	GPIO_writePin(ControlPort, EN, Low);
	_delay_ms(1);
}

void LCD_Displaystring(const u8 *c)
{
	u8 i = 0;
	while(c[i] != '\0')
	{
		LCD_DisplayCharacter(c[i]);
		i++;
	}
}

void LCD_MoveCursor(u8 row, u8 col)
{
	u8 Mem_Adrs;
	switch(row)
	{
	case 0:
		Mem_Adrs = col;
		break;
	case 1:
		Mem_Adrs = col + 0x40;
		break;
	case 2:
		Mem_Adrs = col + 0x10;
		break;
	case 3:
		Mem_Adrs = col + 0x50;
		break;
	}
	LCD_sendCommand(Mem_Adrs | LCD_Cursor_Location);
}

void LCD_DispayStringRowColumn(const u8 * c, u8 row, u8 col)
{
	LCD_MoveCursor(row,col);
	LCD_Displaystring(c);
}

void LCD_Clear()
{
	LCD_sendCommand(LCD_ClearScreen);
}

void LCD_Int_to_Str(int data)
{
	u8 buffer[16];
	itoa(data,buffer,10);
	LCD_Displaystring(buffer);
}
