#ifndef __UTILS_H
#define __UTILS_H
#include <stdbool.h>

bool is_enemy(int id);

bool is_player(int id);

bool is_static(int id);

char* stringify_state(void);

#endif
