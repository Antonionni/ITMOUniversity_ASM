#include <bmp.h>
#include <stdlib.h>
#include "image.h"
#include "bmp.h"

read_error_code_t from_bmp(FILE* in, Image** read) {
    // read head
    bmp_head head;
    if (fread(&head, sizeof(head), 1, in) != 1) {
        return READ_INVALID_HEADER;
    }
    if (head.biBitCount != 24) {
        return READ_INVALID_BITS;
    }
    // in BPM image first two byte equal string "BM"
    if (head.bfType != 0x4d42) {
        return READ_INVALID_SIGNATURE;
    }

    (*read) = malloc(sizeof(Image));
    (*read)->height = head.biHeight;
    (*read)->width = head.biWidth;

    int padding = (4 - ((*read)->width * sizeof(Pixel)) % 4) %4;
    (*read)->data = calloc(head.biHeight, sizeof(Pixel*));

    for (unsigned row = 0; row < head.biHeight; ++row) {
        (*read)->data[row] = calloc(head.biWidth, sizeof(Pixel));
        fread(((*read)->data[row]), sizeof(Pixel), head.biWidth, in);
        fseek(in, padding, SEEK_CUR);
    }
    return READ_OK;
}

write_error_code_t to_bmp(FILE* out, Image* const img) {
    // initialize header
    bmp_head head;
    head.bfType = 0x4d42;
    head.bfileSize = img->width * img->height + sizeof(Pixel) + sizeof(bmp_head);
    head.bfReserved = 0;
    head.bOffBits = 54;
    head.biSize = 40;
    head.biWidth = img->width;
    head.biHeight = img->height;
    head.biPlanes = 1;
    head.biBitCount = 24;
    head.biCompression = 0;
    head.biSizeImage = img->width * img->height + sizeof(Pixel);
    head.biXPelsPerMeter = 0;
    head.biYPelsPerMeter = 0;
    head.biClrUsed = 0;
    head.biClrImportant = 0;

    if (fwrite(&head, sizeof(bmp_head), 1, out) != 1) {
        return WRITE_ERROR;
    }
    const int padding = (4 - (img->width * sizeof(Pixel)) % 4) %4;
    unsigned char trash [padding];

    unsigned long write_size = sizeof(Pixel) * img->width;
    for (unsigned coll = 0; coll < img->height; ++coll) {
        // write content
        if (fwrite(img->data[coll], write_size, 1, out) != 1) {
            return WRITE_ERROR;
        };
        // write padding
        if (padding != 0) {
            if (fwrite(&trash, padding, 1, out) != 1) {
                return WRITE_ERROR;
            }
        }
    }
    return WRITE_OK;
}