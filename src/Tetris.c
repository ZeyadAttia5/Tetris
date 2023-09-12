#include "APP/Tetris.h"
#include "MCAL/EXTI/EXTI_Interface.h"
#include "MCAL/NVIC/NVIC_Interface.h"
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
static s8 Tetris_draw_I(DotMatrix *board, Block new_block);
static s8 Tetris_draw_O(DotMatrix *board, Block new_block);
static s8 Tetris_draw_T(DotMatrix *board, Block new_block);
static s8 Tetris_draw_J(DotMatrix *board, Block new_block);
static s8 Tetris_draw_L(DotMatrix *board, Block new_block);
static s8 Tetris_draw_S(DotMatrix *board, Block new_block);
static s8 Tetris_draw_Z(DotMatrix *board, Block new_block);

static void Tetris_remove_I();
static void Tetris_remove_O();
static void Tetris_remove_T();
static void Tetris_remove_J();
static void Tetris_remove_L();
static void Tetris_remove_S();
static void Tetris_remove_Z();

s8 Tetris_moveBlockRight();
s8 Tetris_moveBlockLeft();

s8 Tetris_drawShape(Tetris *board, u8 copy_u8X, u8 copy_u8Y)
{
	//    s8 LOC_s8BlockNum = (rand() % TETRIS_SHAPE_COUNT);
	// static u8 shape=3;

	static s8 LOC_s8BlockNum = 0;

	Block new_block;
	new_block.center_x = copy_u8X;
	new_block.center_y = copy_u8Y;
	new_block.type = LOC_s8BlockNum;
	LOC_s8BlockNum++;

	// TODO make rotation random
	new_block.rotation = TETRIS_ROTATION_0;

	board->active_block = new_block;

	s8 LOC_u8ErrCode = 0;
	switch (new_block.type)
	{
	case TETRIS_SHAPE_I:
		LOC_u8ErrCode = Tetris_draw_I(&(board->board), new_block);
		break;
	case TETRIS_SHAPE_O:
		LOC_u8ErrCode = Tetris_draw_O(&(board->board), new_block);
		break;
	case TETRIS_SHAPE_T:
		LOC_u8ErrCode = Tetris_draw_T(&(board->board), new_block);
		break;
	case TETRIS_SHAPE_J:
		LOC_u8ErrCode = Tetris_draw_J(&(board->board), new_block);
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
		LOC_u8ErrCode = Tetris_draw_I(&(game_controller.board),
									  game_controller.active_block);
		break;
	case TETRIS_SHAPE_O:
		LOC_u8ErrCode = Tetris_draw_O(&(game_controller.board),
									  game_controller.active_block);
		break;
	case TETRIS_SHAPE_T:
		LOC_u8ErrCode = Tetris_draw_T(&(game_controller.board),
									  game_controller.active_block);
		break;
	case TETRIS_SHAPE_J:
		LOC_u8ErrCode = Tetris_draw_J(&(game_controller.board),
									  game_controller.active_block);
		break;
	case TETRIS_SHAPE_L:
		LOC_u8ErrCode = Tetris_draw_L(&(game_controller.board),
									  game_controller.active_block);
		break;
	case TETRIS_SHAPE_S:
		LOC_u8ErrCode = Tetris_draw_S(&(game_controller.board),
									  game_controller.active_block);
		break;
	case TETRIS_SHAPE_Z:
		LOC_u8ErrCode = Tetris_draw_Z(&(game_controller.board),
									  game_controller.active_block);
		break;

	default:
		break;
	}
	return LOC_u8ErrCode;
}

static s8 Tetris_draw_I(DotMatrix *board, const Block new_block)
{
	u8 LOC_u8Center_x = new_block.center_x;
	u8 LOC_u8Center_y = new_block.center_y;
	s8 LOC_s8DrawStatus = TRUE;

	u8 movements = 0;
	switch (new_block.rotation)
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
		}
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
		}
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
		}
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
				LOC_u8Center_y = new_block.center_y;
			for (u8 reverse = 0; reverse < movements; reverse++)
			{
				board->clrPixel(board->buffer, LOC_u8Center_x,
								LOC_u8Center_y++);
			}
		}
		break;
	default:
		// do nothing
		break;
	}
	return LOC_s8DrawStatus;
}
static s8 Tetris_draw_O(DotMatrix *board, Block new_block)
{
	u8 LOC_u8Center_x = new_block.center_x;
	u8 LOC_u8Center_y = new_block.center_y;
	s8 LOC_u8DrawStatus = TRUE;

	LOC_u8DrawStatus = board->movePixelRight(board->buffer, LOC_u8Center_x,
											 LOC_u8Center_y++, ON_MOVE_SET_OLD);
	if (LOC_u8DrawStatus != TRUE)
	{
		board->movePixelLeft(board->buffer, LOC_u8Center_x, LOC_u8Center_y,
							 ON_MOVE_SET_OLD);
	}

	return LOC_u8DrawStatus;
}
static s8 Tetris_draw_T(DotMatrix *board, Block new_block)
{
	s8 LOC_u8DrawStatus = TRUE;

	LOC_u8DrawStatus = board->movePixelLeft(board->buffer, new_block.center_x,
											new_block.center_y, ON_MOVE_SET_OLD);
	LOC_u8DrawStatus = board->movePixelDown(board->buffer, new_block.center_x,
											new_block.center_y, ON_MOVE_SET_OLD);
	LOC_u8DrawStatus = board->movePixelRight(board->buffer, new_block.center_x,
											 new_block.center_y, ON_MOVE_SET_OLD);

	return LOC_u8DrawStatus;
}
static s8 Tetris_draw_J(DotMatrix *board, Block new_block)
{
	s8 LOC_u8DrawStatus = TRUE;

	LOC_u8DrawStatus = board->movePixelLeft(board->buffer, new_block.center_x,
											new_block.center_y, ON_MOVE_SET_OLD);
	if (LOC_u8DrawStatus != TRUE)
	{
		return LOC_u8DrawStatus;
	}

	LOC_u8DrawStatus = board->movePixelUp(board->buffer, new_block.center_x,
										  new_block.center_y, ON_MOVE_SET_OLD);
	if (LOC_u8DrawStatus != TRUE)
	{
		board->clrPixel(board->buffer, new_block.center_x, new_block.center_y);
		board->clrPixel(board->buffer, new_block.center_x,
						new_block.center_y + 1);
		return LOC_u8DrawStatus;
	}
	new_block.center_x++;

	LOC_u8DrawStatus = board->movePixelUp(board->buffer, new_block.center_x,
										  new_block.center_y, ON_MOVE_SET_OLD);
	if (LOC_u8DrawStatus != TRUE)
	{
		board->clrPixel(board->buffer, new_block.center_x++,
						new_block.center_y);
		board->clrPixel(board->buffer, new_block.center_x, new_block.center_y);
		board->clrPixel(board->buffer, new_block.center_x,
						new_block.center_y + 1);
		return LOC_u8DrawStatus;
	}

	return LOC_u8DrawStatus;
}
static s8 Tetris_draw_L(DotMatrix *board, Block new_block)
{
	s8 LOC_s8DrawStatus = TRUE;
	LOC_s8DrawStatus = board->movePixelRight(board->buffer, new_block.center_x,
											 new_block.center_y, ON_MOVE_SET_OLD);
	LOC_s8DrawStatus = board->movePixelUp(board->buffer, new_block.center_x++,
										  new_block.center_y, ON_MOVE_SET_OLD);
	LOC_s8DrawStatus = board->movePixelUp(board->buffer, new_block.center_x++,
										  new_block.center_y, ON_MOVE_SET_OLD);

	return LOC_s8DrawStatus;
}
static s8 Tetris_draw_S(DotMatrix *board, Block new_block)
{
}
static s8 Tetris_draw_Z(DotMatrix *board, Block new_block)
{
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
	EXTI_voidSetCallBack(Tetris_rotate, EXTI9);
	EXTI_voidSetCallBack(Tetris_moveBlockRight, EXTI9);
	EXTI_voidSetCallBack(Tetris_moveBlockLeft, EXTI9);
	return game_controller;
}

static void Tetris_remove_I()
{
	Block new_block = game_controller.active_block;
	DotMatrix *board = &game_controller.board;

	u8 LOC_u8Center_x = new_block.center_x;
	u8 LOC_u8Center_y = new_block.center_y;

	switch (new_block.rotation)
	{
	case TETRIS_ROTATION_0:
		for (u8 movements = 0; movements < MAX_PIXELS_PER_BLOCK - 1;
			 movements++)
		{
			board->clrPixel(board->buffer, LOC_u8Center_x--, LOC_u8Center_y);
		}
		board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);
		break;
	case TETRIS_ROTATION_90:
		for (u8 movements = 0; movements < MAX_PIXELS_PER_BLOCK - 1;
			 movements++)
		{
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y--);
		}
		board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);
		break;
	case TETRIS_ROTATION_180:
		for (u8 movements = 0; movements < MAX_PIXELS_PER_BLOCK - 1;
			 movements++)
		{
			board->clrPixel(board->buffer, LOC_u8Center_x++, LOC_u8Center_y);
		}
		board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);
		break;
	case TETRIS_ROTATION_270:
		for (u8 movements = 0; movements < MAX_PIXELS_PER_BLOCK - 1;
			 movements++)
		{
			board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y++);
		}
		board->clrPixel(board->buffer, LOC_u8Center_x, LOC_u8Center_y);
		break;
	default:
		// do nothing
		break;
	}
}

Tetris_removeActiveBlock()
{

	switch (game_controller.active_block.type)
	{
	case TETRIS_SHAPE_I:
		Tetris_remove_I();
		break;
	case TETRIS_SHAPE_O:
		// Tetris_remove_O();
		break;
	case TETRIS_SHAPE_T:
		// Tetris_remove_T();
		break;
	case TETRIS_SHAPE_J:
		// Tetris_remove_J();
		break;
	case TETRIS_SHAPE_L:
		// Tetris_remove_L();
		break;
	case TETRIS_SHAPE_S:
		// Tetris_remove_S();
		break;
	case TETRIS_SHAPE_Z:
		// Tetris_remove_Z();
		break;

	default:
		break;
	}
}

s8 Tetris_rotate(void)
{
	s8 LOC_u8RotationErr = 1;

	Tetris_removeActiveBlock(); // remove the current block to prevent it from colliding with itself

	game_controller.active_block.rotation =
		(game_controller.active_block.rotation + 1) % 4; // there are only 4 rotations:   0� -> 360�
	LOC_u8RotationErr = Tetris_drawShape2();

	// if there was an error rotating, draw the block with its old rotation.
	if (LOC_u8RotationErr != TRUE)
	{
		game_controller.active_block.rotation =
			(game_controller.active_block.rotation - 1) % 4;
		Tetris_drawShape2();
	}

	return LOC_u8RotationErr;
}

s8 Tetris_moveBlockRight()
{
}
s8 Tetris_moveBlockLeft()
{
}