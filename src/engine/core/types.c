#include <stdlib.h>

#ifndef NDEBUG
#include <stdio.h>
#endif

#include "engine.h"

void delete_template(Template* template) {
  #ifndef NDEBUG
  if (!template)
    perror( "error in delete_tempalte: attempt to delete null template\n");
  if (!template->components)
    perror( "error in delete_template: attempt to delete template with null components\n");
  #endif


  free(template->components);
  free(template);
}
