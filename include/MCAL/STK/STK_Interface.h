/*******************************************************************/
/* SWC: STK Driver                                                 */
/* Author: Zeyad Attia                                             */
/* Version: v0.0                                                   */
/* Date: 12 Aug 2023                                               */
/* Description: implemntation of the STK driver in the STM32F401CC */
/*******************************************************************/

#ifndef STK_INTERFACE_H
#define STK_INTERFACE_H

#include "LIB/STD_TYPES.h"

void STK_voidInit(void);
void STK_voidSetBusyWait(u32 Copy_u32Ticks);
void STK_voidSetIntervalSingle(u32 Copy_u32Ticks, void (*Copy_ptr)(void));
void STK_voidSetIntervalPeriodic(u32 Copy_u32Ticks, void (*Copy_ptr)(void));
void STK_voidStopTimer(void);
u32 STK_u32GetElapsedTime(void);
u32 STK_u32GetRemainingTime(void);



#define AHB1    0
#define AHB2    1
#define ABP1    2
#define ABP2    3


#endif