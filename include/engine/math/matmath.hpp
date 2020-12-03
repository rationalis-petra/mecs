#ifndef __MATMATH_H
#define __MATMATH_H

#include <iostream>
#include "vecmath.hpp"

template<unsigned rows, unsigned cols, typename T> class Matrix {
public:
  // stored in row-major order
  T arr[rows * cols];

  Vec<rows, T> column(unsigned i) {}
  Vec<cols, T> row(unsigned i) {}

  Matrix(bool init = true) {
    if(init) {
      for (unsigned i = 0; i < (rows * cols); i++) {
        arr[i] = 0;
      }
    }
  }
};

// special for the representation of vectors 2-4
template<typename T> class Matrix<4, 4, T> {
public:
  T arr[16];

  Vec<4, T>column(unsigned col) {
    Vec<4, T> out;
    out.x = arr[col*4];
    out.y = arr[4*col + 1];
    out.z = arr[4*col + 2];
    out.w = arr[4*col + 3];
    return out;
  }

  static Matrix identity() {
    Matrix out;
    for (int i = 0; i < 4; i++) 
      out.arr[i + 4*i] = 1.0;

    return out;
  }

  Matrix(bool init = true) {
    if(init) {
      for (unsigned i = 0; i < 16; i++) {
        arr[i] = 0.0;
      }
    }
  }



  static Matrix scale(const Vec<3, T>& v) { return scale(v.x, v.y, v.z); }
  static Matrix scale(const T x, const T y, const T z) {
    Matrix out = Matrix(false);
    out.arr[0] = x;
    out.arr[1] = 0;
    out.arr[2] = 0;
    out.arr[3] = 0;

    out.arr[4] = 0;
    out.arr[5] = y;
    out.arr[6] = 0;
    out.arr[7] = 0;

    out.arr[8] = 0;
    out.arr[9] = 0;
    out.arr[10] = z;
    out.arr[11] = 0;

    out.arr[12] = 0;
    out.arr[13] = 0;
    out.arr[14] = 0;
    out.arr[15] = 1;
    return out;
  }

  static Matrix translate(const Vec<3, T>& v) { return translate(v.x, v.y, v.z); }
  static Matrix translate(const T x, const T y, const T z) {
    Matrix out = Matrix(false);
    out.arr[0] = 1;
    out.arr[1] = 0;
    out.arr[2] = 0;
    out.arr[3] = 0;

    out.arr[4] = 0;
    out.arr[5] = 1;
    out.arr[6] = 0;
    out.arr[7] = 0;

    out.arr[8] = 0;
    out.arr[9] = 0;
    out.arr[10] = 1;
    out.arr[11] = 0;

    out.arr[12] = x;
    out.arr[13] = y;
    out.arr[14] = z;
    out.arr[15] = 1;
    return out;
  }

  static Matrix rotate(const Vec<3, T>& v) { return rotate(v.x, v.y, v.z); }
  static Matrix rotate(T x, T y, T z) {
    Matrix out;
    out.arr[0] = cos(z) * cos(y);
    out.arr[1] = sin(z) * cos(y);
    out.arr[2] = -sin(y);
    out.arr[3] = 0;

    out.arr[4] = cos(z) * sin(y) * sin(x) - sin(z) * cos(x);
    out.arr[5] = sin(z) * sin(y) * sin(x) + cos(z) * cos(x);
    out.arr[6] = cos(y) * sin(x);
    out.arr[7] = 0;

    out.arr[8] = cos(z) * sin(y) * cos(x) + sin(z) * sin(x);
    out.arr[9] = sin(z) * sin(y) * cos(x) - cos(z) * sin(x);
    out.arr[10] = cos(y) * cos(x);
    out.arr[11] = 0;

    out.arr[12] = 0;
    out.arr[13] = 0;
    out.arr[14] = 0;
    out.arr[15] = 1;
    return out;
  }

  static Matrix perspective(const Vec<3, T>& v) { return perspective(v.x, v.y, v.z); }
  static Matrix perspective(T fov, T aspect, T near, T far) {
    Matrix out;
    // ti = n/t = t inverse
    // ri = n/r = r inverse
    T ti = 1 / tan(fov / 2.0f);
    T ri = ti * aspect;

    out.arr[0] = ti;
    out.arr[1] = 0.0f;
    out.arr[2] = 0.0f;
    out.arr[3] = 0.0f;

    out.arr[4] = 0.0f;
    out.arr[5] = ri;
    out.arr[6] = 0.0f;
    out.arr[7] = 0.0f;

    out.arr[8] = 0.0f;
    out.arr[9] = 0.0f;
    out.arr[10] = -(far+near) / (far - near);
    out.arr[11] = -1.0f;

    out.arr[12] = 0.0f;
    out.arr[13] = 0.0f;
    out.arr[14] = -2*far*near / (far - near);
    out.arr[15] = 0.0f;

    return out;
  }

  static Matrix look_at (Vec<3, T> position, Vec<3, T> target, Vec<3, T> up) {
    Matrix out;
    Vec<3, T> camera_direction = (position - target).normalized();
    Vec<3, T> camera_right = cross<float>(up, camera_direction).normalized();
    Vec<3, T> camera_up = cross<float>(camera_direction, camera_right);

    // look at -> combine re-orientation & translation
    out.arr[0] = camera_right.x;
    out.arr[1] = camera_up.x;
    out.arr[2] = camera_direction.x;
    out.arr[3] = 0.0f;

    out.arr[4] = camera_right.y;
    out.arr[5] = camera_up.y;
    out.arr[6] = camera_direction.y;
    out.arr[7] = 0.0f;

    out.arr[8] = camera_right.z;
    out.arr[9] = camera_up.z;
    out.arr[10] = camera_direction.z;
    out.arr[11] = 0.0f;

    out.arr[12] = -camera_right.x * position.x - camera_right.y * position.y - camera_right.z * position.z;
    out.arr[13] = -camera_up.x * position.x - camera_up.y * position.y - camera_up.z * position.z;
    out.arr[14] = -camera_direction.x * position.x - camera_direction.y * position.y - camera_direction.z * position.z;
    out.arr[15] = 1.0f;
    return out;
  }
};

// template<typename T> Matrix<4, 4, T> () {
// }

template<unsigned rows, unsigned cols, typename T>
bool operator==(const Matrix<rows, cols, T>& left, const Matrix<rows, cols, T>& right) {
  for (unsigned i = 0; i < rows * cols; i++) {
    if (left.arr[i] != right.arr[i]) return false;
  }
  return true;
}

template<unsigned rows, unsigned shared, unsigned cols, typename T>
Matrix<rows, cols, T> operator*(const Matrix<rows, shared, T>& left, const Matrix<shared, cols, T> right) {
  // Column-Major ordering!
  Matrix<rows, cols, T> out = Matrix<rows, cols, T>(true);
  for (unsigned i = 0; i < rows; i++) {        // i = row number    (height)
    for (unsigned j = 0; j < cols; j++) {      // j = column number (width)
      for (unsigned k = 0; k < shared; k++) {
         out.arr[j * rows + i] += (left.arr[k * rows + i] * right.arr[j * rows + k]);
      }
    }
  }
  return out;
}

template<typename T>
Vec<4, T> operator*(const Matrix<4, 4, T>& mat, const Vec<4, T> vec) {
  Vec<4, T> out = Vec<4, T>();
  // essentially, vec^T
  for (int i = 0; i < 4; i++) {
    out.x += mat.arr[i] * vec.x;
    out.x += mat.arr[i + 4] * vec.x;
    out.x += mat.arr[i + 8] * vec.x;
    out.x += mat.arr[i + 12] * vec.x;
  }
  return out;
}


template<unsigned rows, unsigned cols, typename T>
std::ostream& operator<< (std::ostream& os, const Matrix<rows, cols, T>& m) {
  for (unsigned i = 0; i < rows; i++) {
    os << "[";
    for (unsigned j = 0; j < cols; j++) {
      os << m.arr[rows * j + i] << ", ";
    }
    os << "]" << std::endl;
  }
  return os;
}

#endif
