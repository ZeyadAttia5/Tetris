/*******************************************************************/
/* SWC: RCC Driver                                                 */
/* Author: Zeyad Attia                                             */
/* Version: v0.0                                                   */
/* Date: 04 Aug 2023                                               */
/* Description: implemntation of the RCC driver in the STM32F401CC */
/*******************************************************************/

#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

#include "LIB/STD_TYPES.h"

void RCC_voidInitSysClk(void);
void RCC_voidEnablePerClk(u8 Copy_u8BusId, u8 Copy_u8PerId);
void RCC_voidDisablePerClk(u8 Copy_u8BusId, u8 Copy_u8PerId);

#define AHB1            0
#define AHB2            1
#define APB1            2
#define APB2            3

#endif
