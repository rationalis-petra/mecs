#ifndef STATE_H
#define STATE_H

/**@file
 * @brief A file containing the variables for the state of the engine 
 * 
 * @details Contains all generic data structures and information about them in a singe
 *          to avoid the cost of having dedicated structures. As such, this header file 
 *          should only be included in engine-specific .c files, as the game should not
 *          attempt to access these structures directly for safety reasons. 
 */
///@addtogroup State
///@{

#include <stdbool.h>

#define nullptr 0

extern bool running;

// Variables describing the entity storage system. Simple variable-length 2D array of
// pointers to components
extern void*** entities;
extern int entity_capacity;
extern int entity_len;
extern int num_types;

// the methods for deleting and creating components
extern void* (**new_methods)(void);
extern void (**delete_methods)(void*);

// Registries
extern void (**systems)(void);
extern int systems_capacity;
extern int systems_len;

extern int* registered_components;
extern int num_components;

///@}
#endif
