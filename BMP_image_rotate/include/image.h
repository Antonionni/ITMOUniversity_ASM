#ifndef BMP_IMAGE_ROTATE_IMAGE_H
#define BMP_IMAGE_ROTATE_IMAGE_H

#include <stdint.h>

typedef  struct pixel_t {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} __attribute__((__packed__)) Pixel;

typedef struct image_t {
    uint32_t width;
    uint32_t height;
    Pixel **data;
} Image;

void write_pixel_to_file(Image *const source);
Image *rotate(Image* const source);
#endif //BMP_IMAGE_ROTATE_IMAGE_H
