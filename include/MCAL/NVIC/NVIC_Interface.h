/*******************************************************************/
/* SWC: NVIC Driver                                                 */
/* Author: Zeyad Attia                                             */
/* Version: v0.0                                                   */
/* Date: 019 Aug 2023                                               */
/* Description: implemntation of the NVIC driver in the STM32F401CC */
/*******************************************************************/

#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H

#include "../../LIB/STD_TYPES.h"

u8 NVIC_u8EnablePerInt(u8 copy_u8PerID);
u8 NVIC_u8DisablePerInt(u8 copy_u8PerID);
void NVIC_voidSetPendingFlag(u8 copy_u8PerID);
void NVIC_voidClrPendingFlag(u8 copy_u8PerID);
void NVIC_voidSetPriorityConfig(u8 copy_u8PriortyConfig);
void NVIC_voidSetPerPriority(u8 copy_u8PerId, u8 copy_u8GroupId, u8 copy_u8SubGrouPId);

/* error codes */
#define SUCCESS 0
#define FAIL 1

// base address of SCB is 0xE000ED00
#define SCB_AIRCR *((volatile u32 *)0xE000ED00)

#define G16_SG0 0
#define G8_SG2  1
#define G4_SG4  2
#define G2_SG8  3
#define G0_SG16 4

#endif