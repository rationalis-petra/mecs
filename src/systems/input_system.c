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

void input_system(void) {
  int player = first_match(&is_player);
  Transform* player_transform =  get_component(player, TransformType);
  Vec3f* pos = &player_transform->position;

  if (window_should_close() || key_is_pressed(KEY_ESC)) {
    stop();
  }

  Camera* camera = (Camera*) get_component(player, CameraType);
  float phi = camera->phi;

  Vec3f dir = {{{0.0f, 0.0f, 0.0f}}};

  //  phi gives the x-coordinate
  if (key_is_pressed(KEY_W)) {
    Vec3f inp = {{{cos(phi), 0.0f, sin(phi)}}};
    dir = vec3f_sum(inp, dir);
  }
  if (key_is_pressed(KEY_A)) {
    Vec3f inp = {{{sin(phi), 0.0f, -cos(phi)}}};
    dir = vec3f_sum(inp, dir);
  }
  if (key_is_pressed(KEY_S)) {
    Vec3f inp = {{{-cos(phi), 0.0f, -sin(phi)}}};
    dir = vec3f_sum(inp, dir);
  }
  if (key_is_pressed(KEY_D)) {
    Vec3f inp = {{{-sin(phi), 0.0f, cos(phi)}}};
    dir = vec3f_sum(inp, dir);
  }
  if (key_is_pressed(KEY_SPACE)) {
    // check if the cube is on the plane or not
    if (pos->y < 1.e-3f) {
     // then, increase upward velocity
      RigidBody* rigidbody = get_component(player, RigidBodyType);
      Vec3f up = {{{0.0f, 5.0f, 0.0f}}};
      rigidbody->velocity = vec3f_sum(rigidbody->velocity, up);
    }
  }
  dir = vec3f_multiply(0.1, dir);
  *pos = vec3f_sum(dir, *pos);

  // camer
  Cursor new_cursor_pos = get_cursor_pos();
  camera->phi += 0.003 * (new_cursor_pos.x - cursor_pos.x);
  camera->theta += 0.001 * (new_cursor_pos.y - cursor_pos.y);
  cursor_pos = new_cursor_pos;
  // queue_event(type=force, id=player_id, inp=Vec3f{x, 0.0, y});
  //

}

void input_init(void) {
  cursor_pos = get_cursor_pos();
}

void input_clean(void) {
}
