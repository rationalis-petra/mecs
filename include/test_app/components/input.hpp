#ifndef __INPUT_H
#define __INPUT_H

#include "engine.hpp"

/** The Input component is used to capture information from user-input
 *  Currently, it is quite simple. The input only allows the application
 *  of force to objects, which is then picked up by the physics system
 */
class Input : public Component {
public:
  // input_force will allow the input system to add an 'external force'
  // to any entity with an input object, which can then be used by the
  // physics system
  Vec<3, float> input_force;    
  // input torque is much the same as for input force... except for
  // torque
  Vec<3, float> input_torque;    

  Input();
  ~Input();
};

#endif
