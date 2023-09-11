#include "MCAL/RCC/RCC_Interface.h"

#include "MCAL/GPIO/GPIO_Interface.h"

#include "MCAL/STK/STK_Interface.h"
#include "MCAL/EXTI/EXTI_Interface.h"
#include "MCAL/NVIC/NVIC_Interface.h"
#include "HAL/Dot_Matrix/Dot_Matrix_Interface.h"
#include "APP/Tetris.h"
// #include <stddef.h>

// #define container_of(ptr, type, member) ({                      \
//         const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
//         (type *)( (char *)__mptr - offsetof(type,member) ); })
Tetris game_controller;

extern Tetris game_controller;

int main() {
	/*1- Init System Clock*/
	RCC_voidInitSysClk();
	/*2- Enable Clk for the periphral GPIOA & GPIOB*/
	RCC_voidEnablePerClk(AHB1, IOA);
	RCC_voidEnablePerClk(AHB1, IOB);
	RCC_voidEnablePerClk(AHB1, IOC);
	STK_voidInit();

	NVIC_voidSetPerPriority(23, 0, 0);

	/* Test system is working */
	//	GPIO_voidSetPinValue(IOA, PIN9, OUTPUT_HIGH);
//	DotMatrix matrix = DotMatrix_init();
	game_controller = Tetris_init();
	game_controller.drawShape(&game_controller, 1, 0);

	// game_controller.drawShape(&game_controller, 0, 6);
	// game_controller.drawShape(&game_controller, 3, 3);

	// u8 *row = &matrix.copy_u8RowPort;
	// DotMatrix *matrix2 = container_of(row, DotMatrix, copy_u8RowPort);

//	matrix.setPixel(matrix.buffer, 1, 0);

	while (1) {
		matrix_update(game_controller.board);
//		matrix_update(matrix);
	}

	return 0;
}
