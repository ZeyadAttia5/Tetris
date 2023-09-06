#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "MCAL/RCC/RCC_Interface.h"

#include "MCAL/GPIO/GPIO_Interface.h"

#include "MCAL/STK/STK_Interface.h"

#include "MCAL/NVIC/NVIC_Interface.h"

#include "MCAL/EXTI/EXTI_Interface.h"


int main() {
	/*1- Init System Clock*/
	RCC_voidInitSysClk();
	/*2- Enable Clk for the periphral GPIOA & GPIOB*/
	RCC_voidEnablePerClk(AHB1, IOA);
	STK_voidInit();
	for (u8 i = PIN0; i < PIN3; i++) {
		if (i == EXTI0) {
			GPIO_voidSetPinMode(IOA, i, INPUT);
			GPIO_voidSetPinPuPdConfig(IOA, i, INPUT_PU);
			GPIO_voidSetPinSpeed(IOA, i, OUTPUT_LS);

		} else {
			GPIO_voidSetPinMode(IOA, i, OUTPUT);
			GPIO_voidSetPinType(IOA, i, OUTPUT_PP);
			GPIO_voidSetPinSpeed(IOA, i, OUTPUT_LS);
		}
	}
	return 0;
}
