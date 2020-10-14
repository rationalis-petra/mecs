#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "engine.h"

#include "components/components.h"
#include "components/info.h"


void enemy_template(Template* enemy, va_list inpos) {
  enemy->components[InfoType] =  new_info();
  enemy->components[RigidBodyType] = new_rigidbody();
  enemy->components[ModelType] = new_model();

  Info* info = enemy->components[InfoType];
  info->tags = EnemyTag;
  info->name = malloc(sizeof(char) * 5);
  strcpy(info->name, "Dave");

  RigidBody* rigid = enemy->components[RigidBodyType];
  rigid->position.x = va_arg(inpos, double);
  rigid->position.y = va_arg(inpos, double);
  rigid->position.z = va_arg(inpos, double);

  Model* model = enemy->components[ModelType];
  model->position = rigid->position;
  model->texture = get_resource_id(TextureType, "angry.png");
  model->mesh = get_resource_id(MeshType, "enemy");
}
