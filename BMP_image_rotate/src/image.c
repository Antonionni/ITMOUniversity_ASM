#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "image.h"

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

Image *rotate(Image* const source, unsigned angle) {
    if (angle > 360) {
        fprintf(stderr, "Undefined angle; please write number > 0 && < 360");
        return NULL;
    }
    float radian = (2 * 3.1416 * angle) / 360;

    double cosine = (float)cos(radian);
    double sine = (float)sin(radian);

    unsigned height = source->height;
    unsigned width = source->width;

    float point1_x = ((float)(-1) * height * sine);
    float point1_y = (height * cosine);
    float point2_x = (width * cosine - height * sine);
    float point2_y = (height * cosine + width * sine);
    float point3_x = (width * cosine);
    float point3_y = (width * sine);

    float min_x = min(0, min(point1_x, min(point2_x, point3_x)));
    float min_y = min(0, min(point1_y, min(point2_y, point3_y)));

    float max_x = max(point1_x, max(point2_x, point3_x));
    float max_y = max(point1_y, max(point2_y, point3_y));

    int dest_width = (int)ceil(fabs(max_x) - min_x);
    int dest_height = (int)ceil(fabs(max_y) - min_y);


    Image *data_image = malloc(sizeof(Image));
    data_image->width = dest_width;
    data_image->height = dest_height;

    // allocate memory
    data_image->data = calloc(dest_height, sizeof(Pixel*));
    for (unsigned row = 0; row < dest_height; ++row) {
        data_image->data[row] = calloc(dest_width, sizeof(Pixel));
    }

    Pixel white_pixel = { 255, 255, 255};

    // initialize
    for (int y = 0; y < dest_height; ++y) {
        for (int x = 0; x < dest_width; ++x) {
            int src_x = (int)((x + min_x)*cosine + (y + min_y) * sine);
            int src_y = (int)((y + min_y)*cosine - (x + min_x) * sine);
            if (src_x >= 0 && src_x < width && src_y >= 0 && src_y < height) {
                data_image->data[y][x] = source->data[src_y][src_x];
            } else {
                data_image->data[y][x] = white_pixel;
            }
        }
    }
    return data_image;
}

void write_pixel_to_file(Image *const source) {
    FILE *file = fopen("pixel.data", "w");
    for (int h = 0; h < 100; ++h) {
        for (int w = 0; w < 100; ++w) {
            Pixel current_pixel = source->data[h][w];
            fprintf(file, "(%d,%d,%d)", (int)current_pixel.r, (int)current_pixel.g, (int)current_pixel.b);
        }
        fprintf(file, "\n");
    }
}

void free_image(Image *source) {
    for (unsigned i = 0; i < source->height; ++i) {
        free(source->data[i]);
    }
    free(source->data);
    free(source);
}

void copy_image(Image *source, Image *target) {
    for (int row = 0; row < source->height; row++) {
        for (int coll = 0; coll < source->width; coll) {
            target->data[row][coll] = source->data[row][coll];
        }
    }
}

// gaussian blur

int *boxes_for_gauss(double sigma, int n) {
    double w_ideal = sqrt((12 * sigma * sigma / n) + 1);
    int wl = (int)floor(w_ideal);
    if (wl % 2 == 0) wl--;

    int wu = wl + 2;

    double m_ideal = (12 * sigma * sigma - n * wl * wl - 4 * n * wl - 3 * n) / (-4 * wl - 4);
    int m = round(m_ideal);

    int *sizes = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        sizes[i] = i < m ? wl : wu;
    }
    return sizes;
}

void box_blur_h(Image **source, Image **target, int w, int h, int radius) {

}

void box_blur_t(Image **source, Image **target, int w, int h, int radius) {

}

void box_blur(Image **source, Image **target, int w, int h, int radius) {

}

Image *gaussian_blur(Image *source, double radius) {
    int width = source->width;
    int height = source->height;
    // allocate image
    Image *target = malloc(sizeof(Image));

    target->width = width;
    target->height = height;

    target->data = calloc(height, sizeof(Pixel*));
    for (int row = 0; row < height; row++) {
        target->data[row] = calloc(width, sizeof(Pixel));
    }

    int *bxs = boxes_for_gauss(radius, 3);
    box_blur(source, target, width, height, (bxs[0] - 1) / 2);
    box_blur(target, source, width, height, (bxs[1] - 1) / 2);
    box_blur(source, target, width, height, (bxs[2] - 1) / 2);

    //free momory
    free(bxs);
    return target;
}

