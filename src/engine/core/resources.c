#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "engine.h"
#include "engine/core/state.h"


struct Resource {
  char* path;
  void* resource;
};

/* Resources are stored in a 2d array. The first 'dimension' can be thought of
 * as column headers, where each column stores resources of a particular type.
 * Hence, the get_resource function takes both type and ID.
 *
 * Each index i of an array has an associated 'generation'. Only identifiers
 * with the correct generation may access, and generations are incremented
 * each time a resource is deleted
 */
Resource** resources = NULL;              // the actual 2d array containing resources
unsigned int** generations = NULL;        // for use in generational indexing (above)
unsigned int num_resource_types = 0;      // stores the number of columns
unsigned int* resource_capacities = NULL; // Stores the sizes of each column

IntList** free_indices = NULL;            // An array of Integer Lists, where each list in the array stores free indices in a stack-like fashion
GenDict** resource_names = NULL;          // An array of Dictionaries whose keys are strings and values Generational Indices

void* (**resource_loaders)(char* path) = NULL;
void (**resource_destructors)(void* resource) = NULL;

int register_resource_type(void* (*resource_loader)(char* path), void (*resource_destructor)(void* resource)) {

  // allocate the memory & adjust capacity
  unsigned int index = num_resource_types;
  num_resource_types++;
  resource_capacities = realloc(resource_capacities, sizeof(int) * num_resource_types);

  resources = realloc(resources, sizeof(Resource*) * num_resource_types);
  generations = realloc(generations, sizeof(int*) * num_resource_types);

  free_indices = realloc(free_indices, sizeof(IntList*) * num_resource_types);
  resource_names = realloc(resource_names, sizeof(GenDict*) * num_resource_types);

  resource_loaders = realloc(resource_loaders, sizeof(void* (**)(char*)) * num_resource_types);
  resource_destructors = realloc(resource_destructors, sizeof(void (**)(void*)) * num_resource_types);

  // now populate the newly allocated memoryinfo
  resource_capacities[index] = 0;
  resources[index] = NULL;
  generations[index] = NULL;
  free_indices[index] = new_intlist();
  resource_names[index] = new_dict();
  resource_loaders[index] = resource_loader;
  resource_destructors[index] = resource_destructor;

  // return the index of this type
  return index;
}


GenIndex get_resource_id(int type, char* path) {
#ifndef NDEBUG
  if (type >= num_resource_types) {
    fprintf(stderr, "error, attempted to get type of type %d, but there are only %d types registered. Undefined behaviour", type, num_resource_types);
  }
#endif

  GenIndex index;
  if (dict_get(resource_names[type], path, &index)) {
    // the resource does not exist -
    int free;
    if (intlist_pop(free_indices[type], &free)) {
      // there are no free slots - double the size of the resource array
      int old_cap = resource_capacities[type];
      resource_capacities[type] = old_cap == 0 ? 10 : old_cap * 2;
      resources[type] = realloc(resources[type], sizeof(Resource) * resource_capacities[type]);
      generations[type] = realloc(generations[type], sizeof(int) * resource_capacities[type]);

      memset(generations[type] + old_cap, 0, sizeof(int) * resource_capacities[type]);
      for (int i = old_cap + 1; i < resource_capacities[type]; i++) {
        intlist_push(free_indices[type], i);
      }
      free = old_cap;
    }
    generations[type][free]++;

    index.generation = generations[type][free];
    index.index = free;

    resources[type][free].resource = resource_loaders[type](path);
    resources[type][free].path = malloc(strlen(path) + 1);
    strcpy(resources[type][free].path, path);


    // insert resource into
    dict_insert(resource_names[type], path, index);
  }
  return index;
}

void load_resource(int type, char* path) {
  get_resource_id(type, path);
}

void* get_resource(int type, GenIndex resource_id) {
#ifndef NDEBUG
  if (type >= num_resource_types) {
    fprintf(stderr, "error, attempted to get type %d, but there are only %d types registered. Undefined behaviour", type, num_resource_types);
  }
  if (resource_id.index >= resource_capacities[type]) {
    fprintf(stderr, "error, attempted to get index %d, byt the array has size %d. Undefined behaviour", resource_id.index, resource_capacities[type]);
  }
#endif

  if (generations[type][resource_id.index] != resource_id.generation) {
    fprintf(stderr, "error, attempted to get GenIndex generation %d, but the actual generation is %d", resource_id.generation, generations[type][resource_id.index]);
    return NULL;
  }
  else {
    return resources[type][resource_id.index].resource;
  }
}

void delete_resource(int type, GenIndex resource_id) {

}

void delete_resource_named(int type, char* path) {

}
