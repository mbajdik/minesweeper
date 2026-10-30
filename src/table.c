#include <stdbool.h>
#include <stdlib.h>

#include "utils/stdtypes.h"
#include "types.h"

#include "table.h"

table *table_new(i32 width, i32 height, i8 def) {
    i32 size = width*height;
    i8 *cells = (i8*) malloc(size*sizeof(i8));
    table t_init = {size, width, height, cells};

    table *t = (table*) malloc(sizeof(table));
    *t = t_init;

    for (i32 i = 0; i < size; i++) *(t->cells + i) = def;
    
    return t;
}

i8 *table_index_p(table *t, i32 row, i32 col) {
    if (0 > row || row >= t->height) return NULL;
    if (0 > col || col >= t->width) return NULL;
    
    i32 pos = row * t->width + col;
    if (pos < 0 || pos > t->size) return NULL;

    return t->cells + pos;
}

i8 table_index(table *t, i32 row, i32 col, i8 def) {
    if (0 > row || row >= t->height) return def;
    if (0 > col || col >= t->width) return def;
    
    i32 pos = row * t->width + col;
    if (pos < 0 || pos > t->size) return def;

    return t->cells[pos];
}

i8 *table_index_pos_p(table *t, i32 pos) {
    if (pos < 0 || pos > t->size) return NULL;

    return t->cells + pos;
}

i8 table_index_pos(table *t, i32 pos, i8 def) {
    if (pos < 0 || pos > t->size) return def;

    return t->cells[pos];
}

bool table_homogenous(table *t, i32 val) {
    for (i32 i = 0; i < t->size; i++) {
        if (table_index_pos(t, i, val-1) != val) return false;
    }

    return true;
}
