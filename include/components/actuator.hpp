#ifndef __ACTUATOR_H_
#define __ACTUATOR_H_

#include "engine.hpp"

///@addtogroup Components
///@{

/** @brief An actuator is any component which can be controlled by an agent and can act upon the
 *         environment.
 */

typedef enum {Linear, Cannon} TypeofActuator;

class Actuator : public Component {
public:
  static unsigned type_idx;
  TypeofActuator type; ///< Variable giving the type of the actuator - what does it do?
  int amount;          ///< An 'instruction' variable, telling the actuator what action to perform
  int machine;         ///< An id which tells the actuator which machine (robot) it is a part of

  Actuator();
  ~Actuator();
};
///@}

#endif // __ACTUATOR_H_
