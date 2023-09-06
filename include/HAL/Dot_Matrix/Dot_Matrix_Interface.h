#ifndef DOT_MATRIX_INTERFACE
#define DOT_MATRIX_INTERFACE


#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

typedef struct DotMatrix
{
    u8 copy_u8PortNumber;
    u8 buffer[MAX_ROWS]; // Buffer to store the display content
    void (*setPixel)(struct DotMatrix* addr_dotMatrix_t, u8 copy_x, u8 copy_y); // pointer to function that turns a pixel on
    void (*clrPixel)(struct DotMatrix* addr_dotMatrix_t, u8 copy_x, u8 copy_y); // pointer to function that turns a pixel off
} DotMatrix;

DotMatrix* DotMatrix_init(u8 Copy_u8PortNumber);

#endif
