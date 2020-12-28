#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "engine.hpp"
#include "test_app.hpp"

void make_floor(World& world) {
  world.create_entity()
    .add_component<Model>(new Model(world, "floor-tile.jpg", "floor", {0.0, -1.0, 0.0}, {100.0, 1.0, 100.0}));
}
