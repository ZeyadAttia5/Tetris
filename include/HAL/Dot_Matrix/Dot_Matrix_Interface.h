#ifndef DOT_MATRIX_INTERFACE
#define DOT_MATRIX_INTERFACE


#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "HAL/Dot_Matrix/Dot_Matrix_config.h"

typedef struct DotMatrix
{
    u8 copy_u8RowPort;
    u8 copy_u8ColPort;
    void (*setPixel)(u8* buffer, u8 copy_x, u8 copy_y); // pointer to function that turns a pixel on
    void (*clrPixel)(u8* buffer, u8 copy_x, u8 copy_y); // pointer to function that turns a pixel off
    u8 buffer[MAX_ROWS]; // Buffer to store the display content
} DotMatrix;

DotMatrix DotMatrix_init();
void matrix_update(DotMatrix matrix);

#endif
