#include <stdlib.h>

#ifdef DEBUG
#include <stdio.h>
#endif

#include "components/transform.h"
#include "engine/math/vecmath.h"

Vec2i* get_position(Transform* transform) {
  #ifdef DEBUG
  if (!transform) {
    fprintf(stderr, "error calling get_position in component Transform: transform null\n");
  }
  #endif

  return &transform->position;
}

Vec2i* copy_position(Transform* transform) {
  #ifdef DEBUG
  if (!transform) {
    fprintf(stderr, "error calling copy_position in component Transform: transform null\n");
  }
  #endif
  
  Vec2i* position = malloc(sizeof(Vec2i));
  position->x = transform->position.x;
  position->y = transform->position.y;
  return position;
}

int* get_rotation(Transform* transform) {
  #ifdef DEBUG
  if (!transform) {
    fprintf(stderr, "error calling get_rotation in component Transform: transform null\n");
  }
  #endif

  return &transform->rotation;
}

void move(Transform* transform, Vec2i* amount) {
  #ifdef DEBUG
  if (!transform) {
    fprintf(stderr, "error calling move in component Transform: transform null\n");
  }
  if (!amount) {
    fprintf(stderr, "error calling move in component Transform: amount null\n");
  }
  #endif

  transform->position.x += amount->x;
  transform->position.y += amount->y;
}

void rotate(Transform* transform, int amount) {
  transform->rotation += amount;
}

void* new_transform() {
  Transform* transform = (Transform*) malloc(sizeof(Transform));

  transform->position.x = 0;
  transform->position.y = 0;
  transform->rotation = 0;

  transform->get_position = &get_position;
  transform->copy_position = &copy_position;
  transform->get_rotation = &get_rotation;
  transform->move = &move;
  transform->rotate = &rotate;
  return (void*) transform;
}

void delete_transform(void* _transform) {
  Transform* transform = (Transform*) _transform;
  #ifdef DEBUG
  if (!transform) {
    fprintf(stderr, "error in function delete_transform in component Transform: transform is null");
  }
  #endif
  
  free(transform);
}
