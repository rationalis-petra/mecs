#include <stdlib.h>

#include "components/model.h"

void* new_model() {
    return malloc(sizeof(Model));
}

void delete_model(void* model) {
    free(model);
}
