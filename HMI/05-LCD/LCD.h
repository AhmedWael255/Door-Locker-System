/*********************************/
/* Author   :   Spectrum         */
/* Date     :   20 Sep 2021      */
/* Version  :   V01              */
/*********************************/

#ifndef LCD_H_
#define LCD_H_

#include "../01-LIB/STD_Types.h"
#include "../01-GPIO/GPIO_private.h"

/*Modes of data only 4 or 8*/
#define Data_Bit_Mode	8

/*Define The control port (RW,RS,EN)
 * and Data port (dt0, dt1,....dt7)*/
#define ControlPort		C
#define DataPort		A

/*Control Port Pins*/
#define RS							(0)
#define RW							(1)
#define	EN							(2)

/*Data Port Pins
 * default is PIN0*/
#define DataPin						(0)

/* LCD Commands */
#define LCD_8bit					(0x38)
#define LCD_4bit					(0x28)
#define LCD_MoveRight				(0x1C)
#define LCD_MoveLeft				(0x18)
#define LCD_CursorRight			 	(0x14)
#define	LCD_CursorLeft				(0x10)
#define LCD_DispOFF					(0x08)
#define LCD_CURSOR_ON				(0x0E)
#define LCD_DispCrrsorONBlink		(0x0F)
#define LCD_DispONBlink				(0x0D)
#define LCD_CURSOR_OFF				(0x0C)
#define LCD_EntryDec				(0x04)
#define LCD_EntryDecShift			(0x05)
#define LCD_EntryInc				(0x06)
#define LCD_EntryIncShift			(0x07)
#define	LCD_Cursor_Location			(0x80)
#define LCD_ClearScreen				(0x01)
#define LCD_EntryMode				(0x06)
#define LCD_GO_TO_HOME              (0x02)

/*Functions*/
void LCD_init();
void LCD_sendCommand(u8 cmd);
void LCD_DisplayCharacter(u8 c);
void LCD_Displaystring(const u8 *c);
void LCD_MoveCursor(u8 row, u8 col);
void LCD_DispayStringRowColumn(const u8 * c, u8 row, u8 col);
void LCD_Clear();
void LCD_Int_to_Str(int data);


#endif /* 03_HAL_LCD_LCD_H_ */
