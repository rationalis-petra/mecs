#include <iostream>
#include <optional>

#include "engine.hpp"


using std::optional;

Entity::Entity(World& _world, unsigned _idx) : idx(_idx), world(_world) {}

// TODO: throw ComponentAlreadyExists Exeption
