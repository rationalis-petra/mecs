#include <math.h>

#include "engine.hpp"
#include "components/components.hpp"

#include "systems/systems.hpp"
#include "systems/utils.hpp"


void InputSystem::run(World& world, UpdateArgs args) {
  Entity player = world.first_match(&is_player).value();

  RigidBody& player_body = *player.get_component<RigidBody>().value();
  Vec3f& pos = player_body.position;

  if (window_should_close() || key_is_pressed(KEY_ESC)) {
    world.stop();
  }

  Camera& camera = *player.get_component<Camera>().value();
  float phi = camera.phi;

  Vec3f dir = {{{0.0f, 0.0f, 0.0f}}};

  //  phi gives the x-coordinate
  if (key_is_pressed(KEY_W)) {
    Vec3f inp = {{{cosf(phi), 0.0f, sinf(phi)}}};
    dir = vec3f_sum(inp, dir);
  }
  if (key_is_pressed(KEY_A)) {
    Vec3f inp = {{{sinf(phi), 0.0f, -cosf(phi)}}};
    dir = vec3f_sum(inp, dir);
  }
  if (key_is_pressed(KEY_S)) {
    Vec3f inp = {{{-cosf(phi), 0.0f, -sinf(phi)}}};
    dir = vec3f_sum(inp, dir);
  }
  if (key_is_pressed(KEY_D)) {
    Vec3f inp = {{{-sinf(phi), 0.0f, cosf(phi)}}};
    dir = vec3f_sum(inp, dir);
  }

  if (key_is_pressed(KEY_SPACE)) {
    // check if the cube is on the plane or not
    if (pos.y < 1.e-2f) {
     // then, increase upward velocity
      Vec3f up = {{{0.0f, 5.0f, 0.0f}}};
      player_body.velocity = vec3f_sum(player_body.velocity, up);
    }
  }

  dir = vec3f_multiply(0.1f, dir);
  player_body.velocity = vec3f_sum(player_body.velocity, dir);


  // camera
  Cursor new_cursor_pos = get_cursor_pos();
  camera.phi += 0.003 * (new_cursor_pos.x - cursor_pos.x);
  camera.theta += 0.001 * (new_cursor_pos.y - cursor_pos.y);
  cursor_pos = new_cursor_pos;
}

void InputSystem::init() {
  cursor_pos = get_cursor_pos();
}

void InputSystem::clean() {
}
