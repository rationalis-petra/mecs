#ifndef __RESOURCE_TYPES_H_
#define __RESOURCE_TYPES_H_
// texutre

#include <string>

class Texture {
public:
  static unsigned int type_id;
  unsigned int texture;

  Texture(std::string path);
  ~Texture();
};

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
