#include <string>

#include "engine.hpp"

#include "components/components.hpp"

using std::string;

void make_player(World& world) {
  Entity player = world.create_entity()
    .add_component<Model>(new Model("container.jpg", "player", {0, 0, 0}))
    .add_component<RigidBody>(new RigidBody(0, 0, 0))
    .add_component<Info>(new Info("Billy", PlayerTag))
    .add_component<Camera>(new Camera(0.5235987756f, 1.57079632679f, 5.0f));
}
