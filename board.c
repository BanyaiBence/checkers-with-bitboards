//
// Created by bence on 2025. 02. 14..
//

#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>

#include "board.h"

#include <stdlib.h>

#include "macros.h"


Mask board_get_empty(const Board *b)
{
    return ~(b->whites | b->blacks);
}

Mask board_get_color(const Board *b, Color color) {
    switch (color) {
        case WHITE:
            return b->whites;
        case BLACK:
            return b->blacks;
        default:
            ERROR("ERROR: ", "Invalid parameter, valid parameters are: (Color.WHITE, Color.BLACK)");
            DIE;
    }
}
Mask board_get_kings(const Board *b) {
    return b->kings;
}


void board_to_str(const Board *b, char *str)
{
    for (int i = 7; i >= 0; i--)
    {
        for (int j = 7; j >= 0; j--)
        {
            const int idx64 = i * 8 + j;
            const int idx32 = idx64 / 2;
            if ((i + j) % 2 == 1)
            {
                str[idx64] = '.';
                continue;
            }

            if (INTERSECT(b->whites, SHIFT(1ULL, idx32)))
                str[idx64] = WHITE;
            else if (INTERSECT(b->blacks, SHIFT(1ULL, idx32)))
                str[idx64] = BLACK;
            else
                str[idx64] = '.';
            if (INTERSECT(b->kings, SHIFT(1ULL, idx32)))
                str[idx64] = (char) toupper(str[idx64]);
        }
    }
}
void board_print(const Board *b)
{
    char str[64];
    board_to_str(b, str);

    char buffer[1000];
    int index = 0;

    ADD_STR("  ", buffer, index);

    for (int i = 0; i < 8; i++)
        ADD_STR("%d ", buffer, index, i+1);

    ADD_STR("\n", buffer, index);
    for (int i = 0; i < 8; i++)
    {
        index += sprintf(buffer + index, "%c ", 'a' + i);

        for (int j = 0; j < 8; j++)
        {
            index += sprintf(buffer + index, "%c ", str[i * 8 + j]);
        }
        index += sprintf(buffer + index, "\n");
    }
    index += sprintf(buffer + index, "White: %d\n", __builtin_popcountll(b->whites));
    index += sprintf(buffer + index, "Black: %d\n", __builtin_popcountll(b->blacks));
    index += sprintf(buffer + index, "Turn: %s\n", b->turn == WHITE ? "White" : "Black");
    printf("%s", buffer);
}

Mask board_get_moves(const Board *b, const Mask *pos) {
    // Check whether white or black
    const Mask ws = board_get_color(b, WHITE);
    const Mask bs = board_get_color(b, BLACK);
    const Mask ks = board_get_kings(b);
    const Mask empty = board_get_empty(b);
    Mask result = 0x0;
    Color color;
    if (INTERSECT(ws, *pos))
        color = WHITE;
    else if (INTERSECT(bs, *pos))
        color = BLACK;
    else
        return 0x0;

    const bool is_king = INTERSECT(*pos, ks);

    switch (color) {
        case WHITE:
            SET_UNION(result, SHIFT_MASK_RIGHT_UP(*pos));
            SET_UNION(result, SHIFT_MASK_LEFT_UP(*pos));
            if (is_king) {
                SET_UNION(result, SHIFT_MASK_RIGHT_DOWN(*pos));
                SET_UNION(result, SHIFT_MASK_LEFT_DOWN(*pos));
            }
            break;
        case BLACK:
            SET_UNION(result, SHIFT_MASK_RIGHT_DOWN(*pos));
            SET_UNION(result, SHIFT_MASK_LEFT_DOWN(*pos));
            if (is_king) {
                SET_UNION(result, SHIFT_MASK_RIGHT_UP(*pos));
                SET_UNION(result, SHIFT_MASK_LEFT_UP(*pos));
            }
            break;
        default:
            __builtin_unreachable();
    }
    return INTERSECT(result, empty);
}





