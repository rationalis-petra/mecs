#include <stdlib.h>
#include "engine/structures.h"


typedef enum {Red, Black} Colour;

typedef struct Node {
    char* key;
    struct Node* left;
    struct Node* right;

    Colour colour;
    GenIndex value;
} Node;

typedef struct GenDict {
    Node* root;
} dict;

GenDict* new_dict() {
    GenDict* dict = malloc(sizeof(GenDict));
    dict->root = NULL;
    return dict;
}

void recursive_delete(Node* node) {
    if (node == NULL) return;
    recursive_delete(node->left);
    recursive_delete(node->right);
    free(node->key);
    free(node);
}

void delete_dict(GenDict* tree) {
    // walk down tree
    recursive_delete(tree->root);
    free(tree);
}

Node* rec_insert(Node* subtree, char* key, GenIndex value);
void dict_insert(GenDict* dict, char* key, GenIndex value) {
    dict->root = rec_insert(dict->root, key, value);
}

Node* rec_insert(Node* node, char* key, GenIndex value) {
    if (node) {
        int comp = strcmp(key, node->key);
        if (comp == 0) {
            node->value = value;
        }
        else if (comp < 0) {
            node->left = rec_insert(node->left, key, value);
        }
        else {
            node->right = rec_insert(node->right, key, value);
        }
    }
    else {
        node = malloc(sizeof(Node));
        node->key = malloc(strlen(key) + 1);
        strcpy(node->key, key);

        node->left = NULL;
        node->right = NULL;
        node->colour = Red;
        node->value = value;
    }
    return node;
}

int dict_get(GenDict* dict, char* key, GenIndex* value) {
    Node* node = dict->root;
    while (node != NULL) {
        int comp = strcmp(key, node->key);
        if (comp == 0) {
            (*value) = node->value;
            return 0;
        }
        else if (comp < 0) {
            node = node->left;
        }
        else {
            node = node->right;
        }

    }
    return 1;
}

int dict_delete(GenDict* dict, char* key) {
    return 0;
}
