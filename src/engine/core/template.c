#include <stdlib.h>

#ifdef DEBUG
#include <stdio.h>
#endif

#include "engine.h"

void delete_template(Template* template) {
  #ifdef DEBUG
  if (!template)
    fprintf(stderr, "error in delete_tempalte: attempt to delete null template\n");
  if (!template->components)
    fprintf(stderr, "error in delete_template: attempt to delete template with null components\n");
  #endif

  
  free(template->components);
  free(template);
}

