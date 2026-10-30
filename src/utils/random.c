#include <stdlib.h>
#include <time.h>

#include "stdtypes.h"

#include "random.h"

void srand_time() {
    srand(time(NULL));
}

i32 randint(i32 a, i32 b) {
    return rand() % (b + 1 - a) + a;
}
