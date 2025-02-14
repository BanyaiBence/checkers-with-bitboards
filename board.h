#ifndef BOARD_H
#define BOARD_H
#include <stdint.h>
#include "macros.h"

#define WHITE_INIT_MASK  0x00000FFF
#define BLACK_INIT_MASK  0xFFF00000
#define KING_INIT_MASK   0x00000000
#define RIGHT_UP_LEGAL_MASK 0xEEEEEEEE
#define LEFT_UP_LEGAL_MASK  0x77777777
#define RIGHT_DOWN_LEGAL_MASK
#define LEFT_DOWN_LEGAL_MASK
#define INIT_BOARD(B) Board B = {.whites = WHITE_INIT_MASK, .blacks = BLACK_INIT_MASK, .kings = KING_INIT_MASK, .turn = WHITE}

typedef enum {
    WHITE = 'w',
    BLACK = 'b'
} Color;
typedef enum {
    RIGHT_UP_4_LEGAL_MASK   = 0xF0F0F0F0,
    RIGHT_UP_5_LEGAL_MASK   = 0x0E0E0E00,
    LEFT_UP_3_LEGAL_MASK    = 0x70707070,
    LEFT_UP_4_LEGAL_MASK    = 0x0F0F0F00,
    RIGHT_DOWN_3_LEGAL_MASK = 0x0E0E0E0E,
    RIGHT_DOWN_4_LEGAL_MASK = 0x00F0F0F0,
    LEFT_DOWN_5_LEGAL_MASK  = 0x00707070,
    LEFT_DOWN_4_LEGAL_MASK  = 0x0F0F0F0F
} LegalMask;
typedef uint32_t Mask;
typedef struct
{
    Mask whites;
    Mask blacks;
    Mask kings;
    Color turn;
} Board;

Mask board_get_empty(const Board *b);
Mask board_get_color(const Board *b, Color color);
void board_to_str(const Board *b, char *str);
void board_print(const Board *b);
Mask board_get_moves(const Board *b, const Mask *pos);
Mask board_get_kings(const Board *b);

#define SHIFT_MASK_RIGHT_UP(mask) UNION(INTERSECT(SHIFT(mask, 4), RIGHT_UP_4_LEGAL_MASK),\
    INTERSECT(SHIFT(mask, 5), RIGHT_UP_5_LEGAL_MASK))

#define SHIFT_MASK_LEFT_UP(mask) UNION(INTERSECT(SHIFT(mask, 4), LEFT_UP_4_LEGAL_MASK),\
    INTERSECT(SHIFT(mask, 3), LEFT_UP_3_LEGAL_MASK))

#define SHIFT_MASK_RIGHT_DOWN(mask) UNION(INTERSECT(SHIFT(mask, -4), RIGHT_DOWN_4_LEGAL_MASK),\
    INTERSECT(SHIFT(mask, -3), RIGHT_DOWN_3_LEGAL_MASK))

#define SHIFT_MASK_LEFT_DOWN(mask) UNION(INTERSECT(SHIFT(mask, -4), LEFT_DOWN_4_LEGAL_MASK),\
    INTERSECT(SHIFT(mask, -5), LEFT_DOWN_5_LEGAL_MASK))





#endif //BOARD_H
