#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "engine.h"

/** @file
 * @brief contains the collider struct
 */

///@addtogroup Components
///@{

/** @brief The collider struct contains a pointer to a collision mesh, usually simpler than the render mesh.
 *
 * @details The camera struct contains information about it's position relative
 *          to a target
 */
typedef struct RigidBody {
  // all collision boxes are square
  float mass;
  Vec3f velocity;  ///
  Vec3f force;     /// any forces that are acting on the object - gets reset to 0 when physics is called
} RigidBody;

void* new_rigidbody();

void delete_rigidbody(void* rigidbody);
///@}

#endif
