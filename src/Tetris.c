#include "APP/Tetris.h"
#include "MCAL/EXTI/EXTI_Interface.h"
#include "MCAL/NVIC/NVIC_Interface.h"
#include "MCAL/STK/STK_Interface.h"
// #include <stddef.h>

// #define container_of(ptr, type, member) ({                      \
//         const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
//         (type *)( (char *)__mptr - offsetof(type,member) ); })

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
static s8 Tetris_draw_I();
static s8 Tetris_draw_O();
static s8 Tetris_draw_T();
static s8 Tetris_draw_J();
static s8 Tetris_draw_L();
static s8 Tetris_draw_S();
static s8 Tetris_draw_Z();

static void Tetris_remove_I();
static void Tetris_remove_O();
static void Tetris_remove_T();
static void Tetris_remove_J();
static void Tetris_remove_L();
static void Tetris_remove_S();
static void Tetris_remove_Z();

s8 Tetris_moveBlockDown();
s8 Tetris_moveBlockLeft();
s8 Tetris_moveBlockRight();

s8 Tetris_drawShape(Tetris *board, u8 copy_u8X, u8 copy_u8Y)
{
	//    s8 LOC_s8BlockNum = (rand() % TETRIS_SHAPE_COUNT);
	// static u8 shape=3;

	static s8 LOC_s8BlockNum = TETRIS_SHAPE_Z;
	// u8 LOC_u8ErrCode = OutOfBoundsException;
	// game_controller.active_block.center_x = copy_u8X;
	// game_controller.active_block.center_y = copy_u8Y;
	// game_controller.active_block.type = LOC_s8BlockNum;
	// game_controller.active_block.rotation = TETRIS_ROTATION_0; // TODO make rotation random
	// Block new_block = game_controller.active_block;
	Block new_block;
	new_block.points[0].x = copy_u8X;
	new_block.points[0].y = copy_u8Y;
	new_block.type = LOC_s8BlockNum;
	new_block.rotation = TETRIS_ROTATION_0;
	//	LOC_s8BlockNum++;

	board->active_block = new_block;
	//	LOC_s8BlockNum++;

	s8 LOC_u8ErrCode = 0;
	switch (new_block.type)
	{
	case TETRIS_SHAPE_I:
		LOC_u8ErrCode = Tetris_draw_I();
		break;
	case TETRIS_SHAPE_O:
		LOC_u8ErrCode = Tetris_draw_O();
		break;
	case TETRIS_SHAPE_T:
		LOC_u8ErrCode = Tetris_draw_T();
		break;
	case TETRIS_SHAPE_J:
		LOC_u8ErrCode = Tetris_draw_J();
		break;
	case TETRIS_SHAPE_L:
		LOC_u8ErrCode = Tetris_draw_L(&(board->board), new_block);
		break;
	case TETRIS_SHAPE_S:
		LOC_u8ErrCode = Tetris_draw_S(&(board->board), new_block);
		break;
	case TETRIS_SHAPE_Z:
		LOC_u8ErrCode = Tetris_draw_Z(&(board->board), new_block);
		break;

	default:
		LOC_s8BlockNum = -2; // drew nothing
		break;
	}

	return LOC_s8BlockNum;
}

static s8 Tetris_drawShape2(void)
{
	s8 LOC_u8ErrCode = TRUE;
	switch (game_controller.active_block.type)
	{
	case TETRIS_SHAPE_I:
		LOC_u8ErrCode = Tetris_draw_I();
		break;
	case TETRIS_SHAPE_O:
		LOC_u8ErrCode = Tetris_draw_O();
		break;
	case TETRIS_SHAPE_T:
		LOC_u8ErrCode = Tetris_draw_T();
		break;
	case TETRIS_SHAPE_J:
		LOC_u8ErrCode = Tetris_draw_J();
		break;
	case TETRIS_SHAPE_L:
		LOC_u8ErrCode = Tetris_draw_L();
		break;
	case TETRIS_SHAPE_S:
		LOC_u8ErrCode = Tetris_draw_S();
		break;
	case TETRIS_SHAPE_Z:
		LOC_u8ErrCode = Tetris_draw_Z();
		break;

	default:
		break;
	}
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
			return;
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
			return;
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

	switch (game_controller.active_block.type)
	case TETRIS_SHAPE_I:
		if (game_controller.active_block.points[0].x == 0 || game_controller.active_block.points[0].x - 3 == 0)
		{
			// reached the bottom, create new block
			game_controller.drawShape(&game_controller, 7, 7);
		}

	Tetris_removeActiveBlock(); // remove the current block to prevent it from colliding with itself

	--game_controller.active_block.points[0].x;
	LOC_u8RotationErr = Tetris_drawShape2();

	// if there was an error rotating, draw the block with its old rotation.
	if (LOC_u8RotationErr != TRUE)
	{
		++game_controller.active_block.points[0].x;
		game_controller.failedDown++;
		Tetris_drawShape2();
		if (game_controller.failedDown == 3)
		{
			/* Game Over */
			NVIC_u8DisablePerInt(23);
			NVIC_u8DisablePerInt(40);
			while (1)
			{
				matrix_update(game_controller.board, 100000);
			}
		}
	}
	return LOC_u8RotationErr;
}

void Tetris_UpdateBoard()
{

	static u16 LOC_u16Count = 0;
	if (LOC_u16Count < 1000)
	{
		matrix_update(game_controller.board, 250);
		LOC_u16Count++;
	}
	else
	{
		LOC_u16Count = 0;
		// Tetris_moveBlockDown();
		matrix_update(game_controller.board, 250);
	}

	// clear full rows
	for (u8 row = 0; row < DOTMAT_MAX_ROWS; row++)
	{
		if (game_controller.board.buffer[row] == 0xFF)
		{
			game_controller.board.clrRow(game_controller.board.buffer, row);
			Tetris_removeActiveBlock();
		}
		else
		{
			// do nothing
		}
	}
}

static s8 Tetris_draw_I()
{
	DotMatrix *board = &game_controller.board;
	Block *new_block = &game_controller.active_block;

	u8 LOC_u8Center_x = new_block->points[0].x;
	u8 LOC_u8Center_y = new_block->points[0].y;
	s8 LOC_s8DrawStatus = TRUE;

	u8 movements = 0;
	switch (new_block->rotation)
	{
	case TETRIS_ROTATION_0:
		for (; movements < MAX_PIXELS_PER_BLOCK - 1; movements++)
		{
			LOC_s8DrawStatus = board->movePixelDown(board->buffer, LOC_u8Center_x--, LOC_u8Center_y, ON_MOVE_SET_OLD);
		}
		if (LOC_s8DrawStatus != TRUE)
		{
			if (LOC_s8DrawStatus == OutOfBoundsException)
				LOC_u8Center_x = 0;
			for (u8 reverse = 0; reverse < movements; reverse++)
			{
				board->clrPixel(board->buffer, LOC_u8Center_x++,
								LOC_u8Center_y);
			}
			return LOC_s8DrawStatus;
		}
		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x - 1;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x - 2;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x - 3;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y;
		break;

	case TETRIS_ROTATION_90:
		for (movements = 0; movements < MAX_PIXELS_PER_BLOCK - 1; movements++)
		{
			LOC_s8DrawStatus = board->movePixelLeft(board->buffer,
													LOC_u8Center_x, LOC_u8Center_y--, ON_MOVE_SET_OLD);
		}
		if (LOC_s8DrawStatus != TRUE)
		{
			if (LOC_s8DrawStatus == OutOfBoundsException)
				LOC_u8Center_y = 0;
			for (u8 reverse = 0; reverse < movements; reverse++)
			{
				board->clrPixel(board->buffer, LOC_u8Center_x,
								LOC_u8Center_y++);
			}
			return LOC_s8DrawStatus;
		}

		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y - 1;

		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y - 2;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y - 3;
		break;
	case TETRIS_ROTATION_180:
		for (movements = 0; movements < MAX_PIXELS_PER_BLOCK - 1; movements++)
		{
			LOC_s8DrawStatus = board->movePixelUp(board->buffer,
												  LOC_u8Center_x++, LOC_u8Center_y, ON_MOVE_SET_OLD);
		}
		if (LOC_s8DrawStatus != TRUE)
		{
			if (LOC_s8DrawStatus == OutOfBoundsException)
				LOC_u8Center_x = 0;
			for (u8 reverse = 0; reverse < movements; reverse++)
			{
				board->clrPixel(board->buffer, LOC_u8Center_x--,
								LOC_u8Center_y);
			}
			return LOC_s8DrawStatus;
		}

		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x + 1;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x + 2;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x + 3;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y;
		break;
	case TETRIS_ROTATION_270:
		for (movements = 0; movements < MAX_PIXELS_PER_BLOCK - 1; movements++)
		{
			LOC_s8DrawStatus = board->movePixelRight(board->buffer,
													 LOC_u8Center_x, LOC_u8Center_y++, ON_MOVE_SET_OLD);
		}
		if (LOC_s8DrawStatus != TRUE)
		{
			if (LOC_s8DrawStatus == OutOfBoundsException)
				LOC_u8Center_y = LOC_u8Center_y;
			for (u8 reverse = 0; reverse < movements; reverse++)
			{
				board->clrPixel(board->buffer, LOC_u8Center_x,
								LOC_u8Center_y++);
			}
			return LOC_s8DrawStatus;
		}
		break;
		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y + 1;

		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y + 2;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y + 3;
	default:
		// do nothing
		break;
	}
	return LOC_s8DrawStatus;
}

static s8 Tetris_draw_O()
{
	DotMatrix *board = &game_controller.board;
	Block *new_block = &game_controller.active_block;
	u8 LOC_u8Center_x = new_block->points[0].x;
	u8 LOC_u8Center_y = new_block->points[0].y;
	s8 LOC_s8DrawStatus = TRUE;

	LOC_s8DrawStatus = board->movePixelRight(board->buffer, LOC_u8Center_x,
											 LOC_u8Center_y, ON_MOVE_SET_OLD);
	if (LOC_s8DrawStatus != TRUE)
	{
		board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y); // clear the current pixel
		return LOC_s8DrawStatus;
	}

	--LOC_u8Center_x; // move to next row
	LOC_s8DrawStatus = board->movePixelRight(board->buffer, LOC_u8Center_x, LOC_u8Center_y,
											 ON_MOVE_SET_OLD);
	if (LOC_s8DrawStatus != TRUE)
	{
		board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y); // clear the current pixel
		return LOC_s8DrawStatus;
	}

	game_controller.active_block.points[1].x = game_controller.active_block.points[0].x - 1;
	game_controller.active_block.points[1].y = game_controller.active_block.points[0].y;

	game_controller.active_block.points[2].x = game_controller.active_block.points[0].x;
	game_controller.active_block.points[2].y = game_controller.active_block.points[0].y + 1;

	game_controller.active_block.points[3].x = game_controller.active_block.points[0].x - 1;
	game_controller.active_block.points[3].y = game_controller.active_block.points[0].y + 1;
}

static s8 Tetris_draw_T()
{
	DotMatrix *board = &game_controller.board;
	Block *new_block = &game_controller.active_block;
	u8 LOC_u8Center_x = new_block->points[0].x;
	u8 LOC_u8Center_y = new_block->points[0].y;
	s8 LOC_s8DrawStatus = TRUE;

	switch (new_block->rotation)
	{
	case TETRIS_ROTATION_0:
		LOC_s8DrawStatus = board->movePixelLeft(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// nothing is drawn return error status
			return LOC_s8DrawStatus;
		}
		LOC_s8DrawStatus = board->movePixelDown(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// clear the center pixel and the one to its left
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y - 1);
			return LOC_s8DrawStatus;
		}

		LOC_s8DrawStatus = board->movePixelRight(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);

		if (LOC_s8DrawStatus != TRUE)
		{
			// clear the center pixel and the one to its left and to bottom
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y - 1);
			board->clrPixel(board->buffer, LOC_u8Center_x - 1, LOC_u8Center_y);
			return LOC_s8DrawStatus;
		}

		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y - 1;

		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x - 1;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y + 1;
		break;

	case TETRIS_ROTATION_90:

		LOC_s8DrawStatus = board->movePixelDown(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// Nothing is drawn, just return the error
			return LOC_s8DrawStatus;
		}

		LOC_s8DrawStatus = board->movePixelRight(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// clear the center pixel and the one below it
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);
			board->clrPixel(board->buffer, LOC_u8Center_x - 1, LOC_u8Center_y);
			return LOC_s8DrawStatus;
		}

		LOC_s8DrawStatus = board->movePixelUp(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// clear the center pixel and the one to its right and to bottom
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y + 1);
			board->clrPixel(board->buffer, LOC_u8Center_x - 1, LOC_u8Center_y);
			return LOC_s8DrawStatus;
		}

		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x - 1;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y + 1;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x + 1;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y;
		break;
	case TETRIS_ROTATION_180:

		LOC_s8DrawStatus = board->movePixelRight(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// Nothing is drawn, just return the error
			return LOC_s8DrawStatus;
		}

		LOC_s8DrawStatus = board->movePixelUp(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// clear the center pixel and the one above it
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);
			board->clrPixel(board->buffer, LOC_u8Center_x + 1, LOC_u8Center_y);
			return LOC_s8DrawStatus;
		}

		LOC_s8DrawStatus = board->movePixelLeft(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// clear the center pixel and the one to its right and top
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y + 1);
			board->clrPixel(board->buffer, LOC_u8Center_x + 1, LOC_u8Center_y);
			return LOC_s8DrawStatus;
		}

		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y - 1;

		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x + 1;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y + 1;
		break;
	case TETRIS_ROTATION_270:
		LOC_s8DrawStatus = board->movePixelDown(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// Nothing is drawn, just return the error
			return LOC_s8DrawStatus;
		}

		LOC_s8DrawStatus = board->movePixelLeft(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// clear the center pixel and the one to its left
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y - 1);
			return LOC_s8DrawStatus;
		}

		LOC_s8DrawStatus = board->movePixelUp(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// clear the center pixel and the one to its left and top
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y - 1);
			board->clrPixel(board->buffer, LOC_u8Center_x + 1, LOC_u8Center_y);
			return LOC_s8DrawStatus;
		}

		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y - 1;

		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x + 1;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x - 1;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y;

	default:
		break;
	}

	return LOC_s8DrawStatus;
}

static s8 Tetris_draw_J()
{
	DotMatrix *board = &game_controller.board;
	Block *new_block = &game_controller.active_block;
	u8 LOC_u8Center_x = new_block->points[0].x;
	u8 LOC_u8Center_y = new_block->points[0].y;
	s8 LOC_s8DrawStatus = TRUE;
	switch (new_block->rotation)
	{
	case TETRIS_ROTATION_0:
		LOC_s8DrawStatus = board->movePixelLeft(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			return LOC_s8DrawStatus;
		}

		LOC_s8DrawStatus = board->movePixelUp(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y - 1);
			return LOC_s8DrawStatus;
		}
		LOC_u8Center_x++;

		LOC_s8DrawStatus = board->movePixelUp(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			board->clrPixel(board->buffer, LOC_u8Center_x--,
							LOC_u8Center_y);
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y - 1);
			return LOC_s8DrawStatus;
		}

		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y - 1;

		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x + 1;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x + 2;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y;
		break;

	case TETRIS_ROTATION_90:
		LOC_s8DrawStatus = board->movePixelUp(board->buffer, LOC_u8Center_x,
											  LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			return LOC_s8DrawStatus;
		}

		LOC_s8DrawStatus = board->movePixelRight(board->buffer, LOC_u8Center_x,
												 LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);
			board->clrPixel(board->buffer, LOC_u8Center_x + 1,
							LOC_u8Center_y);
			return LOC_s8DrawStatus;
		}
		LOC_u8Center_y++;

		LOC_s8DrawStatus = board->movePixelRight(board->buffer, LOC_u8Center_x,
												 LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			board->clrPixel(board->buffer, LOC_u8Center_x,
							LOC_u8Center_y--);
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);
			board->clrPixel(board->buffer, LOC_u8Center_x + 1,
							LOC_u8Center_y);
			return LOC_s8DrawStatus;
		}

		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x + 1;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y + 1;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y + 2;
		break;

	case TETRIS_ROTATION_180:
		LOC_s8DrawStatus = board->movePixelRight(board->buffer, LOC_u8Center_x,
												 LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			return LOC_s8DrawStatus;
		}

		LOC_s8DrawStatus = board->movePixelDown(board->buffer, LOC_u8Center_x,
												LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);
			board->clrPixel(board->buffer, LOC_u8Center_x,
							LOC_u8Center_y + 1);
			return LOC_s8DrawStatus;
		}
		LOC_u8Center_x--;

		LOC_s8DrawStatus = board->movePixelDown(board->buffer, LOC_u8Center_x,
												LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			board->clrPixel(board->buffer, LOC_u8Center_x--,
							LOC_u8Center_y);
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);
			board->clrPixel(board->buffer, LOC_u8Center_x,
							LOC_u8Center_y + 1);
			return LOC_s8DrawStatus;
		}
		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y + 1;

		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x - 1;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x - 2;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y;
		break;

	case TETRIS_ROTATION_270:
		LOC_s8DrawStatus = board->movePixelDown(board->buffer, LOC_u8Center_x,
												LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			return LOC_s8DrawStatus;
		}

		LOC_s8DrawStatus = board->movePixelLeft(board->buffer, LOC_u8Center_x,
												LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);
			board->clrPixel(board->buffer, LOC_u8Center_x - 1,
							LOC_u8Center_y);
			return LOC_s8DrawStatus;
		}
		LOC_u8Center_y--;

		LOC_s8DrawStatus = board->movePixelLeft(board->buffer, LOC_u8Center_x,
												LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			board->clrPixel(board->buffer, LOC_u8Center_x,
							LOC_u8Center_y++);
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);
			board->clrPixel(board->buffer, LOC_u8Center_x - 1,
							LOC_u8Center_y);
			return LOC_s8DrawStatus;
		}
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
	return LOC_s8DrawStatus;
}

static s8 Tetris_draw_L()
{
	DotMatrix *board = &game_controller.board;
	Block *new_block = &game_controller.active_block;
	u8 LOC_u8Center_x = new_block->points[0].x;
	u8 LOC_u8Center_y = new_block->points[0].y;
	s8 LOC_s8DrawStatus = TRUE;

	switch (new_block->rotation)
	{
	case TETRIS_ROTATION_0:
		LOC_s8DrawStatus = board->movePixelRight(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// nothing to clear, just return the error
			return LOC_s8DrawStatus;
		}

		LOC_s8DrawStatus = board->movePixelUp(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// clear the center pixel and the one to its right
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y + 1);
			return LOC_s8DrawStatus;
		}

		LOC_s8DrawStatus = board->movePixelUp(board->buffer, LOC_u8Center_x + 1, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// clear the center pixel and the one to its right and the one above it
			board->clrPixel(board->buffer, LOC_u8Center_x + 1, LOC_u8Center_y); // top pixel
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);		// center
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y + 1); // to its right
			return LOC_s8DrawStatus;
		}

		// save the location of the points by using the center
		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y + 1;

		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x + 1;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x + 2;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y;
		break;

	case TETRIS_ROTATION_90:

		LOC_s8DrawStatus = board->movePixelDown(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// nothing to clear, just return the error
			return LOC_s8DrawStatus;
		}

		LOC_s8DrawStatus = board->movePixelRight(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// clear the center pixel and the one below it
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);
			board->clrPixel(board->buffer, LOC_u8Center_x - 1, LOC_u8Center_y);
			return LOC_s8DrawStatus;
		}

		LOC_s8DrawStatus = board->movePixelRight(board->buffer, LOC_u8Center_x, LOC_u8Center_y + 1, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// clear the center pixel, one below it, and one to its right
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);		// center
			board->clrPixel(board->buffer, LOC_u8Center_x - 1, LOC_u8Center_y); // bottom pixel
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y + 1); // to its right
			return LOC_s8DrawStatus;
		}

		// save the location of the points by using the center
		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x - 1;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y + 1;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y + 2;
		break;

	case TETRIS_ROTATION_180:

		LOC_s8DrawStatus = board->movePixelLeft(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// nothing to clear, just return the error
			return LOC_s8DrawStatus;
		}

		LOC_s8DrawStatus = board->movePixelDown(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// clear the center pixel and the one to its left
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y - 1);
			return LOC_s8DrawStatus;
		}

		LOC_s8DrawStatus = board->movePixelDown(board->buffer, LOC_u8Center_x - 1, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// clear the center pixel and the one to its left and the one below it
			board->clrPixel(board->buffer, LOC_u8Center_x - 1, LOC_u8Center_y); // bottom pixel
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);		// center pixel
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y - 1); // left   pixel
			return LOC_s8DrawStatus;
		}

		// save the location of the points by using the center
		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y - 1;

		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x - 1;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x - 2;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y;
		break;

	case TETRIS_ROTATION_270:
		LOC_s8DrawStatus = board->movePixelUp(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// nothing to clear, just return the error
			return LOC_s8DrawStatus;
		}

		LOC_s8DrawStatus = board->movePixelLeft(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// clear the center pixel and the one above it
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);
			board->clrPixel(board->buffer, LOC_u8Center_x + 1, LOC_u8Center_y);
			return LOC_s8DrawStatus;
		}

		LOC_s8DrawStatus = board->movePixelLeft(board->buffer, LOC_u8Center_x, LOC_u8Center_y - 1, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// clear the center pixel, one above it, and one to its left
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);		// center
			board->clrPixel(board->buffer, LOC_u8Center_x + 1, LOC_u8Center_y); // top pixel
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y - 1); // to its left
			return LOC_s8DrawStatus;
		}

		// save the location of the points by using the center
		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x + 1;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y - 1;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y - 2;
		break;

		break;
	default:
		break;
	}

	return LOC_s8DrawStatus;
}

static s8 Tetris_draw_S()
{
	DotMatrix *board = &game_controller.board;
	Block *new_block = &game_controller.active_block;
	u8 LOC_u8Center_x = new_block->points[0].x;
	u8 LOC_u8Center_y = new_block->points[0].y;
	s8 LOC_s8DrawStatus = TRUE;

	switch (new_block->rotation)
	{
	case TETRIS_ROTATION_0:

		break;
	case TETRIS_ROTATION_90:

		break;
	case TETRIS_ROTATION_180:

		break;
	case TETRIS_ROTATION_270:

		break;

	default:
		break;
	}
	return LOC_s8DrawStatus;
}

static s8 Tetris_draw_Z()
{
	DotMatrix *board = &game_controller.board;
	Block *new_block = &game_controller.active_block;
	u8 LOC_u8Center_x = new_block->points[0].x;
	u8 LOC_u8Center_y = new_block->points[0].y;
	s8 LOC_s8DrawStatus = TRUE;
	// new_block->rotation %= 2;

	switch (new_block->rotation)
	{
	case TETRIS_ROTATION_0:
		LOC_s8DrawStatus = board->movePixelRight(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// nothing to clear, just return the error
			return LOC_s8DrawStatus;
		}

		LOC_s8DrawStatus = board->movePixelUp(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// clear the center pixel and the one to its right
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y + 1);
			return LOC_s8DrawStatus;
		}

		LOC_s8DrawStatus = board->movePixelLeft(board->buffer, LOC_u8Center_x + 1, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// clear the center pixel and the one to its right and the one above it
			board->clrPixel(board->buffer, LOC_u8Center_x + 1, LOC_u8Center_y); // top pixel
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);		// center
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y + 1); // to its right
			return LOC_s8DrawStatus;
		}

		// save the location of the points by using the center
		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y + 1;

		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x + 1;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x + 1;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y - 1;
		break;
	case TETRIS_ROTATION_90:
		LOC_s8DrawStatus = board->movePixelDown(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// nothing to clear, just return the error
			return LOC_s8DrawStatus;
		}

		LOC_s8DrawStatus = board->movePixelRight(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// clear the center pixel and the one below it
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);
			board->clrPixel(board->buffer, LOC_u8Center_x - 1, LOC_u8Center_y);
			return LOC_s8DrawStatus;
		}

		LOC_s8DrawStatus = board->movePixelUp(board->buffer, LOC_u8Center_x, LOC_u8Center_y + 1, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// clear the center pixel and the one to its right and the one below it
			board->clrPixel(board->buffer, LOC_u8Center_x - 1, LOC_u8Center_y); // top pixel
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);		// center
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y + 1); // to its right
			return LOC_s8DrawStatus;
		}

		// save the location of the points by using the center
		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y + 1;

		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x - 1;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x + 1;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y + 1;
		break;

	case TETRIS_ROTATION_180:
		LOC_s8DrawStatus = board->movePixelRight(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// nothing to clear, just return the error
			return LOC_s8DrawStatus;
		}

		LOC_s8DrawStatus = board->movePixelUp(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// clear the center pixel and the one to its right
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y + 1);
			return LOC_s8DrawStatus;
		}

		LOC_s8DrawStatus = board->movePixelLeft(board->buffer, LOC_u8Center_x + 1, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// clear the center pixel and the one to its right and the one above it
			board->clrPixel(board->buffer, LOC_u8Center_x + 1, LOC_u8Center_y); // top pixel
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);		// center
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y + 1); // to its right
			return LOC_s8DrawStatus;
		}

		// save the location of the points by using the center
		game_controller.active_block.points[1].x = game_controller.active_block.points[0].x;
		game_controller.active_block.points[1].y = game_controller.active_block.points[0].y + 1;

		game_controller.active_block.points[2].x = game_controller.active_block.points[0].x + 1;
		game_controller.active_block.points[2].y = game_controller.active_block.points[0].y;

		game_controller.active_block.points[3].x = game_controller.active_block.points[0].x + 1;
		game_controller.active_block.points[3].y = game_controller.active_block.points[0].y - 1;
		break;

	case TETRIS_ROTATION_270:
		LOC_s8DrawStatus = board->movePixelDown(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// nothing to clear, just return the error
			return LOC_s8DrawStatus;
		}

		LOC_s8DrawStatus = board->movePixelRight(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// clear the center pixel and the one below it
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);
			board->clrPixel(board->buffer, LOC_u8Center_x - 1, LOC_u8Center_y);
			return LOC_s8DrawStatus;
		}

		LOC_s8DrawStatus = board->movePixelUp(board->buffer, LOC_u8Center_x, LOC_u8Center_y + 1, ON_MOVE_SET_OLD);
		if (LOC_s8DrawStatus != TRUE)
		{
			// clear the center pixel and the one to its right and the one below it
			board->clrPixel(board->buffer, LOC_u8Center_x - 1, LOC_u8Center_y); // top pixel
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);		// center
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y + 1); // to its right
			return LOC_s8DrawStatus;
		}

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

	return LOC_s8DrawStatus;
}
