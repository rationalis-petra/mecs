#include <stdbool.h>

#include "engine.h"
#include "components/components.h"
#include "systems/utils.h"

bool is_player(int id) {
  Info* info = (Info*) get_component(id, InfoType);
  if (info) {
    if (info->tags & PlayerTag)
      return true;
  }
  return false;
}

bool is_enemy(int id) {
  Info* info = (Info*) get_component(id, InfoType);
  if (info) {
    if (info->tags & EnemyTag)
      return true;
  }
  return false;
}

char* stringify_state() {
 // take the enemies, player and turn to string!
  char* tmp_state = calloc(100, sizeof(char));
  char* state = calloc(500, sizeof(char));

  int player = first_match(&is_player);
  Transform* player_transform = get_component(player, TransformType);
  Vec3f player_position = player_transform->position;
  sprintf(state, "((%f %f %f)", player_position.x, player_position.y, player_position.z);

  EntityList enemies = predicate_mask(&is_enemy);

  for (int i = 0; i < enemies.len; i++) {
    int enemy = enemies.entities[i];
    Transform* enemy_transform = get_component(enemy, TransformType);
    Vec3f enemy_position = enemy_transform->position;

    sprintf(tmp_state, "(%f %f %f)", enemy_position.x, enemy_position.y, enemy_position.z);
    strcat(state, tmp_state);
  }
  free(tmp_state);
  // append a newline
  state = realloc(state, strlen(state) + 3);
  strcat(state, ")\n");

  return state;
}
