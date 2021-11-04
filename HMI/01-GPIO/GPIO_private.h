/*********************************/
/* Author   :   Spectrum         */
/* Date     :   13 Oct 2020      */
/* Version  :   V01              */
/*********************************/

#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_

/**********************************************************************
 *                   Registers PORTS and PINS                         *
 *********************************************************************/
#define NUM_OF_PORTS           4
#define NUM_OF_PINS_PER_PORT   8

#define PORTA 		*((volatile unsigned char* const) 0x3B)
#define DDRA 		*((volatile unsigned char* const) 0x3A)
#define PINA 		*((volatile unsigned char* const) 0x39)
#define PORTB 		*((volatile unsigned char* const) 0x38)
#define DDRB 		*((volatile unsigned char* const) 0x37)
#define PINB 		*((volatile unsigned char* const) 0x36)
#define PORTC 		*((volatile unsigned char* const) 0x35)
#define DDRC		*((volatile unsigned char* const) 0x34)
#define PINC		*((volatile unsigned char* const) 0x33)
#define PORTD		*((volatile unsigned char* const) 0x32)
#define DDRD		*((volatile unsigned char* const) 0x31)
#define PIND		*((volatile unsigned char* const) 0x30)

#define PIN0	               0
#define PIN1	               1
#define PIN2	               2
#define PIN3	               3
#define PIN4	               4
#define PIN5	               5
#define PIN6	               6
#define PIN7	               7

#endif /* GPIO_GPIO_PRIVATE_H_ */
