#ifndef __UTILS_H
#define __UTILS_H
#include <stdbool.h>

#include "components/transform.h"

bool is_enemy(int id);

bool is_player(int id);

char* stringify_state();
#endif
