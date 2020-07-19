#ifndef __GEN_DICT_H
#define __GEN_DICT_H

#include "engine/core/types.h"

typedef struct GenDict GenDict;

GenDict* new_dict();

void delete_dict(GenDict* tree);

void dict_insert(GenDict* dictionary, char* key, GenIndex value);

int dict_get(GenDict* dictionary, char* key, GenIndex* value);

int dict_delete(GenDict* dictionary, char* key);

#endif
