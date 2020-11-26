#include <optional>
#include <list>

#include "engine.hpp"

#include "components/components.hpp"

#include "systems/systems.hpp"
#include "systems/utils.hpp"

using std::vector;
using std::optional;

typedef Vec<3, float> Vec3f;

void EnemySystem::run(World& world, UpdateArgs args) {
  Entity player = world.first_match(&is_player).value();

  RigidBody& player_transform = *player.get_component<RigidBody>().value();
  Vec3f player_pos = player_transform.position;

  vector<Entity> enemies = world.predicate_mask(&is_enemy);

  for (Entity enemy: enemies) {
    RigidBody& e_rigidbody = *enemy.get_component<RigidBody>().value();

    Vec3f diff = player_pos - e_rigidbody.position;
    diff.y = 0.0f;
    if (diff.magnitude() != 0) {
      diff.normalize();
      e_rigidbody.velocity = diff;
    }
  }

}

void EnemySystem::init(void) {
}

void EnemySystem::clean(void) {
}
