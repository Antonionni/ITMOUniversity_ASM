#include <stdlib.h>
#include <stdio.h>
#include "LinkedList.h"

LinkedNode *list_create(const int value) {
    LinkedNode *node = (LinkedNode*)malloc(sizeof(LinkedNode));
    if (!node) {
        fprintf(stderr, "list_create: Can`t allocate memory to list! \n");
        return NULL;
    }
    node->value = value;
    node->next = NULL;
    return node;
}
int list_add_front(LinkedNode **node, const int value) {
    if (!node) {
        fprintf(stderr, "list_add_front: Empty root node \n");
        return -1;
    }
    LinkedNode *front_node = list_create(value);
    if (!front_node) {
        fprintf(stderr, "list_add_front: Can`t create front node \n");
        return -1;
    }
    front_node->next = *node;
    *node = front_node;
    return 0;
}

int list_add_back(LinkedNode *node, const int value) {
    if (!node) {
        fprintf(stderr, "list_add_front: Empty root node \n");
        return -1;
    }

    if (node->next != NULL) {
        list_add_back(node->next, value);
    } else {
        LinkedNode *back_node = list_create(value);
        if (!back_node) {
            fprintf(stderr, "list_add_front: Can`t create back node \n");
            return -1;
        }
        node->next = back_node;
    }

    return 0;
}

int list_show(LinkedNode *node, const unsigned size) {
    if (!node) {
        fprintf(stderr, "list_show: Empty root node \n");
        return -1;
    }

    LinkedNode *tmp = node;
    if (list_length(tmp) < size) {
        return -1;
    }
    for (unsigned i = 0; i < size; ++i) {
        printf("%d ", tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
    return 0;
}

int list_free(LinkedNode *node) {
    if (!node) {
        fprintf(stderr, "list_free: Empty root node \n");
        return -1;
    }
    unsigned count = 0;
    while(node) {
        LinkedNode *tmp = node->next;
        free(node);
        node = tmp;
        count++;
    }
    printf("free items memory = %d \n", count);
}

int list_sum(LinkedNode *node) {
    int sum = 0;
    LinkedNode *tmp = node;
    while(tmp) {
        sum += tmp->value;
        tmp = tmp->next;
    }
    return sum;
}


int list_length(LinkedNode *node) {
    if (!node) {
        fprintf(stderr, "list_length: Empty root node \n");
        return -1;
    }
    int length = 0;
    LinkedNode *tmp = node;
    while(tmp) {
        length++;
        tmp = tmp->next;
    }
    return length;
}

LinkedNode *list_node_at(LinkedNode const *root, const unsigned index) {
    if (!root) {
        fprintf(stderr, "list_node_at: Empty root node \n");
        return NULL;
    }
    unsigned count = 0;

    LinkedNode *tmp = root;
    while(tmp) {
        if (count == index) {
            return tmp;
        }
        tmp = tmp->next;
        count++;
    }
    return NULL;
}

int list_get(LinkedNode const *root, const unsigned index) {
    if (!root) {
        fprintf(stderr, "list_get: Empty root node \n");
        return -1;
    }
    LinkedNode *find_node;
    if ((find_node = list_node_at(root, index)) == NULL) {
        fprintf(stderr, "list_get: Element not found \n");
        return -1;
    }
    return find_node->value;
}


// use higher-order functions
int foreach(LinkedNode const *root, void(* const func)(const int)) {
    if (!root || !func) {
        fprintf(stderr, "foreach: Empty root node or undefined function \n");
        return -1;
    }
    LinkedNode *tmp = root;
    while(tmp) {
        func(tmp->value);
        tmp = tmp->next;
    }
    return 0;
}

LinkedNode *map(LinkedNode const *root, int(* const func)(const int)) {
    if (!root || !func) {
        fprintf(stderr, "map: Empty root node or undefined function \n");
        return NULL;
    }
    LinkedNode *new_node = list_create(func(root->value));
    if (!new_node) {
        return NULL;
    }
    LinkedNode *tmp = root->next;
    while(tmp) {
        if (list_add_back(new_node, func(tmp->value)) == -1) {
            list_free(new_node);
            return NULL;
        }
        tmp = tmp->next;
    }
    return new_node;
}

int foldl(LinkedNode const *root, int base_value, int (*const func)(const int, const int)) {
    if (!root || !func) {
        fprintf(stderr, "fold: Empty root node or undefined function \n");
        return NULL;
    }
    if (!root->next) {
        return root->value;
    } else {
        LinkedNode *tmp = root;
        while (tmp) {
            base_value = func(base_value, tmp->value);
            tmp = tmp->next;
        }
    }
    return base_value;
}

int abs(const int value) {
    return value < 0 ? -value : value;
}

LinkedNode *map_mut(LinkedNode const *root) {
    return map(root, abs);
}

LinkedNode *iterate_list(int initial_value, const int length, int(*const func)(const int)) {
    if (!func) {
        fprintf(stderr, "Function is undefined");
        return NULL;
    }
    LinkedNode *new_root = list_create(initial_value);
    if (!new_root) {
        fprintf(stderr, "Can`t create list");
        return NULL;
    }
    initial_value++;
    for (unsigned i = 0; i < length - 1; ++i) {
        if (list_add_back(new_root, func(initial_value)) == -1) {
            fprintf(stderr, "Can`t add new item \n");
            list_free(new_root);
            return NULL;
        }
        initial_value++;
    }
    return new_root;

}

bool save(LinkedNode const *root, const char *filename) {
    if (!root) {
        fprintf(stderr, "save: Empty root node \n");
        return false;
    }
    FILE *file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "save: Can`t open file");
        return false;
    }
    printf("filename = ", filename);
    LinkedNode *tmp = root;
    while(tmp) {
        fprintf(file, "%d ", tmp->value);
        tmp = tmp->next;
    }
    fclose(file);
    return true;
}
bool load(LinkedNode const **root, const char *filename) {
    if (!root) {
        fprintf(stderr, "load: Empty root node \n");
        return false;
    }
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "load: Can`t open file");
        return false;
    }
    int number = 0;
    bool first_symbol = true;
    while (fscanf(file, "%d ", &number) != EOF) {
        if (first_symbol) {
            *root = list_create(number);
            if (!root) {
                fprintf(stderr, "Can`t create list");
                return false;
            }
            first_symbol = false;
        } else {
            if (list_add_back(*root, number) == -1) {
                fprintf(stderr, "Can`t add number");
                list_free(*root);
                fclose(file);
                return false;
            }
        }
    }
    fclose(file);
    return true;
}
bool serialize(LinkedNode const *root, const char *filename) {
    if (!root) {
        fprintf(stderr, "serialize: Empty root node \n");
        return false;
    }
    FILE *file = fopen(filename, "wb");
    if (!file) {
        fprintf(stderr, "Can`t open file");
        return false;
    }

    unsigned index = 0;

    LinkedNode *tmp = root;
    const unsigned  list_size = list_length(tmp);
    int buffer[list_size];

    while (tmp) {
        buffer[index] = tmp->value;
        tmp = tmp->next;
        index++;
    }
    if (fwrite(&buffer, sizeof(int), list_size, file) != list_size) {
        fprintf(stderr, "Can`t write all list to file");
        fclose(file);
        return false;
    }
    fclose(file);
    return true;
}
bool deserialize(LinkedNode const **root, const char *filename) {
    if (!root) {
        fprintf(stderr, "deserialize: Empty root node \n");
        return false;
    }
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Can`t open file \n");
        return false;
    }

    fseek(file, 0 ,SEEK_END);
    unsigned  file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    printf("file_size = %d \n", file_size);
    const unsigned total_count = (file_size / sizeof(int));
    printf("total_count = %d \n", total_count);

    int buffer[total_count];
    if (fread(&buffer, sizeof(int), total_count, file) != total_count) {
        fprintf(stderr, "Can`t read all items from file");
        fclose(file);
        return false;
    }

    for (unsigned i = 0; i < total_count; ++i) {
        printf("%d ", buffer[i]);
        if (i == 0) {
            *root = list_create(buffer[i]);
            if (!root) {
                fprintf(stderr, "Can`t create list \n");
                fclose(file);
                return false;
            }
        } else {
            if (list_add_back(*root, buffer[i]) == -1) {
                fprintf(stderr, "Can`t add list item \n");
                fclose(file);
                return false;
            }
        }

    }
    puts("\n");
    fclose(file);
    return true;
}