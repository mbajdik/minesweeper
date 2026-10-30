#include <stdbool.h>

#include "utils/stdtypes.h"
#include "types.h"

#ifndef SERIALIZATION_H
#define SERIALIZATION_H

void save_to_file(game_config *cfg, cmd_config *ccfg, table *t, table *m, i32 elapsed_seconds, bool inserted_mines, game_state state);
bool load_from_file(game_config *cfg, cmd_config *ccfg, table **tp, table **mp, table **ap, i32 *elapsed_seconds, bool *inserted_mines, game_state *state);

#endif 
