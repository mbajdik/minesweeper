#include "utils/stdtypes.h"
#include "types.h"

#ifndef ARGS_H
#define ARGS_H

void print_help(cstr argv0);
void panic_exit(cstr msg);
void panic_exit_help(cstr msg, cstr argv0);
void exit_help(cstr argv0);
cmd_config *parse_args(i32 argc, cstr *argv);

#endif
