#include "physics/physics.hpp"

#include <vector>

const float spring_constant = 1.0f;
const float damp_constant = 1.0f;

using std::vector;


// function which will return a vector which can be decomposed
// into all accelerations experienced by the rigidbodies
vector<float> solve_constraints(vector<float> positions,          // length 3n
                                vector<float> velocities,         // length 3n
                                vector<float> forces,             // length 3n
                                vector<float> masses,             // length n
                                vector<Constraint> constraints) { // length m
  // constraints need to be able to calculate:
  // The value of the constraint function
  // The time derivative of the constraint function
  // The partial derivative of the constraint function with respect to
  //     the position of each particle (Jacobian)
  // The partial derivative of time derivative of the constraint function
  //     with respect to the position of each particle (Jacobian dot)

  // This code is quite compact, but relies on other functions to do much of the heavy-lifting
  // see http://www.cs.cmu.edu/~baraff/sigcourse/notesf.pdf for the theory

  // DiagonalMatrix w = inverse(DiagonalMatrix(masses));

  // SparseMatrix jacobian = generate_jacobian(constraints);

  // SparseMatrix jacobian_dot = generate_jacobian_dot(constraints);

  
  // we want to solve the equation <first_argument> * lambda = <second_argument>
  // vector<float> lambda = matrix_solve(jabobian * w * transpose(jacobian),
  //                                     -1.0f * ((jacobian_dot * velocities) +
  //                                              (jabobian * w * forces) +
  //                                              (spring_constant * generate_valvec(constraints)) +
  //                                              (damp_constrant * generate_valdotvec(constraints))));

  // we return a vector containing all final accelerations!
  // (slidesf, slide 18)
  return vector<float>();// w * (forces + transpose(jacobian) * lambda);
}
