#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "systems/systems.h"
#include "systems/utils.h"
#include "engine.h"
#include "components/components.h"


#ifdef DEBUG
#include <stdio.h>
#endif

void render_system() {
  int player = first_match(&is_player);
  Transform* transform = (Transform*) get_component(player, TransformType);

  Vec3f colour = (Vec3f) {.r = 1.0, .g = 0.0, .b = 0.0};
  draw_triangle_at(transform->position, 10, colour);

  colour = (Vec3f) {.r = 0.0, .g = 1.0, .b = 0.0};
  EntityList enemies = predicate_mask(&is_enemy);
  for (int i = 0; i < enemies.len; i++) {
    transform = (Transform*) get_component(enemies.entities[i], TransformType);

    draw_triangle_at(transform->position, 5, colour);
  }

  display();
  poll_events();

  free(enemies.entities);
}
