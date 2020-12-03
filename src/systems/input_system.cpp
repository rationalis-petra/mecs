#include <math.h>

#include <iostream>

#include "engine.hpp"
#include "components/components.hpp"

#include "systems/systems.hpp"
#include "systems/utils.hpp"

typedef Vec<3, float> Vec3f;

void InputSystem::run(World& world, UpdateArgs args) {
  Entity player = world.first_match(&is_player).value();

  RigidBody& player_body = *player.get_component<RigidBody>().value();
  Vec3f& pos = player_body.position;
  Vec3f& player_rot = player_body.orientation; 

  if (window_should_close() || key_is_pressed(KEY_ESC)) {
    world.stop();
  }

  Camera& camera = *player.get_component<Camera>().value();
  float phi = camera.phi;

  Vec3f dir = {0.0f, 0.0f, 0.0f};
  Vec3f rot = {0.0f, 0.0f, 0.0f};

  //  phi gives the x-coordinate
  if (key_is_pressed(KEY_W)) {
    Vec3f inp = {cosf(phi), 0.0f, sinf(phi)};
    dir += inp;
  }
  if (key_is_pressed(KEY_A)) {
    Vec3f inp = {sinf(phi), 0.0f, -cosf(phi)};
    dir += inp;
  }
  if (key_is_pressed(KEY_S)) {
    Vec3f inp = {-cosf(phi), 0.0f, -sinf(phi)};
    dir += inp;
  }
  if (key_is_pressed(KEY_D)) {
    Vec3f inp = {-sinf(phi), 0.0f, cosf(phi)};
    dir += inp;
  }
  if (key_is_pressed(KEY_Q)) {
    rot.y += 0.1f;
  }
  if (key_is_pressed(KEY_E)) {
    rot.y -= 0.1f;
  }

  if (key_is_pressed(KEY_SPACE)) {
    // check if the cube is on the plane or not
    if (pos.y < 1.e-2f) {
     // then, increase upward velocity
      Vec3f up = {0.0f, 5.0f, 0.0f};
      player_body.velocity += up;
    }
  }

  dir *= 0.1f;
  player_body.velocity += dir;
  player_body.orientation = rot + player_rot;

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
