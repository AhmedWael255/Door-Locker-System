/*********************************/
/* Author   :   Spectrum         */
/* Date     :   13 Oct 2021      */
/* Version  :   V01              */
/*********************************/
#ifndef TMR0_H_
#define TMR0_H_

#define PWM_PORT	B
#define PWM_PIN		3

#include "../01-LIB/STD_Types.h"

typedef enum
{
	CTC,
	PWM,
	NORMAL,
	F_PWM

}WaveFormGen;

typedef enum
{
	NO_CLK_SRC = 0,		//Timer Disable
	F_CPU1 = 1,
	F_CPU8 = 2,
	F_CPU64 = 3,
	F_CPU256 = 4,
	F_CPU1024 = 5,
	EXT_CLK_Falling = 6,
	EXT_CLK_Rising = 7
}TMR0_PRESCALAR;

typedef struct
{
	WaveFormGen Mode;
	TMR0_PRESCALAR PRESCALAR;
}TMR0_Settings;

extern void TMR0_Init(const TMR0_Settings *TMR0_Config);
extern void TMR0_ReadCounterValue(u8* NumofTicks);
extern void TMR0_SetCompareValue(u8 val);
extern void TMR0_SetCounterValue(u8 val);
extern void TMR0_SetOVNumber(u8 val);
extern void TMR0_SetTOVNumber(u8 val);
extern void TMR0_GetTOVNumber(u8* val);
extern void TMR0_GetTicksofSWcounter(u32* val);	//SW Counter
extern void TMR0_PWM_Start(u8 Duty_Cycle);
extern void TMR0_PWM_Stop();

#endif /* TMR0_H_ */
