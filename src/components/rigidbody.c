#include <stdlib.h>

#include "components/rigidbody.h"

#ifndef NDEBUG
#include <stdio.h>
#endif

void* new_rigidbody() {
  RigidBody* rigidbody = malloc(sizeof(RigidBody));

  rigidbody->mass = 0.0f;
  rigidbody->force.x = 0.0f, rigidbody->force.y = 0.0f; rigidbody->force.z = 0.0f;
  rigidbody->velocity.x = 0.0f, rigidbody->velocity.y = 0.0f; rigidbody->velocity.z = 0.0f;

  return rigidbody;
}

void delete_rigidbody(void* rigidbody) {
  #ifndef NDEBUG
  if (!rigidbody) {
    perror( "error in function delete_rigidbody in component Rigidbody: Rigidbody is null\n");
  }
  #endif
  free(rigidbody);
}
