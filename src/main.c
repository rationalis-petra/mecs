#include "engine.h"

#include "components/components.h"
#include "templates/templates.h"
#include "systems/systems.h"


int ModelType;
int CameraType;

int RigidBodyType;
int AttachmentType;

int SensorType;
int ActuatorType;
int AgentType;

int TransformType;
int InfoType;

int TextureType;
int MeshType;

int main(int argc, char** argv)
{
  new_window(2560, 1440);

  // The initialisation
  ModelType = register_component(&new_model, &delete_model);
  CameraType = register_component(&new_camera, &delete_camera);

  RigidBodyType = register_component(&new_rigidbody, &delete_rigidbody);
  AttachmentType = register_component(&new_attachment, &delete_attachment);

  SensorType = register_component(&new_sensor, &delete_sensor);
  ActuatorType = register_component(&new_actuator, &delete_actuator);
  AgentType = register_component(&new_agent, &delete_agent);

  InfoType = register_component(&new_info, &delete_info);

  register_system(&input_system, &input_init, &input_clean);
  register_system(&enemy_system, &enemy_init, &enemy_clean);
  register_system(&ai_system, &ai_init, &ai_clean);
  register_system(&physics_system, &physics_init, &physics_clean);
  register_system(&render_system, &render_init, &render_clean);

  TextureType = register_resource_type(&load_texture, &delete_texture);
  MeshType = register_resource_type(&load_mesh, &delete_mesh);

  add_entity(&player_template);

  add_entity(&enemy_template, 4.0, 0.0, 4.0);
  add_entity(&enemy_template, -5.0, 0.0, 4.0);

  add_entity(&floor_template);

  init();
  run();
  clean();

  return 0;
}
