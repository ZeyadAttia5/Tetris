/*******************************************************************/
/* SWC: NVIC Driver                                                 */
/* Author: Zeyad Attia                                             */
/* Version: v0.0                                                   */
/* Date: 04 Aug 2023                                               */
/* Description: implemntation of the NVIC driver in the STM32F401CC */
/*******************************************************************/

#ifndef NVIC_PRIVATE_H
#define NVIC_RPIVATE_H

#include "STD_TYPES.h" 


typedef struct{
    volatile u32 ISER[32];
    // volatile u32 RES0[24];    //reserved: ICER address - ISER address = 100 bytes; 100 bytes = 25 register; -1 for the ICER = 24 
    volatile u32 ICER[32];
    volatile u32 ISPR[32];
    volatile u32 ICPR[32];
    volatile u32 IABPR[64];
    // volatile u32 res[32];
    volatile u8 IPR[240];
}NVIC_t;


#define NVIC ((volatile NVIC_t *) 0xE000E100)
#define VECT_KEY 0x05FA0000

#define G4Bits_SG0Bits  0b011
#define G3Bits_SG1Bits  0b100
#define G2Bits_SG2Bits  0b101
#define G1Bits_SG3Bits  0b110
#define G0Bits_SG4Bits  0b111
#endif