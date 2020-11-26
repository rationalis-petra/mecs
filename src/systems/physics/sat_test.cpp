#include "engine.hpp"
#include "components/rigidbody.hpp"


typedef Vec<3, float> Vec3f;
	    
Vec3f sat_test(RigidBody& body1, RigidBody& body2) {
  // start by assuming the mesh is a box centred on the origin with side length 1
  const Vec3f& pos1 = body1.position;
  const Vec3f& pos2 = body2.position;

  // currently, we have no rotation, so an SAT test is identical to an AABB test
  float x_dist = pos1.x - pos2.x;
  x_dist = x_dist * x_dist;

  // test x-axis if x-dist > 1, no overlap
  if (x_dist > 1.0f) {
    return Vec3f(0.0f, 0.0f, 0.0f);
  }

  float y_dist = pos1.y - pos2.y;
  y_dist = y_dist * y_dist;
  if (y_dist > 1.0f) {
    return Vec3f(0.0f, 0.0f, 0.0f);
  }

  float z_dist = pos1.z - pos2.z;
  z_dist = z_dist * z_dist;
  if (z_dist > 1.0f) {
    return Vec3f(0.0f, 0.0f, 0.0f);
  }

  // force points pos1.pos2, hence pos2 - pos1
  return (pos2 - pos1).normalized();
}
