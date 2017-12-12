#include <stdbool.h>

#ifndef LINKED_LIST_LINKEDLIST_H
#define LINKED_LIST_LINKEDLIST_H


typedef struct Node {
    int value;
    struct Node *next;
} LinkedNode;

LinkedNode *list_create_node(const int value);
int list_push_back(LinkedNode *node, const int value);
int list_push_front(LinkedNode **node, const int value);
int list_show(LinkedNode *node);
int list_free(LinkedNode *node);
int list_sum(LinkedNode *node);
int list_length(LinkedNode *node);

#endif //LINKED_LIST_LINKEDLIST_H
