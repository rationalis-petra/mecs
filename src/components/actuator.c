#include <stdlib.h>

#include "components/actuator.h"

void* new_actuator(void) {
    return malloc(sizeof(Actuator));
}

void delete_actuator(void* actuator) {
   free(actuator);
}
