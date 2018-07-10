#ifndef CADEL_H
#define CADEL_H

#include <stdint.h>

typedef struct cadel_point_s {
    int64_t x;
    int64_t y;
    uint8_t terminus; // HACK: If you only specify +{x, y}+, this becomes 0.
} CadelPoint;
typedef CadelPoint CadelObject[1024];
#define cadel_object(...) {__VA_ARGS__, {0, 0, 1}}

typedef struct cadel_image_s {
    int64_t width;
    int64_t height;
    uint8_t *data;
} CadelImage;
#define cadel_image(width, height) ((CadelImage){width, height, (uint8_t[width * height]){0,} })

uint8_t cadel_get_pixel(CadelImage image, int64_t x, int64_t y);
void cadel_clear(CadelImage image);
void cadel_render(CadelImage image, CadelObject points);

#endif
