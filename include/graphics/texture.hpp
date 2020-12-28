#ifndef __TEXTURE_HPP
#define __TEXTURE_HPP

#include <string>

class Texture {
public:
  static unsigned int type_id;
  unsigned int texture;

  Texture(std::string path);
  ~Texture();
};

#endif
