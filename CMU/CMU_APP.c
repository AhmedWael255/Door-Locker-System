/*********************************/
/* Author   :   Spectrum         */
/* Date     :   21 Oct 2021      */
/* Version  :   V01              */
/*********************************/

/********************************
 * 				MC2				*
 ********************************/

#include "CMU.h"

int main()
{

	/*Description:
	 * Initialize the Main Modules which are
	 * Buzzer, UART, DC Motor and I2C
	 * And Displays a Message after Initialization
	 */
	Init_Modules();

	/*If its the first time to turn on MC2 then the Password will be set for the first time
	 * then change the status to be active*/
#if (Status == FistOpen)

	/*Description:
	 * Function that receives the Password from MC1 using UART then
	 * saves it on the EEPROM
	 */
	Set_Password();

	/*Change the status from First time Open to active*/
#undef Status
#define Status Active

#endif

#if (Status == Active)

	/*Description:
	 * Function that Receives one of the two actions either
	 * Opening the door or changing the Password
	 * each time it receives and action it sends ACK that its Ready
	 *
	 * if action was Opening the door then it Checks the Password and
	 * if correct it receives a message to open the door , if not after three
	 * times it receives a message to start the Buzzer.
	 *
	 *  if action was changing the password then it wait for the new password
	 *  to be sent then saves it.
	 */

	Recieve_Action();

#endif

	while(1)
	{

	}

	return 0;
}
