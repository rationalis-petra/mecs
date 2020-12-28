#ifndef __CONSTRAINT_HPP
#define __CONSTRAINT_HPP

#include "ecs/ecs.hpp"
#include "physics/dynamics/sparse_matrix.hpp"

class Constraint {
public:
  // calculate the value and value of derivative
  virtual float value() = 0;
  virtual float value_dot() = 0;

  // calculate a partial derivative of the function w.r.t. an input element (del C / del x_i)
  // the dot version calculates (del^2 C/(del x_i del t)
  virtual Block partial() = 0;
  virtual Block partial_dot() = 0;
};


// example constraint subclass:
class DistanceConstraint : public Constraint {
private:
  // the distance constraint joins *two* entities
  Entity e1;
  Entity e2;

  // the desired distance, d
  float d;
  DistanceConstraint();

public:
  DistanceConstraint(Entity e1, Entity e2, float distance);
};

// Allows interface between constraint system and the ECS
class ConstraintRef : public Component {
public:
  Constraint* constraint;
};
#endif
