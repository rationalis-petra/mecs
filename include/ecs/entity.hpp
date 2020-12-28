#ifndef __ENTITY_HPP
#define __ENTITY_HPP

#include <typeinfo>
#include <optional>
#include <iostream>

#include "world.hpp"

class World;

class Entity {
  friend class World;

private:
  unsigned idx;
  World& world;

  Entity(World& world, unsigned int id);

public:
  template<typename T>
  Entity& add_component(T* component) {
    std::string type = typeid(T).name();
    component->type_idx = world.types[type];


#ifndef NDEBUG
    if (world.entities[component->type_idx][idx]) {
      std::cerr << "Error in fn Enitty::add_component: component already exists" << std::endl;
    }
#endif

    world.entities[component->type_idx][idx] = std::make_optional<Component*>(component);

    return *this;
  }

  template<typename T> std::optional<T*> get_component() {
    unsigned type_idx = world.types[typeid(T).name()];
    std::optional<Component*> temp = world.entities[type_idx][idx];
    if (temp) {
      return dynamic_cast<T*>(temp.value());
    }
    else {
      return std::nullopt;
    }
  }

  template<typename T>
  void delete_component() {
    delete world.entities[world.types[typeid(T).name()]][idx];
  }

  template<typename T>
  bool has_component() {
    return world.entities[world.types[typeid(T).name()]][idx].has_value();
  }

};


#endif
