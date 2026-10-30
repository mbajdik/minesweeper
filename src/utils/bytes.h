#include "stdtypes.h"

#ifndef BYTES_H
#define BYTES_H

void fill_buf_with_bytes(u8 *buf, u8 *bytes, i32 start, i32 len);
u8 *int_to_bytes(i32 v);
i32 bytes_to_int(u8 *buf);

#endif
