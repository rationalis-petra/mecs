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
  const char* path;
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
vector<vector<Resource>> resources = vector<vector<Resource>>(0);              // the actual 2d array containing resources
vector<vector<unsigned>> generations = vector<vector<unsigned>>(0);

vector<list<unsigned>> free_indices;
vector<unordered_map<string, GenIndex>> resource_names;

vector<void* (*)(const char*)> resource_loaders = vector<void* (*)(const char* path)>(0);
vector<void (*)(void*)> resource_destructors = vector<void (*)(void*)>(0);

int register_resource_type(void* (*resource_loader)(const char* path), void (*resource_destructor)(void* resource)) {

  // now populate the newly allocated memoryinfo
  resources.push_back(vector<Resource>(0));
  generations.push_back(vector<unsigned>(0));

  free_indices.push_back(list<unsigned>());
  resource_names.push_back(unordered_map<string, GenIndex>());

  resource_loaders.push_back(resource_loader);
  resource_destructors.push_back(resource_destructor);

  // return the index of this type
  return resources.size() - 1;
}


GenIndex get_resource_id(int type, string path) {
#ifndef NDEBUG
  if (type >= resources.size()) {
    fprintf(stderr, "error, attempted to get type of type %d, but there are only %d types registered. Undefined behaviour", type, (int) resources.size());
  }
#endif

  GenIndex index;
  // if failed
  try {
    index = resource_names.at(type).at(path);
  }
  catch (std::out_of_range& e) {
    // the resource does not exist - so we try and load it 
    Resource resource;
    resource.resource = resource_loaders[type](path.c_str());
    resource.path = path.c_str();


    // now, we need to figure otu where to store it...
    // case 1: there are free slots in the array
    if (!free_indices[type].empty()) {
      unsigned free = free_indices[type].front();
      free_indices[type].pop_front();

      index.index = free;
      generations[type][index.index]++;
      index.generation = generations.at(type).at(free);

      resources[type][free] = resource;

      // case 2: the vector is full, so we push_back
    } else {
      // there are no free slots, so we are inserting 
      index.index = resources[type].size();
      index.generation = 0;
      generations[type].push_back(0);

      resources[type].push_back(resource);
    }

    resource_names[type][path] = index;
  }
  return index;
}

void load_resource(int type, char* path) {
  get_resource_id(type, path);
}

void* get_resource(int type, GenIndex resource_id) {
#ifndef NDEBUG
  if (type >= resources.size()) {
    fprintf(stderr, "error, attempted to get type %d, but there are only %d types registered. Undefined behaviour", type, (int) resources.size());
  }
  if (resource_id.index >= resources[type].size()) {
    fprintf(stderr, "error, attempted to get index %d, byt the array has size %d. Undefined behaviour",
            resource_id.index,
            (int) resources[type].size());
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
