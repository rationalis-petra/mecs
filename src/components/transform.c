#include <stdlib.h>

#include "components/transform.h"
#include "engine/math/vecmath.h"

#ifndef NDEBUG
#include <stdio.h>
#endif


void* new_transform() {
  Transform* transform = (Transform*) malloc(sizeof(Transform));
  transform->position.x = 0;
  transform->position.y = 0;
  transform->position.z = 0;
  transform->rotation = 0;

  return (void*) transform;
}

void delete_transform(void* _transform) {
  Transform* transform = (Transform*) _transform;
  #ifndef NDEBUG
  if (!transform) {
    fprintf(stderr, "error in function delete_transform in component Transform: transform is null");
  }
  #endif
  
  free(transform);
}
