#include <stdlib.h>

#include "components/collider.h"

void* new_collider() {
  return malloc(sizeof(Collider));
}

void delete_collider(void* _collider) {
  free(_collider);
}
