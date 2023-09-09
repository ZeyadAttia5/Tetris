#include "MCAL/RCC/RCC_Interface.h"

#include "MCAL/GPIO/GPIO_Interface.h"

#include "MCAL/STK/STK_Interface.h"

#include "HAL/Dot_Matrix/Dot_Matrix_Interface.h"
#include "APP/Tetris.h"
// #include <stddef.h>

// #define container_of(ptr, type, member) ({                      \
//         const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
//         (type *)( (char *)__mptr - offsetof(type,member) ); })

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
	//	GPIO_voidSetPinMode(IOA, PIN9, OUTPUT);
	//	GPIO_voidSetPinType(IOA, PIN9, OUTPUT_PP);
	//	GPIO_voidSetPinSpeed(IOA, PIN9, OUTPUT_LS);
	//	GPIO_voidSetPinValue(IOA, PIN9, OUTPUT_HIGH);
	// DotMatrix matrix = DotMatrix_init();

	Tetris game_controller = Tetris_init();
	game_controller.drawShape(&game_controller, 0, 6);
	game_controller.drawShape(&game_controller, 3, 3);

	// DotMatrix matrix = DotMatrix_init();
	// u8 *row = &matrix.copy_u8RowPort;
	// DotMatrix *matrix2 = container_of(row, DotMatrix, copy_u8RowPort);

	// matrix2->setPixel(matrix2->buffer, 3,3);

	while (1)
	{
		matrix_update(game_controller.board);
		// matrix_update(*matrix2);
	}

	return 0;
}
