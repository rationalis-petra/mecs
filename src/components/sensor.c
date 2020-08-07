#include <stdlib.h>

#include "components/sensor.h"

void* new_sensor(void) {
   return malloc(sizeof(Sensor));
}

void delete_sensor(void* _sensor) {
    Sensor* sensor = _sensor;
    if (sensor->info != NULL) {
       free(sensor->info);
    }

    free(sensor);
}
