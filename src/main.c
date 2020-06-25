#include <stdio.h>
#include "engine.h"

#include "components/components.h"
#include "templates/templates.h"
#include "systems/systems.h"

int main(int argc, char** argv)
{
  new_window(2560, 1440);

  // The initialisation
  register_component(TransformType, &new_transform, &delete_transform);
  register_component(InfoType, &new_info, &delete_info);
  register_component(CreatureType, &new_creature, &delete_creature);
  register_component(CameraType, &new_camera, &delete_camera);
  register_component(RigidBodyType, &new_rigidbody, &delete_rigidbody);

  register_system(&input_system, &input_init, &input_clean);
  register_system(&enemy_system, &enemy_init, &enemy_clean);
  register_system(&render_system, &render_init, &render_clean);
  register_system(&physics_system, &physics_init, &physics_clean);

  add_entity(&player_template);

  add_entity(&enemy_template, 4.0, 0.0, 4.0);
  add_entity(&enemy_template, -5.0, 0.0, 4.0);

  init();
  run();
  clean();

  return 0;
}
