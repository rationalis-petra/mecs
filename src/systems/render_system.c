#include <stdlib.h>
#include <math.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "systems/systems.h"
#include "systems/utils.h"
#include "engine.h"
#include "components/components.h"

#ifdef DEBUG
#include <stdio.h>
#endif

unsigned int VBO;
unsigned int VAO;
unsigned int shader_program;

unsigned int light_program;
unsigned int light_model;
unsigned int light_view;
unsigned int light_projection;

unsigned int model_uniform;
unsigned int view_uniform;
unsigned int projection_uniform;

unsigned int light_colour;
unsigned int object_colour;

unsigned int light_pos;
unsigned int view_pos;

void render_system() {
  // View matrix
  int player = first_match(&is_player);
  Transform* transform = (Transform*) get_component(player, TransformType);
  Camera* camera = (Camera*) get_component(player, CameraType);

  Vec3f play_pos = transform->position;


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
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  free(player_trans);

  // enemies are more red

  EntityList enemies = predicate_mask(&is_enemy);
  for (int i = 0; i < enemies.len; i++) {
    transform = (Transform*) get_component(enemies.entities[i], TransformType);

    Mat4f trans = mat4f_translate(transform->position.x, transform->position.y, transform->position.z);

    glUniform3f(object_colour, 1.0f, 0.0f, 0.0f);
    glUniformMatrix4fv(model_uniform, 1, GL_FALSE, trans);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    free(trans);
  }

  display();
  poll_events();

  free(enemies.entities);

  // Draw ground plane
  // the model matrix
  Mat4f scale = mat4f_scale(100.0f, 1.0f, 100.0f);
  Mat4f trans = mat4f_translate(0.0f, -1.0f, 0.0f);
  Mat4f model = mat4f_multiply(scale, trans);

  // the plane should be grey
  glUniform3f(object_colour, 0.6f, 0.6f, 0.6f);
  glUniformMatrix4fv(model_uniform, 1, GL_FALSE, model);

  glDrawArrays(GL_TRIANGLES, 0, 36);

  free(trans);
  free(scale);
  free(model);
}

void render_init() {
  // Triangle setup, will modify
float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);


  shader_program = new_shader_program("basic");

  model_uniform = get_uniform(shader_program, "model");
  view_uniform = get_uniform(shader_program, "view");
  projection_uniform = get_uniform(shader_program, "projection");

  object_colour = get_uniform(shader_program, "object_colour");
  light_colour = get_uniform(shader_program, "light_colour");

  light_pos = get_uniform(shader_program, "light_pos");
  view_pos = get_uniform(shader_program, "view_pos");

  light_program = new_shader_program("light");

}

void render_clean() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
