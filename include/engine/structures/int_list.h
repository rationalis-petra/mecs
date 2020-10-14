#ifndef __INT_LIST_H
#define __INT_LIST_H

typedef struct IntList IntList;

IntList* new_intlist();

void delete_intlist(IntList* list);

void intlist_push(IntList* list, int val);

int intlist_pop(IntList* list, int* val);

int intlist_head(IntList* list, int* val);

int intlist_tail(IntList* list, IntList* tail);

int intlist_insert(IntList* list, int val, int index);

void intlist_ordered_insert(IntList* list, int val);

#endif
