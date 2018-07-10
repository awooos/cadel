#include <cadel.h>
#include <stdint.h>
#include <stddef.h>

#include <stdio.h>

int64_t cadel_abs(int64_t n)
{
    return (n < 0) ? -n : n;
}

// Set the pixel at the specified (x, y) coordinates on a CadelDisplay.
//
// ASSUMPTION: All pixels you don't want rendered are already zero.
void cadel_set_pixel(CadelDisplay *display, uint64_t x, uint64_t y)
{
    // We use a one-dimensional array to index a two-dimensional plane.
    // Multiply the vertical coordinate by the width to account for this.
    uint64_t y_idx = y * display->dimensions.width;

    // Set the pixel to 1, to enable it.
    display->data[y_idx + x] = 1;
}

// Renders a vertical line to a CadelDisplay.
void cadel_rasterize_vertical_line(CadelDisplay *display,
        int64_t x, int64_t y, int64_t length)
{
    int64_t offset = (length > 0) ? +1 : -1;

    for (int64_t i = 0; i != length; i += offset) {
        cadel_set_pixel(display, x, y + i);
    }
}

void cadel_rasterize_line(CadelDisplay *display,
        CadelPoint l,
        CadelPoint r)
{
    // If +l+ is to the right of +r+, just swap them and render it.
    // This lets us assume we're always going left-to-right later on.
    if (l.x > r.x) {
        cadel_rasterize_line(display, r, l);
        return;
    }

    // To generate the +y+ coordinate that goes with a given +x+ coordinate,
    // use the slope-intercept form of a linear equation:
    //   y = mx+b
    // where
    //   x = x coordinate
    //   y = y coordinate
    //   m = slope
    //   b = y-intercept

    double  m = (double)(r.y - l.y) / (r.x - l.x);
    int64_t b = l.y - (m * l.x);

    int64_t last_y = -1;
    int64_t y;
    for (int64_t x = l.x; x <= r.x; x++) {
        last_y = (m * (x - 1)) + b;
        y = (m * x) + b;

        cadel_set_pixel(display, x, y);
        cadel_rasterize_vertical_line(display, x, y, last_y - y);
    }
}

void cadel_rasterize(CadelDisplay *display, CadelGraph *graph)
{
    CadelPoint *points = graph->points;

    for (size_t idx = 1; idx < graph->size; idx++) {
        cadel_rasterize_line(display, points[idx - 1], points[idx]);
    }
}
