
/*******************************************************************/
/* SWC: GPIO Driver                                                 */
/* Author: Zeyad Attia                                             */
/* Version: v0.0                                                   */
/* Date: 05 Aug 2023                                               */
/* Description: implemntation of the RCC driver in the STM32F401CC */
/*******************************************************************/

#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

void GPIO_voidSetPinMode(u8 copy_u8portId, u8 copy_u8PinId, u8 copy_u8Mode);
void GPIO_voidSetPinType(u8 copy_u8portId, u8 copy_u8PinId, u8 copy_u8Type);
void GPIO_voidSetPinSpeed(u8 copy_u8portId, u8 copy_u8PinId, u8 copy_u8Speed);
void GPIO_voidSetPinPuPdConfig(u8 copy_u8portId, u8 copy_u8PinId, u8 copy_u8PuPd);
void GPIO_voidSetDirectAcces(u8 copy_u8portId, u8 copy_u8PinId, u8 copy_u8SetReset);
void GPIO_voidSetPinValue(u8 copy_u8portId, u8 copy_u8PinId, u8 copy_u8Value);
void GPIO_voidSetPortValue(u8 copy_u8portId, u32 copy_u32Value);
u8 GPIO_voidGetPinValue(u8 copy_u8portId, u8 copy_u8PinId);

#define IOA 0
#define IOB 1
#define IOC 2

#define INPUT   0
#define OUTPUT  1
#define AF      2
#define ANALOG  3

enum
{
    PIN0 = 0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7,
    PIN8,
    PIN9,
    PIN10,
    PIN11,
    PIN12,
    PIN13,
    PIN14,
    PIN15

} PinID;

#define OUTPUT_PP   0
#define OUTPUT_OD   1

#define OUTPUT_LS   0
#define OUTPUT_MS   1
#define OUTPUT_HS   2

#define OUTPUT_SET      0
#define OUTPUT_RST    1

#define OUTPUT_LOW  0
#define OUTPUT_HIGH 1

#define INPUT_FLOATING  0
#define INPUT_PD        1
#define INPUT_PU        2

#endif
