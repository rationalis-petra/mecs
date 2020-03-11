//#include "engine/systems.h"
#include <stdlib.h>


#include "engine.h"

#include "components/components.h"

#include "systems/systems.h"
#include "systems/utils.h"


void enemy_system() {
  EntityList enemies = component_mask(InfoType, CreatureType, TransformType);

  for (int i = 0; i < enemies.len; i++) {
    int enemy = enemies.entities[i];

    Transform* e_transform = (Transform*) get_component(enemy, TransformType);
    Info* info = (Info*) get_component(enemy, InfoType);
    Creature* creature = (Creature*) get_component(enemy, CreatureType);

  }
  
  free(enemies.entities);
}

