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

// gaussian blur
int *boxes_for_gauss(double sigma, int n);
void box_blur_h(Image **source, Image **target, int w, int h, int radius);
void box_blur_t(Image **source, Image **target, int w, int h, int radius);
void box_blur(Image **source, Image **target, int w, int h, int radius);
Image *gaussian_blur(Image *source, double radius);

// common
void write_pixel_to_file(Image *const source);
void copy_image(Image *source, Image *target);
void free_image(Image *source);
#endif //BMP_IMAGE_ROTATE_IMAGE_H