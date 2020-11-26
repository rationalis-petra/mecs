#ifndef __MODEL_H_
#define __MODEL_H_

#include <string>

#include "engine.hpp"

///@addtogroup Components
///@{


class Model : public Component {
public:
  static unsigned type_idx;
  // Resource normal map
  // Resource material_map
  Vec<3, float> position; ///< The position of the model (not necessarily the same position as used for physics)
  Vec<3, float> rotation; ///< The rotation of the model (not necessarily the same position as used for physics)
  Vec<3, float> scale;    ///< The scale of the model (not necessarily the same position as used for physics)

  Resource mesh;
  Resource texture;

  Model(World& world, std::string, std::string, Vec<3, float> position = {0.0, 0.0, 0.0}, Vec<3, float> scale = {0.0, 0.0, 0.0});
  ~Model();
};
///@}

#endif // __MODEL_H_
