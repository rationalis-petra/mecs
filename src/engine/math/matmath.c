#include <stdlib.h>

#include <math.h>

#include "engine/math.h"

#ifdef DEBUG
#include <stdio.h>
#endif

Mat4f mat4f_multiply(Mat4f mat1, Mat4f mat2) {
  Mat4f out = (Mat4f) malloc(sizeof(Mat4f) * 16);

  // Rember, column-major
  for (int i = 0; i < 4; i++) {
    // i = row of mat1
    for (int j = 0; j < 4; j++) {
      // j = col of mat2
      float t = 0.0;
      for (int k = 0; k < 4; k++) {
	//k = accross/down
	t += mat1[4*k + i] * mat2[4*j + k];
      }
      out[4*j + i] = t;
    }
  }
  return out;
}

Mat4f mat4f_identity() {
  Mat4f out = (Mat4f) malloc(sizeof(Mat4f) * 16);
  out[0] = 1.0f;
  out[1] = 0.0f;
  out[2] = 0.0f;
  out[3] = 0.0f;

  out[4] = 0.0f;
  out[5] = 1.0f;
  out[6] = 0.0f;
  out[7] = 0.0f;

  out[8] = 0.0f;
  out[9] = 0.0f;
  out[10] = 1.0f;
  out[11] = 0.0f;

  out[12] = 0.0f;
  out[13] = 0.0f;
  out[14] = 0.0f;
  out[15] = 1.0f;
  return out;
}

Vec4f mat4f_act_on(Mat4f mat, Vec4f vec) {
  Vec4f out = {{{0.0f, 0.0f, 0.0f, 0.0f}}};

  for (int i = 0; i < 4; i++) {
    out.x += vec.x * mat[i*4];
  }
  for (int i = 0; i < 4; i++) {
    out.y += vec.y * mat[i*4 + 1];
  }
  for (int i = 0; i < 4; i++) {
    out.z += vec.z * mat[i*4 + 2];
  }
  for (int i = 0; i < 4; i++) {
    out.w += vec.w * mat[i*4 + 3];
  }

  return out;
}

Mat4f mat4f_scale(float x, float y, float z) {
  Mat4f out = (Mat4f) malloc(sizeof(Mat4f) * 16);
  out[0] = x;
  out[1] = 0;
  out[2] = 0;
  out[3] = 0;

  out[4] = 0;
  out[5] = y;
  out[6] = 0;
  out[7] = 0;

  out[8] = 0;
  out[9] = 0;
  out[10] = z;
  out[11] = 0;

  out[12] = 0;
  out[13] = 0;
  out[14] = 0;
  out[15] = 1;

  return out;
}

Mat4f mat4f_translate(float x, float y, float z) {
  Mat4f out = (Mat4f) malloc(sizeof(Mat4f) * 16);
  out[0] = 1;
  out[1] = 0;
  out[2] = 0;
  out[3] = 0;

  out[4] = 0;
  out[5] = 1;
  out[6] = 0;
  out[7] = 0;

  out[8] = 0;
  out[9] = 0;
  out[10] = 1;
  out[11] = 0;

  out[12] = x;
  out[13] = y;
  out[14] = z;
  out[15] = 1;

  return out;
}

// x, then y, then z
Mat4f mat4f_rotate(float x, float y, float z) {
  Mat4f out = (Mat4f) malloc(sizeof(Mat4f) * 16);

  out[0] = cos(z) * cos(y);
  out[1] = sin(z) * cos(y);
  out[2] = -sin(y);
  out[3] = 0;

  out[4] = cos(z) * sin(y) * sin(x) - sin(z) * cos(x);
  out[5] = sin(z) * sin(y) * sin(x) + cos(z) * cos(x);
  out[6] = cos(y) * sin(x);
  out[7] = 0;

  out[8] = cos(z) * sin(y) * cos(x) + sin(z) * sin(x);
  out[9] = sin(z) * sin(y) * cos(x) - cos(z) * sin(x);
  out[10] = cos(y) * cos(x);
  out[11] = 0;

  out[12] = 0;
  out[13] = 0;
  out[14] = 0;
  out[15] = 1;

  return out;
}

Mat4f mat4f_look_at(Vec3f position, Vec3f target, Vec3f up) {
  Mat4f out = (Mat4f) malloc(sizeof(Mat4f) * 16);

  Vec3f camera_direction = vec3f_normalize(vec3f_difference(position, target));
  Vec3f camera_right = vec3f_normalize(vec3f_cross(up, camera_direction));
  Vec3f camera_up = vec3f_cross(camera_direction, camera_right);

  // look at -> combine re-orientation & translation
  out[0] = camera_right.x;
  out[1] = camera_right.y;
  out[2] = camera_right.z;
  out[3] = 0;

  out[4] = camera_up.x;
  out[5] = camera_up.y;
  out[6] = camera_up.z;
  out[7] = 0;

  out[8] = camera_direction.x;
  out[9] = camera_direction.y;
  out[10] = camera_direction.z;
  out[11] = 0;

  out[12] = -camera_right.x * position.x - camera_up.x * position.y - camera_direction.x * position.z;
  out[13] = -camera_right.y * position.x - camera_up.y * position.y - camera_direction.y * position.z;
  out[14] = -camera_right.z * position.x - camera_up.z * position.y - camera_direction.z * position.z;
  out[15] = 1;

  return out;
}

Mat4f mat4f_perspective(float fov, float aspect, float near, float far) {
  Mat4f out = (Mat4f) malloc(sizeof(Mat4f) * 16);

  #ifdef DEBUG
  if (fov <= 0) {
    fprintf(stderr, "error in mat4f_perspective in matmath: fov <= 0\n");
  }
  if (aspect == 0) {
    fprintf(stderr, "error in mat4f_perspective in matmath: aspect == 0\n");
  }
  #endif

  // ti = n/t = t inverse
  // ri = n/r = r inverse
  float ti = 1 / tan(fov / 2.0f);
  float ri = ti * aspect;

  out[0] = ti; 
  out[1] = 0.0f;
  out[2] = 0.0f;
  out[3] = 0.0f;
  
  out[4] = 0.0f;
  out[5] = ri;
  out[6] = 0.0f;
  out[7] = 0.0f;

  out[8] = 0.0f;
  out[9] = 0.0f;
  out[10] = -(far+near) / (far - near);
  out[11] = -1.0f;

  out[12] = 0.0f;
  out[13] = 0.0f;
  out[14] = -2*far*near / (far - near);
  out[15] = 0.0f;

  return out;
}
