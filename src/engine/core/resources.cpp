#include <unordered_map>
#include <vector>
#include <string>
#include <list>
#include <stdexcept>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "engine.hpp"
#include "engine/core/state.hpp"

using std::unordered_map;
using std::vector;
using std::string;
using std::list;

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

vector<list<unsigned>> free_indices;
vector<unordered_map<string, GenIndex>> resource_names;

vector<void* (*)(const char*)> resource_loaders = vector<void* (*)(const char* path)>(0);
vector<void (*)(void*)> resource_destructors = vector<void (*)(void*)>(0);

int register_resource_type(void* (*resource_loader)(const char* path), void (*resource_destructor)(void* resource)) {

  // allocate the memory & adjust capacity
  unsigned int index = num_resource_types;
  num_resource_types++;
  resource_capacities = (unsigned int*) realloc(resource_capacities, sizeof(int) * num_resource_types);

  resources = (Resource**) realloc(resources, sizeof(Resource*) * num_resource_types);
  generations = (unsigned int**) realloc(generations, sizeof(int*) * num_resource_types);

  // now populate the newly allocated memoryinfo
  resource_capacities[index] = 0;
  resources[index] = NULL;
  generations[index] = NULL;

  free_indices.push_back(list<unsigned>());
  resource_names.push_back(unordered_map<string, GenIndex>());

  resource_loaders.push_back(resource_loader);
  resource_destructors.push_back(resource_destructor);

  // return the index of this type
  return index;
}


GenIndex get_resource_id(int type, string path) {
#ifndef NDEBUG
  if (type >= num_resource_types) {
    fprintf(stderr, "error, attempted to get type of type %d, but there are only %d types registered. Undefined behaviour", type, num_resource_types);
  }
#endif

  GenIndex index;
  // if failed
  try {
    index = resource_names[type].at(path);
  }
  catch (std::out_of_range& e) {
    // the resource does not exist -
    int free;
    if (!free_indices[type].empty()) {
      free = free_indices[type].front();
      free_indices[type].pop_front();
      // there are no free slots - double the size of the resource array
      int old_cap = resource_capacities[type];
      resource_capacities[type] = old_cap == 0 ? 10 : old_cap * 2;
      resources[type] = (Resource*) realloc(resources[type], sizeof(Resource) * resource_capacities[type]);
      generations[type] = (unsigned int*) realloc(generations[type], sizeof(int) * resource_capacities[type]);

      memset(generations[type] + old_cap, 0, sizeof(int) * resource_capacities[type]);
      for (unsigned  i = old_cap + 1; i < resource_capacities[type]; i++) {
        free_indices[type].push_front(i);
      }
      free = old_cap;
    }
    generations[type][free]++;

    index.generation = generations[type][free];
    index.index = free;

    resources[type][free].resource = resource_loaders[type](path.c_str());
    resources[type][free].path = (char*) malloc(strlen(path.c_str()) + 1);
    strcpy(resources[type][free].path, path.c_str());


    // insert resource into
    resource_names[type][path] = index;
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
