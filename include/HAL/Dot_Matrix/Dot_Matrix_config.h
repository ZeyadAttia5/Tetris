#ifndef DOT_MATRIX_CONFIG
#define DOT_MATRIX_CONFIG

#define DOTMAT_MAX_ROWS 8
#define DOTMAT_MAX_COLS 8

/*Please write row can column ports*/
#define DOTMAT_ROW_PORT IOA
#define DOTMAT_COL_PORT IOB

/*Please write port,pin in pair*/
#define DOTMAT_ROW0     DOTMAT_ROW_PORT, 0
#define DOTMAT_ROW1     DOTMAT_ROW_PORT, 1
#define DOTMAT_ROW2     DOTMAT_ROW_PORT, 2
#define DOTMAT_ROW3     DOTMAT_ROW_PORT, 3
#define DOTMAT_ROW4     DOTMAT_ROW_PORT, 4
#define DOTMAT_ROW5     DOTMAT_ROW_PORT, 5
#define DOTMAT_ROW6     DOTMAT_ROW_PORT, 6
#define DOTMAT_ROW7     DOTMAT_ROW_PORT, 7

/*Please write port,pin in pair*/
#define DOTMAT_COL0     DOTMAT_COL_PORT, 0
#define DOTMAT_COL1     DOTMAT_COL_PORT, 1
#define DOTMAT_COL2     DOTMAT_COL_PORT, 2 // 3 for jtag
#define DOTMAT_COL3     DOTMAT_COL_PORT, 3 // 4 for jtagA
#define DOTMAT_COL4     DOTMAT_COL_PORT, 4
#define DOTMAT_COL5     DOTMAT_COL_PORT, 5
#define DOTMAT_COL6     DOTMAT_COL_PORT, 6
#define DOTMAT_COL7     DOTMAT_COL_PORT, 7

#endif
