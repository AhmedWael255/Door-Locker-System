/*********************************/
/* Author   :   Spectrum         */
/* Date     :   21 Oct 2021      */
/* Version  :   V01              */
/*********************************/

#ifndef CMU_H_
#define CMU_H_

#include "01-LIB/STD_Types.h"

extern u8 Status;

/*Address where EEPROM saves the Password*/

#define EEPROM_BASE_ADDRESS		0x0311
#define EEPROM_STATUS_ADDRESS	0x00C8

/*Macros to display the Status of a Function in MC1*/
#define Idle			11
#define Active			22
#define MainMenu		33
#define Warning			44
#define ActionBuzzer	55
#define ActionDoor		60
#define Door			6

/*Displays the Size of Password*/
#define PasswordSize    5


/*Message Macros that is sent or received by the UART*/
#define Ready			0x10
#define Correct			0xFF
#define Wrong			0x00
#define OpenDoor 		0x01
#define ChangePW		0x02
#define DoorAction		0x20
#define OpenBuzzer		0x40

/************************
 * 		Functions		*
 ************************/

/*Description:
 * Initialize the Main Modules which are
 * Buzzer, UART, DC Motor and I2C
 * And Displays a Message after Initialization.
 */
void Init_Modules(void);

/*Description:
 *Receives the Password from MC1 and Saves it in the EEPROM.
 */
void Set_Password(void);

/*Description:
 * Receives Password from MC1 then Checks it with the
 * Password saved on the EEPROM and if its correct then
 * send a message which says its correct and if its
 * wrong then send a message which says its wrong.
 */
void Check_Password(void);

/*Description:
 * Opens the Motor with 25% Clockwise for 1 Second then
 * Motor Stops for 3 Seconds then
 * Motor Starts with 25% Counter Clockwise for 1 Second.
 * */
void Open_Door(void);

/*Description:
 *Buzzer start to alert for 2 seconds then stops.
 * */
void Start_Buzzer(void);

#endif /* CMU_H_ */
