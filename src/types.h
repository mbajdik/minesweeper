#include "utils/stdtypes.h"

#ifndef TYPES_H
#define TYPES_H

typedef struct {
    i32 width;
    i32 height;
    i32 mines;
    cstr file;
} cmd_config;

typedef struct {
    i32 width;
    i32 height;
    i32 mines;
} game_config;

typedef struct {
    i32 size;
    i32 width;
    i32 height;
    i8 *cells;
} table;

typedef i32 game_resp;
typedef i32 game_state;

#endif
