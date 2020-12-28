#ifndef __MESH_HPP
#define __MESH_HPP

#include <string>

class Mesh {
public:
  static unsigned int type_id;

  unsigned int VAO;
  unsigned int VBO;
  unsigned int num_triangles;

  Mesh(std::string path);
  ~Mesh();
};


#endif
