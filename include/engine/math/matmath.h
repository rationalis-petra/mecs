#ifndef MATMATH_H
#define MATMATH_H

/** @brief a typedef for a 4x4 float Matrix - we use /column-major/ ordering
 *
 */
typedef float* Mat4f;

/** @brief Tests if two matrices are equal
 *
 */
int mat4f_equals(Mat4f mat1, Mat4f mat2);

/** @brief multiplies two matrices
 *
 */
Mat4f mat4f_multiply(Mat4f mat1, Mat4f mat2);

/** @brief pre-multiplies the vector vec by the matrix mat
 *
 */
Vec4f mat4f_act_on(Mat4f mat, Vec4f vec);

/**@brief returns the identity matrix in 4d-space
 *
 */
Mat4f mat4f_identity();

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

/** @brief Prints a representation of the matrix, for debugging purposes*/
void mat4f_print(Mat4f matrxi);

/// @}

#endif
