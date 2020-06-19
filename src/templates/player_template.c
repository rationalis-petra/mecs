#include <stdlib.h>
#include <string.h>

#include "engine.h"
#include <stdio.h>

#include "components/components.h"

Template* player_template() {
  void** components = malloc(entity_size * sizeof(void*));

  components[TransformType] = new_transform();
  components[InfoType] = new_info();
  components[CreatureType] = new_creature();
  components[CameraType] = new_camera();

  Transform* trans = components[TransformType];
  trans->position.x = 0.0f;
  trans->position.y = 0.0f;
  trans->position.z = 0.0f;

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

  Camera* camera = (Camera*) components[CameraType];

  camera->theta = 0.5235987756f;
  camera->phi = 0.0f;
  camera->r = 5.0f;
  

  Template* player = (Template*) malloc(sizeof(Template));

  player->components = components;

  return player;
}
