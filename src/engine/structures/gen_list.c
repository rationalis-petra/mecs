#include <stdlib.h>

typedef struct GenListElement {
    struct GenListElement* next;
    void* value;
} GenListElement;

typedef struct GenList {
    GenListElement* head;
} GenList;

GenList* new_genlist(void) {
    return calloc(sizeof(GenList), 1);
}

void delete_genlist(GenList* list) {
    GenListElement* element = list->head;

    while (element != NULL) {
        free(element->value);
        GenListElement* next = element->next;

        free(element);
        element = next;
    }
}

void genlist_push(GenList* list, void* val) {
    GenListElement* new_head = malloc(sizeof(GenListElement));
    new_head->next = list->head;
    new_head->value = val;

    list->head = new_head;
}

int genlist_pop(GenList* list, void** val) {
    if (list->head == NULL) {
        *val = NULL;
        return 1;
    }
    else {
       *val = list->head->value;
       return 0;
    }
}

//int genlist_insert(GenList* list, void* val, int index) {}
