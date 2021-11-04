/*********************************/
/* Author   :   Spectrum         */
/* Date     :   21 Oct 2021      */
/* Version  :   V01              */
/*********************************/

#ifndef CMU_H_
#define CMU_H_

/*Address where EEPROM saves the Password*/

#define EEPROM_BASE_ADDRESS		0x0311

/*Macros to display the Status of MC2*/
#define FirstOpen		0
#define Active			1
#define Status			FirstOpen

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
 *Receives an action either to change password or open the door
 *this function send ACK in the two options which indicates that
 *UART is Ready for data.
 *If Status is to Change Password then Call the Set_Password Function.
 *If Status is to Open Door then if Password if Correct then it call Open_Door() Function.
 *If Password is Wrong for three times then Call Start_Buzzer() function.
 */
void Recieve_Action(void);

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
void Save_Password(void);

#endif /* CMU_H_ */
