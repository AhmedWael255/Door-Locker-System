/*********************************/
/* Author   :   Spectrum         */
/* Date     :   21 Oct 2021      */
/* Version  :   V01              */
/*********************************/


#include "Buzzer.h"

#include "../01-GPIO/GPIO.h"

/*Descriptions:
 * Initialize the Direction of the Ports in which the Buzzer is Inserted
 * and Setting the Pins to Low
 * */

void Buzzer_Init(void)
{
	GPIO_setPinDirection(BuzzerPort, Buzzer_First_Pin, OUTPUT);
	GPIO_setPinDirection(BuzzerPort, Buzzer_Second_Pin, OUTPUT);
	GPIO_writePin(BuzzerPort, Buzzer_First_Pin, Low);
	GPIO_writePin(BuzzerPort, Buzzer_Second_Pin, Low);
}

/*Descriptions:
 * Setting the Pins to High to Start the Buzzer
 * */

void Buzzer_ON(void)
{
	GPIO_writePin(BuzzerPort, Buzzer_First_Pin, High);
	GPIO_writePin(BuzzerPort, Buzzer_Second_Pin, High);
}

/*Descriptions:
 * Setting the Pins to Low to Stop the Buzzer
 * */

void Buzzer_OFF(void)
{
	GPIO_writePin(BuzzerPort, Buzzer_First_Pin, Low);
	GPIO_writePin(BuzzerPort, Buzzer_Second_Pin, Low);
}
