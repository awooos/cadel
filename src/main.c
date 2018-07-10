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

        printf("%li - %li = %li\n", last_y, y, last_y - y);
        if (cadel_abs(last_y - y) <= 1) {
            continue;
        }

        cadel_rasterize_vertical_line(display,
                cadel_point(x, y - (y - last_y) + 1),
                cadel_point(x, last_y + (y - last_y)));
    }
}

void cadel_rasterize(CadelDisplay *display, CadelGraph *graph)
{
    CadelPoint *points = graph->points;

    for (size_t idx = 1; idx < graph->size; idx++) {
        cadel_rasterize_line(display, points[idx - 1], points[idx]);
    }
}
