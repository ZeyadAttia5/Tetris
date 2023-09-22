#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "MCAL/GPIO/GPIO_Interface.h"
#include "MCAL/STK/STK_Interface.h"

#include "HAL/STP/STP_Config.h"
#include "HAL/STP/STP_Private.h"
#include "HAL/STP/STP_Interface.h"

void STP_voidInit()
{
    GPIO_voidSetPinMode(SERIAL_PIN, OUTPUT);
    GPIO_voidSetPinMode(STORE_CLK_PIN, OUTPUT);
    GPIO_voidSetPinMode(SHIFT_CLK_PIN, OUTPUT);

    GPIO_voidSetPinType(SERIAL_PIN, OUTPUT_PP);
    GPIO_voidSetPinType(STORE_CLK_PIN, OUTPUT_PP);
    GPIO_voidSetPinType(SHIFT_CLK_PIN, OUTPUT_PP);

    GPIO_voidSetPinSpeed(SERIAL_PIN, OUTPUT_LS);
    GPIO_voidSetPinSpeed(STORE_CLK_PIN, OUTPUT_LS);
    GPIO_voidSetPinSpeed(SHIFT_CLK_PIN, OUTPUT_LS);
}

void STP_voidSendSynch(u8 copy_u8Data)
{
    u8 LOC_u8BitVal = 0;

    for (s8 LOC_s8Counter = 7; LOC_s8Counter >= 0; LOC_s8Counter--)
    {
        LOC_u8BitVal = GET_BIT(copy_u8Data, LOC_s8Counter);
        GPIO_voidSetPinValue(SERIAL_PIN, LOC_u8BitVal);

        GPIO_u8SetPinValue(SHIFT_CLK_PIN, OUTPUT_HIGH);
        STK_voidSetBusyWait(1);
        GPIO_u8SetPinValue(SHIFT_CLK_PIN, OUTPUT_LOW);
        STK_voidSetBusyWait(1);
    }
    
    GPIO_u8SetPinValue(STORE_CLK_PIN, OUTPUT_HIGH);
    STK_voidSetBusyWait(1);
    GPIO_u8SetPinValue(STORE_CLK_PIN, OUTPUT_LOW);
    STK_voidSetBusyWait(1);
}