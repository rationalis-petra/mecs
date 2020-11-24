#include <optional>
#include <list>

#include "engine.hpp"

#include "components/components.hpp"

#include "systems/systems.hpp"
#include "systems/utils.hpp"

using std::vector;
using std::optional;

void EnemySystem::run(World& world, UpdateArgs args) {
  Entity player = world.first_match(&is_player).value();

  RigidBody& player_transform = *player.get_component<RigidBody>().value();
  Vec3f player_pos = player_transform.position;

  vector<Entity> enemies = world.predicate_mask(&is_enemy);

  for (Entity enemy: enemies) {
    RigidBody& e_rigidbody = *enemy.get_component<RigidBody>().value();

    Vec3f diff = vec3f_difference(player_pos, e_rigidbody.position);
    diff.y = 0.0f;
    if (vec3f_magnitude(diff) != 0) {
      diff = vec3f_normalize(diff);
      e_rigidbody.velocity = diff;
    }
  }

}

void EnemySystem::init(void) {
}

void EnemySystem::clean(void) {
}
