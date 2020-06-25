#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#include "engine.h"
#include "engine/core/state.h"

EntityListList* query_result_list = NULL;

EntityList component_mask(int n_args, ...) {
  va_list comps;
  va_start(comps, n_args);
  int* types = malloc(sizeof(int) * n_args);
  for (int i = 0; i < n_args; i++) {
    types[i] = va_arg(comps, int);
  }
  va_end(comps);

  EntityList l;
  l.len = 0;
  l.entities = (int*) malloc(sizeof(int) * entity_len);

  for (int entity = 0; entity < entity_len; entity++) {
    for (int i = 0; i < n_args; i++) {
      if (!get_component(entity, types[i])) {
	goto skip;
      }
    }
    l.entities[l.len] = entity;
    l.len++;
  skip: continue;
  }

  free(types);

  EntityListList* intermediate = query_result_list;
  query_result_list = malloc(sizeof(EntityListList));

  query_result_list->head = l.entities;
  query_result_list->tail = intermediate;

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

  EntityListList* intermediate = query_result_list;
  query_result_list = malloc(sizeof(EntityListList));

  query_result_list->head = l.entities;
  query_result_list->tail = intermediate;

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
