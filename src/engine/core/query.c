#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#include "engine.h"
#include "engine/core/state.h"


EntityList component_mask(int n_args, ...) {
  va_list comps;

  EntityList l;
  l.len = 0;
  l.entities = (int*) malloc(sizeof(int) * entity_len);

  for (int entity = 0; entity < entity_len; entity++) {
  va_start(comps, n_args);
  start:
    for (int i = 0; i < n_args; i++) {
      if (!get_component(entity, va_arg(comps, int))) {
	goto start;
      }
    }

    l.entities[l.len] = entity;
    l.len++;
  }

  va_end(comps);
  return l;
}

EntityList predicate_mask(bool (*predicate)(int)) {
  EntityList l;
  l.len = 0;
  l.entities = (int*) malloc(sizeof(int) * entity_len);
  for (int i = 0; i < entity_len; i++) {
    if ((*predicate)(i)) {
      l.entities[l.len] = i;
      l.len++;
    }
  }
  return l;
}

int first_match(bool (*predicate)(int)) {
  for (int i = 0; i < entity_len; i++) {
    if ((*predicate)(i)) {
      return i;
    }
  }

#ifndef NDEBUG
  fprintf(stderr, "error in function first_match: no match found\n");
#endif

  return -1;
}
