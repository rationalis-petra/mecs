#include <stdlib.h>
#include <string.h>

#include "engine.h"
#include <stdio.h>

#include "components/components.h"

void player_template(Template* player, va_list _args) {
  player->components[ModelType] = new_model();
  player->components[CameraType] = new_camera();

  player->components[RigidBodyType] = new_rigidbody();

  player->components[InfoType] = new_info();

  Model* model = player->components[ModelType];
  model->texture = get_resource_id(TextureType, "container.jpg");
  model->mesh = get_resource_id(MeshType, "player");
  model->position.x = 0.0f;
  model->position.y = 0.0f;
  model->position.z = 0.0f;

  RigidBody* rigid = player->components[RigidBodyType];
  rigid->position.x = 0.0f;
  rigid->position.y = 0.0f;
  rigid->position.z = 0.0f;

  Info* info = player->components[InfoType];
  info->tags = PlayerTag;
  info->name = malloc(sizeof(char) * 6);
  strcpy(info->name, "Billy");


  Camera* camera = player->components[CameraType];

  camera->theta = 0.5235987756f;
  camera->phi = 1.57079632679f; // pi / 2
  camera->r = 5.0f;
}
