#ifndef __RIGIDBODY_H
#define __RIGIDBODY_H

#include "engine.hpp"

///@addtogroup Components
///@{

/** @brief The Rigidbody struct contains a pointer to a collision mesh, usually simpler than the render mesh.
 *         It also contains various bits of physics information
 *
 * @details The camera struct contains information about it's position relative
 *          to a target
 */
class RigidBody : public Component {
public:
  static unsigned type_idx;

  float mass;                 /// Standard newtonian mass
  Vec<3, float> position;     /// Store the postion - allows visual position changes (via Model) without changing the 'physics' position
  Vec<3, float> orientation;  /// A triple of Euler angles: theta, phi, psi
  Vec<3, float> velocity;     /// Change in position w.r.t time
  Vec<3, float> force;        /// any forces that are acting on the object - gets reset to 0 when physics is called
  //Resource mesh;              /// the mesh used for collisions

  RigidBody();
  RigidBody(float x, float y, float z);
  ~RigidBody();
};
///@}

#endif
