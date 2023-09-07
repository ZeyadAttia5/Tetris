/*******************************************************************/
/* SWC: RCC Driver                                                 */
/* Author: Zeyad Attia                                             */
/* Version: v0.0                                                   */
/* Date: 04 Aug 2023                                               */
/* Description: implemntation of the RCC driver in the STM32F401CC */
/*******************************************************************/

#ifndef RCC_PRIVATE_H
#define RCC_RPIVATE_H

// RCC: AHB1, Base Address: 0x40023800

#define RCC_CR *((volatile u32 *)0x40023800)
#define RCC_PLLCFGR *((volatile u32 *)0x40023804)
#define RCC_CFGR *((volatile u32 *)0x40023808)
#define RCC_AHB1ENR *((volatile u32 *)0x40023830)
#define RCC_AHB2ENR *((volatile u32 *)0x40023834)
#define RCC_APB1ENR *((volatile u32 *)0x40023840)
#define RCC_APB2ENR *((volatile u32 *)0x40023844)

// private macros

#define HSI 0
#define HSE 1
#define PLL 2

// Bits Configuration

// RCC_CR Bits
#define HSION 0
#define HSEON 16
#define PLLON 24

// RCC_CFGR
#define SW0 0
#define SW1 1

// RCC_PLLCFGR Bits
#define PLLSRC 22
#define N_OFFSET 6
#define M_OFFSET 0
#define P_OFFSET 16

#define NOTPYBASSED 0
#define BYPASSED 1

#endif
