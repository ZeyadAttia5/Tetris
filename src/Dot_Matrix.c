#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

#include "MCAL/GPIO/GPIO_Interface.h"

#include "HAL/Dot_Matrix/Dot_Matrix_config.h"
#include "HAL/Dot_Matrix/Dot_Matrix_Interface.h"

//#include <malloc.h>

void setPixel(DotMatrix *addr_dotMatrix_t, u8 copy_x, u8 copy_y) {
	if (copy_x < MAX_ROWS && copy_y < MAX_COLS) {
		SET_BIT(addr_dotMatrix_t->buffer[copy_y], copy_x);
	}
}
void clrPixel(DotMatrix *addr_dotMatrix_t, u8 copy_x, u8 copy_y) {
	if (copy_x < MAX_ROWS && copy_y < MAX_COLS) {
		CLR_BIT(addr_dotMatrix_t->buffer[copy_y], copy_x);
	}
}

DotMatrix DotMatrix_init() {
	DotMatrix addr_dotMatrix; // = (DotMatrix *)malloc(sizeof(DotMatrix));

//    if (addr_dotMatrix == NULL)
//    {
//        // Handle memory allocation error
//        return NULL;
//    }

    addr_dotMatrix.setPixel = setPixel;
    addr_dotMatrix.clrPixel = clrPixel;

	/* Set mode to output */
	GPIO_voidSetPinMode(DOTMAT_ROW0, OUTPUT);
	GPIO_voidSetPinMode(DOTMAT_ROW1, OUTPUT);
	GPIO_voidSetPinMode(DOTMAT_ROW2, OUTPUT);
	GPIO_voidSetPinMode(DOTMAT_ROW3, OUTPUT);
	GPIO_voidSetPinMode(DOTMAT_ROW4, OUTPUT);
	GPIO_voidSetPinMode(DOTMAT_ROW5, OUTPUT);
	GPIO_voidSetPinMode(DOTMAT_ROW6, OUTPUT);
	GPIO_voidSetPinMode(DOTMAT_ROW7, OUTPUT);

	GPIO_voidSetPinMode(DOTMAT_COL0, OUTPUT);
	GPIO_voidSetPinMode(DOTMAT_COL1, OUTPUT);
	GPIO_voidSetPinMode(DOTMAT_COL2, OUTPUT);
	GPIO_voidSetPinMode(DOTMAT_COL3, OUTPUT);
	GPIO_voidSetPinMode(DOTMAT_COL4, OUTPUT);
	GPIO_voidSetPinMode(DOTMAT_COL5, OUTPUT);
	GPIO_voidSetPinMode(DOTMAT_COL6, OUTPUT);
	GPIO_voidSetPinMode(DOTMAT_COL7, OUTPUT);

	/* Set output to push pull */
	GPIO_voidSetPinType(DOTMAT_ROW0, OUTPUT_PP);
	GPIO_voidSetPinType(DOTMAT_ROW1, OUTPUT_PP);
	GPIO_voidSetPinType(DOTMAT_ROW2, OUTPUT_PP);
	GPIO_voidSetPinType(DOTMAT_ROW3, OUTPUT_PP);
	GPIO_voidSetPinType(DOTMAT_ROW4, OUTPUT_PP);
	GPIO_voidSetPinType(DOTMAT_ROW5, OUTPUT_PP);
	GPIO_voidSetPinType(DOTMAT_ROW6, OUTPUT_PP);
	GPIO_voidSetPinType(DOTMAT_ROW7, OUTPUT_PP);

	GPIO_voidSetPinType(DOTMAT_COL0, OUTPUT_PP);
	GPIO_voidSetPinType(DOTMAT_COL1, OUTPUT_PP);
	GPIO_voidSetPinType(DOTMAT_COL2, OUTPUT_PP);
	GPIO_voidSetPinType(DOTMAT_COL3, OUTPUT_PP);
	GPIO_voidSetPinType(DOTMAT_COL4, OUTPUT_PP);
	GPIO_voidSetPinType(DOTMAT_COL5, OUTPUT_PP);
	GPIO_voidSetPinType(DOTMAT_COL6, OUTPUT_PP);
	GPIO_voidSetPinType(DOTMAT_COL7, OUTPUT_PP);

	/* set speed to high */
	GPIO_voidSetPinSpeed(DOTMAT_ROW0, OUTPUT_HS);
	GPIO_voidSetPinSpeed(DOTMAT_ROW1, OUTPUT_HS);
	GPIO_voidSetPinSpeed(DOTMAT_ROW2, OUTPUT_HS);
	GPIO_voidSetPinSpeed(DOTMAT_ROW3, OUTPUT_HS);
	GPIO_voidSetPinSpeed(DOTMAT_ROW4, OUTPUT_HS);
	GPIO_voidSetPinSpeed(DOTMAT_ROW5, OUTPUT_HS);
	GPIO_voidSetPinSpeed(DOTMAT_ROW6, OUTPUT_HS);
	GPIO_voidSetPinSpeed(DOTMAT_ROW7, OUTPUT_HS);

	GPIO_voidSetPinSpeed(DOTMAT_COL0, OUTPUT_HS);
	GPIO_voidSetPinSpeed(DOTMAT_COL1, OUTPUT_HS);
	GPIO_voidSetPinSpeed(DOTMAT_COL2, OUTPUT_HS);
	GPIO_voidSetPinSpeed(DOTMAT_COL3, OUTPUT_HS);
	GPIO_voidSetPinSpeed(DOTMAT_COL4, OUTPUT_HS);
	GPIO_voidSetPinSpeed(DOTMAT_COL5, OUTPUT_HS);
	GPIO_voidSetPinSpeed(DOTMAT_COL6, OUTPUT_HS);
	GPIO_voidSetPinSpeed(DOTMAT_COL7, OUTPUT_HS);

    return addr_dotMatrix;
}
