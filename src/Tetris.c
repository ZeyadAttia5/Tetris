#include "APP/Tetris.h"

// four becuase it is TETRis
#define MAX_PIXELS_PER_BLOCK 4

#define TETRIS_ROTATION_0 0
#define TETRIS_ROTATION_90 1
#define TETRIS_ROTATION_180 2
#define TETRIS_ROTATION_270 3
#define TETRIS_ROTATIONS_COUNT 4

static s8 Tetris_draw_I(DotMatrix *board, Block new_block);
static s8 Tetris_draw_O(DotMatrix *board, Block new_block);
static s8 Tetris_draw_T(DotMatrix *board, Block new_block);
static s8 Tetris_draw_J(DotMatrix *board, Block new_block);
static s8 Tetris_draw_L(DotMatrix *board, Block new_block);
static s8 Tetris_draw_S(DotMatrix *board, Block new_block);
static s8 Tetris_draw_Z(DotMatrix *board, Block new_block);

s8 Tetris_drawShape(Tetris *board, u8 copy_u8X, u8 copy_u8Y)
{
    //    s8 LOC_s8BlockNum = (rand() % TETRIS_SHAPE_COUNT);
    // static u8 shape=3;

    static s8 LOC_s8BlockNum = 3;
    Block new_block;
    new_block.center_x = copy_u8X;
    new_block.center_y = copy_u8Y;
    new_block.type = LOC_s8BlockNum;
    LOC_s8BlockNum++;

    // TODO make rotation random
    new_block.rotation = TETRIS_ROTATION_0;

    switch (new_block.type)
    {
    case TETRIS_SHAPE_I:
        Tetris_draw_I(&(board->board), new_block);
        break;
    case TETRIS_SHAPE_O:
        Tetris_draw_O(&(board->board), new_block);
        break;
    case TETRIS_SHAPE_T:
        Tetris_draw_T(&(board->board), new_block);
        break;
    case TETRIS_SHAPE_J:
        Tetris_draw_J(&(board->board), new_block);
        break;
    case TETRIS_SHAPE_L:
        Tetris_draw_L(&(board->board), new_block);
        break;
    case TETRIS_SHAPE_S:
        Tetris_draw_S(&(board->board), new_block);
        break;
    case TETRIS_SHAPE_Z:
        Tetris_draw_Z(&(board->board), new_block);
        break;

    default:
        LOC_s8BlockNum = -1;
        break;
    }

    return LOC_s8BlockNum;
}

static s8 Tetris_draw_I(DotMatrix *board, const Block new_block)
{
    u8 LOC_u8Center_x = new_block.center_x;
    u8 LOC_u8Center_y = new_block.center_y;
    s8 LOC_u8DrawStatus = TRUE;
    switch (new_block.rotation)
    {
    case TETRIS_ROTATION_0:
        for (u8 movements = 0; movements < MAX_PIXELS_PER_BLOCK - 1; movements++)
        {
            LOC_u8DrawStatus = board->movePixelDown(board->buffer, LOC_u8Center_x++, LOC_u8Center_y, ON_MOVE_SET_OLD);
            if (LOC_u8DrawStatus != TRUE)
            {
                break;
            }
        }
        break;
    case TETRIS_ROTATION_90:
        for (u8 i = 0; i < MAX_PIXELS_PER_BLOCK - 1; i++)
        {
            LOC_u8DrawStatus = board->movePixelLeft(board->buffer, LOC_u8Center_x, LOC_u8Center_y--, ON_MOVE_SET_OLD);
            if (LOC_u8DrawStatus != TRUE)
            {
                board->movePixelRight(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);
                break;
            }
        }
        break;
    default:
        // do nothing
        break;
    }
    return LOC_u8DrawStatus;
}

static s8 Tetris_draw_O(DotMatrix *board, Block new_block)
{
    u8 LOC_u8Center_x = new_block.center_x;
    u8 LOC_u8Center_y = new_block.center_y;
    s8 LOC_u8DrawStatus = TRUE;

    LOC_u8DrawStatus = board->movePixelRight(board->buffer, LOC_u8Center_x, LOC_u8Center_y++, ON_MOVE_SET_OLD);
    if (LOC_u8DrawStatus != TRUE)
    {
        board->movePixelLeft(board->buffer, LOC_u8Center_x, LOC_u8Center_y, ON_MOVE_SET_OLD);
    }

    return LOC_u8DrawStatus;
}
static s8 Tetris_draw_T(DotMatrix *board, Block new_block)
{
    s8 LOC_u8DrawStatus = TRUE;

    LOC_u8DrawStatus = board->movePixelLeft(board->buffer, new_block.center_x, new_block.center_y, ON_MOVE_SET_OLD);
    LOC_u8DrawStatus = board->movePixelDown(board->buffer, new_block.center_x, new_block.center_y, ON_MOVE_SET_OLD);
    LOC_u8DrawStatus = board->movePixelRight(board->buffer, new_block.center_x, new_block.center_y, ON_MOVE_SET_OLD);

    return LOC_u8DrawStatus;
}
static s8 Tetris_draw_J(DotMatrix *board, Block new_block)
{
    s8 LOC_u8DrawStatus = TRUE;

    LOC_u8DrawStatus = board->movePixelLeft(board->buffer, new_block.center_x, new_block.center_y, ON_MOVE_SET_OLD);
    if (LOC_u8DrawStatus != TRUE)
    {
        return LOC_u8DrawStatus;
    }

    LOC_u8DrawStatus = board->movePixelUp(board->buffer, new_block.center_x, new_block.center_y, ON_MOVE_SET_OLD);
    if (LOC_u8DrawStatus != TRUE)
    {
        board->clrPixel(board->buffer, new_block.center_x, new_block.center_y);
        board->clrPixel(board->buffer, new_block.center_x, new_block.center_y + 1);
        return LOC_u8DrawStatus;
    }
    new_block.center_x--;

    LOC_u8DrawStatus = board->movePixelUp(board->buffer, new_block.center_x, new_block.center_y, ON_MOVE_SET_OLD);
    if (LOC_u8DrawStatus != TRUE)
    {
        board->clrPixel(board->buffer, new_block.center_x++, new_block.center_y);
        board->clrPixel(board->buffer, new_block.center_x, new_block.center_y);
        board->clrPixel(board->buffer, new_block.center_x, new_block.center_y + 1);
        return LOC_u8DrawStatus;
    }

    return LOC_u8DrawStatus;
}
static s8 Tetris_draw_L(DotMatrix *board, Block new_block)
{
    s8 LOC_s8DrawStatus = TRUE;
    LOC_s8DrawStatus = board->movePixelRight(board->buffer, new_block.center_x, new_block.center_y, ON_MOVE_SET_OLD);
    LOC_s8DrawStatus = board->movePixelUp(board->buffer, new_block.center_x--, new_block.center_y, ON_MOVE_SET_OLD);
    LOC_s8DrawStatus = board->movePixelUp(board->buffer, new_block.center_x--, new_block.center_y, ON_MOVE_SET_OLD);

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
    return game_controller;
}
