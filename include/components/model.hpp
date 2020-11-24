#ifndef __MODEL_H_
#define __MODEL_H_

#include <string>

#include "engine.hpp"

///@addtogroup Components
///@{


class Model : public Component {
public:
  static unsigned type_idx;
  ResourceID mesh;
  ResourceID texture;
  // Resource normal map
  // Resource material_map
  Vec3f position; ///< The position of the model (not necessarily the same position as used for physics)
  Vec3f rotation; ///< The rotation of the model (not necessarily the same position as used for physics)
  Vec3f scale;    ///< The scale of the model (not necessarily the same position as used for physics)

  Model();
  Model(std::string, std::string, Vec3f position = {0.0, 0.0, 0.0}, Vec3f scale = {0.0, 0.0, 0.0});
  ~Model();
};
///@}

#endif // __MODEL_H_
