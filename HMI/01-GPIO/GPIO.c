/*********************************/
/* Author   :   Spectrum         */
/* Date     :   13 Oct 2020      */
/* Version  :   V01              */
/*********************************/

#include "../01-GPIO/GPIO.h"

#include "../01-GPIO/GPIO_private.h"
#include "../01-LIB/BIT_Math.h"

void GPIO_setPinDirection(GPIO_PORT port, u8 pin, GPIO_directionType direction)
{
	/*Check that number of ports doesnt exceed NUM_OF_PORTS*/
	if((pin < NUM_OF_PINS_PER_PORT) || (port < NUM_OF_PORTS))
	{

		/* Setup the pin direction as required */
		switch(port)
		{
		case A:
			if(direction == OUTPUT)
			{
				SET_Bit(DDRA,pin);
			}
			else
			{
				CLR_Bit(DDRA,pin);
			}
			break;
		case B:
			if(direction == OUTPUT)
			{
				SET_Bit(DDRB,pin);
			}
			else
			{
				CLR_Bit(DDRB,pin);
			}
			break;
		case C:
			if(direction == OUTPUT)
			{
				SET_Bit(DDRC,pin);
			}
			else
			{
				CLR_Bit(DDRC,pin);
			}
			break;
		case D:
			if(direction == OUTPUT)
			{
				SET_Bit(DDRD,pin);
			}
			else
			{
				CLR_Bit(DDRD,pin);
			}
			break;
		}
	}
}

void GPIO_writePin(GPIO_PORT port, u8 pin, u8 value)
{
	/*Check that number of ports doesnt exceed NUM_OF_PORTS*/
	if((pin < NUM_OF_PINS_PER_PORT) || (port < NUM_OF_PORTS))
	{
		/* Write the pin value as required */
		switch(port)
		{
		case A:
			if(value == High)
			{
				SET_Bit(PORTA,pin);
			}
			else
			{
				CLR_Bit(PORTA,pin);
			}
			break;
		case B:
			if(value == High)
			{
				SET_Bit(PORTB,pin);
			}
			else
			{
				CLR_Bit(PORTB,pin);
			}
			break;
		case C:
			if(value == High)
			{
				SET_Bit(PORTC,pin);
			}
			else
			{
				CLR_Bit(PORTC,pin);
			}
			break;
		case D:
			if(value == High)
			{
				SET_Bit(PORTD,pin);
			}
			else
			{
				CLR_Bit(PORTD,pin);
			}
			break;
		}
	}
}

u8 GPIO_readPin(GPIO_PORT port, u8 pin)
{
	u8 pin_value = Low;

	/*Check that number of ports doesnt exceed NUM_OF_PORTS*/
	if((pin < NUM_OF_PINS_PER_PORT) || (port < NUM_OF_PORTS))
	{
		/* Read the pin value as required */
		switch(port)
		{
		case A:
			if(isSET(PINA,pin))
			{
				pin_value = High;
			}
			else
			{
				pin_value = Low;
			}
			break;
		case B:
			if(isSET(PINB,pin))
			{
				pin_value = High;
			}
			else
			{
				pin_value = Low;
			}
			break;
		case C:
			if(isSET(PINC,pin))
			{
				pin_value = High;
			}
			else
			{
				pin_value = Low;
			}
			break;
		case D:
			if(isSET(PIND,pin))
			{
				pin_value = High;
			}
			else
			{
				pin_value = Low;
			}
			break;
		}
	}

	return pin_value;
}

void GPIO_setPortDirection(GPIO_PORT port, GPIO_PortdirectionType direction)
{
	/*Check that number of ports doesn't exceed NUM_OF_PORTS*/
	if(port < NUM_OF_PORTS)
	{
		/* Setup the port direction as required */
		switch(port)
		{
		case A:
			DDRA = direction;
			break;
		case B:
			DDRB = direction;
			break;
		case C:
			DDRC = direction;
			break;
		case D:
			DDRD = direction;
			break;
		}
	}
}

void GPIO_writePort(GPIO_PORT port, u8 value)
{
	/*Check that number of ports doesnt exceed NUM_OF_PORTS*/
	if(port < NUM_OF_PORTS)
	{
		/* Write the port value as required */
		switch(port)
		{
		case A:
			PORTA = value;
			break;
		case B:
			PORTB = value;
			break;
		case C:
			PORTC = value;
			break;
		case D:
			PORTD = value;
			break;
		}
	}
}

u8 GPIO_readPort(GPIO_PORT port)
{
	u8 value = Low;

	/*Check that number of ports doesnt exceed NUM_OF_PORTS*/
	if(port < NUM_OF_PORTS)
	{
		/* Read the port value as required */
		switch(port)
		{
		case A:
			value = PINA;
			break;
		case B:
			value = PINB;
			break;
		case C:
			value = PINC;
			break;
		case D:
			value = PIND;
			break;
		}
	}

	return value;
}
