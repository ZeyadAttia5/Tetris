#include "APP/Tetris.h"
#include "MCAL/EXTI/EXTI_Interface.h"
#include "MCAL/NVIC/NVIC_Interface.h"
#include "MCAL/STK/STK_Interface.h"
#include <stdlib.h>

// four becuase it is TETRis
#define MAX_PIXELS_PER_BLOCK 4

#define TETRIS_ROTATION_0 0
#define TETRIS_ROTATION_90 1
#define TETRIS_ROTATION_180 2
#define TETRIS_ROTATION_270 3
#define TETRIS_ROTATIONS_COUNT 4

extern Tetris game_controller;
s8 Tetris_rotate(void);
static s8 Tetris_drawShape2(void);
static void Tetris_draw_I();
static void Tetris_draw_O();
static void Tetris_draw_T();
static void Tetris_draw_J();
static void Tetris_draw_L();
static void Tetris_draw_S();
static void Tetris_draw_Z();

s8 Tetris_moveBlockDown();
s8 Tetris_moveBlockLeft();
s8 Tetris_moveBlockRight();

s8 Tetris_drawShape(u8 copy_u8X, u8 copy_u8Y)
{
	// static u8 shape=3;

	// static s8 LOC_s8BlockNum = TETRIS_SHAPE_S;
	// u8 LOC_u8ErrCode = OutOfBoundsException;
	// game_controller.active_block.center_x = copy_u8X;
	// game_controller.active_block.center_y = copy_u8Y;
	// game_controller.active_block.type = LOC_s8BlockNum;
	// game_controller.active_block.rotation = TETRIS_ROTATION_0; // TODO make rotation random
	// Block new_block = game_controller.active_block;

	s8 LOC_s8BlockNum = (rand() % TETRIS_SHAPE_COUNT);
	DotMatrix *board = &game_controller.board;

	// create new block, initialize its center
	Block new_block;
	new_block.points[0].x = copy_u8X;
	new_block.points[0].y = copy_u8Y;
	new_block.type = LOC_s8BlockNum;
	new_block.rotation = TETRIS_ROTATION_0;
	game_controller.active_block = new_block;
	//	LOC_s8BlockNum++;

	// initialize the other 3 points
	s8 LOC_u8ErrCode = 0;
	switch (new_block.type)
	{
	case TETRIS_SHAPE_I:
		Tetris_draw_I();
		break;
	case TETRIS_SHAPE_O:
		Tetris_draw_O();
		break;
	case TETRIS_SHAPE_T:
		Tetris_draw_T();
		break;
	case TETRIS_SHAPE_J:
		Tetris_draw_J();
		break;
	case TETRIS_SHAPE_L:
		Tetris_draw_L();
		break;
	case TETRIS_SHAPE_S:
		Tetris_draw_S();
		break;
	case TETRIS_SHAPE_Z:
		Tetris_draw_Z();
		break;

	default:
		LOC_s8BlockNum = -2; // drew nothing
		break;
	}

	// update the new block
	new_block = game_controller.active_block;

	/* check for boundaries */
	for (u8 row = 0; row < MAX_PIXELS_PER_BLOCK; row++)
	{
		// if the point is out of bounds, return
		if (new_block.points[row].x >= DOTMAT_MAX_ROWS || new_block.points[row].y >= DOTMAT_MAX_COLS)
			return OutOfBoundsException;
	}
	/* check for boundaries */

	/* check for collision */
	for (u8 row = 0; row < MAX_PIXELS_PER_BLOCK; row++)
	{
		// if there is already a one in the buffer in that pixel, then collision detected, RETURN
		if (1 == GET_BIT(board->buffer[new_block.points[row].x], new_block.points[row].y))
			return CollisionDetectedException;
	}
	/* check for collision */

	/* draw the shape */
	for (u8 row = 0; row < MAX_PIXELS_PER_BLOCK; row++)
	{
		board->setPixel(board->buffer, new_block.points[row].x, new_block.points[row].y);
	}
	/* draw the shape */
	return LOC_s8BlockNum;
}

static s8 Tetris_drawShape2(void)
{
	DotMatrix *board = &game_controller.board;
	Block *new_block = &game_controller.active_block;

	s8 LOC_u8ErrCode = TRUE;
	switch (game_controller.active_block.type)
	{
	case TETRIS_SHAPE_I:
		Tetris_draw_I();
		break;
	case TETRIS_SHAPE_O:
		Tetris_draw_O();
		break;
	case TETRIS_SHAPE_T:
		Tetris_draw_T();
		break;
	case TETRIS_SHAPE_J:
		Tetris_draw_J();
		break;
	case TETRIS_SHAPE_L:
		Tetris_draw_L();
		break;
	case TETRIS_SHAPE_S:
		Tetris_draw_S();
		break;
	case TETRIS_SHAPE_Z:
		Tetris_draw_Z();
		break;

	default:
		break;
	}

	/* check for boundaries */
	for (u8 row = 0; row < MAX_PIXELS_PER_BLOCK; row++)
	{
		// if the point is out of bounds, return
		if (new_block->points[row].x >= DOTMAT_MAX_ROWS || new_block->points[row].y >= DOTMAT_MAX_COLS)
			return OutOfBoundsException;
	}
	/* check for boundaries */

	/* check for collision */
	for (u8 row = 0; row < MAX_PIXELS_PER_BLOCK; row++)
	{
		// if there is already a one in the buffer in that pixel, then collision detected, RETURN
		if (1 == GET_BIT(board->buffer[new_block->points[row].x], new_block->points[row].y))
			return CollisionDetectedException;
	}
	/* check for collision */

	/* draw the shape */
	for (u8 row = 0; row < MAX_PIXELS_PER_BLOCK; row++)
	{
		board->setPixel(board->buffer, new_block->points[row].x, new_block->points[row].y);
	}
	/* draw the shape */
	return LOC_u8ErrCode;
}

Tetris Tetris_init(void)
{
	Tetris game_controller;
	game_controller.board = DotMatrix_init();
	game_controller.drawShape = Tetris_drawShape;
	EXTI_voidInit(EXTI8);
	EXTI_voidInit(EXTI9);
	EXTI_voidInit(EXTI10);
	NVIC_voidSetPriorityConfig(G0_SG16);
	EXTI_voidSetCallBack(Tetris_moveBlockRight, EXTI8);
	EXTI_voidSetCallBack(Tetris_moveBlockLeft, EXTI9);
	EXTI_voidSetCallBack(Tetris_rotate, EXTI10);
	//	STK_voidSetIntervalPeriodic(000000, Tetris_moveBlockDown);
	return game_controller;
}

Tetris_removeActiveBlock()
{

	Block *activeBlock = &game_controller.active_block;
	DotMatrix *board = &game_controller.board;
	for (u8 row = 0; row < MAX_PIXELS_PER_BLOCK; row++)
	{
		board->clrPixel(board->buffer, activeBlock->points[row].x, activeBlock->points[row].y);
	}
}

s8 Tetris_rotate(void)
{
	s8 LOC_u8RotationErr = 1;

	Tetris_removeActiveBlock(); // remove the current block to prevent it from colliding with itself

	// there are only 4 rotations:   0 -> 360
	game_controller.active_block.rotation = (game_controller.active_block.rotation + 1) % 4;
	LOC_u8RotationErr = Tetris_drawShape2();

	// if there was an error rotating, draw the block with its old rotation.
	if (LOC_u8RotationErr != TRUE)
	{
		game_controller.active_block.rotation = (game_controller.active_block.rotation - 1) % 4;
		Tetris_drawShape2();
	}

	return LOC_u8RotationErr;
}

s8 Tetris_moveBlockRight()
{
	for (u8 point = 0; point < MAX_PIXELS_PER_BLOCK; point++)
	{
		if (game_controller.active_block.points[point].y == 7)
		{
			return OutOfBoundsException;
		}
	}
	s8 LOC_u8RotationErr = 1;

	Tetris_removeActiveBlock(); // remove the current block to prevent it from colliding with itself

	++game_controller.active_block.points[0].y; // there are only 4 rotations:   0� -> 360�
	LOC_u8RotationErr = Tetris_drawShape2();

	// if there was an error rotating, draw the block with its old rotation.
	if (LOC_u8RotationErr != TRUE)
	{
		--game_controller.active_block.points[0].y;
		Tetris_drawShape2();
	}

	return LOC_u8RotationErr;
}

s8 Tetris_moveBlockLeft()
{

	for (u8 point = 0; point < MAX_PIXELS_PER_BLOCK; point++)
	{
		if (game_controller.active_block.points[point].y == 0)
		{
			return OutOfBoundsException;
		}
	}

	s8 LOC_u8RotationErr = 1;

	Tetris_removeActiveBlock(); // remove the current block to prevent it from colliding with itself

	--game_controller.active_block.points[0].y;
	LOC_u8RotationErr = Tetris_drawShape2();

	// if there was an error rotating, draw the block with its old rotation.
	if (LOC_u8RotationErr != TRUE)
	{
		++game_controller.active_block.points[0].y;
		Tetris_drawShape2();
	}
	return LOC_u8RotationErr;
}

s8 Tetris_moveBlockDown()
{
	s8 LOC_u8RotationErr = 1;
	static u8 LOC_u8SpawnCol = 4;

	for (u8 row = 0; row < MAX_PIXELS_PER_BLOCK; row++)
	{
		if (game_controller.active_block.points[row].x == 0)
		{
			// reached the bottom, create new block
			game_controller.drawShape(DOTMAT_MAX_ROWS - 1, LOC_u8SpawnCol);
			return TRUE;
		}
	}

	Tetris_removeActiveBlock(); // remove the current block to prevent it from colliding with itself

	--game_controller.active_block.points[0].x;
	LOC_u8RotationErr = Tetris_drawShape2();

	// if there was an error in movement, draw the block with its old location and spawn a new block
	if (LOC_u8RotationErr != TRUE)
	{
		++game_controller.active_block.points[0].x;
		Tetris_drawShape2();
		LOC_u8RotationErr = game_controller.drawShape(DOTMAT_MAX_ROWS - 1, LOC_u8SpawnCol);

		// //cant move the new block into the matrix
		// if (LOC_u8RotationErr == CollisionDetectedException && game_controller.active_block.points[0].x > 7);
		// {

		// 	/* Game Over */
		// 	NVIC_u8DisablePerInt(23);
		// 	NVIC_u8DisablePerInt(40);
		// 	while (1)
		// 	{
		// 		matrix_update(game_controller.board, 100000);
		// 	}
		// }
	}
	return LOC_u8RotationErr;
}

void Tetris_UpdateBoard()
{
	s8 LOC_s8RemovedBlock = -5;
	static u16 LOC_u16Count = 0;
	if (LOC_u16Count < 500)
	{
		matrix_update(game_controller.board, 250);
		LOC_u16Count++;
	}
	else
	{
		LOC_u16Count = 0;
		Tetris_moveBlockDown();
		// matrix_update(game_controller.board, 250);
	}

	// clear full rows
	for (u8 row = 0; row < DOTMAT_MAX_ROWS; row++)
	{
		if (game_controller.board.buffer[row] == 0xFF)
		{

			STK_voidSetBusyWait(2000000);
			game_controller.board.clrRow(game_controller.board.buffer, row);
			Tetris_removeActiveBlock();
			LOC_s8RemovedBlock = TRUE;
			for (u8 remainingRows = row + 1; remainingRows < DOTMAT_MAX_ROWS; remainingRows++)
			{
				game_controller.board.buffer[remainingRows - 1] = game_controller.board.buffer[remainingRows];
			}
		}
		else
		{
			// do nothing
		}
	}

	if (LOC_s8RemovedBlock == TRUE)
	{
		// create a new block
		Tetris_drawShape(DOTMAT_MAX_ROWS - 1, DOTMAT_MAX_COLS / 2);
	}
}

static void Tetris_draw_I()
{
	Block *new_block = &game_controller.active_block;

	switch (new_block->rotation)
	{
	case TETRIS_ROTATION_0:

		/* New Location */
		new_block->points[1].x = new_block->points[0].x - 1;
		new_block->points[1].y = new_block->points[0].y;

		new_block->points[2].x = new_block->points[0].x - 2;
		new_block->points[2].y = new_block->points[0].y;

		new_block->points[3].x = new_block->points[0].x - 3;
		new_block->points[3].y = new_block->points[0].y;
		/* New Location */
		break;

	case TETRIS_ROTATION_90:

		/* New Location */
		new_block->points[1].x = new_block->points[0].x;
		new_block->points[1].y = new_block->points[0].y - 1;

		new_block->points[2].x = new_block->points[0].x;
		new_block->points[2].y = new_block->points[0].y - 2;

		new_block->points[3].x = new_block->points[0].x;
		new_block->points[3].y = new_block->points[0].y - 3;
		/* New Location */

		break;

	case TETRIS_ROTATION_180:
		/* New Location */
		new_block->points[1].x = new_block->points[0].x + 1;
		new_block->points[1].y = new_block->points[0].y;

		new_block->points[2].x = new_block->points[0].x + 2;
		new_block->points[2].y = new_block->points[0].y;

		new_block->points[3].x = new_block->points[0].x + 3;
		new_block->points[3].y = new_block->points[0].y;
		/* New Location */

		break;
	case TETRIS_ROTATION_270:

		/* New Location */
		new_block->points[1].x = new_block->points[0].x;
		new_block->points[1].y = new_block->points[0].y + 1;

		new_block->points[2].x = new_block->points[0].x;
		new_block->points[2].y = new_block->points[0].y + 2;

		new_block->points[3].x = new_block->points[0].x;
		new_block->points[3].y = new_block->points[0].y + 3;
		/* New Location */
		break;
	default:
		// do nothing
		break;
	}
}

static void Tetris_draw_O()
{
	Block *new_block = &game_controller.active_block;

	/* New Location */
	new_block->points[1].x = new_block->points[0].x - 1;
	new_block->points[1].y = new_block->points[0].y;

	new_block->points[2].x = new_block->points[0].x;
	new_block->points[2].y = new_block->points[0].y + 1;

	new_block->points[3].x = new_block->points[0].x - 1;
	new_block->points[3].y = new_block->points[0].y + 1;
	/* New Location */
}

static void Tetris_draw_T()
{
	Block *new_block = &game_controller.active_block;

	switch (new_block->rotation)
	{
	case TETRIS_ROTATION_0:

		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y - 1;

		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x - 1;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y + 1;
		break;

	case TETRIS_ROTATION_90:

		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x - 1;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y + 1;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x + 1;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y;
		break;
	case TETRIS_ROTATION_180:

		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y - 1;

		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x + 1;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y + 1;
		break;
	case TETRIS_ROTATION_270:

		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y - 1;

		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x + 1;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x - 1;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y;
		break;
	default:
		break;
	}
}

static void Tetris_draw_J()
{
	Block *new_block = &game_controller.active_block;
	switch (new_block->rotation)
	{
	case TETRIS_ROTATION_0:

		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y - 1;

		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x + 1;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x + 2;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y;
		break;

	case TETRIS_ROTATION_90:

		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x + 1;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y + 1;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y + 2;
		break;

	case TETRIS_ROTATION_180:

		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y + 1;

		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x - 1;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x - 2;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y;
		break;

	case TETRIS_ROTATION_270:

		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x - 1;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y - 1;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y - 2;
		break;

	default:
		break;
	}
}

static void Tetris_draw_L()
{
	Block *new_block = &game_controller.active_block;

	switch (new_block->rotation)
	{
	case TETRIS_ROTATION_0:

		// save the location of the points by using the center
		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y + 1;

		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x + 1;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x + 2;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y;
		break;

	case TETRIS_ROTATION_90:

		// save the location of the points by using the center
		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x - 1;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y + 1;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y + 2;
		break;

	case TETRIS_ROTATION_180:

		// save the location of the points by using the center
		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y - 1;

		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x - 1;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x - 2;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y;
		break;

	case TETRIS_ROTATION_270:

		// save the location of the points by using the center
		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x + 1;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y - 1;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y - 2;
		break;

	default:
		break;
	}
}

static void Tetris_draw_S()
{
	Block *new_block = &game_controller.active_block;
	new_block->rotation %= 2;

	switch (new_block->rotation)
	{
	case TETRIS_ROTATION_0:

		// save the location of the points by using the center
		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y - 1;

		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x + 1;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x + 1;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y + 1;
		break;
	case TETRIS_ROTATION_90:

		// save the location of the points by using the center
		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y - 1;

		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x - 1;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x + 1;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y - 1;
		break;

	default:
		// do nothing
		break;
	}
}

static void Tetris_draw_Z()
{
	Block *new_block = &game_controller.active_block;
	new_block->rotation %= 2;

	switch (new_block->rotation)
	{
	case TETRIS_ROTATION_0:

		// save the location of the points by using the center
		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y + 1;

		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x + 1;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x + 1;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y - 1;
		break;
	case TETRIS_ROTATION_90:

		// save the location of the points by using the center
		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y + 1;

		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x - 1;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x + 1;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y + 1;
		break;
	default:
		// do nothing
		break;
	}
}
