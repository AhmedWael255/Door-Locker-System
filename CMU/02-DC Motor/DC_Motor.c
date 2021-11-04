/*********************************/
/* Author   :   Spectrum         */
/* Date     :   20 Sep 2021      */
/* Version  :   V01              */
/*********************************/

#include "DC_Motor.h"
#include "../04-TMR0/TMR0.h"
#include "../01-GPIO/GPIO.h"

/*Stepper motor option if its full wave or half wave*/
#if Stepper_Motor == FULL_WAVE_STEPS
	u8 steps[] = {12, 6, 3, 9};

#elif	Stepper_Motor == HALF_WAVE_STEPS
	u8 steps[] = {12, 4, 6, 2, 3, 1, 9, 8};
#endif

/*Init the motor pins as output*/
/*Takes void and returns void*/
void DC_Motor_Init(void)
{
	GPIO_setPinDirection(MOTOR_PORT,FISRT_PIN, OUTPUT); /*Set Pin0 in Port B as Output*/
	GPIO_setPinDirection(MOTOR_PORT,SECOND_PIN, OUTPUT); /*Set Pin1 in Port B as Output*/
	GPIO_writePin(MOTOR_PORT,SECOND_PIN, Low);  /*Set Pin0 in Port B as Low (0)*/
	GPIO_writePin(MOTOR_PORT,FISRT_PIN, Low);/*Set Pin1 in Port B as Low (0)*/
}

/*Rotation options of motor
 * first parameter is Clockwise or Counter Clockwise
 * second the speed in percentage (100% or 75% or 50% or 25% only)*/
void DC_Motor_Rotate(u8 state, u8 speed)
{
	switch(state)
	{
	case CW:
		GPIO_writePin(MOTOR_PORT,SECOND_PIN, Low);	/*Set Pin1 in Port B as Low (0)*/
		GPIO_writePin(MOTOR_PORT,FISRT_PIN, High);	/*Set Pin0 in Port B as High (1)*/
		break;
	case CCW:
		GPIO_writePin(MOTOR_PORT,SECOND_PIN, High); /*Set Pin1 in Port B as High (1)*/
		GPIO_writePin(MOTOR_PORT,FISRT_PIN, Low); /*Set Pin0 in Port B as Low (0)*/
		break;
	default: return;
	}

	u8 DC;
	switch (speed)
	{
	case 100:
		DC = 255;
		break;
	case 75:
		DC = 192;
		break;
	case 50:
		DC = 128;
		break;
	case 25:
		DC = 64;
		break;
	}
	TMR0_PWM_Start(DC);
}

/*Stops the Motor*/
void DC_Motor_Stop(void)
{
	GPIO_writePin(MOTOR_PORT,SECOND_PIN, Low);  /*Set Pin0 in Port B as Low (0)*/
	GPIO_writePin(MOTOR_PORT,FISRT_PIN, Low);/*Set Pin1 in Port B as Low (0)*/
}

 /*If Stepper Motor is used*/
#ifdef	USING_STEPPER_MOTOR

/*Function to switch Motor
 * Options:
 * 	CW or CCW
 * 	PORT which the motor is inserted
 * 	Number of steps needed*/
void StepperMotor_Switch(u8 state, GPIO_MOTOR_PORT MOTOR_PORT, u8 cnt)
{
	switch(state)
	{
	case CW:
		GPIO_writePin(MOTOR_PORT,SECOND_PIN, Low);	/*Set Pin1 in Port B as Low (0)*/
		GPIO_writePin(MOTOR_PORT,FISRT_PIN, High);	/*Set Pin0 in Port B as High (1)*/
		break;
	case CCW:
		GPIO_writePin(MOTOR_PORT,SECOND_PIN, High); /*Set Pin1 in Port B as High (1)*/
		GPIO_writePin(MOTOR_PORT,FISRT_PIN, Low); /*Set Pin0 in Port B as Low (0)*/
		break;
	default: return;
	}

	while(cnt != Stepper_Motor)
	{

#if Stepper_Motor == FULL_WAVE_STEPS
	MOTOR_PORT = (steps[cnt] & 0x0F) | (MOTOR_PORT & 0xF0);
#elif
	MOTOR_PORT = (steps[Stepper_Motor - cnt - 1] & 0x0F) | (MOTOR_PORT & 0xF0);
#endif

	cnt++;
	}
	if(cnt == Stepper_Motor)
		cnt = 0;
}
#endif
