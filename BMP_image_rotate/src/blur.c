#include <image.h>
#include <stdlib.h>
#include <math.h>

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

void box_blur_h(Image *source, Image *target, int w, int h, int radius) {
    double iarr = (double)1 / (radius + radius + 1);
    for (int i = 0; i < h; i++) {
        int ti = i * w;
        int li = ti;
        int ri = ti + radius;
        Pixel fv = get_pixel(source, ti);
        Pixel lv = get_pixel(source, ti + w - 1);

        unsigned currennt_r = fv.r * (radius + 1);
        unsigned currennt_g = fv.g * (radius + 1);
        unsigned currennt_b = fv.b * (radius + 1);

        for (int j = 0; j < radius; j++) {
            Pixel pixel = get_pixel(source, ti + j);
            currennt_r += pixel.r;
            currennt_g += pixel.g;
            currennt_b += pixel.b;
        }

        for (int j = 0; j <= radius; j++) {
            Pixel pixel = get_pixel(source, ri++);
            currennt_r += (pixel.r - fv.r);
            currennt_g += (pixel.g - fv.g);
            currennt_b += (pixel.b - fv.b);

            set_pixel(target, ti++, currennt_r * iarr, currennt_g * iarr, currennt_b * iarr);
        }

        for (int j = radius + 1; j < w - radius; j++) {
            Pixel first_pixel = get_pixel(source, ri++);
            Pixel second_pixle = get_pixel(source, li++);

            currennt_r += (first_pixel.r - second_pixle.r);
            currennt_g += (first_pixel.g - second_pixle.g);
            currennt_b += (first_pixel.b - second_pixle.b);

            set_pixel(target, ti++, currennt_r * iarr, currennt_g * iarr, currennt_b * iarr);
        }

        for (int j = w - radius; j < w; j++) {
            Pixel pixel = get_pixel(source, li++);

            currennt_r += (lv.r - pixel.r);
            currennt_g += (lv.g - pixel.g);
            currennt_b += (lv.b - pixel.b);

            set_pixel(target, ti++, currennt_r * iarr, currennt_g * iarr, currennt_b * iarr);
        }
    }
}

void box_blur_t(Image *source, Image *target, int w, int h, int radius) {
    double iarr = (double)1 / (radius + radius + 1);
    for (int i = 0; i < w; i++) {
        int ti = i;
        int li = ti;
        int ri = ti + radius * w;

        Pixel fv = get_pixel(source, ti);
        Pixel lv = get_pixel(source, ti + w * (h - 1));

        unsigned currennt_r = fv.r * (radius + 1);
        unsigned currennt_g = fv.g * (radius + 1);
        unsigned currennt_b = fv.b * (radius + 1);

        for (int j = 0; j < radius; j++) {
            Pixel pixel = get_pixel(source, ti + j * w);
            currennt_r += pixel.r;
            currennt_g += pixel.g;
            currennt_b += pixel.b;
        }

        for (int j = 0; j <= radius; j++) {
            Pixel pixel = get_pixel(source, ri);
            currennt_r += (pixel.r - fv.r);
            currennt_g += (pixel.g - fv.g);
            currennt_b += (pixel.b - fv.b);

            set_pixel(target, ti, currennt_r * iarr, currennt_g * iarr, currennt_b * iarr);

            ri += w;
            ti += w;
        }

        for (int j = radius + 1; j < h - radius; j++) {
            Pixel first_pixel = get_pixel(source, ri);
            Pixel second_pixle = get_pixel(source, li);

            currennt_r += (first_pixel.r - second_pixle.r);
            currennt_g += (first_pixel.g - second_pixle.g);
            currennt_b += (first_pixel.b - second_pixle.b);

            set_pixel(target, ti, currennt_r * iarr, currennt_g * iarr, currennt_b * iarr);

            li += w;
            ri += w;
            ti += w;
        }

        for (int j = h - radius; j < h; j++) {
            Pixel pixel = get_pixel(source, li);

            currennt_r += (lv.r + pixel.r);
            currennt_g += (lv.g + pixel.g);
            currennt_b += (lv.b + pixel.b);

            set_pixel(target, ti, currennt_r * iarr, currennt_g * iarr, currennt_b * iarr);

            li += w;
            ti += w;
        }
    }
}

void box_blur(Image *source, Image *target, int w, int h, int radius) {
    copy_image(source, target);
    box_blur_h(target, source, w, h, radius);
    box_blur_t(source, target, w, h, radius);
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
