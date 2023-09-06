
/*******************************************************************/
/* SWC: GPIO Driver                                                 */
/* Author: Zeyad Attia                                             */
/* Version: v0.0                                                   */
/* Date: 05 Aug 2023                                               */
/* Description: implemntation of the RCC driver in the STM32F401CC */
/*******************************************************************/

#ifndef GPIO_PRV_H
#define GPIO_PRV_H

#include "../../LIB/STD_TYPES.h"

/*
Base Addresses:
GPIOA:  0x4002 0000
GPIOB:  0x4002 0400
GPIOC:  0x4002 0800
*/

/* Registers' Addresses */

typedef struct GPIO_t
{
    volatile u32 MODER;
    volatile u32 OTYPER;
    volatile u32 OSPEEDR;
    volatile u32 IDR;
    volatile u32 ODR;
    volatile u32 PUPDR;
    volatile u32 BSRR;
    volatile u32 LCKR;
    volatile u32 AFRL;
    volatile u32 AFRH;

} GPIO_t;

#define GPIOA (((volatile GPIO_t *)0x40020000))
#define GPIOB (((volatile GPIO_t *)0x40020400))
#define GPIOC (((volatile GPIO_t *)0x40020800))

#endif
