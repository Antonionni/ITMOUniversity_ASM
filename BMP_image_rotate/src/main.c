#include <stdio.h>
#include "bmp.h"


int main(int argc, char *argv[]) {
    FILE *file = fopen("small.bmp", "rb");
    if (!file) {
        fprintf(stderr, "Can`t open file to read");
        return -1;
    }
    Image *current_image;
    read_error_code_t read_code = from_bmp(file, &current_image);
    switch (read_code) {
        case READ_INVALID_HEADER:
            fprintf(stderr, "can`t read header of BMP image");
            return -1;
        case READ_INVALID_SIGNATURE:
            fprintf(stderr, "Invalid signature in image file");
            return -1;
        case READ_INVALID_BITS:
            fprintf(stderr, "Invalid bits bmp file");
            return -1;
        case READ_OK:
            printf("Image successfully read");
            break;
        default:
            fprintf(stderr, "Undefined error");
            return -1;
    }

    write_pixel_to_file(current_image);

    FILE *file_out = fopen("new_small.bmp", "wb");
    if (!file_out) {
        fprintf(stderr, "Can`t open file to write");
        return -1;
    }

    write_error_code_t write_code = to_bmp(file_out, current_image);

    switch (write_code) {
        case WRITE_ERROR:
            fprintf(stderr, "can`t write BMP image");
            return -1;
        case WRITE_OK:
            break;
        default:
            fprintf(stderr, "Undefined error");
            return -1;
    }
    return 0;
}