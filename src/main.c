#include <cadel.h>
#include <stdint.h>
#include <stddef.h>

#include <stdio.h>

uint8_t blah = 0;

// Set the pixel at the specified (x, y) coordinates on a CadelDisplay.
//
// ASSUMPTION: All pixels you don't want rendered are already zero.
void cadel_set_pixel(CadelDisplay *display, uint64_t x, uint64_t y)
{
    // We use a one-dimensional array to index a two-dimensional plane.
    // Multiply the vertical coordinate by the width to account for this.
    uint64_t y_idx = y * display->dimensions.width;

    // Set the pixel to 1, to enable it.
    display->data[y_idx + x] = blah;//1;
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
    if (a.x > b.x) {
        cadel_rasterize_horizontal_line(display, b, a);
        return;
    }

    for (uint64_t x = a.x; x <= b.x; x++) {
        cadel_set_pixel(display, x, a.y);
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
    if (a.y > b.y) {
        cadel_rasterize_vertical_line(display, b, a);
        return;
    }

    for (uint64_t y = a.y; y <= b.y; y++) {
        cadel_set_pixel(display, a.x, y);
    }
}

void cadel_rasterize_sloped_line(CadelDisplay *display,
        CadelPoint l,
        CadelPoint r)
{
    // If +l+ is to the right of +r+, just swap them and render it.
    // This lets us assume we're always going left-to-right later on.
    if (l.x > r.x) {
        cadel_rasterize_sloped_line(display, r, l);
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

    int64_t y;
    for (int64_t x = l.x; x <= r.x; x++) {
        y = (m * x) + b;
        printf("%li = (%f * %li) + %li\n", y, m, x, b);
        cadel_set_pixel(display, x, y);
    }

}

void cadel_rasterize_line(CadelDisplay *display, CadelPoint a, CadelPoint b)
{
    // Handle horizontal lines.
    if (a.y == b.y) {
        cadel_rasterize_horizontal_line(display, a, b);
        return;
    }

    // Handle vertical lines.
    if (a.x == b.x) {
        cadel_rasterize_vertical_line(display, a, b);
        return;
    }

    cadel_rasterize_sloped_line(display, a, b);
}

void cadel_rasterize(CadelDisplay *display, CadelGraph *graph)
{
    CadelPoint *points = graph->points;

    for (size_t idx = 1; idx < graph->size; idx++) {
        blah = idx;
        cadel_rasterize_line(display, points[idx - 1], points[idx]);
    }
}
