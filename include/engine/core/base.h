#ifndef BASE_H
#define BASE_H

/** @file
 *
 * @brief Core engine functionality - may get moved to other files over time and become an aggregating include
 */

///@addtogroup Base
///@{

#include <stdio.h>

#include "engine/core/types.h"


/** @brief creates a new entity in the engine from the provided template
 * 
 * @details The template contains two arrays: one which contains components for the engine to give the entity,
 *          and another detailing what type thet are. The exact implementation of the template function is left
 *          to the user, all that matters is that they provice a valid template.
 *
 * @param[in] template_creator: a function which creates a template object
 * 
 * @return entity_id: The handle to the created entity within the engine. Allows the engine user to access the 
 *         entity's components
 */
int add_entity(void (template_creator)(Template*));


void delete_entity(int id);


/** @brief gets the component of a specific type from the provided entity
 *
 * @details Will return a pointer to the entity's component of that type if it exists, or a nullptr otherwise
 *          if the entity given is not valid, will either experience undefined behaviour (not in debug mode) 
 *          or output an error to the log and return null. The same will happen for invalid types
 *
 * @param[in] id: The id of a specific entity in the engine
 *
 * @param[in] type: The (enum) type that you want to get. types can be registered through register_type()
 *
 * @return a pointer to either null or the object you wanted
 */
void* get_component(int id, int type);

/** @brief Adds a component as a valid type to the component system.
 *
 * @details Takes 
 *
 * @param[in] type: The type is an int which is associated with a specific component type - it corresponds to the
 *                  index of all components in each record.
 * 
 * @param[in] new_function: a function which will create a component of type type.
 *
 * @param[in] delete_function: a function which should free all data in a component
 */
void register_component(int type, void* (*new_function)(), void (*delete_function)(void*));

void register_system(void (*system)(), void (*sys_init)(), void (*sys_clean)());

void init();

void run();

void stop();

void clean();

///@}
#endif
