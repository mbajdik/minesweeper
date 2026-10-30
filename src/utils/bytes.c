#include <stdlib.h>

#include "stdtypes.h"

#include "bytes.h"

void fill_buf_with_bytes(u8 *buf, u8 *bytes, i32 start, i32 len) {
    for (int i = 0; i < len; i++) {
        buf[start+i] = bytes[i];
    }
}

u8 *int_to_bytes(i32 v) {
    u8 *buf = (u8*) malloc(4*sizeof(u8));
    
    buf[0] = (v >> 24) & 0xFF;
    buf[1] = (v >> 16) & 0xFF;
    buf[2] = (v >> 8)  & 0xFF;
    buf[3] = v         & 0xFF;

    return buf;
}

i32 bytes_to_int(u8 *buf) {
    return ((i32) buf[0] << 24) | ((i32) buf[1] << 16) | ((i32) buf[2] << 8) | (i32) buf[3];
}
