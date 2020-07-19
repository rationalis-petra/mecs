#ifndef __CAMERA_H
#define __CAMERA_H

/** @file
 * @brief contains the camera struct
 */

///@addtogroup Components
///@{

/** @brief The camera struct allows a camera to be attached to the entity which
 *         contains it.
 *
 * @details The camera struct contains information about it's position relative
 *          to a target
 */
typedef struct Camera {
  float theta;   ///< The angle of inclination from the camera to the target
  float phi;     ///< The azmithal angle from the x-axis to the target
  float r;       ///< The spherical radial distance from the player to the camera
} Camera;

void* new_camera();

void delete_camera(void* _camera);
///@}

#endif
