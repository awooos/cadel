#ifndef CADEL_H
#define CADEL_H

#include <stdint.h>

typedef struct cadel_point_s {
    uint32_t x;
    uint32_t y;
} CadelPoint;

typedef struct cadel_dimensions_s {
    uint32_t width;
    uint32_t height;
} CadelDimensions;

typedef struct cadel_display_s {
    CadelDimensions dimensions;
    uint8_t *data;
} CadelDisplay;

typedef CadelPoint CadelPointList[1024];
typedef struct cadel_graph_s {
    CadelDimensions dimensions;
    uint32_t size;
    CadelPoint points[1024];
} CadelGraph;

void cadel_rasterize(CadelDisplay *display, CadelGraph *graph);

#define cadel_dimensions(width, height) ((CadelDimensions){width, height})

#define cadel_graph(dimensions, size, ...) ((CadelGraph){dimensions, size, {__VA_ARGS__}})

#define cadel_display(width, height) ((CadelDisplay){ {width, height}, (uint8_t[width * height]){0,} })

#endif
