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
  init();
  new_window(1200, 720);

  // The initialisation
  register_component(TransformType, &new_transform, &delete_transform);
  register_component(InfoType, &new_info, &delete_info);
  register_component(CreatureType, &new_creature, &delete_creature);

  register_system(&input_system);
  register_system(&enemy_system);
  register_system(&render_system);
  
  add_entity(&player_template);

  add_entity(&enemy_template);
  add_entity(&enemy_template);

  run();
  clean();

  delete_window(0);

  return 0;
}
