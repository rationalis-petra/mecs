#include <string>

#include "components/model.hpp"

using std::string;

Model::Model() {
}

Model::Model(string _texture, string _mesh, Vec3f _position, Vec3f _scale) : position(_position), scale(_scale) {
  texture = get_resource_id(TextureType, _texture.c_str());
  mesh = get_resource_id(MeshType, _mesh.c_str());
}

Model::~Model() {
}
