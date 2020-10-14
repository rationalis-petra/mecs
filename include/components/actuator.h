#ifndef __ACTUATOR_H_
#define __ACTUATOR_H_


///@addtogroup Components
///@{

/** @brief An actuator is any component which can be controlled by an agent and can act upon the
 *         environment.
 */

typedef enum {Linear, Cannon} TypeofActuator;

typedef struct {
    TypeofActuator type; ///< Variable giving the type of the actuator - what does it do?
    int amount;          ///< An 'instruction' variable, telling the actuator what action to perform
    int machine;         ///< An id which tells the actuator which machine (robot) it is a part of
} Actuator;
///@}

void* new_actuator(void);

void delete_actuator(void* actuator);

#endif // __ACTUATOR_H_
