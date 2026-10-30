#include <stdio.h>
#include <stdlib.h>

#include "utils/stdtypes.h"
#include "args.h"
#include "game.h"
#include "types.h"

int main(i32 argc, cstr *argv) {
    cmd_config *ccfg = parse_args(argc, argv);
    
    game(ccfg);
    free(ccfg);
}
