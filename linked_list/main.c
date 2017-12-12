#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "LinkedList.h"

int main(int argc, char *argv[]) {
    int number = 0;
    int counter = 0;
    bool fist_item = true;

    LinkedNode *root;
    char c;
    while(scanf("%d", &number) != EOF) {
        if (counter == INT_MAX) {
            fprintf(stderr, "Yoy try add so many items; max items value = %d", INT_MAX);
            return -1;
        }
        if (fist_item) {
            root = list_create_node(number);
            if (!root) {
                fprintf(stderr, "Can`t create list");
                return -1;
            }
            fist_item = false;
        } else {
            printf("info: push front value = %d \n", number);
            if (list_push_front(&root, number) == -1) {
                fprintf(stderr, "Can`t push item to list");
                return -1;
            }
        }
        counter++;
    }
    printf("items counter = %d \n", counter);

    if (list_show(root) == -1) {
        fprintf(stderr, "Can`t show items");
        return -1;
    }

    if (list_free(root) == -1) {
        fprintf(stderr, "Can`t free list");
        return -1;
    }

    return 0;
}