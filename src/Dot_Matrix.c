#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

#include "MCAL/GPIO/GPIO_Interface.h"
#include "MCAL/STK/STK_Interface.h"

#include "HAL/Dot_Matrix/Dot_Matrix_config.h"
#include "HAL/Dot_Matrix/Dot_Matrix_Interface.h"

// #include <malloc.h>
static void matrix_set_pixel(u8 row, u8 col);
static void matrix_clr_pixel(u8 row, u8 col);

/* control of pixels */
void setPixel(u8 *buffer, u8 copy_x, u8 copy_y)
{
	if (copy_x < DOTMAT_MAX_ROWS && copy_y < DOTMAT_MAX_COLS)
	{
		SET_BIT(buffer[copy_x], copy_y);
	}
}
void clrPixel(u8 *buffer, u8 copy_x, u8 copy_y)
{
	if (copy_x < DOTMAT_MAX_ROWS && copy_y < DOTMAT_MAX_COLS)
	{
		CLR_BIT(buffer[copy_x], copy_y);
	}
}
void setRow(u8 *buffer, u8 copy_x)
{
	if (copy_x < DOTMAT_MAX_ROWS)
	{
		ASSIGN_REG(buffer[copy_x], 0xFF);
	}
}
void clrRow(u8 *buffer, u8 copy_x)

{
	if (copy_x < DOTMAT_MAX_ROWS)
	{
		ASSIGN_REG(buffer[copy_x], 0x00);
	}
}
/* control of pixels */

/* movement of pixels */
u8 movePixelUp(u8 *buffer, u8 copy_x, u8 copy_y)
{
	u8 LOC_ErrMovedPixel = OutOfBoundsException;
	if (copy_x < 0 || copy_y < 0)
	{
		// out of bounds
		u8 LOC_ErrMovedPixel = OutOfBoundsException;
	}
	else
	{
		if (GET_BIT(buffer[copy_x - 1], copy_y) == 1) // if bit up is 1, collision detected
		{
			LOC_ErrMovedPixel = CollisionDetectedException;
		}
		else
		{
			setPixel(buffer, copy_x - 1, copy_y);
			LOC_ErrMovedPixel = TRUE;
		}
	}
	return LOC_ErrMovedPixel;
}
u8 movePixelDown(u8 *buffer, u8 copy_x, u8 copy_y)
{
	u8 LOC_ErrMovedPixel = OutOfBoundsException;
	if (copy_x > DOTMAT_MAX_ROWS || copy_y > DOTMAT_MAX_COLS)
	{
		// out of bounds
		LOC_ErrMovedPixel = OutOfBoundsException;
	}
	else
	{
		if (GET_BIT(buffer[copy_x + 1], copy_y) == 1) // if bit down is 1, collision detected
		{
			LOC_ErrMovedPixel = CollisionDetectedException;
		}
		else
		{
			setPixel(buffer, copy_x + 1, copy_y);
			LOC_ErrMovedPixel = TRUE;
		}
		return LOC_ErrMovedPixel;
	}
}
u8 movePixelLeft(u8 *buffer, u8 copy_x, u8 copy_y)
{
	u8 LOC_ErrMovedPixel = OutOfBoundsException;

	if (copy_x > DOTMAT_MAX_ROWS || copy_y < 0)
	{
		// out of bounds
		LOC_ErrMovedPixel = OutOfBoundsException;
	}
	else
	{
		if (GET_BIT(buffer[copy_x], copy_y - 1)) // if bit to the left is 1, collision detected
		{
			LOC_ErrMovedPixel = CollisionDetectedException;
		}
		else
		{
			setPixel(buffer, copy_x, copy_y - 1);
		}
	}
	return LOC_ErrMovedPixel;
	// LSHIFT_REG(buffer[copy_x], 1);
}
u8 movePixelRight(u8 *buffer, u8 copy_x, u8 copy_y)
{
	u8 LOC_ErrMovedPixel = OutOfBoundsException;
	if (copy_x > DOTMAT_MAX_ROWS || copy_y > DOTMAT_MAX_COLS)
	{
		// out of bounds return false
		LOC_ErrMovedPixel = OutOfBoundsException;
	}
	else
	{
		if (GET_BIT(buffer[copy_x], copy_y + 1)) // if bit to the right is 1, collision detected
		{
			LOC_ErrMovedPixel = CollisionDetectedException;
		}
		else
		{
			setPixel(buffer, copy_x, copy_y + 1);
			LOC_ErrMovedPixel = TRUE;
		}
	}
	return LOC_ErrMovedPixel;
}
/* movement of pixels */


DotMatrix DotMatrix_init()
{
	DotMatrix Copy_DotMatrix; // = (DotMatrix *)malloc(sizeof(DotMatrix));

	//    if (addr_dotMatrix == NULL)
	//    {
	//        // Handle memory allocation error
	//        return NULL;
	//    }

	Copy_DotMatrix.setPixel = setPixel;
	Copy_DotMatrix.clrPixel = clrPixel;
	Copy_DotMatrix.setRow = setRow;
	Copy_DotMatrix.clrRow = clrRow;

	Copy_DotMatrix.movePixelUp = movePixelUp;
	Copy_DotMatrix.movePixelDown = movePixelDown;
	Copy_DotMatrix.movePixelLeft = movePixelLeft;
	Copy_DotMatrix.movePixelRight = movePixelRight;

	Copy_DotMatrix.copy_u8RowPort = DOTMAT_ROW_PORT;
	Copy_DotMatrix.copy_u8ColPort = DOTMAT_COL_PORT;
	for (u8 i = 0; i < DOTMAT_MAX_ROWS; i++)
	{
		Copy_DotMatrix.buffer[i] = 0; // initialize the buffer to Zero
	}

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

	return Copy_DotMatrix;
}

void matrix_update(DotMatrix matrix)
{

	for (u8 row = 0; row < DOTMAT_MAX_ROWS; row++)
	{
		for (u8 col = 0; col < DOTMAT_MAX_COLS; ++col)
		{
			if (1 == GET_BIT(matrix.buffer[row], col))
			{
				matrix_set_pixel(row, col);
				STK_voidSetBusyWait(250);
			}
			matrix_clr_pixel(row, col);
		}
	}
}

static void matrix_set_pixel(u8 row, u8 col)
{
	GPIO_voidSetPinValue(DOTMAT_ROW_PORT, row, OUTPUT_HIGH);
	GPIO_voidSetPinValue(DOTMAT_COL_PORT, col, OUTPUT_LOW);
}

static void matrix_clr_pixel(u8 row, u8 col)
{
	GPIO_voidSetPinValue(DOTMAT_ROW_PORT, row, OUTPUT_LOW);
	GPIO_voidSetPinValue(DOTMAT_COL_PORT, col, OUTPUT_HIGH);
}
