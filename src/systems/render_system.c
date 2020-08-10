#include <stdlib.h>
#include <math.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "engine.h"

#include "systems/systems.h"
#include "systems/utils.h"
#include "components/components.h"

#ifndef NDEBUG
#include <stdio.h>
#endif

unsigned int shader_program;

unsigned int model_uniform;
unsigned int view_uniform;
unsigned int projection_uniform;

unsigned int light_colour;
unsigned int object_colour;

unsigned int light_pos;
unsigned int view_pos;


void render_system(void) {
  // View matrix
  int player = first_match(&is_player);
  RigidBody* rigid = (RigidBody*) get_component(player, RigidBodyType);
  Camera* camera = (Camera*) get_component(player, CameraType);

  Vec3f play_pos = rigid->position;


  Vec3f delta = {{{ camera->r * -cos(camera->theta) * cos(camera->phi),
		    camera->r * sin(camera->theta),
		    camera->r * -cos(camera->theta) * sin(camera->phi)}}};

  Vec3f camera_pos = vec3f_sum(delta, play_pos);
  Vec3f camera_target = play_pos;
  Vec3f camera_up = {{{0.0f, 1.0f, 0.0f}}};

  Mat4f look_at = mat4f_look_at(camera_pos, camera_target, camera_up);

  Mat4f projection = mat4f_perspective(1.57079632679, get_window_aspect(), 0.1f, 100.0f);

  glUseProgram(shader_program);
  glUniformMatrix4fv(view_uniform, 1, GL_FALSE, look_at);
  glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, projection);

  free(look_at);
  free(projection);

  // lighting
  glUniform3f(object_colour, 0.05f, 0.8f, 0.05f);
  glUniform3f(light_colour, 1.0f, 1.0f, 1.0f);

  glUniform3f(light_pos, 0.0f, 8.0f, 0.0f);
  glUniform3f(view_pos, camera_pos.x, camera_pos.y, camera_pos.z);

  // draw player
  Mat4f player_trans = mat4f_translate(play_pos.x, play_pos.y, play_pos.z);
  glUniformMatrix4fv(model_uniform, 1, GL_FALSE, player_trans);


  Model* model = get_component(player, ModelType);
  unsigned int texture =  *((unsigned int*) get_resource(TextureType, model->texture));
  glBindTexture(GL_TEXTURE_2D, texture);


  Mesh* mesh = get_resource(MeshType, model->mesh);
  glBindVertexArray(mesh->VAO);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  free(player_trans);

  // Draw all enemies

  EntityList enemies = predicate_mask(&is_enemy);
  for (int i = 0; i < enemies.len; i++) {
    RigidBody* body = get_component(enemies.entities[i], RigidBodyType);

    Mat4f trans = mat4f_translate(body->position.x, body->position.y, body->position.z);

    glUniformMatrix4fv(model_uniform, 1, GL_FALSE, trans);

    Model* model = get_component(enemies.entities[i], ModelType);
    Mesh* mesh = get_resource(MeshType, model->mesh);

    glBindVertexArray(mesh->VAO);
    unsigned int texture =  *((unsigned int*) get_resource(TextureType, model->texture));
    glBindTexture(GL_TEXTURE_2D, texture);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    free(trans);
  }

  // Draw all static objects:
  EntityList statics = predicate_mask(&is_static);
  for (int i = 0; i < statics.len; i++) {
    Model* model = get_component(statics.entities[i], ModelType);

    Mesh* mesh = get_resource(MeshType, model->mesh);

    glBindVertexArray(mesh->VAO);

    unsigned int texture =  *((unsigned int*) get_resource(TextureType, model->texture));

    Mat4f scale = mat4f_scale(model->scale.x, model->scale.y, model->scale.z);
    Mat4f trans = mat4f_translate(model->position.x, model->position.y, model->position.z);
    Mat4f model_mat = mat4f_multiply(scale, trans);


    glBindTexture(GL_TEXTURE_2D, texture);

    glUniformMatrix4fv(model_uniform, 1, GL_FALSE, model_mat);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    free(trans);
    free(scale);
    free(model_mat);
  }



  display();
  poll_events();
}

void render_init(void) {
  shader_program = new_shader_program("basic");

  model_uniform = get_uniform(shader_program, "model");
  view_uniform = get_uniform(shader_program, "view");
  projection_uniform = get_uniform(shader_program, "projection");

  object_colour = get_uniform(shader_program, "object_colour");
  light_colour = get_uniform(shader_program, "light_colour");

  light_pos = get_uniform(shader_program, "light_pos");
  view_pos = get_uniform(shader_program, "view_pos");
}

void render_clean(void) {
}
