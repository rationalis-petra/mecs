#ifndef __MODEL_H_
#define __MODEL_H_


///@addtogroup Components
///@{

#include "engine.h"

typedef struct {
    ResourceID mesh;
    ResourceID texture;
    // Resource normal map
    // Resource material_map
    Vec3f position; ///< The position of the model (not necessarily the same position as used for physics)
    Vec3f rotation; ///< The rotation of the model (not necessarily the same position as used for physics)
    Vec3f scale;    ///< The scale of the model (not necessarily the same position as used for physics)
} Model;


void* new_model(void);

void delete_model(void* model);
///@}

#endif // __MODEL_H_
