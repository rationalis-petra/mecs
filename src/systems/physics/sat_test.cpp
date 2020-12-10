#include <iostream>

#include "engine.hpp"
#include "components/rigidbody.hpp"

typedef Vec<3, float> Vec3f;
typedef Vec<4, float> Vec4f;
typedef Matrix<4, 4, float> Mat4f;


bool run = false;

Vec3f sat_test(RigidBody& body1, RigidBody& body2) {
  /* Crude, inefficient SAT collision detection
   * The process is as follows:
   *   + 1. Acquire plane normals as the normals to each face on a cube
   *     + 1.1: rotate each mesh
   *     + 1.2: select 3 orthogonal edges (parallel to face)
   *   + 2. For each axis, test for a collision
   *     + 2.1 For each axis (edge), project all vertices onto that axis 
   *     + 2.2 Find the min/max for each shape
   *     + 2.3 Test for overlap, if they are not overlapped, then shapes must not be colliding
   *     + 2.4 if overlap on all, then shapes /are/ colliding
   */

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

  // 1.1
  Mat4f body1_rot = Mat4f::rotate(body1.orientation);
  Mat4f body2_rot = Mat4f::rotate(body2.orientation);
  Mat4f body1_model = Mat4f::translate(body1.position) * body1_rot;
  Mat4f body2_model = Mat4f::translate(body2.position) * body2_rot;

  for (int i = 0; i < 8; i++) {
    mesh1[i] = Vec3f(body1_model * Vec4f(mesh1[i], 1)); 
    mesh2[i] = Vec3f(body2_model * Vec4f(mesh2[i], 1));
  }

  if (!run) {
    run = true;

    std::cout << "mat1\n" << body1_model << std::endl;
    std::cout << "mesh1\n";
    for (int i = 0; i < 8; i++) {
      std::cout << mesh1[i] << std::endl;
    }
    std::cout << "mat2\n" << body2_model << std::endl;
    std::cout << "\n\nmesh2\n";
    for (int i = 0; i < 8; i++) {
      std::cout << mesh2[i] << std::endl;
    }
  }

  // 1.2
  // We choose 6 axes, based on the orientation of the two bodies
  Vec3f axes[] = {
    Vec3f(body2_rot.column(0)),
    Vec3f(body2_rot.column(1)),
    Vec3f(body2_rot.column(2)),
    Vec3f(body1_rot.column(0)),
    Vec3f(body1_rot.column(1)),
    Vec3f(body1_rot.column(2))};

  // 2.
  for (int j = 0; j < 6; j++) {
    const Vec3f& axis = axes[j];

    float xmin, xmax, ymin, ymax, x, y;

    xmin = xmax = axis * mesh1[0];
    ymin = ymax = axis * mesh2[0];
    for (int i = 1; i < 8; i++) {
    // 2.2 & 2.1 (2.1 is the dot product
      x = axis * mesh1[i];
      xmin = x < xmin ? x : xmin;
      xmax = x > xmax ? x : xmax;

      y = axis * mesh2[i];
      ymin = y < ymin ? y : ymin;
      ymax = y > ymax ? y : ymax;
    }

    // 2.3 if there is /no/ collision, return 0
    // this is always false - why?
    if (ymax < xmin || xmax < ymin) {
      return Vec3f(0.0f, 0.0f, 0.0f);
    }
    if (xmax == ymax && xmin == ymin) {
      //std::cout << "equal" << std::endl;
    }
  }

  // 2.4
  return (body2.position - body1.position).normalized();
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
