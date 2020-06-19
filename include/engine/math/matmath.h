#ifndef MATMATH_H
#define MATMATH_H

/**@file
 * @brief a set of functions and types for doing math on matrices
 */
/// @addtogroup Matrices
/// @{

/*
#define define_mat4(Type, Prefix)		\
  typedef Mat4##Prefix Type*;	  \
*/

//define_mat4(double, d);
//define_mat4(float, f);
//define_mat4(int, i);

typedef float* Mat4f;

/** @brief multiplies two matrices
 *
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
 *
 */
Mat4f mat4f_translate(float x, float y, float z);

/** @brief Creates a view matrix which will translate to coordinates
 * 
 * @details The matrix will perform a translation such that the default
 *          OpenGl rendering will result in a view from the position given
 *          looking at the target, with an orientation specificed by the 
 *          up vector
 */
Mat4f mat4f_look_at(Vec3f position, Vec3f target, Vec3f up);

/** @brief Perspective projection matrices reduce the size of an object the
 *         further away it is.
 * 
 * @details The perspective projection matrix projects all 3d coordinates into a plane.
 *          The breadth of the view frustrum is affected by the fov, while the width and
 *          height are calculated from the ratio (which is width / height).
 */
Mat4f mat4f_perspective(float fov, float ratio, float near, float far);

/// @}

#endif
