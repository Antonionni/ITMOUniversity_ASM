#include <stdio.h>
#include "bmp.h"


int main(int argc, char *argv[]) {
    FILE *file_in = fopen("big.bmp", "rb");
    if (!file_in) {
        fprintf(stderr, "Can`t open file to read");
        return -1;
    }
    Image *current_image;

    read_error_code_t read_code = from_bmp(file_in, &current_image);

    fclose(file_in);

    switch (read_code) {
        case READ_INVALID_HEADER:
            fprintf(stderr, "can`t read header of BMP image\n");
            return -1;
        case READ_INVALID_SIGNATURE:
            fprintf(stderr, "Invalid signature in image file\n");
            return -1;
        case READ_INVALID_BITS:
            fprintf(stderr, "Invalid bits bmp file\n");
            return -1;
        case READ_OK:
            printf("Image successfully read\n");
            break;
        default:
            fprintf(stderr, "Undefined error\n");
            return -1;
    }

    // debugger
    write_pixel_to_file(current_image);

    unsigned angle = 0;
    puts("Please, write the angle of image rotate:");
    fflush(stdout);

    scanf("%d", &angle);

    Image *result = rotate(current_image, 10);
    if (!result) {
        fprintf(stderr, "Can`t rotate image");
        return -1;
    }

    FILE *file_out = fopen("big_test.bmp", "wb");
    if (!file_out) {
        fprintf(stderr, "Can`t open file to write");
        return -1;
    }

    write_error_code_t write_code = to_bmp(file_out, result);

    fclose(file_out);
    switch (write_code) {
        case WRITE_ERROR:
            fprintf(stderr, "can`t write BMP image");
            return -1;
        case WRITE_OK:
            printf("Image successfully saved\n");
            break;
        default:
            fprintf(stderr, "Undefined error");
            return -1;
    }

    free_image(current_image);
    free_image(result);
    return 0;
}