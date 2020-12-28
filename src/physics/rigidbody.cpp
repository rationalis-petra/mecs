#include <stdlib.h>

#include "physics/rigidbody.hpp"

#ifndef NDEBUG
#include <stdio.h>
#endif

RigidBody::RigidBody() :
  mass(0.0f),
  position(0.0f, 0.0f, 0.0f),
  orientation(0.0f, 0.0f, 0.0f),
  velocity(0.0f, 0.0f, 0.0f),
  force(0.0f, 0.0f, 0.0f) {}

RigidBody::RigidBody(float x, float y, float z) :
  mass(1.0f),
  position(x, y, z),
  orientation(0.0f, 0.0f, 0.0f),
  velocity(0.0f, 0.0f, 0.0f),
  force(0.0f, 0.0f, 0.0f) {}

RigidBody::~RigidBody() {
}
