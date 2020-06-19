// #derive (component, Transform)
#ifndef TRANSFORM_H
#define TRANSFORM_H
/**@file
 */

#include "engine/math/vecmath.h"

typedef struct Transform {
  Vec3f position;
  int rotation;
} Transform;

void* new_transform();

void delete_transform(void* transform);


#endif
