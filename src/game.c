#include <curses.h>
#include <stdlib.h>
#include <time.h>

#include "utils/stdtypes.h"
#include "enums.h"
#include "display.h"
#include "logic.h"
#include "serialization.h"
#include "table.h"
#include "types.h"

#include "game.h"

game_config *default_game_config() {
    game_config *cfg = (game_config*) malloc(sizeof(game_config));
    
    game_config cfg_init = {10, 10, 10};
    *cfg = cfg_init;

    return cfg;
}

void game(cmd_config *ccfg) {
    game_config *cfg = default_game_config();
    table *t;
    table *m;
    table *a;
    i32 elapsed_seconds = 0;
    bool inserted_mines = false;
    game_state state = STATE_RUNNING;

    if (ccfg->file == NULL || !load_from_file(cfg, ccfg, &t, &m, &a, &elapsed_seconds, &inserted_mines, &state)) {
        cfg->width = ccfg->width;
        cfg->height = ccfg->height;
        cfg->mines = ccfg->mines;
        t = table_new(cfg->width, cfg->height, 0);
        m = table_new(cfg->width, cfg->height, 0);
        a = table_new(cfg->width, cfg->height, 1);
        inserted_mines = false;
    }

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    curs_set(0);

    if (has_colors()) {
        start_color();
        use_default_colors();
        
        init_pair(1, COLOR_BLUE,    -1);
        init_pair(2, COLOR_GREEN,   -1);
        init_pair(3, COLOR_RED,     -1);
        init_pair(4, COLOR_BLUE,    -1);
        init_pair(5, COLOR_RED,     -1);
        init_pair(6, COLOR_CYAN,    -1);
        init_pair(7, COLOR_BLACK,   COLOR_WHITE);
        init_pair(8, COLOR_WHITE,   -1);
        
        init_pair(9, COLOR_BLACK,   COLOR_RED);
        
        init_pair(11, COLOR_BLACK,   COLOR_GREEN);
        init_pair(12, COLOR_BLACK,   COLOR_RED);
    }

    struct timespec start_time;
    struct timespec end_time;

    timespec_get(&start_time, TIME_UTC);

    bool runs = true;
    i32 key;
    i32 w, h;
    MEVENT mev;
    while (runs) {
        clear();
        getmaxyx(stdscr, h, w);
        if (w >= cfg->width*2+1 && h >= cfg->height+4) {
            display_table(0, 0, t, state == STATE_RUNNING ? m : a);
            if (state != STATE_RUNNING) display_end_message(cfg->height+1, 0, elapsed_seconds, state);
            display_keybinds(h-1, 0);
        } else {
            display_windowsize_message(w, h);
        }
        refresh();

        key = getch();

        switch (key) {
            case KEY_MOUSE:
                if (getmouse(&mev) == OK && state == STATE_RUNNING) {
                    i32 mx = mev.x, my = mev.y;
                    bool left = mev.bstate & BUTTON1_CLICKED;
                    bool right = mev.bstate & BUTTON3_CLICKED;

                    i32 row = my;
                    i32 col = (mx - 1)/2;
                    if (mx % 2 == 1 && row < cfg->height && col < cfg->width) {
                        if (!inserted_mines) {
                            insert_mines(t, row, col, cfg->mines);
                            inserted_mines = true;
                        }

                        game_resp resp;
                        if (row < t->height && col < t->width) {
                            if (left) resp = handle_left_click(t, m, row, col);
                            if (right) resp = handle_right_click(t, m, row, col);

                            if (resp == RESPONSE_DEAD) {
                                state = STATE_LOST;
                                timespec_get(&end_time, TIME_UTC);
                                elapsed_seconds += (int) (end_time.tv_sec - start_time.tv_sec);
                            }
                            else if (resp == RESPONSE_ALIVE && table_homogenous(m, 1)) {
                                state = STATE_WON;
                                timespec_get(&end_time, TIME_UTC);
                                elapsed_seconds += (int) (end_time.tv_sec - start_time.tv_sec);
                            }
                        }
                    }
                }
                break;
            case 'q':
                runs = false;
                break;
        }
    }

    if (state == STATE_RUNNING) {
        timespec_get(&end_time, TIME_UTC);
        elapsed_seconds += (int) (end_time.tv_sec - start_time.tv_sec);
    }
    if (ccfg->file != NULL) save_to_file(cfg, ccfg, t, m, elapsed_seconds, inserted_mines, state);
    
    endwin();

    free(cfg);
    free(t);
    free(m);
    free(a);
}
