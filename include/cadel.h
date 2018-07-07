#ifndef CADEL_H
#define CADEL_H

#include <stddef.h>
#include <stdint.h>

typedef void *(CadelMallocFn)(size_t size);
typedef void (CadelFreeFn)(void *ptr);

typedef struct cadel_memory_manager_functions_s {
    CadelMallocFn *malloc;
    CadelFreeFn *free;
} CadelMemoryManagerFunctions;

typedef struct cadel_point_s {
    uint32_t x;
    uint32_t y;
} CadelPoint;

typedef struct cadel_dimensions_s {
    uint32_t width;
    uint32_t height;
} CadelDimensions;

typedef CadelPoint CadelPointList[1024];
typedef struct cadel_graph_s {
    CadelDimensions dimensions;
    uint32_t size;
    CadelPoint points[1024];
} CadelGraph;

void cadel_init(CadelMallocFn *mallocfn, CadelFreeFn *freefn);
void cadel_rasterize(CadelDimensions dimensions, uint8_t *dpy, CadelGraph *graph);

#define cadel_graph(dimensions, size, ...) ((CadelGraph){dimensions, size, {__VA_ARGS__}})

#endif
