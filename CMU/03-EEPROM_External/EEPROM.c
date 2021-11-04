/*********************************/
/* Author   :   Spectrum         */
/* Date     :   20 Sep 2021      */
/* Version  :   V01              */
/*********************************/

#include "EEPROM.h"
#include "../03-I2C/I2C.h"

u8 EEPROM_writeData(u16 Copy_u16Address, u8 Copy_u8Data)
{
	/*Start bit of the I2C and Check if TWI status is Ready
	 * Slave Sends ACK*/
	TWI_Start();
	if(TWI_getStatus() != TWI_START)
	{
		return Error;
	}

	/*Write the Slave Address and Check if TWI status is Ready
	 *Slave Sends ACK*/
	TWI_Write((u8)(0xA0 | ((Copy_u16Address & 0x0700)>>7)));
	if(TWI_getStatus() != TWI_MT_SWrite_ACK)
	{
		return Error;
	}

	/*Write the Memory Address and Check if TWI status is Ready
	 *Slave Sends ACK*/
	TWI_Write(Copy_u16Address);
	if(TWI_getStatus() != TWI_MT_DATA_ACK)
	{
		return Error;
	}

	/*Write the Data to the Memory and Check if TWI status is Ready
	 *Slave Sends ACK*/
	TWI_Write(Copy_u8Data);
	if(TWI_getStatus() != TWI_MT_DATA_ACK)
	{
		return Error;
	}

	/*TWI Stop Bit*/
	TWI_Stop();
	return NoError;
}

u8 EEPROM_ReadData(u16 Copy_u16Address, u8* Copy_u8Data)
{
	/*Start bit of the I2C and Check if TWI status is Ready
	 * Slave Sends ACK*/
	TWI_Start();
	if(TWI_getStatus() != TWI_START)
	{
		return Error;
	}

	/*Write the Slave Address and Check if TWI status is Ready
	 *Slave Sends ACK*/
	TWI_Write((u8)(0xA0 | ((Copy_u16Address & 0x0700)>>7)));
	if(TWI_getStatus() != TWI_MT_SWrite_ACK)
	{
		return Error;
	}

	/*Write the Memory Address and Check if TWI status is Ready
	 *Slave Sends ACK*/
	TWI_Write(Copy_u16Address);
	if(TWI_getStatus() != TWI_MT_DATA_ACK)
	{
		return Error;
	}

	/*Restart bit of the I2C and Check if TWI status is Ready
	 * Slave Sends ACK
	 * Now make master Reads data*/
	TWI_Start();
	if(TWI_getStatus() != TWI_START)
	{
		return Error;
	}

	/*Read Data From Memory and Check if TWI status is Ready*/
	Copy_u8Data = TWI_readWithNACK();
	if(TWI_getStatus() != TWI_MR_DATA_NACK)
	{
		return Error;
	}

	/*TWI Stop Bit*/
	TWI_Stop();
	return NoError;
}

