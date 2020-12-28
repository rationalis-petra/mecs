#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "engine.hpp"
#include "test_app.hpp"


void make_enemy(World& world, float x, float y, float z) {
  world.create_entity()
    .add_component<RigidBody>(new RigidBody(x, y, z))
    .add_component<Model>(new Model(world, "angry.png", "enemy", {x, y, z}));
}
