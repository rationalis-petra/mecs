#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "engine.h"
#include "engine/core/state.h"

void** resources = NULL;
unsigned int num_resource_types = 0;
unsigned int resource_type_capacity = 0;
unsigned int* num_resources = 0;
unsigned int* resources_capacity = 0;
unsigned int** generations = 0;
IntList* free_indices = 0;

void* (**resource_loaders)(char* path, char* args) = NULL;
void (**resource_destructors)(void* resource) = NULL;

int register_resource_type(char* path, void* (*resource_loader)(char* path, char* args), void (*resource_destructor)(void* resource)) {

  // allocate the memory & adjust capacity
  num_resource_types++;
  resources = realloc(resources, sizeof(void*) * num_resource_types);
  num_resources = realloc(num_resources, sizeof(int) * num_resource_types);
  resource_loaders = realloc(resource_loaders,  sizeof(void* (**)(void)) * num_resource_types);
  resource_destructors = realloc(resource_destructors, sizeof(void (**)) * num_resource_types);

  free_indices = realloc(free_indices, sizeof(IntList) * num_resource_types);
  generations = realloc(generations, sizeof(int*) * num_resource_types);


 // assign values to memory
  resource_loaders[num_resource_types] = resource_loader;
  resource_destructors[num_resource_types] = resource_destructor;


  // return, *then* increment
  return num_resource_types-1;
}


GenIndex load_resource(int type, char* path, char* args) {

}


void delete_resource(int type, GenIndex resource_id) {
#ifdef DEBUG
  if (type > num_resource_types) {
    fprintf(stderr, "attempted to delete type, id = %d, but only %d are registered", type, num_resource_types);
  }
  if (num_resources != NULL) {
    if (num_resources[type] < resource_id.index) {
      fprintf(stderr, "attempted to delete resource of type %d and index %d, but that type array only has capacity %d", type, resource_id.index, num_resources[type]);
    }
  }
#endif

  if (*generations[type] == resource_id.generation) {
    // free the resource
    generations[type]++;
    resource_destructors[type](&resources[type][resource_id.index]);

    // add a new free index to the list
    IntList* new_head = malloc(sizeof(IntList));
    new_head->element = resource_id.index;
    new_head->next = &free_indices[type];

    free_indices[type] = *new_head;
  }
#ifdef DEBUG
  else {
    fprintf(stderr, "attempted to delete resource (type = %d, index = %f), but was already deleted", type, resource_id.index);
  }
#endif
}
