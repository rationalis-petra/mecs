#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "engine.h"
#include "components/components.h"

#include "systems/systems.h"
#include "systems/utils.h"


void input_system() {
  int player = first_match(&is_player);
  Transform* player_transform = (Transform*) get_component(player, TransformType);
  Vec3i* pos = &player_transform->position;

  if (window_should_close()) {
    stop();
  }

  if (key_is_pressed(KEY_W)) {
    pos->z += 1;
  }
  if (key_is_pressed(KEY_A)) {
    pos->x -= 1;
  }
  if (key_is_pressed(KEY_S)) {
    pos->z -= 1;
  }
  if (key_is_pressed(KEY_D)) {
    pos->x += 1;
  }
  if (key_is_pressed(KEY_SPACE)) {
    pos->y += 1;
  }
  else {
    pos->y -= 0.1 * pos->y;
  }
}

void input_init() {
}

void input_clean() {
}
