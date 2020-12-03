#include <vector>

#include <stdlib.h>
#include <math.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "engine.hpp"

#include "systems/systems.hpp"
#include "systems/utils.hpp"
#include "components/components.hpp"

using std::vector;

typedef Vec<3, float> Vec3f;
typedef Matrix<4, 4, float> Mat4f;

void RenderSystem::run(World& world, UpdateArgs args) {
  // View matrix
  Entity player = world.first_match(&is_player).value();
  Model& player_model = *player.get_component<Model>().value();
  Camera& camera = *player.get_component<Camera>().value();

  Vec3f& play_pos = player_model.position;
  Vec3f& play_rot = player_model.rotation;


  Vec3f delta = Vec3f( camera.r * -cosf(camera.theta) * cosf(camera.phi),
                       camera.r *  sinf(camera.theta),
                       camera.r * -cosf(camera.theta) * sinf(camera.phi));

  Vec3f camera_pos = delta + play_pos;
  Vec3f camera_target = play_pos;
  Vec3f camera_up = Vec3f(0.0f, 1.0f, 0.0f);

  Mat4f look_at = Mat4f::look_at(camera_pos, camera_target, camera_up);

  Mat4f projection = Mat4f::perspective(1.57079632679f, get_window_aspect(), 0.1f, 100.0f);

  glUseProgram(shader_program);
  glUniformMatrix4fv(view_uniform, 1, GL_FALSE, look_at.arr);
  glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, projection.arr);

  // // lighting
  glUniform3f(object_colour, 0.05f, 0.8f, 0.05f);
  glUniform3f(light_colour, 1.0f, 1.0f, 1.0f);

  glUniform3f(light_pos, 0.0f, 8.0f, 0.0f);
  glUniform3f(view_pos, camera_pos.x, camera_pos.y, camera_pos.z);

  // draw player
  Mat4f player_trans = Mat4f::translate(play_pos.x, play_pos.y, play_pos.z);
  Mat4f player_rot = Mat4f::rotate(play_rot.x, play_rot.y, play_rot.z);
  Mat4f player_model_mat = player_trans * player_rot;
  glUniformMatrix4fv(model_uniform, 1, GL_FALSE, player_model_mat.arr);


  Texture* t = player_model.texture.value<Texture>();
  glBindTexture(GL_TEXTURE_2D, t->texture);

  Mesh* mesh = player_model.mesh.value<Mesh>();
  glBindVertexArray(mesh->VAO);
  glDrawArrays(GL_TRIANGLES, 0, 36);

  // Draw all enemies

  vector<Entity> enemies = world.predicate_mask(&is_enemy);
  for (Entity enemy : enemies) {
    Model& model = *enemy.get_component<Model>().value();

    Mesh* mesh = model.mesh.value<Mesh>();
    Mat4f scale = Mat4f::identity();
    Mat4f trans = Mat4f::translate(model.position);
    Mat4f model_mat = scale * trans;

    glUniformMatrix4fv(model_uniform, 1, GL_FALSE, model_mat.arr);

    glBindVertexArray(mesh->VAO);
    Texture* t = model.texture.value<Texture>();
    glBindTexture(GL_TEXTURE_2D, t->texture);

    glDrawArrays(GL_TRIANGLES, 0, 36);
  }

  // Draw all static objects:
  vector<Entity> statics = world.predicate_mask(&is_static);
  for (Entity static_entity : statics) {
    Model& model = *static_entity.get_component<Model>().value();

    Mesh* mesh = model.mesh.value<Mesh>();

    glBindVertexArray(mesh->VAO);

    Texture* t = model.texture.value<Texture>();

    Mat4f scale = Mat4f::scale(model.scale);
    Mat4f trans = Mat4f::translate(model.position);
    Mat4f model_mat = scale * trans;


    glBindTexture(GL_TEXTURE_2D, t->texture);

    glUniformMatrix4fv(model_uniform, 1, GL_FALSE, model_mat.arr);

    glDrawArrays(GL_TRIANGLES, 0, 36);
  }


  display();
  poll_events();
}

void RenderSystem::init(void) {
  shader_program = new_shader_program("basic");

  model_uniform = get_uniform(shader_program, "model");
  view_uniform = get_uniform(shader_program, "view");
  projection_uniform = get_uniform(shader_program, "projection");

  object_colour = get_uniform(shader_program, "object_colour");
  light_colour = get_uniform(shader_program, "light_colour");

  light_pos = get_uniform(shader_program, "light_pos");
  view_pos = get_uniform(shader_program, "view_pos");
}

void RenderSystem::clean(void) {
}
