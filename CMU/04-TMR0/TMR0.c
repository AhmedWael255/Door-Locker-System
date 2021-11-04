/*********************************/
/* Author   :   Spectrum         */
/* Date     :   13 Oct 2021      */
/* Version  :   V01              */
/*********************************/
#include "../04-TMR0/TMR0.h"

#include "../01-GPIO/GPIO.h"
#include "../01-GPIO/GPIO_private.h"
#include "../01-LIB/BIT_Math.h"
#include "../01-LIB/STD_Types.h"
#include "TMR0_private.h"
#include "TMR0.h"

u8 TOV_Number;
/*Init Timer in Normal or CTC or PWM or Fast PWM*/
extern void TMR0_Init(const TMR0_Settings *TMR0_Config)
{

	//-----Adjust Mode-----//
	if(TMR0_Config->Mode == NORMAL)
	{

	}
	if(TMR0_Config->Mode == CTC)
	{
		TCCR0 |= (1<<WGM01);
	}

	if(TMR0_Config->Mode == PWM)
	{
		TCCR0 |= (1<<WGM00);
	}

	if(TMR0_Config->Mode == F_PWM)
	{
		TCCR0 |= (1<<WGM00);
		TCCR0 |= (1<<WGM01);
	}

	TCCR0 = ((TCCR0 & 0xF8) | (TMR0_Config->PRESCALAR));
}
/*Read Timer Start Value*/
extern void TMR0_ReadCounterValue(u8* NumofTicks)
{
	*NumofTicks = TCNT0;
}

/*Set Timer Compare Value*/
extern void TMR0_SetCompareValue(u8 val)
{
	OCR0 = val;
}
/*Set Timer Start Value*/
extern void TMR0_SetCounterValue(u8 val)
{
	TCNT0 = val;
}

/*Set Timer  Overflow flag*/
extern void TMR0_SetTOVNumber(u8 val)
{
	TOV_Number = val;
}

/*Read Timer  Overflow flag*/
extern void TMR0_GetTOVNumber(u8* val)
{
	*val = TOV_Number;
}

/*Number of ticks*/
extern void TMR0_GetTicksofSWcounter(u32* val)
{
	*val = (256*TOV_Number) + TCNT0;
}

/*Init the PWM by setting duty cycle*/
extern void TMR0_PWM_Start(u8 Duty_Cycle)
{
	TMR0_SetCounterValue(0);
	TMR0_SetCompareValue(Duty_Cycle);
	GPIO_setPinDirection(PWM_PORT,PWM_PIN,OUTPUT);
	TMR0_Settings config = {F_PWM, F_CPU8};
	TMR0_Init(&config);
	TCCR0 |= (1<<COM01);
}

/*Stop the PWM by switching clock to zero*/
extern void TMR0_PWM_Stop()
{
	TCCR0 = ((TCCR0 & 0xF8) | NO_CLK_SRC);
}
