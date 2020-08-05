#include <string.h>
#include <stdlib.h>
#include "engine/structures.h"


typedef enum {Red, Black} Colour;
typedef enum {Left, Right} Side;

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
    if (node->left)
        recursive_delete(node->left);
    if (node->right)
        recursive_delete(node->right);
    free(node->key);
    free(node);
}

void delete_dict(GenDict* tree) {
    // walk down tree
    recursive_delete(tree->root);
    free(tree);
}

Node* rec_insert(Node* node, Node* parent, Node* grandparent, Side side,
                 char* key, GenIndex value, int* return_value);

void dict_insert(GenDict* dict, char* key, GenIndex value) {
    dict->root = rec_insert(dict->root, NULL, NULL, 0, key, value, NULL);
}


Node* rec_insert(Node* node, Node* parent, Node* grandparent, Side side,
                 char* key, GenIndex value, int* value_out) {

    Node* child;
    int val = 0;

    if (node != NULL) {
        int comp = strcmp(key, node->key);
        if (comp == 0) {
            node->value = value;
        }
        else if (comp < 0) {
            child = rec_insert(node->left, node, parent, Left, key, value, &val);
            if (val == 0 || val == 3 || val == 4) {
                node->left = child;

                switch (val) {
                    case 3: *value_out = 2;
                        break;
                    case 4:
                        *value_out = 5;
                        parent->colour = grandparent == NULL;
                        break;
                }

                return node;
            }
            if (val == 5) node->left = child;

        }
        else {
            child = rec_insert(node->right, node, parent, Right, key, value, &val);
            if (val == 0 || val == 3 || val == 4) {
                node->right = child;
                switch (val) {
                    case 3: *value_out = 2;
                        break;
                    case 4:
                        *value_out = 5;
                        parent->colour = grandparent == NULL;
                        break;
                }
                return node;
            }
            if (val == 5) node->right = child;
        }

        switch(val) {
            // we are the parent, return child to grandparent
            case 1:
                *value_out = 2;
                return child;
            // we are the grandparent, return node to great grandparent.
            case 2:
                return child;

        }
    }
    else {
        // Create the new node
        node = malloc(sizeof(Node));
        node->key = malloc(strlen(key) + 1);
        strcpy(node->key, key);

        node->left = NULL;
        node->right = NULL;
        node->colour = Red;
        node->value = value;

    }

    // Now the node has been inserted, we should 'fix' the tree.
    // Invariant 1. The root is always black
    if (parent == NULL) {
        node->colour = Black;
        return node;
    }

    // It is possible no action is needed. This is the case when the parent is black
    if (parent->colour == Black) {
        return node;
    }


    // Now, we know that parent->colour *must* be red, hence the grandparent exists and is black
    // step 1: determine who the uncle is
    Side p_side = grandparent->left == parent ? Left : Right;
    Node* uncle = p_side == Left ? grandparent->right : grandparent->left;

    // step 2: determine whether uncle was red or black
    // Case 1: Black Uncle, so we need to do a tree rotation
    if (uncle == NULL || uncle->colour == Black) {
        grandparent->colour = Red;
        // substep 1: check if line g-p-n is straight or not
        // case 1: straight g-p-n line
        if (p_side == side) {
            parent->colour = Black;

            if (side == Left) {
                grandparent->left = parent->right;
                parent->right = grandparent;
            }
            else {
                grandparent->right = parent->left;
                parent->left = grandparent;
            }

            *value_out = 3;
            return node;
        }
        // case 2: "zig-zag" g-p-n line
        else {
            *value_out = 1;
            node->colour = Black;


            if (side == Left) {
                grandparent->right = node->left;
                parent->left = node->right;

                node->left = grandparent;
                node->right = parent;
                return node;
            }
            else {
                grandparent->left = node->right;
                parent->right = node->left;

                node->right = grandparent;
                node->left = parent;
                return node;
            }
        }
    }

    // case 2: Red Uncle
    else {
        // then uncle is red -> colour swap, so easy to solve :)
        grandparent->colour = Red;
        parent->colour = Black;
        uncle->colour = Black; // since uncle is red, it cannot be null

        *value_out = 4; // indicate that color may need changing
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
    Node* node = dict->root;
    while(node != NULL) {
        int comp = strcmp(key, node->key);
        if (comp == 0) {
            if (node->left == NULL && node->right == NULL) {
                free(node);
                return 0;
            }
            // do fancy swap-with-predecessor things
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
