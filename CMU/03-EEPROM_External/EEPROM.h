/*********************************/
/* Author   :   Spectrum         */
/* Date     :   20 Sep 2021      */
/* Version  :   V01              */
/*********************************/

#ifndef EEPROM_H_
#define EEPROM_H_

#include "../01-LIB/STD_Types.h"


u8 EEPROM_writeData(u16 Copy_u16Address, u8 Copy_u8Data);
u8 EEPROM_ReadData(u16 Copy_u16Address, u8* Copy_u8Data);

#endif /* EEPROM_H_ */
