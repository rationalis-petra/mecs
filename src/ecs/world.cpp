#include <functional>
#include <iostream>
#include <vector>
#include <optional>

#include <GLFW/glfw3.h>

#include "engine.hpp"

// Assets: assets
// GenerationalIndexAllocator
// AnyMap components - the anymap can store exactly one of every type we put into it
// our anymap will store Arrays of a specific type, i.e. one array for each component
using std::vector;
using std::optional;
using std::reference_wrapper;

World::World() {
  entities = vector<vector<optional<Component*>>>(0);
  free_indices = vector<unsigned>(0);
  entity_len = 0;


  systems = vector<System*>(0);
  running = false;
}

World::~World() {}

/*
 * ENTITY/COMPONENT CODe
 */

Entity World::create_entity() {
  // entity may be constructed
  unsigned id;
  if (free_indices.empty()) {
    id = entity_len++;

    // initialise to null
    for (vector<optional<Component*>>& component_vec : entities) {
      component_vec.push_back(std::nullopt);
    }
  }
  else {
    id = free_indices[free_indices.size() - 1];
    free_indices.pop_back();
  }

  return Entity(*this, id);
}


/*
 * SYSTEM CODE
 */
void World::register_system(System* s) {
  systems.push_back(s);

  if (running) {
    s->init();
  }
}

void World::stop() {
  running = false;
}

void World::run() {
  running = true;

  update_args.dt = 0.0;
  while (running) {
    glfwSetTime(0.0);
    for (System* s : systems) {
      s->run(*this, update_args);
    }

    update_args.dt = glfwGetTime();
  }
}

void World::init(void) {
  for (System* s: systems) {
    s->init();
  }
}

void World::clean() {
  // systems
  for (System* s : systems) {
    s->clean();
  }

  // graphics
  //free_shaders();

  delete_window(0);
}


/*
 * Querying functionality
 */

vector<Entity> World::predicate_mask(bool (*predicate)(Entity)) {
  vector<Entity> entity_vec;

  for (unsigned i = 0; i < entity_len; i++) {
    Entity e = Entity(*this, i);
    if ((*predicate)(e)) {
      entity_vec.push_back(e);
    }
  }

  return entity_vec;
}

optional<Entity> World::first_match(bool (*predicate)(Entity)) {
  for (unsigned i = 0; i < entity_len; i++) {
    Entity e = Entity(*this, i);
    if ((*predicate)(e)) {
      return e;
    }
  }
  return std::nullopt;
}
