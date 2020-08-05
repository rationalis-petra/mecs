#include <stdlib.h>

#include "components/camera.h"

#ifndef NDEBUG
#include <stdio.h>
#endif

void* new_camera() {
  return malloc(sizeof(Camera));
}

void delete_camera(void* _camera) {
  #ifndef NDEBUG
  if (!_camera) {
    perror("error in function delete_camera in component Camera: camera is null\n");
  }
  #endif
  free(_camera);
}
