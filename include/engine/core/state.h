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

#include <stdbool.h>
#include "query.h"
#include "types.h"
#include "engine/structures.h"

typedef struct EnityListLIst {
    struct EntityListList* tail;
    int* head;
} EntityListList;

#ifndef NDEBUG
extern bool entities_added;
#endif

extern EntityListList* query_result_list;

///@addtogroup State
///@{

#define nullptr 0
typedef unsigned int uint;

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


/// @addtogroup Registries
/// @{

extern void (**systems)(void);
extern void (**sys_inits)(void);
extern void (**sys_cleans)(void);
extern int systems_capacity;
extern int systems_len;

extern int* registered_components;
extern int num_components;

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
extern IntList** free_indices;

extern void* (**resource_loaders)(char* path);
extern void (**resource_destructors)(void* resource);

///@}
#endif
