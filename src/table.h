#include <stdbool.h>

#include "utils/stdtypes.h"
#include "types.h"

#ifndef TABLE_H
#define TABLE_H

table *table_new(i32 width, i32 height, i8 def);
i8 *table_index_p(table *t, i32 row, i32 col);
i8 table_index(table *t, i32 row, i32 col, i8 def);
i8 *table_index_pos_p(table *t, i32 pos);
i8 table_index_pos(table *t, i32 pos, i8 def);
bool table_homogenous(table *t, i32 val);

#endif
