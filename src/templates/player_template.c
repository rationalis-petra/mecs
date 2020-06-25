#include <stdlib.h>
#include <string.h>

#include "engine.h"
#include <stdio.h>

#include "components/components.h"

void player_template(Template* player, va_list _nouse) {
  player->components[TransformType] = new_transform();
  player->components[InfoType] = new_info();
  player->components[CreatureType] = new_creature();
  player->components[CameraType] = new_camera();

  Transform* trans = player->components[TransformType];
  trans->position.x = 0.0f;
  trans->position.y = 0.0f;
  trans->position.z = 0.0f;

  Info* info = player->components[InfoType];
  info->tags = PlayerTag;
  info->name = malloc(sizeof(char) * 6);
  strcpy(info->name, "Billy");

  Creature* creature = player->components[CreatureType];

  creature->strength = 10;
  creature->dexterity = 10;
  creature->constitution = 10;
  creature->wisdom = 10;
  creature->charisma = 10;
  creature->intelligence = 10;
  creature->health = 100;

  Camera* camera = player->components[CameraType];

  camera->theta = 0.5235987756f;
  camera->phi = 1.57079632679f; // pi / 2
  camera->r = 5.0f;
}
