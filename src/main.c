#include "MCAL/RCC/RCC_Interface.h"

#include "MCAL/GPIO/GPIO_Interface.h"

#include "MCAL/STK/STK_Interface.h"

#include "HAL/Dot_Matrix/Dot_Matrix_Interface.h"

int main() {
	/*1- Init System Clock*/
	RCC_voidInitSysClk();
	/*2- Enable Clk for the periphral GPIOA & GPIOB*/
	RCC_voidEnablePerClk(AHB1, IOA);
	RCC_voidEnablePerClk(AHB1, IOB);
	RCC_voidEnablePerClk(AHB1, IOC);
	STK_voidInit();

	/* Test system is working */
//	GPIO_voidSetPinMode(IOA, PIN9, OUTPUT);
//	GPIO_voidSetPinType(IOA, PIN9, OUTPUT_PP);
//	GPIO_voidSetPinSpeed(IOA, PIN9, OUTPUT_LS);
//	GPIO_voidSetPinValue(IOA, PIN9, OUTPUT_HIGH);
	DotMatrix matrix = DotMatrix_init();

	matrix.setRow(matrix.buffer, 0);
	s8 col = DOTMAT_MAX_COLS - 1;
	for (s8 row = DOTMAT_MAX_ROWS - 1; row >= 0; row--) {

		matrix.setPixel(matrix.buffer, row, col);
		col--;
		if(col < 0) break;
	}
	matrix.setRow(matrix.buffer, DOTMAT_MAX_ROWS-1);

	while (1) {
		matrix_update(matrix);
	}

	return 0;
}
