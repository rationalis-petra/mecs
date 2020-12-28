#include <iostream>

#include "engine.hpp"

typedef Vec<3, float> Vec3f;
typedef Vec<4, float> Vec4f;
typedef Matrix<4, 4, float> Mat4f;

	    
bool aabb_test(RigidBody& body1, RigidBody& body2) {
  // start by assuming the mesh is a box centred on the origin with side length 1
  const Vec3f& pos1 = body1.position;
  const Vec3f& pos2 = body2.position;

  float x_dist = pos1.x - pos2.x;
  x_dist = x_dist * x_dist;

  // test x-axis if x-dist > 1, no overlap
  if (x_dist > 1.0f) {
    return false;
  }
  float y_dist = pos1.y - pos2.y;
  y_dist = y_dist * y_dist;
  if (y_dist > 1.0f) {
    return false;
  }

  float z_dist = pos1.z - pos2.z;
  z_dist = z_dist * z_dist;
  if (z_dist > 1.0f) {
    return false;
  }


  // pos2 - pos1 will be a vector which we can use to determine
  // *a* translation vector which will allow us to move the two
  // rigidbodies apart. It will not necessarily be the mtv...

  // return *just* a direction: 
  return true;
}
