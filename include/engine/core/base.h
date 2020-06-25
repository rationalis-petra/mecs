#ifndef BASE_H
#define BASE_H

/** @file
 *
 * @brief Core engine functionality - may get moved to other files over time and become an aggregating include
 */

///@addtogroup Base
///@{

#include <stdio.h>
#include <stdarg.h>

#include "engine/core/types.h"


/** @brief creates a new entity in the engine from the provided template
 * 
 * @details The function which will allow an entity to be created, then inserted into the ecs
 *
 * @param[in] template_creator: a function which creates a template object, potentially accepting some arguments
 *
 * @param[in] args: a variable number of arguments to pass to the template_creator function
 *
 * @return entity_id: The handle to the created entity within the engine. Allows the engine user to access the 
 *         entity's components
 */
int add_entity(void (template_creator)(Template*, va_list), ...);


/** @brief deletes the entity with given id
 *
 * @param[in] id: the id of the entity which should be deleted
 */
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

/** @brief Add a system to the list of usable systems.
 *
 * @details Will add the main function, init function and clean function to the
 *          ECS' internal state. Hence, the system will run when run() is called,
 *          and initi will run when init() is called, etc.
 *
 * @param[in] System: a function, which represents the system, and will get called every update
 *
 * @param[in] Init: a function which only gets called once, when init() is called. Should be
 *            used to initialize any internal state
 *
 * @param[in] Delete: a function which only gets called once, when clean() is called. Should
 *            be used to de-allocate any system state (if necessary)
 */
void register_system(void (*system)(), void (*sys_init)(), void (*sys_clean)());

/** @brief Initialises the state of the systems
 *
 * @details This primarily calls all system initialisers, but may do more in the future
 */
void init();

/** @brief Triggers the main loop
 */
void run();

/** @brief stops the main loop from running, call to end the system
 */
void stop();

/** @brief performs a memory cleanup by calling all delete functions
 *
 * @details This function should only be called once, as it will result in all
 * memory being de-alloc'd, rendering the system in an unusable state afterwards.
 * This may change in the future
 */
void clean();

///@}
#endif
