/*********************************/
/* Author   :   Spectrum         */
/* Date     :   13 Oct 2020      */
/* Version  :   V01              */
/*********************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../01-LIB/STD_Types.h"

/*	Definitions	*/

/* Configure number of rows and columns of the keypad */
#define KEYPAD_Columns            4
#define KEYPAD_Rows               4

/* Keypad Port and Pin Configurations */
#define KEYPAD_Port                   	B

#define KEYPAD_FisrtRowPin        		0
#define KEYPAD_FirstColPin       		4

/* Keypad button Configuration */
#define KEYPAD_BUTTON_PRESSED           Low
#define KEYPAD_BUTTON_RELEASED          High

/*	Functions	*/

/*Get the Keypad pressed button*/
u8 KEYPAD_getPressedKey(void);

#endif
