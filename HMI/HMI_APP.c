/*********************************/
/* Author   :   Spectrum         */
/* Date     :   21 Oct 2021      */
/* Version  :   V01              */
/*********************************/


/********************************
 * 				MC1				*
 ********************************/

#include "HMI.h"

int main()
{

	/*Description:
	 * Initialize the Main Modules which are
	 * LCD and UART
	 * And Displays a Message after Initialization
	 */
	Init_Modules();


	/*Description:
	 * Function that waits for writing the new password at the first
	 * time then sends it to the MC2
	 */
	Enter_Password();

	/*Description:
	 * Function that Displays the Options Menu which is:
	 * Open Door or Change Password
	 */
	Display_Menu();

	while(1)
	{

	}

	return 0;
}
