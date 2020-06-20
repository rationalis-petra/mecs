#include <stdlib.h>
#include <string.h>

#include "engine.h"

#include "components/components.h"
#include "components/transform.h"
#include "components/info.h"


void enemy_template(Template* enemy) {
  enemy->components[TransformType] =  new_transform();
  enemy->components[InfoType] =  new_info();
  enemy->components[CreatureType] =  new_creature();

  Info* info = enemy->components[InfoType];
  info->tags = EnemyTag;
  info->name = malloc(sizeof(char) * 5);
  strcpy(info->name, "Dave");

  Creature* creature =  enemy->components[CreatureType];

  creature->strength = 10;
  creature->dexterity = 10;
  creature->constitution = 10;
  creature->wisdom = 10;
  creature->charisma = 10;
  creature->intelligence = 10;
  creature->health = 20;
}

