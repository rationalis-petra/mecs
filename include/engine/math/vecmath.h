#ifndef VECMATH_H
#define VECMATH_H

/** @file 
 * @brief a set of functions for doing math on vectors
 */

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
};\

define_vec2(double, d) 
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

double vec2d_magnitude(Vec2d* vec);
float vec2f_magnitude(Vec2f* vec);
int vec2i_magnitude(Vec2i* vec);

Vec2d vec2d_sum(Vec2d* vec1, Vec2d* vec2);
Vec2f vec2f_sum(Vec2f* vec1, Vec2f* vec2);
Vec2i vec2i_sum(Vec2i* vec1, Vec2i* vec2);

Vec2d vec2d_difference(Vec2d* vec1, Vec2d* vec2);
Vec2f vec2f_difference(Vec2f* vec1, Vec2f* vec2);
Vec2i vec2i_difference(Vec2i* vec1, Vec2i* vec2);

double vec2d_dot(Vec2d* vec1, Vec2d* vec2);
float vec2f_dot(Vec2f* vec1, Vec2f* vec2);
int vec2i_dot(Vec2i* vec1, Vec2i* vec2);

double vec3d_magnitude(Vec3d* vec);
float vec3f_magnitude(Vec3f* vec);
int vec3i_magnitude(Vec3i* vec);

Vec3d vec3d_sum(Vec3d* vec1, Vec3d* vec2);
Vec3f vec3f_sum(Vec3f* vec1, Vec3f* vec2);
Vec3i vec3i_sum(Vec3i* vec1, Vec3i* vec2);

Vec3d vec3d_difference(Vec3d* vec1, Vec3d* vec2);
Vec3f vec3f_difference(Vec3f* vec1, Vec3f* vec2);
Vec3i vec3i_difference(Vec3i* vec1, Vec3i* vec2);

double vec3d_dot(Vec3d* vec1, Vec3d* vec2);
float vec3f_dot(Vec3f* vec, Vec3f* vec2);
int vec3i_dot(Vec3i* vec, Vec3i* vec2);

Vec3d vec3d_cross(Vec3d* vec1, Vec3d* vec2);
Vec3f vec3f_cross(Vec3f* vec1, Vec3f* vec2);
Vec3i vec3i_cross(Vec3i* vec1, Vec3i* vec2);

#endif
