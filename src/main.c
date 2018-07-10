#include <cadel.h>
#include <stdint.h>
#include <stddef.h>

// returns +b+ in
//   b = y - (m * x)
// where
//   m is the slope
//   x is the x coordinate
//   y is the y coordinate
//   b is the y intercept
uint32_t cadel_y_intercept(uint32_t slope, CadelPoint point)
{
    return (point.y - (slope * point.x));
}

// returns +m+ in
//   m = (y1 - y2) / (x1 - x2)
// where
//   m is the slope
//   (x1, y1) is the first coordinate
//   (x2, y2) is the second coordinate
int32_t cadel_slope(CadelPoint a, CadelPoint b)
{
    uint32_t x1 = a.x;
    uint32_t y1 = a.y;
    uint32_t x2 = b.x;
    uint32_t y2 = b.y;

    if (y1 > y2) {
        return cadel_slope(b, a);
    }

    return (y2 - y1) / (x2 - x1);
}


int32_t cadel_abs(int32_t n)
{
    return ((n < 0) ? -n : n);
}

void cadel_set_pixel(CadelDisplay *display, uint32_t x, uint32_t y)
{
    // We use a one-dimensional array to index a two-dimensional plane.
    // Multiply the vertical coordinate by the width to account for this.
    uint32_t y_idx = (y - 1) * display->dimensions.width;

    display->data[y_idx + x] = 1;
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
    CadelPoint *points = graph->points;

    for (size_t gidx = 1; gidx < graph->size; gidx++) {
        CadelLine line = cadel_line(points[gidx - 1], points[gidx]);

        cadel_rasterize_line(display, line);
    }
}
