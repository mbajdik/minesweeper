#include <stdlib.h>

#include "utils/random.h"
#include "utils/stdtypes.h"
#include "enums.h"
#include "table.h"
#include "types.h"

#include "logic.h"

void insert_mines(table *t, i32 s_row, i32 s_col, i32 n) {
    srand_time();

    for (i32 i = 0; i < n; i++) {
        i32 pos = -1;
        i32 row = 0;
        i32 col = 0;

        do {
            pos = randint(0, t->size-1);
            row = pos / t->width;
            col = pos % t->width;
        } while (table_index_pos(t, pos, -1) == -1 || row == s_row || col == s_col);

        *table_index_pos_p(t, pos) = -1;
        
        for (i32 row_d = -1; row_d <= 1; row_d++) {
            for (i32 col_d = -1; col_d <= 1; col_d++) {
                if (row_d == 0 && col_d == 0) continue;

                i8 *p = table_index_p(t, row+row_d, col+col_d);
                if (p == NULL) continue;
                if (*p == -1) continue;

                (*p)++;
            }
        }
    }
}

void reveal_around(table *t, table *m, i32 row, i32 col) {
    i8 mv = table_index(m, row, col, 0);
    if (mv) return;
    
    i8 tv = table_index(t, row, col, 1);
    if (tv != 0) return;

    i8 *p = table_index_p(m, row, col);
    if (p != NULL) *p = 1;

    reveal_around(t, m, row-1, col);
    reveal_around(t, m, row+1, col);
    reveal_around(t, m, row, col-1);
    reveal_around(t, m, row, col+1);
}

game_resp handle_left_click(table *t, table *m, i32 row, i32 col) {
    i8 mv = table_index(m, row, col, 0);
    if (mv) return RESPONSE_ALIVE;
    
    i8 tv = table_index(t, row, col, -2);
    if (tv == -2) return RESPONSE_ALIVE;
    
    if (tv == -1) return RESPONSE_DEAD;
    if (tv == 0) reveal_around(t, m, row, col);
    else *table_index_p(m, row, col) = 1;

    return RESPONSE_ALIVE;
}

game_resp handle_right_click(table *t, table *m, i32 row, i32 col) {
    i8 v = table_index(t, row, col, -2);
    if (v != -1) return RESPONSE_DEAD;
    
    *table_index_p(m, row, col) = 1;
    return RESPONSE_ALIVE;
}
