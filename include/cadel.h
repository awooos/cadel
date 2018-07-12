#ifndef CADEL_H
#define CADEL_H

#include <stdint.h>

typedef struct cadel_point_s {
    int64_t x;
    int64_t y;
} CadelPoint;
static CadelPoint CADEL_TERMINUS = {-100, -100};
typedef CadelPoint CadelObject[1024];
#define cadel_object(...) {__VA_ARGS__, CADEL_TERMINUS}
#define cadel_terminus(point) ((point.x) == CADEL_TERMINUS.x && (point.y) == CADEL_TERMINUS.y)

typedef struct cadel_canvas_s {
    int64_t width;
    int64_t height;
    uint8_t *data;
} CadelCanvas;
#define cadel_canvas(w, h) ((CadelCanvas){w, h, (uint8_t[w * h]){0,} })

uint8_t cadel_get_pixel(CadelCanvas canvas, int64_t x, int64_t y);
void cadel_clear(CadelCanvas canvas);
void cadel_render_object(CadelCanvas canvas, CadelObject points);

#endif
