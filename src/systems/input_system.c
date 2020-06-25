#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "engine.h"
#include "components/components.h"

#include "systems/systems.h"
#include "systems/utils.h"

Cursor cursor_pos;

void input_system() {
  int player = first_match(&is_player);
  Transform* player_transform = (Transform*) get_component(player, TransformType);
  Vec3f* pos = &player_transform->position;

  if (window_should_close()) {
    stop();
  }

  if (key_is_pressed(KEY_W)) {
    pos->z += 0.1;
  }
  if (key_is_pressed(KEY_A)) {
    pos->x += 0.1;
  }
  if (key_is_pressed(KEY_S)) {
    pos->z -= 0.1;
  }
  if (key_is_pressed(KEY_D)) {
    pos->x -= 0.1;
  }
  if (key_is_pressed(KEY_SPACE)) {
    pos->y += 0.1;
  }
  else {
    pos->y -= 0.01 * pos->y;
  }

  // camera
  Camera* camera = (Camera*) get_component(player, CameraType);

  Cursor new_cursor_pos = get_cursor_pos();
  camera->phi += 0.003 * (new_cursor_pos.x - cursor_pos.x);
  camera->theta += 0.001 * (new_cursor_pos.y - cursor_pos.y);
  cursor_pos = new_cursor_pos;

  if (key_is_pressed(KEY_ESC)) {
    stop();
  }
}

void input_init() {
  cursor_pos = get_cursor_pos();
}

void input_clean() {
}
