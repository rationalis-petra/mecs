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
  Vec2i* pos = &player_transform->position;

  if (window_should_close()) {
    stop();
  }

  if (key_is_pressed(KEY_W)) {
    pos->y += 1;
  }
  if (key_is_pressed(KEY_A)) {
    pos->x -= 1;
  }
  if (key_is_pressed(KEY_S)) {
    pos->y -= 1;
  }
  if (key_is_pressed(KEY_D)) {
    pos->x += 1;
  }
}
