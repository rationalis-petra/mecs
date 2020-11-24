#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#include "engine.h"
#include "engine/core/state.h"

using std::list;

// list<Entity> component_mask(int n_args, ...) {
//   va_list comps;
//   va_start(comps, n_args);
//   int* types = malloc(sizeof(int) * n_args);
//   for (int i = 0; i < n_args; i++) {
//     types[i] = va_arg(comps, int);
//   }
//   va_end(comps);

//   EntityList l;
//   l.len = 0;
//   l.entities = (int*) malloc(sizeof(int) * entity_len);

//   for (int entity = 0; entity < entity_len; entity++) {
//     for (int i = 0; i < n_args; i++) {
//       if (!get_component(entity, types[i])) {
// 	goto skip;
//       }
//     }
//     l.entities[l.len] = entity;
//     l.len++;
//   skip: continue;
//   }

//   free(types);

//   EntityListList* intermediate = query_result_list;
//   query_result_list = malloc(sizeof(EntityListList));

//   query_result_list->head = l.entities;
//   query_result_list->tail = intermediate;

//   return l;
// }

