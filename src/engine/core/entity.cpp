#include <iostream>
#include <optional>

#include "engine.hpp"


using std::optional;

Entity::Entity(World& _world, unsigned _idx) : world(_world), idx(_idx) {
}

// TODO: throw ComponentAlreadyExists Exeption
template<typename T>
Entity& Entity::add_component(T* c) {
#ifndef NDEBUG
  if (world.entities[T::type_idx][idx] != std::nullopt) {
    std::cerr << "Error in fn Enitty::add_component: component already exists" << std::endl;
  }
#endif

  world.entities[T::type_idx][idx] = optional{c};

  return *this;
}

template<typename T>
std::optional<T*> Entity::get_component() {
  return dynamic_cast<std::optional<T*>>(world.entities[T::type_idx][idx]);
}

template<typename T>
void Entity::delete_component() {
  delete world.entities[T::type_idx][idx];
}

template<typename T>
bool Entity::has_component() {
  return world.entities[T::type_idx][idx].has_value();
}
