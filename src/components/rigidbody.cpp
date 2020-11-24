#include <stdlib.h>

#include "components/rigidbody.hpp"

#ifndef NDEBUG
#include <stdio.h>
#endif

RigidBody::RigidBody() : mass(0.0f), position({0.0f, 0.0f, 0.0f}), force({0.0f, 0.0f, 0.0f}), velocity({0.0f, 0.0f, 0.0f}) {}

RigidBody::RigidBody(float x, float y, float z) : mass(0.0f), position({x, y, z}), force({0.0f, 0.0f, 0.0f}), velocity({0.0f, 0.0f, 0.0f}) {}

RigidBody::~RigidBody() {
#ifndef NDEBUG
  if (!this) {
    perror( "error in function delete_rigidbody in component Rigidbody: Rigidbody is null\n");
  }
#endif
}
