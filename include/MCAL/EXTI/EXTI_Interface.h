#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

#define EXTI_SC_RisingEdge  0
#define EXTI_SC_FallingEdge 1
#define EXTI_SC_DoubleEdge 2

#define EXTI0   0
#define EXTI1   1
#define EXTI2   2
#define EXTI3   3
#define EXTI4   4
#define EXTI5   5
#define EXTI6   6
#define EXTI7   7
#define EXTI8   8
#define EXTI9   9
#define EXTI10  10
#define EXTI11  11
#define EXTI12  12
#define EXTI13  13
#define EXTI14  14
#define EXTI15	15

typedef void (*EXTI_Callback_t)(void);


void EXTI_voidInit();
void EXTI_voidEXTILineEnable(u8);
void EXTI_voidEXTILineDisable(u8);
void EXTI_voidSetSenseControl(u8 copy_u8SenseControl, u8 copy_u8Line);
void EXTI_voidSetEXTIPinConfig(u8 copy_u8PortId, u8 copy_u8Line);
void EXTI_voidSetEXTIConfig(u8 copy_u8PortId, u8 copy_u8Line);
void EXTI_voidClrPendingFlag(u8);
void EXTI_voidSetCallBack(EXTI_Callback_t callback, u8 copy_u8LineId);
#endif
