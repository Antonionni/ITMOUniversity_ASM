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

    // initialize
    for (unsigned x = 0; x < dest_width; ++x) {
        for (unsigned y = 0; y < dest_height; ++y) {
            int src_x = (int)((x + min_x)*cosine + (y + min_y) * sine);
            int src_y = (int)((y + min_y)*cosine - (x + min_x) * sine);
            if (src_x >= 0 && src_x < width && src_y >= 0 && src_y < height) {
                data_image->data[x][y] = source->data[src_x][src_y];
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