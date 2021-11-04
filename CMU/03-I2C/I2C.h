/*********************************/
/* Author   :   Spectrum         */
/* Date     :   20 Sep 2021      */
/* Version  :   V01              */
/*********************************/

#ifndef I2C_H_
#define I2C_H_

#include "../01-LIB/STD_Types.h"

#define SLAVE_ADDRESS		0x02
#define TWI_CLOCK			0x02

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SWrite_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SRead_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */


void TWI_Init(void);
void TWI_Start(void);
void TWI_Stop(void);
void TWI_Write(u8 data);
u8 TWI_readWithACK(void);
u8 TWI_readWithNACK(void);
u8 TWI_getStatus(void);

#endif /* 02_MCAL_I2C_I2C_H_ */
