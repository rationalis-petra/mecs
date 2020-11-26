#include <string>

#include "components/model.hpp"

using std::string;

Model::Model(World& world, string _texture, string _mesh, Vec<3, float> _position, Vec<3, float> _scale) :
  position(_position),
  rotation(0.0f, 0.0f, 0.0f),
  scale(_scale),
  mesh (world.get_resource_or_construct<Mesh>(_mesh)),
  texture (world.get_resource_or_construct<Texture>(_texture)) {}

Model::~Model() {
}
