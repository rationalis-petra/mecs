#include <stdlib.h>
#include <string.h>

#include "engine.h"

#include "components/components.h"
#include "components/transform.h"
#include "components/info.h"


Template* enemy_template() {
  void** components = malloc(entity_size * sizeof(void*));

  components[TransformType] =  new_transform();
  components[InfoType] =  new_info();
  components[CreatureType] =  new_creature();

  Info* info = components[InfoType];
  info->tags = EnemyTag;
  info->name = malloc(sizeof(char) * 5);
  strcpy(info->name, "Dave");

  Creature* creature = (Creature*) components[CreatureType];

  creature->strength = 10;
  creature->dexterity = 10;
  creature->constitution = 10;
  creature->wisdom = 10;
  creature->charisma = 10;
  creature->intelligence = 10;
  creature->health = 20;

  Template* enemy = (Template*) malloc(sizeof(Template));

  enemy->components = components;

  return enemy;
}

