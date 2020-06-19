#ifndef VECMATH_H
#define VECMATH_H

/** @file
 * @brief a set of functions and types for doing math on vectors
 */

/// @addtogroup Vectors
/// @{
#define define_vec2(Type, Prefix) \
typedef struct Vec2##Prefix Vec2##Prefix; \
struct Vec2##Prefix { \
    Type x; \
    Type y; \
};


#define define_vec3(Type, Prefix) \
typedef struct Vec3##Prefix Vec3##Prefix; \
struct Vec3##Prefix { \
union { \
    struct { \
	Type x; \
	Type y; \
	Type z; \
    }; \
    struct { \
	Type r; \
	Type g; \
	Type b; \
    }; \
}; \
};

#define define_vec4(Type, Prefix) \
typedef struct Vec4##Prefix Vec4##Prefix; \
    struct Vec4##Prefix { \
    union { \
	struct { \
	    Type x; \
	    Type y; \
	    Type z; \
	    Type w; \
	}; \
	struct { \
	    Type r; \
	    Type g; \
	    Type b; \
	    Type a; \
	};\
    };\
};

define_vec2(double, d);
define_vec2(float, f)
define_vec2(int, i)
define_vec2(unsigned int, u)

define_vec3(double, d)
define_vec3(float, f)
define_vec3(int, i)
define_vec3(unsigned int, u)

define_vec4(double, d)
define_vec4(float, f)
define_vec4(int, i)
define_vec4(unsigned int, u)

Vec2d new_vec2d();
Vec2f new_vec2f();
Vec2i new_vec2i();

int vec2d_equals(Vec2d vec1, Vec2d vec2);
int vec2f_equals(Vec2f vec1, Vec2f vec2);
int vec2i_equals(Vec2i vec1, Vec2i vec2);

Vec2d vec2d_normalize(Vec2d vec);
Vec2f vec2f_normalize(Vec2f vec);
Vec2i vec2i_normalize(Vec2i vec);

double vec2d_magnitude(Vec2d vec);
float vec2f_magnitude(Vec2f vec);
int vec2i_magnitude(Vec2i vec);

Vec2d vec2d_sum(Vec2d vec1, Vec2d vec2);
Vec2f vec2f_sum(Vec2f vec1, Vec2f vec2);
Vec2i vec2i_sum(Vec2i vec1, Vec2i vec2);

Vec2d vec2d_difference(Vec2d vec1, Vec2d vec2);
Vec2f vec2f_difference(Vec2f vec1, Vec2f vec2);
Vec2i vec2i_difference(Vec2i vec1, Vec2i vec2);

double vec2d_dot(Vec2d vec1, Vec2d vec2);
float vec2f_dot(Vec2f vec1, Vec2f vec2);
int vec2i_dot(Vec2i vec1, Vec2i vec2);

Vec3d new_vec3d(double x, double y, double z);
Vec3f new_vec3f(float x, float y, float z);
Vec3i new_vec3i(int x, int y, int z);

int vec3d_equals(Vec3d vec1, Vec3d vec2);
int vec3f_equals(Vec3f vec1, Vec3f vec2);
int vec3i_equals(Vec3i vec1, Vec3i vec2);

Vec3d vec3d_multiply(double d, Vec3d vc);
Vec3f vec3f_multiply(float f, Vec3f vec);
Vec3i vec3i_multiply(int i, Vec3i vec);

double vec3d_magnitude(Vec3d vec);
float vec3f_magnitude(Vec3f vec);
int vec3i_magnitude(Vec3i vec);

Vec3d vec3d_normalize(Vec3d vec);
Vec3f vec3f_normalize(Vec3f vec);
Vec3i vec3i_normalize(Vec3i vec);

Vec3d vec3d_sum(Vec3d vec1, Vec3d vec2);
Vec3f vec3f_sum(Vec3f vec1, Vec3f vec2);
Vec3i vec3i_sum(Vec3i vec1, Vec3i vec2);

Vec3d vec3d_difference(Vec3d vec1, Vec3d vec2);
Vec3f vec3f_difference(Vec3f vec1, Vec3f vec2);
Vec3i vec3i_difference(Vec3i vec1, Vec3i vec2);

double vec3d_dot(Vec3d vec1, Vec3d vec2);
float vec3f_dot(Vec3f vec, Vec3f vec2);
int vec3i_dot(Vec3i vec, Vec3i vec2);

Vec3d vec3d_cross(Vec3d vec1, Vec3d vec2);
Vec3f vec3f_cross(Vec3f vec1, Vec3f vec2);
Vec3i vec3i_cross(Vec3i vec1, Vec3i vec2);

Vec4d new_vec4d(double x, double y, double z, double w);
Vec4f new_vec4f(float x, float y, float z, float w);
Vec4i new_vec4i(int x, int y, int z, int w);

int vec4d_equals(Vec4d vec1, Vec4d vec2);
int vec4f_equals(Vec4f vec1, Vec4f vec2);
int vec4i_equals(Vec4i vec1, Vec4i vec2);

Vec4d vec4d_multiply(double d, Vec4d vc);
Vec4f vec4f_multiply(float f, Vec4f vec);
Vec4i vec4i_multiply(int i, Vec4i vec);

double vec4d_magnitude(Vec4d vec);
float vec4f_magnitude(Vec4f vec);
int vec4i_magnitude(Vec4i vec);

Vec4d vec4d_normalize(Vec4d vec);
Vec4f vec4f_normalize(Vec4f vec);
Vec4i vec4i_normalize(Vec4i vec);

Vec4d vec4d_sum(Vec4d vec1, Vec4d vec2);
Vec4f vec4f_sum(Vec4f vec1, Vec4f vec2);
Vec4i vec4i_sum(Vec4i vec1, Vec4i vec2);

Vec4d vec4d_difference(Vec4d vec1, Vec4d vec2);
Vec4f vec4f_difference(Vec4f vec1, Vec4f vec2);
Vec4i vec4i_difference(Vec4i vec1, Vec4i vec2);

double vec4d_dot(Vec4d vec1, Vec4d vec2);
float vec4f_dot(Vec4f vec, Vec4f vec2);
int vec4i_dot(Vec4i vec, Vec4i vec2);

/// @}
#endif
