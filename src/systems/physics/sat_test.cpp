#include "engine.hpp"
#include "components/rigidbody.hpp"


typedef Vec<3, float> Vec3f;
typedef Matrix<4, float> Mat4f;

Vec3f sat_test(RigidBody& body1, RigidBody& body2) {
  Vec3f mesh1[] = {{ 0.5,  0.5,  0.5},
                   { 0.5,  0.5, -0.5},
                   { 0.5, -0.5,  0.5},
                   { 0.5, -0.5, -0.5},
                   {-0.5,  0.5,  0.5},
                   {-0.5,  0.5, -0.5},
                   {-0.5, -0.5,  0.5},
                   {-0.5, -0.5, -0.5}};
  Vec3f mesh2[] = {{ 0.5,  0.5,  0.5},
                   { 0.5,  0.5, -0.5},
                   { 0.5, -0.5,  0.5},
                   { 0.5, -0.5, -0.5},
                   {-0.5,  0.5,  0.5},
                   {-0.5,  0.5, -0.5},
                   {-0.5, -0.5,  0.5},
                   {-0.5, -0.5, -0.5}};

  // assume that the mesh is a box centred on the origin with side length 1
  const Vec3f& pos1 = body1.position;
  const Vec3f& rot1 = body1.orientation;
  const Vec3f& pos2 = body2.position;
  const Vec3f& rot2 = body2.orientation;

  Mat4f body1_rot = Mat4f::rotate(body1.orientation);
  Mat4f body2_rot = Mat4f::rotate(body2.orientation);
  Mat4f body1_model = Mat4f::translate(body1.position) * body1_rot;
  Mat4f body2_model = Mat4f::translate(body2.position) * body2_rot;

  for (int i = 0; i < 8; i++) {
    mesh1[i] = body1_model * mesh[i]; 
    mesh2[i] = body1_model * mesh2[i];
  }

  // We choose 6 axes, based on the orientation of the two bodies
  Vec3f  axes[] = {
    Vec3f(body2_rot.column[0]),
    Vec3f(body2_rot.column[1]),
    Vec3f(body2_rot.column[2]),
    Vec3f(body1_rot.column[0]),
    Vec3f(body1_rot.column[1]),
    Vec3f(body1_rot.column[2])};

  // perform test for each axis, if there exists /one/ axis where they do not collide, no collusiton!
  for (Vec3f axis : axes) {
    float xmin, xmax, ymin, ymax;
    // dot product
    xmin = xmax = axes[0] * mesh1[0];
    ymin = ymax = axes[0] * mesh2[0];
    for (int i = 1; i < 8; i++) {
      x = axes[i] * mesh1[i];
      xmin = x < xmin ? x : xmin;
      xmax = x > xmax ? x : xmax;

      y = axes[i] * mesh1[i];
      ymin = y < ymin ? y : ymin;
      ymax = y > ymax ? y : ymax;
    }
    if (ymin < xmax && xmin < ymax) {
      return Vec3f(0.0f, 0.0f, 0.0f);
    }
  }
  return (pos2 - pos1).normalized();
}
	    
Vec3f aabb_test(RigidBody& body1, RigidBody& body2) {
  // start by assuming the mesh is a box centred on the origin with side length 1
  const Vec3f& pos1 = body1.position;
  const Vec3f& pos2 = body2.position;

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
