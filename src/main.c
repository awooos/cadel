#include <cadel.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

int32_t cadel_abs(int32_t n)
{
    return ((n < 0) ? -n : n);
}

void cadel_set_pixel(CadelDisplay *display, uint32_t x, uint32_t y)
{
    display->data[(y - 1) * display->dimensions.width + x] = 1;
}

void cadel_rasterize_horizontal_line(CadelDisplay *display, CadelLine line)
{
    CadelPoint a = line.a;
    CadelPoint b = line.b;

    int32_t offset = ((a.y - b.y) > 0) ? 1 : -1;
    for (uint32_t y = a.y; y != b.y; y += offset) {
        cadel_set_pixel(display, a.x, y);
    }
}

void cadel_rasterize_vertical_line(CadelDisplay *display, CadelLine line)
{
    CadelPoint a = line.a;
    CadelPoint b = line.b;

    int32_t offset = ((a.x - b.x) > 0) ? 1 : -1;
    for (uint32_t x = a.x; x != b.x; x += offset) {
        cadel_set_pixel(display, x, a.y);
    }
}

void cadel_rasterize_line(CadelDisplay *display, CadelLine line)
{
    CadelPoint a = line.a;
    CadelPoint b = line.b;

    // Handle horizontal lines.
    if (a.x == b.x) {
        cadel_rasterize_horizontal_line(display, line);
        return;
    }

    // Handle vertical lines.
    if (a.y == b.y) {
        cadel_rasterize_vertical_line(display, line);
        return;
    }

    // TODO: Handle everything else.
}

void cadel_rasterize(CadelDisplay *display, CadelGraph *graph)
{
    CadelDimensions dimensions = display->dimensions;
    CadelPoint *points = graph->points;

    for (size_t gidx = 1; gidx < graph->size; gidx++) {
        CadelLine line = cadel_line(points[gidx - 1], points[gidx]);

        cadel_rasterize_line(display, line);
    }
}
