#include <stdlib.h>

#include "components/camera.h"

void* new_camera() {
  return malloc(sizeof(Camera));
}

void delete_camera(void* _camera) {
  free(_camera);
}
