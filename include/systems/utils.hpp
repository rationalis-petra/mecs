#ifndef __UTILS_H
#define __UTILS_H

bool is_enemy(Entity e);

bool is_player(Entity e);

bool is_static(Entity e);

bool has_rigidbody(Entity e);

bool has_model_rigidbody(Entity e);

char* stringify_state(void);

#endif
