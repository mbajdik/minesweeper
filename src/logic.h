#include "utils/stdtypes.h"
#include "types.h"

#ifndef LOGIC_H
#define LOGIC_H

void insert_mines(table *t, i32 s_row, i32 s_col, i32 n);
void reveal_around(table *t, table *m, i32 row, i32 col);
game_resp handle_left_click(table *t, table *m, i32 row, i32 col);
game_resp handle_right_click(table *t, table *m, i32 row, i32 col);

#endif
