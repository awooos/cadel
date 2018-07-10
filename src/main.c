#include <cadel.h>
#include <stdint.h>
#include <stddef.h>

#include <stdio.h>

// Returns +b+ in
//   b = y - (m * x)
// where
//   m is the slope
//   x is the x coordinate
//   y is the y coordinate
//   b is the y intercept
int64_t cadel_y_intercept(int64_t slope, CadelPoint point)
{
    return (point.y - (slope * point.x));
}

// Returns +m+ in
//   m = (y1 - y2) / (x1 - x2)
// where
//   m is the slope
//   (x1, y1) is the first coordinate
//   (x2, y2) is the second coordinate
//
// WARNING: Equivalent x coordinates will cause a division-by-zero error.
int64_t cadel_slope(CadelPoint a, CadelPoint b)
{
    int64_t x1 = a.x;
    int64_t y1 = a.y;
    int64_t x2 = b.x;
    int64_t y2 = b.y;

    return (y2 - y1) / (x2 - x1);
}

// Set the pixel at the specified (x, y) coordinates on a CadelDisplay.
//
// ASSUMPTION: All pixels you don't want rendered are already zero.
void cadel_set_pixel(CadelDisplay *display, uint64_t x, uint64_t y)
{
    // We use a one-dimensional array to index a two-dimensional plane.
    // Multiply the vertical coordinate by the width to account for this.
    int64_t y_idx = (y - 1) * display->dimensions.width;

    // Set the pixel to 1, to enable it.
    display->data[y_idx + x] = 1;
}

// Renders a horizontal line to a CadelDisplay.
//
// Assumptions:
// - x coordinates are different.
// - y coordinates are the same.
void cadel_rasterize_horizontal_line(CadelDisplay *display,
        CadelPoint a,
        CadelPoint b)
{
    int64_t offset = ((a.y - b.y) > 0) ? 1 : -1;
    for (uint64_t y = a.y; y != b.y; y += offset) {
        cadel_set_pixel(display, a.x, y);
    }
}

// Renders a vertical line to a CadelDisplay.
//
// Assumptions:
// - x coordinates are the same.
// - y coordinates are different.
void cadel_rasterize_vertical_line(CadelDisplay *display,
        CadelPoint a,
        CadelPoint b)
{
    int32_t offset = ((a.x - b.x) > 0) ? 1 : -1;
    for (uint64_t x = a.x; x != b.x; x += offset) {
        cadel_set_pixel(display, x, a.y);
    }
}

void cadel_rasterize_line(CadelDisplay *display, CadelPoint a, CadelPoint b)
{
    // Handle horizontal lines.
    if (a.x == b.x) {
        cadel_rasterize_horizontal_line(display, a, b);
        return;
    }

    // Handle vertical lines.
    if (a.y == b.y) {
        cadel_rasterize_vertical_line(display, a, b);
        return;
    }

    // If +b+ is to the right of +a+, just swap them and render it.
    // This lets us assume we're always going left-to-right later on.
    if (a.x > b.x) {
        cadel_rasterize_line(display, b, a);
        return;
    }

    // If we get this far, the following are all true:
    // 1. +a.x != b.x+
    // 2. +a.y != b.y+
    // 3. +a.x <  b.x+

    // To generate the +y+ coordinate that goes with a given +x+ coordinate,
    // use the slope-intercept form of a linear equation:
    //   y = mx+b
    // which can be rewritten as:
    //   y = (slope * x) + y_intercept

    int64_t slope = cadel_slope(a, b);
    int64_t y_intercept = cadel_y_intercept(slope, a);

    uint64_t y;
    for (uint64_t x = a.x; x < b.x; x++) {
        y = (slope * x) + y_intercept;
        printf("Rendering: (%li, %li)\n", x, y);
        cadel_set_pixel(display, x, y);

        if (y == b.y) {
            break;
        }
    }
}

void cadel_rasterize(CadelDisplay *display, CadelGraph *graph)
{
    CadelPoint *points = graph->points;

    for (size_t idx = 1; idx < graph->size; idx++) {
        cadel_rasterize_line(display, points[idx - 1], points[idx]);
    }
}
