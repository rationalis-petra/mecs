#include <stdlib.h>

#include "components/creature.h"

#ifndef NDEBUG
#include <stdio.h>
#endif

void* new_creature() {
  Creature* creature = (Creature*) malloc(sizeof(Creature));
  return (void*) creature;
}

void delete_creature(void* _creature) {
#ifndef NDEBUG
  if (!_creature) {
    fprintf(stderr, "error in function delete_creature in component Creature: creature is null\n");
  }
  #endif
  free(_creature);
}
