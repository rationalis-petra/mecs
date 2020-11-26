#include <string>

#include "components/model.hpp"

using std::string;

Model::Model(World& world, string _texture, string _mesh, Vec3f _position, Vec3f _scale) :
  position(_position),
  scale(_scale),
  texture (world.get_resource_or_construct<Texture>(_texture)),
  mesh (world.get_resource_or_construct<Mesh>(_mesh)) {
}

Model::~Model() {
}
