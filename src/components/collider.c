#include <stdlib.h>

#include "components/collider.h"

#ifndef NDEBUG
#include <stdio.h>
#endif

void* new_collider() {
  return malloc(sizeof(Collider));
}

void delete_collider(void* _collider) {
  #ifndef NDEBUG
  if (!_collider) {
    fprintf(stderr, "error in function delete_collider in component Collider: collider is null\n");
  }
  #endif
  free(_collider);
}
