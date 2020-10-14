#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "engine.h"
#include "components/components.h"

#include "systems/systems.h"
#include "systems/utils.h"

Cursor cursor_pos;
bool b_npressed = true;

void input_system(void) {
  int player = first_match(&is_player);
  RigidBody* player_body = get_component(player, RigidBodyType);
  Vec3f* pos = &player_body->position;

  if (window_should_close() || key_is_pressed(KEY_ESC)) {
    stop();
  }

  Camera* camera = (Camera*) get_component(player, CameraType);
  float phi = camera->phi;

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
    if (pos->y < 1.e-2f) {
     // then, increase upward velocity
      Vec3f up = {{{0.0f, 5.0f, 0.0f}}};
      player_body->velocity = vec3f_sum(player_body->velocity, up);
    }
  }

  dir = vec3f_multiply(0.1f, dir);
  player_body->velocity = vec3f_sum(player_body->velocity, dir);


  // camer
  Cursor new_cursor_pos = get_cursor_pos();
  camera->phi += 0.003 * (new_cursor_pos.x - cursor_pos.x);
  camera->theta += 0.001 * (new_cursor_pos.y - cursor_pos.y);
  cursor_pos = new_cursor_pos;
}

void input_init(void) {
  cursor_pos = get_cursor_pos();
}

void input_clean(void) {
}
