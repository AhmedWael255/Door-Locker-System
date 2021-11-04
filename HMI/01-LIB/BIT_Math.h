/*********************************/
/* Author   :   Spectrum         */
/* Date     :   20 Sep 2021      */
/* Version  :   V01              */
/*********************************/

#ifndef BIT_MATH_H
#define BIT_MATH_H

/*Set the specified bit of the specified register to 1*/
#define SET_Bit(REG,BIT)      	(REG) |=  (1 << (BIT))

/*Clear the specified bit of the specified register to 0*/
#define CLR_Bit(REG,BIT)      	(REG) &= ~(1 << (BIT))

/*Toggle the specified bit of the specified register*/
#define TOG_Bit(REG,BIT)      	(REG) ^=  (1 << (BIT))

/*Get the value of the specified bit of the specified register to 1*/
#define Get_Bit(REG,BIT)     	((REG) >> (BIT) & 1)

/* Rotate right the register value with specific number of rotates */
#define ROR(REG,BIT)     		(REG = (REG >> BIT) | (REG << (8-BIT)))

/* Rotate left the register value with specific number of rotates */
#define ROL(REG,BIT) 		 	(REG = (REG << BIT) | (REG >> (8-BIT)))

/* Check if a specific bit is set in any register and return true if yes */
#define isSET(REG,BIT)  		(REG & (1<<BIT))

/* Check if a specific bit is cleared in any register and return true if yes */
#define isCLR(REG,BIT) 			(!(REG & (1<<BIT)))

#endif
