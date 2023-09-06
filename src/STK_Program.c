/*******************************************************************/
/* SWC: STK Driver                                                 */
/* Author: Zeyad Attia                                             */
/* Version: v0.0                                                   */
/* Date: 12 Aug 2023                                               */
/* Description: implemntation of the STK driver in the STM32F401CC */
/*******************************************************************/

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "STK_Interface.h"
#include "STK_Private.h"
#include "STK_Config.h"

/* Global Pointer to Function */
void (*GPF)(void) = NULL;

/* Interval mode */
u8 Global_u8ModeOfInterval = 2;

void STK_voidInit(void)
{
    // disable systick
    CLR_BIT(STK_CTRL, 0);

    // disable systick interrupt
    CLR_BIT(STK_CTRL, 1);

#if STK_CLK_SRC == AHB_DIV_8
    CLR_BIT(STK_CTRL, 2);
#elif STK_CLK_SRC == AHB_CLK
    SET_BIT(STK_CTRL, 2);
#else
#warning "Invalid Clock source for Systick"
#endif
}

/*
    tick time = 1 microsecond
*/
void STK_voidSetBusyWait(u32 Copy_u32Ticks)
{
    // 1- load value in the load register
    ASSIGN_REG(STK_LOAD, Copy_u32Ticks);

    // 2- start timer
    SET_BIT(STK_CTRL, 0);

    // 3- wait for flag
    while (GET_BIT(STK_CTRL, 16) != 1)
    {
    }

    // 4- stop timer
    CLR_BIT(STK_CTRL, 0);

    // 4.2- make sure it doesnt count again, if the (4) didnt work
    ASSIGN_REG(STK_LOAD, 0);
    ASSIGN_REG(STK_VAL, 0);
}
void STK_voidSetIntervalSingle(u32 Copy_u32Ticks, void (*Copy_ptr)(void))
{
    // 1- load value in the load register
    ASSIGN_REG(STK_LOAD, Copy_u32Ticks);

    // 2- start timer
    SET_BIT(STK_CTRL, 0);

    // 3- GPL = COPY_PTR
    GPF = Copy_ptr;

    // 4- set mode of interval
    Global_u8ModeOfInterval = SINGLE_INTERVAL_MODE;

    // 5- enable systick interrupt
    SET_BIT(STK_CTRL, 1);
}
void STK_voidSetIntervalPeriodic(u32 Copy_u32Ticks, void (*Copy_ptr)(void))
{
    // 1- load value in the load register
    ASSIGN_REG(STK_LOAD, Copy_u32Ticks);

    // 2- start timer
    SET_BIT(STK_CTRL, 0);

    // 3- GPL = COPY_PTR
    GPF = Copy_ptr;

    // 4- set mode of interval
    Global_u8ModeOfInterval = PERIODIC_INTERVAL_MODE;

    // 5- enable systick interrupt
    SET_BIT(STK_CTRL, 1);
}
void STK_voidStopTimer(void)
{
    CLR_BIT(STK_CTRL, 0);
    ASSIGN_REG(STK_LOAD, 0);
    ASSIGN_REG(STK_VAL, 0);
}
u32 STK_u32GetElapsedTime(void)
{

    return (STK_LOAD - STK_VAL);
}
u32 STK_u32GetRemainingTime(void)
{
    return STK_VAL;
}

void SysTick_Handler()
{

    if (Global_u8ModeOfInterval == SINGLE_INTERVAL_MODE)
    {
        // Stop Timer
        STK_voidStopTimer();
    }
    else if (Global_u8ModeOfInterval == PERIODIC_INTERVAL_MODE)
    {
        // do nothing
    }

    u8 Local_tmp = 0;
    if (GPF != NULL)
    {
        GPF();
    }

    // clear flag
    GET_BIT(STK_CTRL, 16);
}