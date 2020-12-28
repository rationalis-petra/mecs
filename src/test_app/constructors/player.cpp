#include <string>

#include "engine.hpp"
#include "test_app.hpp"

using std::string;

void make_player(World& world) {
  world.create_entity()
    .add_component<Model>(new Model(world, "container.jpg", "player", {0, 0, 0}))
    .add_component<Input>(new Input)
    .add_component<RigidBody>(new RigidBody(0, 0, 0))
    .add_component<Camera>(new Camera(0.5235987756f, 1.57079632679f, 5.0f));
}
