#include <optional>

#include "engine.hpp"
#include "components/components.hpp"
#include "systems/utils.hpp"

using std::optional;

bool is_player(Entity e) {
  optional<Info*> info = e.get_component<Info>();
  if (info.has_value()) {
    if ((*info.value()).tags & PlayerTag)
      return true;
  }
  return false;
}

bool is_enemy(Entity e) {
  optional<Info*> info = e.get_component<Info>();
  if (info) {
    if ((*info.value()).tags & EnemyTag)
      return true;
  }
  return false;
}

bool is_static(Entity e) {
  return (!e.has_component<RigidBody>()) && e.has_component<Model>();
}

bool has_rigidbody(Entity e) {
  return e.has_component<RigidBody>();
}

bool has_model_rigidbody(Entity e) {
  return e.has_component<RigidBody>() && e.has_component<Model>();
}

// char* stringify_state(void) {
//  // take the enemies, player and turn to string!
//   char* tmp_state = calloc(100, sizeof(char));
//   char* state = calloc(500, sizeof(char));

//   int player = first_match(&is_player);
//   RigidBody* player_transform = get_component(player, RigidBodyType);
//   Vec3f player_position = player_transform->position;
//   sprintf(state, "((%f %f %f)", player_position.x, player_position.y, player_position.z);

//   EntityList enemies = predicate_mask(&is_enemy);

//   for (int i = 0; i < enemies.len; i++) {
//     int enemy = enemies.entities[i];
//     RigidBody* enemy_transform = get_component(enemy, RigidBodyType);
//     Vec3f enemy_position = enemy_transform->position;

//     sprintf(tmp_state, "(%f %f %f)", enemy_position.x, enemy_position.y, enemy_position.z);
//     strcat(state, tmp_state);
//   }
//   free(tmp_state);
//   // append a newline
//   state = realloc(state, strlen(state) + 3);
//   strcat(state, ")\n");

//   return state;
// }
