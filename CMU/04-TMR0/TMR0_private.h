/*
 * TMR0_private.h
 *
 *  Created on: Oct 13, 2021
 *      Author: medoa
 */

#ifndef TMR0_PRIVATE_H_
#define TMR0_PRIVATE_H_

//-----TMR0 Registers-----//
#define TCCR0 *((volatile u8*) (0x53))
#define TCNT0 *((volatile u8*) (0x52))
#define TIMSK *((volatile u8*) (0x59))
#define OCR0  *((volatile u8*) (0x5C))

//----TCCR0 Registers----//
#define FOC0	7
#define WGM00	6
#define COM01	5
#define COM00	4
#define WGM01	3
#define CS02	2
#define CS01	1
#define CS00	0
//-----Enable TMR0 Pin-----//
#define TOIE0 	0
#define OCIE0	1

#endif /* 02_MCAL_TMR0_TMR0_PRIVATE_H_ */
