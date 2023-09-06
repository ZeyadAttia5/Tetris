#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H

// EXTI Base address: 0x40013C00
#define Base_address 0x40013C00

#include "STD_TYPES.h"

// #define EXTI_IMR     *((volatile u32 *)(Base_address + 0x00))
// #define EXTI_EMR     *((volatile u32 *)(Base_address + 0x04))
// #define EXTI_RTSR    *((volatile u32 *)(Base_address + 0x08))
// #define EXTI_FTSR    *((volatile u32 *)(Base_address + 0x0C))
// #define EXTI_SWIER   *((volatile u32 *)(Base_address + 0x10))
// #define EXTI_PR      *((volatile u32 *)(Base_address + 0x14))

typedef struct EXTI_Private
{
    u32 IMR;
    u32 EMR;
    u32 RTSR;
    u32 FTSR;
    u32 SWIER;
    u32 PR;
} EXTI_t;

#define private_EXTI0   0
#define private_EXTI1   1
#define private_EXTI2   2
#define private_EXTI3   3
#define private_EXTI4   4
#define private_EXTI5   5
#define private_EXTI6   6
#define private_EXTI7   7
#define private_EXTI8   8
#define private_EXTI9   9
#define private_EXTI10 10
#define private_EXTI11 11
#define private_EXTI12 12
#define private_EXTI13 13
#define private_EXTI14 14
#define private_EXTI15 15

#define EXTI5_9     23
#define EXTI10_15   40

#define EXTI ((volatile EXTI_t *)(Base_address))

#endif