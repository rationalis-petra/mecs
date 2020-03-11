#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "engine.h"
#include "engine/core/state.h"

bool running = true;
// Assets: assets
// GenerationalIndexAllocator
// AnyMap components - the anymap can store exactly one of every type we put into it
// our anymap will store Arrays of a specific type, i.e. one array for each component
void*** entities = 0;
int entity_capacity = 0;
int entity_len = 0;

void (**systems)(void) = 0;
int systems_capacity = 0;
int systems_len = 0;

int* registered_components = 0;
int num_components = 0;

void* (**new_methods)(void) = 0;
void (**delete_methods)(void*) = 0;

int add_entity(Template* (template)(void)) {
  Template* entity = template();

  #ifdef DEBUG
  if (!entity)
    fprintf(stderr, "error in add_entity in engine: attempting to use template which returns null\n");
  if (!entity->components)
    fprintf(stderr, "error in add_entity in engine: attempring to add a template with no components\n");
  #endif
  
  if (entity_len == entity_capacity) {
    int old_capacity = entity_capacity;
    entity_capacity = (entity_capacity == 0) ? 10 : entity_capacity * 2;

    // now, we want to go through each comopnent array and re-allocate the memory
    for (int type = 0; type < num_components; type++) {
      entities[type] = realloc(entities[type], sizeof(void*) * entity_capacity);

      // zero-out the newly allocated memory
      for (int i = old_capacity; i < entity_capacity; i++) {
	entities[type][i] = 0;
      }
    }

  }

  for (int type = 0; type < entity->num_components; type++) {
    entities[type][entity_len] = entity->components[type];
  }

  delete_template(entity);
  entity_len++;

  return entity_len-1;
}

void* get_component(int entity, int type) {
  #ifdef DEBUG
  if (entity > entity_len || entity < 0) {
    fprintf(stderr, "error in get_component in engine: attempt to get non-existent entity: %d\n", entity);
  }
  #endif

  return entities[type][entity];
}

void register_component(int type, void* (*new_function)(), void (*delete_function)(void*)) {
  if (type == num_components) {

    num_components++;

    entities = realloc(entities, sizeof(void*) * num_components);
    registered_components = realloc(registered_components, sizeof(int*) * num_components);

    new_methods = (void* (**)()) realloc(new_methods, sizeof(void* (**)(void)) * num_components);
    delete_methods = (void (**)(void*)) realloc(delete_methods, sizeof(void (**)(void*)) * num_components);
    
    #ifdef DEBUG
    if (!(entities || registered_components || new_methods || delete_methods))
	fprintf(stderr, "error in register_component: memory allocation failed!");
    #endif

    registered_components[type] = type;
    new_methods[type] = new_function;
    delete_methods[type] = delete_function;
    entities[type] = malloc(sizeof(void*) * entity_capacity);
    for (int i = 0; i < entity_capacity; i++) {
      entities[type][i] = 0;
    }

    // zero out the pointers in the newly allocated entites block
  }

  else {
    fprintf(stderr, "error: failed to register component, %d\n", type);
  }
}
void delete_component(void* component, int type) {
  delete_methods[type](component);
}

void register_system(void (*system_function)()) {
  if (systems_capacity == systems_len) {
    systems_capacity += 10;
    systems = realloc(systems, sizeof(void (*)()) * systems_capacity);
  }
  systems[systems_len] = system_function;
  systems_len++;
}

void stop() {
  running = false;
}

void init() {
}

void run() {
  while(running) {
    for (int i = 0; i < systems_len; i++) {
      systems[i]();
    }
  }
}


void clean() {
  for (int type = 0; type < num_components; type++) {
    for (int i = 0; i < entity_len; i++) {
      (*delete_component)(entities[type][i], type);
    }
    free(entities[type]);
  }

  free(entities);
  free(systems);
  free(new_methods);
  free(delete_methods);
  free(registered_components);

  delete_window(0);
}
