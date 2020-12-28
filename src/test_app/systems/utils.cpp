#include <optional>

#include "engine.hpp"
#include "test_app.hpp"

using std::optional;


bool is_static(Entity e) {
  return (!e.has_component<RigidBody>()) && e.has_component<Model>();
}

bool has_rigidbody(Entity e) {
  return e.has_component<RigidBody>();
}

bool has_model_rigidbody(Entity e) {
  return e.has_component<RigidBody>() && e.has_component<Model>();
}

