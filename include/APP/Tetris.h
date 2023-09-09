/*******************************************************************/
/* Author: Zeyad Attia                                             */
/* Version: v0.0                                                   */
/* Date: 09 Sep 2023                                               */
/* Description: Tetris shapes represented on LED_MATRIX            */
/*******************************************************************/
#include "LIB/STD_TYPES.h"
#include "HAL/Dot_Matrix/Dot_Matrix_Interface.h"

#define TETRIS_SHAPE_I 0
#define TETRIS_SHAPE_O 1
#define TETRIS_SHAPE_T 2
#define TETRIS_SHAPE_J 3
#define TETRIS_SHAPE_L 4
#define TETRIS_SHAPE_S 5
#define TETRIS_SHAPE_Z 6
#define TETRIS_SHAPE_COUNT 7

typedef struct Tetris
{
    DotMatrix board;

    s8 (*drawShape)(struct Tetris *board, u8 copy_u8X, u8 copy_u8Y);
} Tetris;

typedef struct
{
    u8 center_x : 3; // 0 to 7, inclusive
    u8 center_y : 3; // 0 to 7, inclusive
    u8 type : 3;     // 0 to 7, inclusive
    u8 rotation : 2; // 0 to 3, inclusive
    // total bits: 11 = u16
} Block;

/******************************************************************/
/* Func. Name: Tetris_drawShape                                   */
/* i/p arguments: void                                            */
/* o/p arguments: s8 number of drawn shape; (-1) if error         */
/* Desc. : This API allows user draw a random shape from tetris   */
/******************************************************************/
s8 Tetris_drawShape(Tetris* board, u8 copy_u8X, u8 copy_u8Y);


Tetris Tetris_init(void);