#ifndef DOT_MATRIX_INTERFACE
#define DOT_MATRIX_INTERFACE

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "HAL/Dot_Matrix/Dot_Matrix_config.h"

#define OutOfBoundsException -1
#define CollisionDetectedException 0
#define TRUE 1

#define ON_MOVE_CLEAR_OLD 0
#define ON_MOVE_SET_OLD 1

typedef struct DotMatrix
{
    u8 copy_u8RowPort;
    u8 copy_u8ColPort;

    void (*setPixel)(u8 *buffer, u8 copy_x, u8 copy_y); // pointer to function that turns a pixel on
    void (*clrPixel)(u8 *buffer, u8 copy_x, u8 copy_y); // pointer to function that turns a pixel off
    void (*setRow)(u8 *buffer, u8 copy_x);              // pointer to function that turns a pixel off
    void (*clrRow)(u8 *buffer, u8 copy_x);              // pointer to function that turns a pixel off

    s8 (*movePixelUp)(u8 *buffer, u8 copy_x, u8 copy_y, u8 copy_u8OnMoveAction);    // pointer to function that moves a pixel up    (x-1)
    s8 (*movePixelDown)(u8 *buffer, u8 copy_x, u8 copy_y, u8 copy_u8OnMoveAction);  // pointer to function that moves a pixel down  (x+1)
    s8 (*movePixelLeft)(u8 *buffer, u8 copy_x, u8 copy_y, u8 copy_u8OnMoveAction);  // pointer to function that moves a pixel left  (y-1)
    s8 (*movePixelRight)(u8 *buffer, u8 copy_x, u8 copy_y, u8 copy_u8OnMoveAction); // pointer to function that moves a pixel right (y+1)

    u8 buffer[DOTMAT_MAX_ROWS]; // Buffer to store the display content
} DotMatrix;

DotMatrix DotMatrix_init();
void matrix_update(DotMatrix matrix, u32 copy_u32STKVal);

#endif
