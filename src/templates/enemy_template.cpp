#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "engine.hpp"

#include "components/components.hpp"
#include "components/info.hpp"


void make_enemy(World& world, float x, float y, float z) {
  Entity enemy = world.create_entity()
    .add_component<Info>(new Info("Dave", EnemyTag))
    .add_component<RigidBody>(new RigidBody(x, y, z))
    .add_component<Model>(new Model("angry.png", "enemy", {x, y, z}));
}
