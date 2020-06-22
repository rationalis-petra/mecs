#ifndef COLLIDER_H
#define COLLIDER_H

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
typedef float* Mesh;
typedef struct Collider {
  Mesh* mesh;   ///< The angle of inclination from the camera to the target
} Collider;

void* new_collider();

void delete_collider(void* _collider);
///@}

#endif
