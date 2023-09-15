#include "MCAL/RCC/RCC_Interface.h"

#include "MCAL/GPIO/GPIO_Interface.h"

#include "MCAL/STK/STK_Interface.h"
#include "MCAL/EXTI/EXTI_Interface.h"
#include "MCAL/NVIC/NVIC_Interface.h"
#include "HAL/Dot_Matrix/Dot_Matrix_Interface.h"
#include "APP/Tetris.h"


Tetris game_controller;

extern Tetris game_controller;

int main()
{
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
	game_controller = Tetris_init();
	game_controller.drawShape(8, 4);

	//	 game_controller.drawShape(&game_controller, 0, 6);
	//	 game_controller.drawShape(&game_controller, 3, 3);

	while (1)
	{
		Tetris_UpdateBoard();
		// matrix_update(game_controller.board, 250);
		//		matrix_update(matrix);
	}

	return 0;
}

// u8 *row = &matrix.copy_u8RowPort;
// DotMatrix *matrix2 = container_of(row, DotMatrix, copy_u8RowPort);

//	DotMatrix matrix = DotMatrix_init();
//	matrix.movePixelUp(matrix.buffer, 3, 3, ON_MOVE_SET_OLD);
//	matrix.movePixelDown(matrix.buffer, 3, 3, ON_MOVE_SET_OLD);
//	matrix.movePixelLeft(matrix.buffer, 3, 3, ON_MOVE_SET_OLD);
//	matrix.movePixelRight(matrix.buffer, 3, 3, ON_MOVE_SET_OLD);
//	matrix.setPixel(matrix.buffer, 1, 0);
