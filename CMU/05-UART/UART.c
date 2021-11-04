/*********************************/
/* Author   :   Spectrum         */
/* Date     :   20 Sep 2021      */
/* Version  :   V01              */
/*********************************/


#include "../05-UART/UART.h"

#include "../01-LIB/BIT_Math.h"
#include "../01-LIB/STD_Types.h"
#include <avr/io.h>

void UART_init(u32 baud_rate)
{
	u16 ubrrVal = 0;

	/* U2X = 1 for double transmission speed */
	UCSRA = (1<<U2X);

	/************************** UCSRB Description **************************
	 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART TX Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * UCSZ2 = 0 For 8-bit data mode
	 * RXB8 & TXB8 not used for 8-bit data mode
	 ***********************************************************************/
	UCSRB = (1<<RXEN) | (1<<TXEN);

	/************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   = 0 Asynchronous Operation
	 * UPM1:0  = 00 Disable parity bit
	 * USBS    = 0 One stop bit
	 * UCSZ1:0 = 11 For 8-bit data mode
	 * UCPOL   = 0 Used with the Synchronous operation only
	 ***********************************************************************/
	UCSRC = (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);

	/* Calculate the UBRR register value */
	ubrrVal = (u16)(((F_CPU / (baud_rate * 8UL))) - 1);

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH = ubrrVal>>8;
	UBRRL = ubrrVal;
}

void UART_sendData(const u8 data)
{
	/* Wait until Flag is set to Send data*/
	while(isCLR(UCSRA,UDRE)){}
	UDR = data;
}

u8 UART_recieveData(void)
{
	/* Wait until Flag is set to Receive data*/
	while(isCLR(UCSRA,RXC)){}
    return UDR;
}

void UART_sendString(const u8 *Str)
{
	u8 i = 0;
	while(Str[i] != '\0')
	{
		UART_sendData(Str[i]);
		i++;
	}
}

void UART_receiveString(u8 *Str)
{
	u8 i = 0;

	/* Receive the first byte */
	Str[i] = UART_recieveData();

	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveData();
	}

	Str[i] = '\0';
}
