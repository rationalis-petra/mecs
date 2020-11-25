#ifndef __WORLD_HPP
#define __WORLD_HPP

#include <optional>
#include <vector>

#include "types.hpp"
#include "system.hpp"

class Component;
//class System;
class Entity;

class World {
  friend class Entity;
private:
  std::vector<std::vector<std::optional<Component*>>> entities;
  std::vector<unsigned> free_indices;

  unsigned int entity_len;

  std::vector<System*> systems;

  bool running;
  UpdateArgs update_args;

#ifndef NDEBUG
  bool entities_added;
#endif

public:
  World();
  ~World();

  Entity create_entity();
  template <typename T>
  void register_component() {
    // subclass of Component
    T::type_idx = entities.size();

    entities.push_back(std::vector<std::optional<Component*>>(entity_len));

    for (unsigned i = 0; i < entity_len; i++) {
      entities[T::type_idx][i] = std::nullopt;
    }
  }



  void register_system(System* s);
  void stop();
  void init();
  void run();
  void clean();

  std::vector<Entity> predicate_mask(bool (*predicate)(Entity));
  std::optional<Entity> first_match(bool (*predicate)(Entity));
};

#endif
