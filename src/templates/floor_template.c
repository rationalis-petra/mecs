#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "engine.h"

#include "components/components.h"
#include "components/info.h"


void floor_template(Template* floor, va_list inpos) {
    floor->components[ModelType] = new_model();

    Model* model = floor->components[ModelType];
    model->position.x = 0.0f;
    model->position.y = -1.0f;
    model->position.z = 0.0f;

    model->scale.x = 100.0f;
    model->scale.y = 1.0f;
    model->scale.z = 100.0f;

    model->texture = get_resource_id(TextureType, "floor-tile.jpg");
    model->mesh = get_resource_id(MeshType, "floor");
}
