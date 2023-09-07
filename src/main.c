
#include "MCAL/RCC/RCC_Interface.h"

#include "MCAL/GPIO/GPIO_Interface.h"

#include "MCAL/STK/STK_Interface.h"

#include "HAL/Dot_Matrix/Dot_Matrix_Interface.h"

int main()
{
	/*1- Init System Clock*/
	RCC_voidInitSysClk();
	/*2- Enable Clk for the periphral GPIOA & GPIOB*/
	RCC_voidEnablePerClk(AHB1, IOA);
	RCC_voidEnablePerClk(AHB1, IOB);
	RCC_voidEnablePerClk(AHB1, IOC);
	STK_voidInit();

	/* Test system is working */
	GPIO_voidSetPinMode(IOA, PIN9, OUTPUT);
	GPIO_voidSetPinType(IOA, PIN9, OUTPUT_PP);
	GPIO_voidSetPinSpeed(IOA, PIN9, OUTPUT_LS);
	GPIO_voidSetPinValue(IOA, PIN9, OUTPUT_HIGH);

	DotMatrix matrix = DotMatrix_init();

	while (1)
	{
		matrix.setPixel(matrix.buffer, 0, 0);
		matrix_update(matrix);
		STK_voidSetBusyWait(2500000);
		matrix.clrPixel(matrix.buffer, 0, 0);
		matrix_update(matrix);
		STK_voidSetBusyWait(2500000);
	}

	return 0;
}
