/*********************************/
/* Author   :   Spectrum         */
/* Date     :   20 Sep 2021      */
/* Version  :   V01              */
/*********************************/

#ifndef DC_MOTOR_H_
#define	DC_MOTOR_H_


#include "../01-LIB/STD_Types.h"

#define FULL_WAVE_STEPS 4
#define HALF_WAVE_STEPS 8

#define MOTOR_PORT	B
#define FISRT_PIN	0
#define SECOND_PIN	1

enum{CW, CCW};

#ifdef USING_STEPPER_MOTOR
	#define Stepper_Motor  FULL_WAVE_STEPS
#endif

void DC_Motor_Init(void);
void DC_Motor_Rotate(u8 state, u8 speed);
void DC_Motor_Stop(void);

#ifdef USING_STEPPER_MOTOR
	void StepperMotor_Switch(u8 state, GPIO_PORT port, u8 cnt);
#endif

#endif /* DC_MOTOR_DC_MOTOR_H_ */
