#include "utils/stdtypes.h"
#include "types.h"

#ifndef DISPLAY_H
#define DISPLAY_H

void display_table(i32 y, i32 x, table *t, table *m);
void display_end_message(i32 y, i32 x, i32 elapsed_seconds, game_state state);
void display_keybinds(i32 y, i32 x);
void display_windowsize_message(i32 width, i32 height);

#endif
