#include <stdlib.h>
#include <stdio.h>
#include "LinkedList.h"

LinkedNode *list_create_node(const int value) {
    LinkedNode *node = (LinkedNode*)malloc(sizeof(LinkedNode));
    if (!node) {
        fprintf(stderr, "list_create_node: Can`t allocate memory to list!");
        return NULL;
    }
    node->value = value;
    node->next = NULL;
    return node;
}
int list_push_front(LinkedNode **node, const int value) {
    if (!node) {
        fprintf(stderr, "list_push_front: Empty root node");
        return -1;
    }
    LinkedNode *front_node = list_create_node(value);
    if (!front_node) {
        fprintf(stderr, "list_push_front: Can`t create front node");
        return -1;
    }
    front_node->next = *node;
    *node = front_node;
    return 0;
}

int list_push_back(LinkedNode *node, const int value) {
    if (!node) {
        fprintf(stderr, "list_push_front: Empty root node");
        return -1;
    }

    if (node->next != NULL) {
        list_push_back(node->next, value);
    } else {
        LinkedNode *back_node = list_create_node(value);
        if (!back_node) {
            fprintf(stderr, "list_push_front: Can`t create back node");
            return -1;
        }
        node->next = back_node;
    }

    return 0;
}

int list_show(LinkedNode *node) {
    if (!node) {
        fprintf(stderr, "list_show: Empty root node");
        return -1;
    }

    LinkedNode *tmp = node;
    while(tmp != NULL) {
        printf("%d ", tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
    return 0;
}

int list_free(LinkedNode *node) {
    if (!node) {
        fprintf(stderr, "list_free: Empty root node");
        return -1;
    }
    unsigned count = 0;
    while(node) {
        LinkedNode *tmp = node->next;
        free(node);
        node = tmp;
        count++;
    }
    printf("free items memory = %d", count);
}