#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "engine.h"
#include "engine/core/state.h"

bool running = false;
// Assets: assets
// GenerationalIndexAllocator
// AnyMap components - the anymap can store exactly one of every type we put into it
// our anymap will store Arrays of a specific type, i.e. one array for each component
void*** entities = 0;
int entity_capacity = 0;
int entity_len = 0;

void (**systems)(void) = nullptr;
void (**sys_inits)(void) = nullptr;
void (**sys_cleans)(void) = nullptr;
int systems_capacity = 0;
int systems_len = 0;

int* registered_components = 0;
int num_components = 0;

void* (**new_methods)(void) = 0;
void (**delete_methods)(void*) = 0;

#ifdef DEBUG
bool entities_added = false;
#endif

void delete_component(void* component, int type) {
  delete_methods[type](component);
}

int add_entity(void (entity_creator)(Template*)) {
  // create a new template, null all pointers, then pass it to the template function so the
  // entity may be constructed
  Template* template = malloc(sizeof(Template));
  template->components = (void**) malloc(sizeof(void*) * num_components);
  for (int i = 0; i < num_components; i++) {
    template->components[i] = NULL;
  }
  entity_creator(template);

  if (entity_len == entity_capacity) {
    int old_capacity = entity_capacity;
    entity_capacity = (entity_capacity == 0) ? 10 : entity_capacity * 2;

    // now, we want to go through each comopnent array and re-allocate the memory
    for (int type = 0; type < num_components; type++) {
      entities[type] = realloc(entities[type], sizeof(void*) * entity_capacity);

      // zero-out the newly allocated memory
      for (int i = old_capacity; i < entity_capacity; i++) {
        entities[type][i] = NULL;
      }
    }
  }

  for (int type = 0; type < num_components; type++) {
    entities[type][entity_len] = template->components[type];
  }

  delete_template(template);
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
#ifdef DEBUG
  if (entities_added) {
    fprintf(stderr, "error: registering a component when entities have already been added will result in undefined behaviour!\n");
  }
#endif
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
    fprintf(stderr, "error: failed to register component, %d, as there are %d registered components\n", type);
  }
}

void register_system(void (*system_function)(), void (*sys_init)(), void (*sys_clean)()) {
  if (systems_capacity == systems_len) {
    systems_capacity += 10;
    systems = realloc(systems, sizeof(void (*)()) * systems_capacity);
    sys_inits = realloc(sys_inits, sizeof(void(*)()) * systems_capacity);
    sys_cleans = realloc(sys_cleans, sizeof(void(*)()) * systems_capacity);
  }

  systems[systems_len] = system_function;
  sys_inits[systems_len] = sys_init;
  sys_cleans[systems_len] = sys_clean;

  if (running) {
    sys_init();
  }
  systems_len++;
}

void stop() {
  running = false;
}

void init() {
  for (int i = 0; i < systems_len; i++){
    sys_inits[i]();
  }
}

void run() {
  running = true;
  while(running) {
    for (int i = 0; i < systems_len; i++) {
      systems[i]();
    }
  }
}


void clean() {
  // clean all components from grid
  for (int type = 0; type < num_components; type++) {
    for (int i = 0; i < entity_len; i++) {
      if (!entities[type][i]) {
        (*delete_component)(entities[type][i], type);
      }
    }
    free(entities[type]);
  }

  // entities
  free(entities);
  // systems
  free(systems);
  for (int i = 0; i < systems_len; i++) {
    sys_cleans[i]();
  }
  // components
  free(new_methods);
  free(delete_methods);
  free(registered_components);

  // graphics
  //free_shaders();
  //free_models();

  delete_window(0);
}
