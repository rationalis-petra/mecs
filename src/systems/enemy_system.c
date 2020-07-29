//#include "engine/systems.h"
#include <stdlib.h>
#include "engine.h"
#include <stdio.h>

#include "components/components.h"

#include "systems/systems.h"
#include "systems/utils.h"


void enemy_system(void) {
  int player = first_match(&is_player);
  Transform* player_transform =  get_component(player, TransformType);
  Vec3f player_pos = player_transform->position;
  EntityList enemies = predicate_mask(&is_enemy);

  for (int i = 0; i < enemies.len; i++) {
    int enemy = enemies.entities[i];

    Transform* e_transform = get_component(enemy, TransformType);
    RigidBody* e_rigidbody = get_component(enemy, RigidBodyType);
    //Info* info = (Info*) get_component(enemy, InfoType);
    //Creature* creature = (Creature*) get_component(enemy, CreatureType);

    Vec3f diff = vec3f_difference(player_pos, e_transform->position);
    diff.y = 0.0f;
    if (vec3f_magnitude(diff) != 0) {
      diff = vec3f_normalize(diff);
      e_rigidbody->velocity = diff;
    }
  }

}

void enemy_init(void) {
}

void enemy_clean(void) {
}
