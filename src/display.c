#include <ncurses.h>
#include <strings.h>

#include "utils/stdtypes.h"
#include "enums.h"
#include "table.h"
#include "types.h"

#include "display.h"

void display_table(i32 y, i32 x, table *t, table *m) {
    for (i32 row = 0; row < t->height; row++) {
        for (i32 col = 0; col < t->width; col++) {
            i32 color = 0;
            
            char s;
            if (table_index(m, row, col, 0)) {
                i8 v = table_index(t, row, col, 0);
                if (v == -1) { 
                    color = 9;
                    s = '!';
                } else { 
                    color = v;
                    s = v == 0 ? ' ' : '0' + v; 
                }
            } else {
                s = '~';
            }

            if (color != 0) attron(COLOR_PAIR(color));
            mvaddch(y+row, x+col*2+1, s);
            if (color != 0) attroff(COLOR_PAIR(color));
        }
    }
}

void display_end_message(i32 y, i32 x, i32 elapsed_seconds, game_state state) {
    attron(COLOR_PAIR(10+state));
    mvprintw(y, x, state == STATE_WON ? "WON!" : "LOST!");
    attroff(COLOR_PAIR(10+state));
    
    mvprintw(y+1, x, "took %dm %ds", elapsed_seconds / 60, elapsed_seconds % 60);
}

void display_keybinds(i32 y, i32 x) {
    attron(A_DIM);
    mvprintw(y, x, "[q] to quit | [left click] safe | [right click] mark");
    attroff(A_DIM);
}

void display_windowsize_message(i32 width, i32 height) {
    cstr msg = "Resize window to fit the map!";
    i32 len = strlen(msg);
    
    mvprintw(height/2, width/2 - len/2, msg);
}
