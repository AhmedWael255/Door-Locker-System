/*********************************/
/* Author   :   Spectrum         */
/* Date     :   20 Sep 2021      */
/* Version  :   V01              */
/*********************************/

#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_

#define TWDR		*((volatile unsigned char* const) 0x23)
#define TWAR		*((volatile unsigned char* const) 0x22)
#define TWSR		*((volatile unsigned char* const) 0x21)
#define TWBR		*((volatile unsigned char* const) 0x20)
#define TWCR		*((volatile unsigned char* const) 0x56)


/*TWCR PINS*/
#define TWIE		0
#define TWEN		2
#define	TWWC		3
#define TWSTO		4
#define TWSTA		5
#define TWEA		6
#define TWINT		7

/*TWAR PINS*/
#define TWGCE		0

#endif /* I2C_PRIVATE_H_ */
