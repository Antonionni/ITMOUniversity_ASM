#include <stdio.h>
#include "image.h"

Image *rotate(Image* const source) {
    
    return NULL;
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