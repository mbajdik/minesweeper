#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "utils/stdtypes.h"

#include "args.h"

void print_help(cstr argv0) {
    printf(
        "Simple(st) minesweeper game written entirely in standard C\n"
        "Usage: %s [OPTIONS]\n"
        "\n"
        "Options:\n"
        "    -w, --width <int>    sets the map's width (default = 10)\n"
        "    -h, --height <int>   sets the map's height (default = 10)\n"
        "    -m, --mines <int>    sets the amount of mines planted on the map (default = 10)\n"
        "    -f, --file <str>     sets where the game progress should be saved to\n"
        "        --help           prints this help message\n",
        argv0
    );
}

void panic_exit(cstr msg) {
    printf("\033[31m%s\033[0m\n", msg);
    exit(1);
}

void panic_exit_help(cstr msg, cstr argv0) {
    printf("\033[31m%s\033[0m\n", msg);
    print_help(argv0);
    exit(1);
}

void exit_help(cstr argv0) {
    print_help(argv0);
    exit(0);
}

cmd_config *parse_args(i32 argc, cstr *argv) {
    i32 index = 1;
    cmd_config *ccfg = (cmd_config*) malloc(sizeof(cmd_config));
    
    cmd_config ccfg_init = {10, 10, 10, NULL};
    *ccfg = ccfg_init;

    while (index < argc) {
        cstr arg = argv[index];

        bool found = false;
        if (strcmp(arg, "-w") == 0 || strcmp(arg, "--width") == 0) {
            if (index + 1 >= argc) panic_exit_help("No value provided for width", *argv);
            
            found = true;
            ccfg->width = atoi(argv[index+1]);

            index += 2;
        }
        else if (strcmp(arg, "-h") == 0 || strcmp(arg, "--height") == 0) {
            if (index + 1 >= argc) panic_exit_help("No value provided for height", *argv);
            
            found = true;
            ccfg->height = atoi(argv[index+1]);

            index += 2;
        }
        else if (strcmp(arg, "-m") == 0 || strcmp(arg, "--mines") == 0) {
            if (index + 1 >= argc) panic_exit_help("No value provided for mines", *argv);
            
            found = true;
            ccfg->mines = atoi(argv[index+1]);

            index += 2;
        }
        else if (strcmp(arg, "-f") == 0 || strcmp(arg, "--file") == 0) {
            if (index + 1 >= argc) panic_exit_help("No value provided for file", *argv);
            
            found = true;
            ccfg->file = argv[index+1];

            index += 2;
        }
        else if (strcmp(arg, "--help") == 0) exit_help(*argv);

        if (!found) panic_exit_help("Unknown parameter provided!", *argv);
    }

    return ccfg;
}
