#ifndef __CAMERA_HPP
#define __CAMERA_HPP

#include "math/math.hpp"
#include "ecs/ecs.hpp"


/** @brief The camera struct allows a camera to be attached to the entity which
 *         contains it.
 *
 * @details The camera struct contains information about it's position relative
 *          to a target
 */
class Camera : public Component {
public:
  float theta;   ///< The angle of inclination from the camera to the target
  float phi;     ///< The azmithal angle from the x-axis to the target
  float r;       ///< The spherical radial distance from the player to the camera

  Camera();
  Camera(float theta, float phi, float r);
  ~Camera();
};


#endif
