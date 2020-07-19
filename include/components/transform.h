#ifndef __TRANSFORM_H
#define __TRANSFORM_H
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
