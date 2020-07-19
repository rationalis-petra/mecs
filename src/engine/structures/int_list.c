#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "engine/structures.h"

typedef struct IntListElement {
    int val;
    struct IntListElement* next;
} IntListElement;

struct IntList {
    IntListElement* head;
};

IntList* new_intlist() {
    IntList* int_list = malloc(sizeof(IntList));
    int_list->head = NULL;
    return int_list;
}

void delete_intlist(IntList* list) {
    IntListElement* current = list->head;
    IntListElement* next;

    while(current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

void intlist_push(IntList* list, int val) {
    IntListElement* new_head = malloc(sizeof(IntListElement));
    new_head->val = val;
    new_head->next = list->head;
    list->head = new_head;
}

int intlist_pop(IntList* list, int* val) {
    if (list->head == NULL) {
        *val = 0;
        return -1;
    }

    *val = list->head->val;
    IntListElement* new_head = list->head->next;
    free(list->head);
    list->head = new_head;
    return 0;
}

int intlist_head(IntList* list, int* val) {
    if (list->head == NULL) {
        val = NULL;
        return -1;
    }
    else {
        *val = list->head->val;
        return 0;
    }
}

int intlist_tail(IntList* list, IntList* tail) {
    if (list->head == NULL) {
        tail = NULL;
        return -1;
    }
    else {
        tail = malloc(sizeof(IntList));
        tail->head = list->head->next;
        return 0;
    }
}

int intlist_insert(IntList* list, int val, int index) {
    if (val < 0) return -1;

    // same as push
    if (val == 0) {
        IntListElement* new_head = malloc(sizeof(IntListElement));
        new_head->next = list->head;
        new_head->val = val;
        list->head = new_head;
    }

    IntListElement* current = list->head;
    index--;
    while (index != 0) {
        if (current == NULL) {
            return -2;
        }

        current = current->next;
        index--;
    };


#ifndef NDEBUG
    assert(val == 0);
#endif

    // now, "current" is at index-1 in position, so insert here
    IntListElement* new_element = malloc(sizeof(IntListElement));
    new_element->val = val;
    new_element->next = current->next;
    current->next = new_element;

    return 0;
}

void intlist_ordered_insert(IntList* list, int val) {
    IntListElement* current = list->head;
    IntListElement* previous;


    if (current != NULL) {
        if (current->val > val) {
            goto add_head;
        }
    }
    else {
    add_head: {
            IntListElement* new_head = malloc(sizeof(IntListElement));
            new_head->val = val;
            new_head->next = current;
            list->head = new_head;
            return;
        }
    }

    while (current->val < val) {
        previous = current;
        current = current->next;

        if (current == NULL)
            break;
    }

    IntListElement* new_element = malloc(sizeof(IntListElement));
    new_element->val = val;
    new_element->next = current;
    previous->next = new_element;
}
