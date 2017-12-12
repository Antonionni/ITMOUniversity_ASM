#include <stdbool.h>

#ifndef LINKED_LIST_LINKEDLIST_H
#define LINKED_LIST_LINKEDLIST_H


typedef struct Node {
    int value;
    struct Node *next;
} LinkedNode;

LinkedNode *list_create(const int value);
int list_add_back(LinkedNode *node, const int value);
int list_add_front(LinkedNode **node, const int value);
int list_show(LinkedNode *node, const unsigned size);
int list_free(LinkedNode *node);
int list_sum(LinkedNode *node);
int list_length(LinkedNode *node);
LinkedNode *list_node_at(LinkedNode const *root, const unsigned index);
int list_get(LinkedNode const *root, const unsigned index);


//higher-order functions
int foreach(LinkedNode const *root, void(* const func)(const int));
LinkedNode *map(LinkedNode const *root, int(* const func)(const int));
int foldl(LinkedNode const *root, int base_value, int (*const func)(const int, const int));
LinkedNode *map_mut(LinkedNode const *root);
LinkedNode *iterate_list(int initial_value, const int length, int(*const func)(const int));
bool save(LinkedNode const *root, const char *filename);
bool load(LinkedNode const **root, const char *filename);
bool serialize(LinkedNode const *root, const char *filename);
bool deserialize(LinkedNode const **root, const char *filename);
#endif //LINKED_LIST_LINKEDLIST_H
