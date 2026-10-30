#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils/bytes.h"
#include "utils/stdtypes.h"
#include "table.h"
#include "types.h"

#include "serialization.h"

void save_to_file(game_config *cfg, cmd_config *ccfg, table *t, table *m, i32 elapsed_seconds, bool inserted_mines, game_state state) {
    i32 savesize = 4*sizeof(i32) + 2*sizeof(u8) + (t->size)*sizeof(i8) + (m->size)*sizeof(i8);
    u8 buf[savesize];

    u8 *width_bytes = int_to_bytes(cfg->width);
    u8 *height_bytes = int_to_bytes(cfg->height);
    u8 *mines_bytes = int_to_bytes(cfg->mines);
    u8 *seconds_bytes = int_to_bytes(elapsed_seconds);

    fill_buf_with_bytes(buf, width_bytes, 0, 4);
    fill_buf_with_bytes(buf, height_bytes, 4, 4);
    fill_buf_with_bytes(buf, mines_bytes, 8, 4);
    fill_buf_with_bytes(buf, seconds_bytes, 12, 4);

    buf[16] = (u8) inserted_mines;
    buf[17] = (u8) state;

    for (i32 i = 0; i < t->size; i++) {
        buf[18+i] = (u8) (t->cells[i]);
    }

    for (i32 i = 0; i < m->size; i++) {
        buf[18+(t->size)+i] = (u8) (m->cells[i]);
    }

    FILE *f = fopen(ccfg->file, "w");
    if (f == NULL) return;

    fwrite(buf, sizeof(u8), savesize, f);
    fclose(f);
}

bool load_from_file(game_config *cfg, cmd_config *ccfg, table **tp, table **mp, table **ap, i32 *elapsed_seconds, bool *inserted_mines, game_state *state) {
    FILE *f = fopen(ccfg->file, "r");

    if (f == NULL) {
        return false;
    }

    i32 metasize = 2*sizeof(i32);
    u8 metabuf[metasize];
    i32 metabuf_read = fread(metabuf, sizeof(u8), metasize, f);
    if (metabuf_read != metasize) {
        fclose(f);
        return false;
    }

    i32 width = bytes_to_int(metabuf);
    i32 height = bytes_to_int(metabuf+4);

    i32 size = width*height;
    i32 savesize = 2*sizeof(i32) + 2*sizeof(u8) + (size)*sizeof(i8) + (size)*sizeof(i8);
    u8 buf[savesize];
    i32 buf_read = fread(buf, sizeof(u8), savesize, f);
    if (buf_read != savesize) {
        fclose(f);
        return false;
    }
    
    fclose(f);

    i32 mines = bytes_to_int(buf);
    i32 seconds = bytes_to_int(buf+4);

    table *t = table_new(width, height, 0);
    table *m = table_new(width, height, 0);
    table *a = table_new(width, height, 1);

    for (i32 i = 0; i < t->size; i++) {
        t->cells[i] = (i8) (buf[10+i]);
    }

    for (i32 i = 0; i < m->size; i++) {
        m->cells[i] = (i8) (buf[10+(t->size)+i]);
    }

    cfg->width = width;
    cfg->height = height;
    cfg->mines = mines;
    *tp = t;
    *mp = m;
    *ap = a;
    *elapsed_seconds = seconds;
    *inserted_mines = (bool) buf[8];
    *state = (game_state) buf[9];

    return true;
}
