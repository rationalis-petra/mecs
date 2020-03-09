#ifndef UTILS_H
#define UTILS_H
#include <stdbool.h>

#include "components/transform.h"

bool is_enemy(int id);

bool is_player(int id);

int distance(Transform* t1, Transform* t2);

Vec2i vec_diff(Vec2i* p1, Vec2i* p2);
#endif
