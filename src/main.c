#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "MCAL/RCC/RCC_Interface.h"

#include "MCAL/GPIO/GPIO_Interface.h"

#include "MCAL/STK/STK_Interface.h"

#include "MCAL/NVIC/NVIC_Interface.h"

#include "MCAL/EXTI/EXTI_Interface.h"

int main()
{
	/*1- Init System Clock*/
	RCC_voidInitSysClk();
	/*2- Enable Clk for the periphral GPIOA & GPIOB*/
	RCC_voidEnablePerClk(AHB1, IOA);
	RCC_voidEnablePerClk(AHB1, IOB);
	RCC_voidEnablePerClk(AHB1, IOC);
	STK_voidInit();
	for (u8 i = PIN0; i < PIN15; i++)
	{
		GPIO_voidSetPinMode(IOA, i, OUTPUT);
		GPIO_voidSetPinPuPdConfig(IOA, i, OUTPUT_PP);
		GPIO_voidSetPinSpeed(IOA, i, OUTPUT_LS);

		GPIO_voidSetPinMode(IOB, i, OUTPUT);
		GPIO_voidSetPinType(IOB, i, OUTPUT_PP);
		GPIO_voidSetPinSpeed(IOB, i, OUTPUT_LS);
		GPIO_voidSetPinValue(IOB, i, OUTPUT_HIGH);

		GPIO_voidSetPinMode(IOC, i, OUTPUT);
		GPIO_voidSetPinType(IOC, i, OUTPUT_PP);
		GPIO_voidSetPinSpeed(IOC, i, OUTPUT_LS);
	}

	while (1)
	{
		GPIO_voidSetPinValue(IOA, PIN0, OUTPUT_HIGH);
		GPIO_voidSetPinValue(IOB, PIN0, OUTPUT_LOW);
	}

	return 0;
}
