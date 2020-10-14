#ifndef __RIGIDBODY_H
#define __RIGIDBODY_H

#include "engine.h"

///@addtogroup Components
///@{

/** @brief The Rigidbody struct contains a pointer to a collision mesh, usually simpler than the render mesh.
 *         It also contains various bits of physics information
 *
 * @details The camera struct contains information about it's position relative
 *          to a target
 */
typedef struct RigidBody {
  float mass;      ///< Standard newtonian mass
  Vec3f position;  ///< Store the postion - allows visual position changes (via Model) without changing the 'physics' position
  Vec3f velocity;  ///< Change in position w.r.t time
  Vec3f force;     ///< any forces that are acting on the object - gets reset to 0 when physics is called
  ResourceID mesh; ///< the mesh used for collisions
} RigidBody;

void* new_rigidbody();

void delete_rigidbody(void* rigidbody);
///@}

#endif
