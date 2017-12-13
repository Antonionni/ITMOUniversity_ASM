#ifndef BMP_IMAGE_ROTATE_BMP_H
#define BMP_IMAGE_ROTATE_BMP_H

#include <stdint-gcc.h>
#include <stdio.h>

#include "image.h"

typedef enum {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER
} read_error_code_t;

typedef struct {
    uint16_t bfType;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} __attribute__((__packed__)) bmp_head;

typedef enum {
    WRITE_OK = 0,
    WRITE_ERROR
} write_error_code_t;

// function
read_error_code_t from_bmp(FILE* in, Image** read);
write_error_code_t to_bmp(FILE* out, Image* const img);
#endif //BMP_IMAGE_ROTATE_BMP_H
