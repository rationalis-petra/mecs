#ifndef __VECMATH_H
#define __VECMATH_H

#include <iostream>
#include <cmath>

template<unsigned i = 3, typename T = float> class Vec {
  T arr[i];
  T& dot();
  T& magnitude() {
  }
  T& normalize();
  T& normalized();
  Vec() {
    for (int j = 0; j < i; j++) {
      arr[j] = 0;
    }
  }
  Vec operator=(const Vec& o) {
    for (int j = 0; j < i; j++)
      arr[i] = o.arr[j];
    return *this;
  }
  Vec operator+(const Vec& o) {
    Vec out;
    for (int j = 0; j < i; j++) {
      out.arr[j] = arr[j] + o.arr[j];
    }
    return out;
  }
  Vec operator+=(const Vec& o) {
    for (int j = 0; j < i; j++) {
      arr[j] += o.arr[j];
    }
    return *this;
  }
  Vec operator-(const Vec& o) {
    Vec out;
    for (int j = i; j < i; j++) {
      out.arr[j] = arr[j] - o.arr[j];
    }
  }
  Vec operator-=(const Vec& o); 
  Vec operator*(T scale); 
  Vec operator*=(T scale); 
};

template <int i, typename T> bool operator==(const Vec<i, T>& l, const Vec<i, T>& r) {
  for (int j = 0; j < i; j++) {
    if (l.arr[i] != r.arr[i])
      return false;
  }
  return true;
}
  
template<typename T> class Vec<2, T> {
public:
  T x;
  T y;
};

template<typename T> bool operator==(const Vec<2, T>& l, const Vec<2, T>& r) {
  return l.x == r.x && l.y == r.y;
}

template<typename T> class Vec<3, T> {
public:
  union {
    struct {
      T x;
      T y;
      T z;
    };
    struct {
      T r;
      T g;
      T b;
    };
  };

  Vec() : x(0), y(0), z(0) {}
  Vec(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
  Vec(const Vec<4, T>& copy) : x(copy.x), y(copy.y), z(copy.z) {};

  bool operator==(const Vec<3, T>& o) {
    return x == o.x && y == o.y && z == o.z;
  }
  Vec operator+=(const Vec<3, T>& o) {
    x += o.x;
    y += o.y;
    z += o.z;
    return *this;
  }
  Vec operator-=(const Vec<3, T> &o) {
    x -= o.x;
    y -= o.y;
    z -= o.z;
    return *this;
  }
  Vec operator *=(const T scale) {
    x *= scale;
    y *= scale;
    z *= scale;
    return *this;
  }
  T magnitude () const {
    return sqrt(x*x + y*y + z*z);
  }
  Vec normalize() {
    T m = magnitude();
    x = x / m;
    y = y / m;
    z = z / m;
    return *this;
  }
  Vec normalized() const {
    T m = magnitude();
    return Vec(x / m, y / m, z / m);
  }
};

template <typename T> Vec<3, T> operator+(const Vec<3, T>& l, const Vec<3, T>& r) {
  return Vec<3, T>(l.x + r.x, l.y + r.y, l.z + r.z);
}
template <typename T> Vec<3, T> operator-(const Vec<3, T>& left, const Vec<3, T>& right) {
  return Vec<3, T>(left.x - right.x, left.y - right.y, left.z - right.z);
}
template<typename T> Vec<3, T> operator*(const T& scale, const Vec<3, T>& vec) {
  return Vec<3, T>(scale * vec.x, scale * vec.y, scale * vec.z);
}
template<typename T> Vec<3, T> operator*(const Vec<3, T>& vec, const T& scale) {
  return Vec<3, T>(scale * vec.x, scale * vec.y, scale * vec.z);
}


template<typename T> T operator*(const Vec<3, T>& left, const Vec<3, T>& right) {
  return left.x * right.x + left.y * right.y + left.z * right.z;
}

template<typename T> Vec<3, T> cross(const Vec<3, T>& left, const Vec<3, T>& right) {
  return Vec<3, T>(left.y * right.z - left.z * right.y,
                   left.z * right.x - left.x * right.z,
                   left.x * right.y - left.y * right.x);
}

template<typename T> std::ostream& operator<<(std::ostream& os, const Vec<3, T>& v) {
  os << "[" << v.x << ", " << v.y << ", " << v.z << ", " << "]";
  return os;
}


template<typename T> class Vec<4, T> {
public:
  union {
    struct {
      T x;
      T y;
      T z;
      T w;
    };
    struct {
      T r;
      T g;
      T b;
      T a;
    };
  };

  Vec(T _x = 0, T _y = 0, T _z = 0, T _w = 0) : x(_x), y(_y), z(_z), w(_w) {}
  Vec (const Vec<3, T>& v, const T _w) : x(v.x), y (v.y), z (v.z), w(_w) {}

};

template<typename T> T operator*(const Vec<4, T>& left, const Vec<4, T>& right) {
  return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
}

template<typename T> std::ostream& operator<<(std::ostream& os, const Vec<4, T>& v) {
  os << "[" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << "]";
  return os;
}

#endif
