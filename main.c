#include <stdio.h>
#include "board.h"
#include "macros.h"

MAIN() {
    INIT_BOARD(board);
    board_print(&board);
    return 0;
}