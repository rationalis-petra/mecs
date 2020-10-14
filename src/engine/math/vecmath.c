#include <math.h>

#include "engine/math/vecmath.h"

#define CONCAT_THREE(x, y, z) \
  x ## y ## z

#define define_new_vec2(Prefix, Type) \
  Vec2##Prefix CONCAT_THREE(new_, vec2, Prefix)(Type x, Type y) {	\
  Vec2##Prefix out; \
  out.x = x; \
  out.y = y; \
  return out; \
  }

#define define_vec2_equals(Prefix) \
  int CONCAT_THREE(vec2, Prefix, _equals)(Vec2##Prefix vec) { \
  return (vec1.x == vec2.x) && (vec1.y == vec2.y);	       \
  }

#define define_vec2_magnitude(Prefix, Type)			  \
  Type CONCAT_THREE(vec2, Prefix, _magnitude)(Vec2##Prefix vec) { \
    return sqrt(vec.x * vec.x + vec.y * vec.y);			  \
  }

#define define_vec2_normalize(Prefix, Type)				\
  Vec2##Prefix CONCAT_THREE(vec2, Prefix, _normalize)(Vec2##Prefix vec) { \
    Type mag = sqrt(vec.x * vec.x + vec.y * vec.y);			\
    Vec2##Prefix out;							\
    out.x = vec.x / mag;						\
    out.y = vec.y / mag;						\
    return out;								\
  }

#define define_vec2_sum(Prefix)						\
  Vec2##Prefix CONCAT_THREE(vec2, Prefix, _sum)(Vec2##Prefix vec1, Vec2##Prefix vec2) { \
    Vec2##Prefix out;							\
    out.x = vec1.x + vec2.x;						\
    out.y = vec1.y + vec2.y;						\
    return out;								\
  }

#define define_vec2_difference(Prefix) \
  Vec2##Prefix CONCAT_THREE(vec2, Prefix, _difference)(Vec2##Prefix vec1, Vec2##Prefix vec2) { \
    Vec2##Prefix out;							\
    out.x = vec1.x - vec2.x;						\
    out.y = vec1.y - vec2.y;						\
    return out;								\
  }

#define define_vec2_dot(Prefix, Type)					\
  Type CONCAT_THREE(vec2, Prefix, _dot)(Vec2##Prefix vec1, Vec2##Prefix vec2) { \
    return vec1.x * vec2.x + vec1.y * vec2.y;				\
  }


#define define_new_vec3(Prefix, Type) \
  Vec3##Prefix CONCAT_THREE(new_, vec3, Prefix)(Type x, Type y, Type z) { \
    Vec3##Prefix out;							\
    out.x = x;								\
    out.y = y;								\
    out.z = z;								\
    return out;								\
  }

#define define_vec3_multiply(Prefix, Type)				\
  Vec3##Prefix CONCAT_THREE(vec3, Prefix, _multiply)(Type v, Vec3##Prefix vec) { \
  vec.x *= v;								\
  vec.y *= v;								\
  vec.z *= v;								\
  return vec;								\
}


#define define_vec3_magnitude(Prefix, Type) \
  Type CONCAT_THREE(vec3, Prefix, _magnitude)(Vec3##Prefix vec) { \
    return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);	  \
  }

#define define_vec3_normalize(Prefix, Type) \
  Vec3##Prefix CONCAT_THREE(vec3, Prefix, _normalize)(Vec3##Prefix vec) { \
    Type mag = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);	\
    vec.x = vec.x / mag;						\
    vec.y = vec.y / mag;						\
    vec.z = vec.z / mag;						\
    return vec;								\
  }

#define define_vec3_equals(Prefix) \
  int CONCAT_THREE(vec3, Prefix, _equals)(Vec3##Prefix vec1, Vec3##Prefix vec2) { \
    return (vec1.x == vec2.x) && (vec1.y == vec2.y) && (vec1.z == vec2.z); \
  }

#define define_vec3_sum(Prefix) \
  Vec3##Prefix CONCAT_THREE(vec3, Prefix, _sum)(Vec3##Prefix vec1, Vec3##Prefix vec2) { \
    Vec3##Prefix out;							\
    out.x = vec1.x + vec2.x;						\
    out.y = vec1.y + vec2.y;						\
    out.z = vec1.z + vec2.z;						\
    return out;								\
  }
  
#define define_vec3_difference(Prefix) \
  Vec3##Prefix CONCAT_THREE(vec3, Prefix, _difference)(Vec3##Prefix vec1, Vec3##Prefix vec2) { \
    Vec3##Prefix out;							\
    out.x = vec1.x - vec2.x;						\
    out.y = vec1.y - vec2.y;						\
    out.z = vec1.z - vec2.z;						\
    return out;								\
  }

#define define_vec3_dot(Prefix, Type)					\
  Type CONCAT_THREE(vec3, Prefix, _dot)(Vec3##Prefix vec1, Vec3##Prefix vec2) { \
    return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;		\
  }

#define define_vec3_cross(Prefix) \
  Vec3##Prefix CONCAT_THREE(vec3, Prefix, _cross)(Vec3##Prefix vec1, Vec3##Prefix vec2) { \
    Vec3##Prefix out;							\
    out.x = vec1.y * vec2.z - vec1.z * vec2.y;				\
    out.y = vec1.z * vec2.x - vec1.x * vec2.z;				\
    out.z = vec1.x * vec2.y - vec1.y * vec2.x;				\
    return out;								\
  }

#define define_new_vec4(Prefix, Type) \
  Vec4##Prefix CONCAT_THREE(new_, vec4, Prefix)(Type x, Type y, Type z, Type w) { \
    Vec4##Prefix out;							\
    out.x = x;								\
    out.y = y;								\
    out.z = z;								\
    out.w = w;								\
    return out;								\
  }

#define define_vec4_multiply(Prefix, Type)				\
  Vec4##Prefix CONCAT_THREE(vec4, Prefix, _multiply)(Type v, Vec4##Prefix vec) { \
  vec.x *= v;								\
  vec.y *= v;								\
  vec.z *= v;								\
  vec.w *= v;								\
  return vec;								\
}
  

#define define_vec4_magnitude(Prefix, Type) \
  Type CONCAT_THREE(vec4, Prefix, _magnitude)(Vec4##Prefix vec) { \
    return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w); \
  }

#define define_vec4_normalize(Prefix, Type) \
  Vec4##Prefix CONCAT_THREE(vec4, Prefix, _normalize)(Vec4##Prefix vec) { \
  Type mag = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w); \
    vec.x = vec.x / mag;						\
    vec.y = vec.y / mag;						\
    vec.z = vec.z / mag;						\
    vec.w = vec.w / mag;						\
    return vec;								\
  }

#define define_vec4_equals(Prefix) \
  int CONCAT_THREE(vec4, Prefix, _equals)(Vec4##Prefix vec1, Vec4##Prefix vec2) { \
    return (vec1.x == vec2.x) && (vec1.y == vec2.y) && (vec1.z == vec2.z) && (vec1.w == vec2.w); \
  }

#define define_vec4_sum(Prefix) \
  Vec4##Prefix CONCAT_THREE(vec4, Prefix, _sum)(Vec4##Prefix vec1, Vec4##Prefix vec2) { \
    Vec4##Prefix out;							\
    out.x = vec1.x + vec2.x;						\
    out.y = vec1.y + vec2.y;						\
    out.z = vec1.z + vec2.z;						\
    out.w = vec1.w + vec2.w;						\
    return out;								\
  }
  
#define define_vec4_difference(Prefix) \
  Vec4##Prefix CONCAT_THREE(vec4, Prefix, _difference)(Vec4##Prefix vec1, Vec4##Prefix vec2) { \
    Vec4##Prefix out;							\
    out.x = vec1.x - vec2.x;						\
    out.y = vec1.y - vec2.y;						\
    out.z = vec1.z - vec2.z;						\
    out.w = vec1.w - vec2.w;						\
    return out;								\
  }

#define define_vec4_dot(Prefix, Type)					\
  Type CONCAT_THREE(vec4, Prefix, _dot)(Vec4##Prefix vec1, Vec4##Prefix vec2) { \
    return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z + vec1.w * vec2.w;		\
  }

define_vec2_magnitude(d, double)
define_vec2_magnitude(f, float)
define_vec2_magnitude(i, int)

define_vec2_normalize(d, double)
define_vec2_normalize(f, float)
define_vec2_normalize(i, int)

define_vec2_sum(d)
define_vec2_sum(f)
define_vec2_sum(i)

define_vec2_difference(d)
define_vec2_difference(f)
define_vec2_difference(i)

define_vec2_dot(d, double)
define_vec2_dot(f, float)
define_vec2_dot(i, int)

define_new_vec3(d, double)
define_new_vec3(f, float)
define_new_vec3(i, int)

define_vec3_equals(d)
define_vec3_equals(f)
define_vec3_equals(i)

define_vec3_multiply(d, double)
define_vec3_multiply(f, float)
define_vec3_multiply(i, int)

define_vec3_magnitude(d, double)
define_vec3_magnitude(f, float)
define_vec3_magnitude(i, int)

define_vec3_normalize(d, double)
define_vec3_normalize(f, float)
define_vec3_normalize(i, int)

define_vec3_sum(d)
define_vec3_sum(f)
define_vec3_sum(i)

define_vec3_difference(d)
define_vec3_difference(f)
define_vec3_difference(i)

define_vec3_dot(d, double)
define_vec3_dot(f, float)
define_vec3_dot(i, int)

define_vec3_cross(d)
define_vec3_cross(f)
define_vec3_cross(i)

define_new_vec4(d, double)
define_new_vec4(f, float)
define_new_vec4(i, int)

define_vec4_equals(d)
define_vec4_equals(f)
define_vec4_equals(i)

define_vec4_multiply(d, double)
define_vec4_multiply(f, float)
define_vec4_multiply(i, int)

define_vec4_magnitude(d, double)
define_vec4_magnitude(f, float)
define_vec4_magnitude(i, int)

define_vec4_normalize(d, double)
define_vec4_normalize(f, float)
define_vec4_normalize(i, int)

define_vec4_sum(d)
define_vec4_sum(f)
define_vec4_sum(i)

define_vec4_difference(d)
define_vec4_difference(f)
define_vec4_difference(i)

define_vec4_dot(d, double)
define_vec4_dot(f, float)
define_vec4_dot(i, int)
