#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "engine.h"

#include "components/components.h"
#include "components/transform.h"
#include "components/info.h"


void enemy_template(Template* enemy, va_list inpos) {
  enemy->components[TransformType] =  new_transform();
  enemy->components[InfoType] =  new_info();
  enemy->components[CreatureType] =  new_creature();
  enemy->components[RigidBodyType] = new_rigidbody();

  Info* info = enemy->components[InfoType];
  info->tags = EnemyTag;
  info->name = malloc(sizeof(char) * 5);
  strcpy(info->name, "Dave");

  Transform* transform = enemy->components[TransformType];
  transform->position.x = (float) va_arg(inpos, double);
  transform->position.y = (float) va_arg(inpos, double);
  transform->position.z = (float) va_arg(inpos, double);

  Creature* creature =  enemy->components[CreatureType];

  creature->strength = 10;
  creature->dexterity = 10;
  creature->constitution = 10;
  creature->wisdom = 10;
  creature->charisma = 10;
  creature->intelligence = 10;
  creature->health = 20;
}

