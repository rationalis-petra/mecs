//#include "engine/systems.h"
#include <stdlib.h>
#include "engine.h"
#include <stdio.h>

#include "components/components.h"

#include "systems/systems.h"
#include "systems/utils.h"


void enemy_system() {
  int player = first_match(&is_player);
  Transform* player_transform = (Transform*) get_component(player, TransformType);
  Vec3f player_pos = player_transform->position;
  EntityList enemies = predicate_mask(&is_enemy);

  for (int i = 0; i < enemies.len; i++) {
    int enemy = enemies.entities[i];

    Transform* e_transform = (Transform*) get_component(enemy, TransformType);
    //Info* info = (Info*) get_component(enemy, InfoType);
    //Creature* creature = (Creature*) get_component(enemy, CreatureType);

    Vec3f* enemy_position = &e_transform->position;
    Vec3f diff = vec3f_difference(player_pos, *enemy_position);
    if (vec3f_magnitude(diff) != 0) {
      diff = vec3f_normalize(diff);
      *enemy_position = vec3f_sum(*enemy_position, vec3f_multiply(0.02, diff));
    }
  }

}

void enemy_init() {
}

void enemy_clean() {
}
