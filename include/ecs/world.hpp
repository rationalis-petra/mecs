#ifndef __WORLD_HPP
#define __WORLD_HPP

#include <typeinfo>
#include <optional>
#include <vector>
#include <variant>
#include <unordered_map>
#include <string>


#include "system.hpp"

class Entity;
class Component;
class Resource {
  friend class World;

private:
  World& world;
  // todo: change to GenerationalIndex
  unsigned int idx;

  //Resource(World& world);
  Resource(World& _world, unsigned _idx);

public:
  template <typename T> T* value();
  template <typename T> void remove();
};

class World {
  friend class Entity;
  friend class Resource;

private:
  std::unordered_map<std::string, unsigned int> types;
  std::vector<std::vector<std::optional<Component*>>> entities;
  std::vector<unsigned> free_indices;

  unsigned int entity_len;

  std::vector<System*> systems;

  bool running;
  UpdateArgs update_args;

  std::vector<std::vector<void*>> resources;
  std::vector<std::unordered_map<std::string, Resource>> resource_indices;

public:
  World();
  ~World();

  // entity/component Functions
  Entity create_entity();

  // Add some subclass of component to the ECS at runtime
  template <typename T> void register_component() {
    // the index of this type is simply the size of the entity vector
    unsigned type_idx = entities.size();
    types.insert({typeid(T).name(), type_idx});

    // add a new component vector to the ECS
    entities.push_back(std::vector<std::optional<Component*>>(entity_len));

    // make sure to null-out all new components
    for (unsigned i = 0; i < entity_len; i++) {
      entities[type_idx][i] = std::nullopt;
    }
  }

  // System Functions
  void register_system(System* s);
  void stop();
  void init();
  void run();
  void clean();

  // Util Functions
  std::vector<Entity> predicate_mask(bool (*predicate)(Entity));
  std::optional<Entity> first_match(bool (*predicate)(Entity));

  // Resource Functions

  template <typename T> void register_resource_type() {
    resources.push_back(std::vector<void*>(0));
    resource_indices.push_back(std::unordered_map<std::string, Resource>());
  }
  template <typename T> std::variant<Resource, Resource (*)(T*)> get_resource(std::string name) {

    Resource r = Resource(*this, 0);
    if (resource_indices[T::type_id].find(name) != resource_indices[T::type_id].end()) {
      r.idx = resource_indices[T::type_id].at(name).idx;
      return r;
    } else {
      r.idx = resources[T::type_id].size();
      resource_indices[T::type_id].insert({name, r});
      resources[T::type_id].push_back(nullptr);
      // return lambda
      return [&](T* val) -> Resource {
        resources[T::type_id][r.idx] = (void*) val;
        return r;
      };
    }
  }

  template <typename T> Resource get_resource_or_construct(std::string name_path) {
    Resource r = Resource(*this, 0);
    if (resource_indices[T::type_id].find(name_path) != resource_indices[T::type_id].end()) {
      r.idx = resource_indices[T::type_id].at(name_path).idx;
    } else {
      r.idx = resources[T::type_id].size();
      resource_indices[T::type_id].insert({name_path, r});
      resources[T::type_id].push_back(new T(name_path));
    }
    return r;
  }
};

#endif
