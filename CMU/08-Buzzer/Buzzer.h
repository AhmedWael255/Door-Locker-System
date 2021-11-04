/*********************************/
/* Author   :   Spectrum         */
/* Date     :   21 Oct 2021      */
/* Version  :   V01              */
/*********************************/

#ifndef BUZZER_H_
#define BUZZER_H_

/*Defines the Port and PINS which the Buzzer is Inserted*/
#define BuzzerPort				A
#define Buzzer_First_Pin		0
#define Buzzer_Second_Pin		2


/************************
 * 		Functions		*
 ************************/
void Buzzer_Init(void);
void Buzzer_ON(void);
void Buzzer_OFF(void);

#endif /* 08_BUZZER_BUZZER_H_ */
