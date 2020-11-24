#ifndef __STATE_H
#define __STATE_H

/**@file
 * @brief A file containing the variables for the state of the engine
 *
 * @details Contains all generic data structures and information about them in a singe
 *          to avoid the cost of having dedicated structures. As such, this header file
 *          should only be included in engine-specific .c files, as the game should not
 *          attempt to access these structures directly for safety reasons.
 */

#include <vector>
#include "types.hpp"


#ifndef NDEBUG
extern bool entities_added;
#endif


///@addtogroup State
///@{

#define nullptr 0
typedef unsigned int uint;

extern bool running;

// Variables describing the entity storage system. Simple variable-length 2D array of
// pointers to components

/// @addtogroup Registries
/// @{

extern unsigned int* registered_shaders;
extern unsigned int num_shaders;

extern unsigned int* registered_models;
extern unsigned int num_models;

///@}


typedef struct Resource Resource;
extern Resource** resources;
extern unsigned int num_resource_types;
extern unsigned int* num_resources;
extern unsigned int* resources_capacity;
extern unsigned int** generations;

extern std::vector<void* (*)(const char*)> resource_loaders;
extern std::vector<void (*)(void*)> resource_destructors;

///@}
#endif
