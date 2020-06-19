#include <stdio.h>
#include "engine.h"

#include "components/components.h"
#include "components/info.h"
#include "components/creature.h"
#include "components/transform.h"

#include "templates/templates.h"
#include "systems/systems.h"

int main(int argc, char** argv)
{
  new_window(1200, 720);

  // The initialisation
  register_component(TransformType, &new_transform, &delete_transform);
  register_component(InfoType, &new_info, &delete_info);
  register_component(CreatureType, &new_creature, &delete_creature);
  register_component(CameraType, &new_camera, &delete_camera);

  register_system(&input_system, &input_init, &input_clean);
  register_system(&enemy_system, &enemy_init, &enemy_clean);
  register_system(&render_system, &render_init, &render_clean);

  add_entity(&player_template);

  add_entity(&enemy_template);
  add_entity(&enemy_template);

  init();
  run();
  clean();

  return 0;
}
