#ifndef __CAMERA_H_
#define __CAMERA_H_

///@addtogroup Components
///@{

/** @brief The camera struct allows a camera to be attached to the entity which
 *         contains it.
 *
 * @details The camera struct contains information about it's position relative
 *          to a target
 */
class Camera {
public:
  static unsigned type_idx;
  
  float theta;   ///< The angle of inclination from the camera to the target
  float phi;     ///< The azmithal angle from the x-axis to the target
  float r;       ///< The spherical radial distance from the player to the camera

  Camera();
  Camera(float theta, float phi, float r);
  ~Camera();
};

///@}

#endif
