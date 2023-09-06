/*******************************************************************/
/* SWC: RCC Driver                                                 */
/* Author: Zeyad Attia                                             */
/* Version: v0.0                                                   */
/* Date: 04 Aug 2023                                               */
/* Description: implemntation of the RCC driver in the STM32F401CC */
/*******************************************************************/

#ifndef RCC_CONFIG_H
#define RCC_CONFIG_H


/*
    PLL Configuration
    VCO output frequency = VCO input frequency × PLLN with 192 ≤ PLLN ≤432
    VCO input frequency = PLL input clock frequency / PLLM with 2 ≤ PLLM ≤63
    PLL output clock frequency = VCO frequency / PLLP with PLLP = 2, 4, 6, or 8
    PLLP = 00, 01, 10, 11 == 0, 1, 2, 3

    This register is used to configure the PLL clock outputs according to the formulas:
        •   f(VCO clock) = f(PLL clock input) × (PLLN / PLLM)
        •   f(PLL general clock output) = f(VCO clock) / PLLP
        •   f(USB OTG FS, SDIO, RNG clock output) = f(VCO clock) / PLLQ
    
    where:
    PLLSRC: PLL entry clock source
        0: HSI oscillator clock / 2 selected as PLL input clock
        1: HSE oscillator clock selected as PLL input clock
    PLLM[5:0]: Division factor for the main PLL (PLL) and audio PLL (PLLI2S) input clock
        These bits must be written when PLL is disabled.
        These bits can be written only when PLL is disabled, PLLRDY = 0.
        2 ≤ PLLM ≤ 63
    PLLN[8:0]: Main PLL (PLL) multiplication factor for VCO
        These bits can be written only when PLL is disabled, PLLRDY = 0.
        192 ≤ PLLN ≤ 432
    PLLP[1:0]: Main PLL (PLL) division factor for main system clock
        These bits can be written only when PLL is disabled, PLLRDY = 0.
        0 = 0b00: PLLP = 2 
        1 = 0b01: PLLP = 4 
        2 = 0b10: PLLP = 6 
        3 = 0b11: PLLP = 8 
    PLLQ[3:0]: Main PLL (PLL) division factor for USB OTG FS, SDIO and random number generator clocks
        These bits can be written only when PLL is disabled, PLLRDY = 0.
        2 ≤ PLLQ ≤ 15
*/

// SYS_CLK_SRC options: HSI, HSE, PLL
#define SYS_CLK_SRC HSI

// PLL Configuration
#define PLL_SRC HSI
#define PLL_M_Value 2   // must be between 2 and 63, inclusive
#define PLL_N_Value 200 // must be between 192 and 432 MHz, inclusive
#define PLL_P_Value 2   // must be 00, 01, 10, 11 == 0, 1, 2, 3
#endif