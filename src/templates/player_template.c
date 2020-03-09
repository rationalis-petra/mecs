#include <stdlib.h>
#include <string.h>

#include "engine.h"

#include "components/components.h"
#include "components/transform.h"
#include "components/info.h"

int num_components;

Template* player_template() {
  void** components = malloc(num_components * sizeof(void*));

  components[TransformType] = new_transform();
  components[InfoType] = new_info();
  components[CreatureType] = new_creature();

  Info* info = components[InfoType];
  info->tags = PlayerTag;
  info->name = malloc(sizeof(char) * 6);
  strcpy(info->name, "Billy");

  Creature* creature = (Creature*) components[CreatureType];

  creature->strength = 10;
  creature->dexterity = 10;
  creature->constitution = 10;
  creature->wisdom = 10;
  creature->charisma = 10;
  creature->intelligence = 10;
  creature->health = 100;

  Template* player = (Template*) malloc(sizeof(Template));

  player->components = components;
  player->num_components = num_components;

  return player;
}
