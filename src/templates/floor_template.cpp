#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "engine.hpp"

#include "components/components.hpp"
#include "components/info.hpp"


void floor_template(World& world) {
  world.create_entity()
    .add_component<Model>(new Model("floor-tile.jpg", "floor", {0.0, -1.0, 0.0}, {100.0, 1.0, 100.0}));
}
