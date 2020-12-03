#include "engine.hpp"

#include "components/components.hpp"
#include "templates/templates.hpp"
#include "systems/systems.hpp"

#include <iostream>


// types
unsigned int Model::type_idx;
unsigned int Camera::type_idx;
unsigned int RigidBody::type_idx;
unsigned int AttachmentElement::type_idx;
unsigned int Sensor::type_idx;
unsigned int Actuator::type_idx;
unsigned int Agent::type_idx;
unsigned int Info::type_idx;

// resources
unsigned int Texture::type_id;
unsigned int Mesh::type_id;

void test_multiplication() {

}

int main(int argc, char** argv) {
  new_window(2560, 1440);

  World world = World();

  // The initialisation
  world.register_component<Model>();
  world.register_component<Camera>();
  world.register_component<RigidBody>();
  world.register_component<AttachmentElement>();
  world.register_component<Sensor>();
  world.register_component<Actuator>();
  world.register_component<Agent>();
  world.register_component<Info>();

  world.register_system(new EnemySystem());
  // register_system(&ai_system, &ai_init, &ai_clean);
  world.register_system(new InputSystem());
  world.register_system(new PhysicsSystem());
  world.register_system(new RenderSystem());

  world.register_resource_type<Texture>();
  world.register_resource_type<Mesh>();

  make_player(world);
  make_enemy(world, 4.0, 0.0, 4.0);
  make_enemy(world, -5.0, 0.0, 4.0);
  make_floor(world);

  world.init();
  world.run();
  world.clean();

  return 0;
}
