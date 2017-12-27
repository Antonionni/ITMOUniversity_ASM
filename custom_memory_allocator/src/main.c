#include <stdio.h>
#include <stdlib.h>
#include "mem.h"

int main() {
    size_t matrix_size = 5;

    //first step
    int **matrix = _calloc(matrix_size, sizeof(int*));
    for (int i = 0; i < matrix_size; ++i) {
        matrix[i] = _calloc(matrix_size, sizeof(int));
    }
    for (int i = 0; i < matrix_size; ++i) {
        for (int j = 0; j < matrix_size; ++j) {
            matrix[i][j] = j + i;
        }
    }
    // print
    for (int i = 0; i < matrix_size; ++i) {
        for (int j = 0; j < matrix_size; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < matrix_size; ++i) {
        _free(matrix[i]);
    }
    _free(matrix);

    // pause
    fflush(stdout);
    getchar();

    //second step
    size_t new_matrix_size = 100;
    int **new_matrix = _calloc(new_matrix_size, sizeof(int*));
    for (int i = 0; i < new_matrix_size; ++i) {
        new_matrix[i] = _calloc(new_matrix_size, sizeof(int));
    }
    for (int i = 0; i < new_matrix_size; ++i) {
        for (int j = 0; j < new_matrix_size; ++j) {
            new_matrix[i][j] = j + i;
        }
    }
    // print
    for (int i = 0; i < new_matrix_size; ++i) {
        for (int j = 0; j < new_matrix_size; ++j) {
            printf("%d ", new_matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < new_matrix_size; ++i) {
        _free(new_matrix[i]);
    }
    _free(new_matrix);

    // pause
    fflush(stdout);
    getchar();
    return 0;
}