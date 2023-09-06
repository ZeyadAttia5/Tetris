/*******************************************************************/
/* SWC: STK Driver                                                 */
/* Author: Zeyad Attia                                             */
/* Version: v0.0                                                   */
/* Date: 12 Aug 2023                                               */
/* Description: implemntation of the STK driver in the STM32F401CC */
/*******************************************************************/

#ifndef STk_PRIVATE_H
#define STk_RPIVATE_H

// STK: CORE, Base Address: 0xE000E010

#define STK_CTRL    *((volatile u32 *)0xE000E010)
#define STK_LOAD    *((volatile u32 *)0xE000E014)
#define STK_VAL     *((volatile u32 *)0xE000E018)
#define STK_CALIB   *((volatile u32 *)0xE000E01C)

// private macros

#define SINGLE_INTERVAL_MODE  0
#define PERIODIC_INTERVAL_MODE  1

#endif