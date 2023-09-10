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
void test_setPixelEXTI(void);

int main() {
	/*1- Init System Clock*/
	RCC_voidInitSysClk();
	/*2- Enable Clk for the periphral GPIOA & GPIOB*/
	RCC_voidEnablePerClk(AHB1, IOA);
	RCC_voidEnablePerClk(AHB1, IOB);
	RCC_voidEnablePerClk(AHB1, IOC);
	STK_voidInit();

	EXTI_voidInit(EXTI9);
	NVIC_voidSetPriorityConfig(G0_SG16);
	NVIC_voidSetPerPriority(23, 0, 0);
	EXTI_voidSetCallBack(test_setPixelEXTI, EXTI9);


	/* Test system is working */
//	GPIO_voidSetPinValue(IOA, PIN9, OUTPUT_HIGH);
//	DotMatrix matrix = DotMatrix_init();
	game_controller = Tetris_init();
	// game_controller.drawShape(&game_controller, 0, 6);
	// game_controller.drawShape(&game_controller, 3, 3);

	// DotMatrix matrix = DotMatrix_init();
	// u8 *row = &matrix.copy_u8RowPort;
	// DotMatrix *matrix2 = container_of(row, DotMatrix, copy_u8RowPort);
	while (1) {
		matrix_update(game_controller.board);
		//		matrix_update(matrix);
	}

	return 0;
}

void test_setPixelEXTI(void) {
	static u8 x = 0;
	static u8 y = 0;
	if(x >7){
		x = 0;
		y++;
	}
	game_controller.board.setPixel(game_controller.board.buffer, x++, y);
	STK_voidSetBusyWait(100000);
}
