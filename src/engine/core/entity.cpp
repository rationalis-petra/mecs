#include <iostream>
#include <optional>

#include "engine.hpp"


using std::optional;

Entity::Entity(World& _world, unsigned _idx) : world(_world), idx(_idx) {
}

// TODO: throw ComponentAlreadyExists Exeption
