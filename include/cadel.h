#ifndef CADEL_H
#define CADEL_H

#include <stdint.h>

typedef struct cadel_point_s {
    uint32_t x;
    uint32_t y;
} CadelPoint;
#define cadel_point(x, y) ((CadelPoint){x, y})

typedef struct cadel_line_s {
    CadelPoint a;
    CadelPoint b;
} CadelLine;
#define cadel_line(a, b) ((CadelLine){a, b})

typedef struct cadel_dimensions_s {
    uint32_t width;
    uint32_t height;
} CadelDimensions;
#define cadel_dimensions(width, height) ((CadelDimensions){width, height})

typedef CadelPoint CadelPointList[1024];
typedef struct cadel_graph_s {
    CadelDimensions dimensions;
    uint32_t size;
    CadelPoint points[1024];
} CadelGraph;
#define cadel_graph(dimensions, size, ...) ((CadelGraph){dimensions, size, {__VA_ARGS__}})

typedef struct cadel_display_s {
    CadelDimensions dimensions;
    uint8_t *data;
} CadelDisplay;
#define cadel_display(width, height) ((CadelDisplay){ {width, height}, (uint8_t[width * height]){0,} })

void cadel_rasterize(CadelDisplay *display, CadelGraph *graph);

#endif
