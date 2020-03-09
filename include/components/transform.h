// #derive (component, Transform)
#ifndef TRANSFORM_H
#define TRANSFORM_H
/**@file
 */

#include "engine/math/vecmath.h"

typedef struct Transform {
  Vec2i position;
  int rotation;

  Vec2i* (*get_position)(struct Transform*);
  Vec2i* (*copy_position)(struct Transform*);
  int* (*get_rotation)(struct Transform*);
  void (*move)(struct Transform*, Vec2i*);
  void (*rotate)(struct Transform*, int);
} Transform;

void* new_transform();

void delete_transform(void* transform);


#endif
