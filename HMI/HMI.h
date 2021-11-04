/*********************************/
/* Author   :   Spectrum         */
/* Date     :   21 Oct 2021      */
/* Version  :   V01              */
/*********************************/

#ifndef HMI_H_
#define HMI_H_

/*Displays the Size of Password*/
#define PasswordSize    5

/*Defines the Number of times to try writing the Password if it Wrong*/
#define NO_OF_TRIAL		3

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
 * LCD and UART
 * And Displays a Message after Initialization.
 */
void Init_Modules(void);

/*Description:
 * Function that waits for writing the new password at the first
 * time then sends it to the MC2.
 */
void Enter_Password(void);

/*Description:
 * Function that Displays the Options Menu which is:
 * Open Door or Change Password.
 */
void Display_Menu(void);

/*Description:
 * Get the Pressed key which is only + or - to take action,
 * Either + to Open the Door or - to Change Password.
 * */
void Make_Action(void);

/*Description:
 * Sends Message to MC2 to inform that user wants to Open the Door and wait for ACK,
 * then let user enters the password.
 * if password is correct then send MC2 message to open the door
 * if password is wrong then the user will try for another two times,
 * if its wrong for the three times then LCD displays message that System is Locked
 * */
void Open_Door(void);

/*Description:
 * Sends Message to MC2 to inform that user wants to change Password and wait for ACK,
 * then let user enters the new password then displays the Main Menu that display options.
 * */
void Change_Password(void);

#endif /* HMI_H_ */
