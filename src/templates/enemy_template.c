#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "engine.h"

#include "components/components.h"
#include "components/info.h"


void enemy_template(Template* enemy, va_list inpos) {
  enemy->components[InfoType] =  new_info();
  enemy->components[RigidBodyType] = new_rigidbody();

  Info* info = enemy->components[InfoType];
  info->tags = EnemyTag;
  info->name = malloc(sizeof(char) * 5);
  strcpy(info->name, "Dave");

  RigidBody* rigid = enemy->components[RigidBodyType];
  rigid->position.x = 0.0f;
  rigid->position.y = 0.0f;
  rigid->position.z = 0.0f;

}
