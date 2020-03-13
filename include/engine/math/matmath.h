#ifndef MATMATH_H
#define MATMATH_H

/**@file
 * @brief a set of functions and types for doing math on matrices
 */

//#define define_mat4(Type, Prefix)		\
  //typedef Mat4##Prefix Type*;	  \

//define_mat4(double, d);
//define_mat4(float, f);
//define_mat4(int, i);

typedef float* Mat4f;

/** @brief multiplies two matrices
 */
Mat4f mat4f_multiply(Mat4f mat1, Mat4f mat2);

/** @brief creates a mstrix which will scale a vector by (x, y, z)
 * 
 */
Mat4f mat4f_scale(float x, float y, float z);

/** @brief Creates a rotation matrix which will rotate a vector by (x, y, z)
 * 
 * @details will apply the rotations the following order: x->y->z
 */
Mat4f mat4f_rotate(float x, float y, float z);

/** @brief Creates a matrix which will translate a vector by (x, y, z)
 */
Mat4f mat4f_translate(float x, float y, float z);

#endif
