#ifndef BMP_IMAGE_ROTATE_BLUR_H
#define BMP_IMAGE_ROTATE_BLUR_H

#include "image.h"

// gaussian blur
static int *boxes_for_gauss(double sigma, int n);
static void box_blur_h(Image *source, Image *target, int w, int h, int radius);
static void box_blur_t(Image *source, Image *target, int w, int h, int radius);
static void box_blur(Image *source, Image *target, int w, int h, int radius);
Image *gaussian_blur(Image *source, double radius);

#endif //BMP_IMAGE_ROTATE_BLUR_H
