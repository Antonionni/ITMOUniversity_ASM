#include <stdio.h>
#include <limits.h>

#include "LinkedList.h"

void show_with_space(const int value) {
    printf("%d ", value);
}
void show_with_newline(const int value) {
    printf("%d\n", value);
}

int square(const int value) {
    return value * value;
}

int cube(const int value) {
    return value * value * value;
}

int max(const int first, const int second) {
    return first > second ? first : second;
}
int min(const int first, const int second) {
    return first < second ? first : second;
}
int sum(const int first, const int second) {
    return first + second;
}
int twice(const int value) {
    return value * 2;
}
int main(int argc, char *argv[]) {
    int number = 0;
    int counter = 0;
    bool fist_item = true;

    LinkedNode *root;
    char c;
    while(scanf("%d", &number) != EOF) {
        if (counter == INT_MAX) {
            fprintf(stderr, "Yoy try add so many items; max items value = %d \n", INT_MAX);
            return -1;
        }
        if (fist_item) {
            root = list_create(number);
            if (!root) {
                fprintf(stderr, "Can`t create list \n");
                return -1;
            }
            fist_item = false;
        } else {
            if (list_add_front(&root, number) == -1) {
                fprintf(stderr, "Can`t push item to list \n");
                return -1;
            }
        }
        counter++;
    }
    printf("list length = %d \n", list_length(root));

    printf("print first 5 items: \n");
    if (list_show(root, 5) == -1) {
        fprintf(stderr, "Can`t show items \n");
        return -1;
    }

    printf("List sum: %d \n", list_sum(root));

    printf("Get element(valid): %d \n", list_get(root, 1));
    printf("Get element(invalid): %d \n", list_get(root, 100));

    printf("Foreach with space: \n");
    foreach(root, show_with_space);
    puts("\n");

    printf("Foreach with newline: \n");
    foreach(root, show_with_newline);

    printf("Map square \n");
    LinkedNode *new_root = map(root, square);
    if (new_root) {
        printf("Print square \n");
        foreach(new_root, show_with_space);
        puts("\n");
        list_free(new_root);
    } else {
        printf("Can`t show square list \n");
    }

    printf("Map cube \n");
    new_root = map(root, cube);
    if (new_root) {
        printf("Print cube \n");
        foreach(new_root, show_with_space);
        puts("\n");
        list_free(new_root);
    } else {
        printf("Can`t show cube list \n");
    }

    printf("foldl max: %d\n", foldl(root, INT_MIN, max));
    printf("foldl min: %d\n", foldl(root, INT_MAX, min));
    printf("foldl sum: %d\n", foldl(root, 0, sum));
    puts("\n");

    printf("Map_mut \n");
    new_root = map_mut(root);
    if (new_root) {
        printf("Print abs \n");
        foreach(new_root, show_with_space);
        puts("\n");
        list_free(new_root);
    } else {
        printf("Can`t show abs list \n");
    }

    printf("Iterate \n");
    new_root = iterate_list(1, 10, twice);
    if (new_root) {
        printf("Print powers \n");
        foreach(new_root, show_with_space);
        puts("\n");
        list_free(new_root);
    } else {
        fprintf(stderr, "Can`t iterate \n");
    }

    printf("Try save list: \n");
    if (save(root, "storage.txt")) {
        printf("successfully saved \n");
    } else {
        fprintf(stderr, "Can`t save list \n");
    }

    printf("Try read list: \n");
    if (load(&new_root, "storage.txt")) {
        printf("successfully loaded \n");
        foreach(new_root, show_with_space);
        puts("\n");
        list_free(new_root);
    } else {
        fprintf(stderr, "Can`t load list \n");
    }

    printf("Try serialize list: \n");
    if (serialize(root, "storage.bin")) {
        printf("successfully serialized \n");
    } else {
        fprintf(stderr, "Can`t serialize list \n");
    }

    printf("Try deserialize list: \n");
    if (deserialize(&new_root, "storage.bin")) {
        printf("successfully deserialized \n");
        foreach(new_root, show_with_space);
        puts("\n");
        list_free(new_root);
    } else {
        fprintf(stderr, "Can`t deserialize list \n");
    }

    if (list_free(root) == -1) {
        fprintf(stderr, "Can`t free list \n");
        return -1;
    }
    return 0;
}