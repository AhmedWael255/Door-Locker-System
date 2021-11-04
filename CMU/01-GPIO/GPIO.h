/*********************************/
/* Author   :   Spectrum         */
/* Date     :   20 Sep 2021      */
/* Version  :   V01              */
/*********************************/

#ifndef GPIO_H_
#define GPIO_H_

#include "../01-LIB/STD_Types.h"
#include "GPIO_private.h"

typedef enum	{INPUT,OUTPUT} GPIO_directionType;
typedef enum	{A, B, C, D} GPIO_PORT;


/*Set the PIN Direction to either INPUT or OUTPUT*/
void GPIO_setPinDirection(GPIO_PORT port, u8 pin, GPIO_directionType direction);


/*Write the value on PIN either Logic HIGH or Logic LOW*/
void GPIO_writePin(GPIO_PORT port, u8 pin, u8 value);

/*Read the value of the PIN*/
u8 GPIO_readPin(GPIO_PORT port, u8 pin);

/*Set all the PORT Direction to either INPUT or OUTPUT*/
void GPIO_setPortDirection(GPIO_PORT port, GPIO_directionType direction);

/*Write the value on all PORT either Logic HIGH or Logic LOW*/
void GPIO_writePort(GPIO_PORT port, u8 value);

/*Read the value on all PORT */
u8 GPIO_readPort(GPIO_PORT port);

#endif /* 02_MCAL_GPIO_GPIO_H_ */
