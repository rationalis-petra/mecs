#ifndef __BASE_HPP
#define __BASE_HPP

/** @file
 *
 * @brief Core engine functionality - may get moved to other files over time and become an aggregating include
 */

///@addtogroup Base
///@{

#include <stdarg.h>

#include "engine/core/types.hpp"


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
int add_entity(void (template_creator)(*, va_list), ...);


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
template <typename T> T get_component(int id, int type);

/** @brief Returns a boolean indicating whether the component exists or is NULL
 */
template <typename T> bool has_component(int id, int type);

/** @brief Adds a component as a valid type to the component system.
 *
 * @details Takes 
 *
 * @param[in] new_function: a function which will create a component of type type.
 *
 * @param[in] delete_function: a function which should free all data in a component
 *
 * @return Type: a integer which can be used to access that type
 */
int register_component(void* (*new_function)(void), void (*delete_function)(void*));

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
void register_system(void (*system)(void), void (*sys_init)(void), void (*sys_clean)(void));

/** @brief Initialises the state of the systems
 *
 * @details This primarily calls all system initialisers, but may do more in the future
 */
void init(void);

/** @brief Triggers the main loop
 */
void run(void);

/** @brief Returns an instance of the UpdateArgs struct
 */
UpdateArgs get_update_args(void);

/** @brief stops the main loop from running, call to end the system
 */
void stop(void);

/** @brief performs a memory cleanup by calling all delete functions
 *
 * @details This function should only be called once, as it will result in all
 * memory being de-alloc'd, rendering the system in an unusable state afterwards.
 * This may change in the future
 */
void clean(void);

///@}
#endif