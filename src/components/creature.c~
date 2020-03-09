#include <stdlib.h>

#include "components/creature.h"

void* new_creature() {
  Creature* creature = (Creature*) malloc(sizeof(Creature));
  return (void*) creature;
}

void delete_creature(void* _creature) {
  Creature* creature = (Creature*) _creature;
  free(creature);
}
