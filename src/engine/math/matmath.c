#include <stdlib.h>

#include <math.h>

#include "engine/math.h"

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

