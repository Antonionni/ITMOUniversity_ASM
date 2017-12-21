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

// rotate image
Image *rotate(Image* const source, unsigned angle);

// common
void write_pixel_to_file(Image *const source);
Pixel get_pixel(Image *source, int index);
void set_pixel(Image *source, int index, int r, int g, int b);
void copy_image(Image *source, Image *target);
void free_image(Image *source);
#endif //BMP_IMAGE_ROTATE_IMAGE_H