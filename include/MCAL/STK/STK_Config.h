/*******************************************************************/
/* SWC: STK Driver                                                 */
/* Author: Zeyad Attia                                             */
/* Version: v0.0                                                   */
/* Date: 12 Aug 2023                                               */
/* Description: implemntation of the STK driver in the STM32F401CC */
/*******************************************************************/

#ifndef STK_CONFIG_H
#define STK_CONFIG_H



/* 
    STK_CLK_SRC:
        - AHB_CLK
        - AHB_CLK_DIV_8
*/
#define STK_CLK_SRC AHB_CLK

#define AHB_CLK         7123
#define AHB_CLK_DIV_8   8431
#endif