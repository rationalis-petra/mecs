#include "engine.hpp"
#include "test_app.hpp"

#include <iostream>

// resources
unsigned int Texture::type_id;
unsigned int Mesh::type_id;

typedef Matrix<4, 4, float> Mat4f;

int main(int argc, char** argv) {
  new_window(2560, 1440);

  World world = World();

  // The initialisation
  world.register_component<Model>();
  world.register_component<Camera>();
  world.register_component<RigidBody>();
  world.register_component<Input>();
  //world.register_component<ConstraintElement>();

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
