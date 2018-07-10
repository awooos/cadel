#include <cadel.h>
#include <stdint.h>
#include <stddef.h>

#include <stdio.h>

uint8_t blah = 0;

// Returns the absolute value of +n+.
int64_t cadel_abs(int64_t n)
{
    return (n < 0) ? -n : n;
}

// Returns +y+ in
//   y = (m * x) + b
// where
//   m is the slope
//   x is the x coordinate
//   y is the y coordinate
//   b is the y intercept
int64_t cadel_y(float slope, int64_t x, int64_t y_intercept)
{
    return (slope * x) + y_intercept;
}

// Returns +b+ in
//   b = y - (m * x)
// where
//   m is the slope
//   x is the x coordinate
//   y is the y coordinate
//   b is the y intercept
int64_t cadel_y_intercept(float slope, CadelPoint point)
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
float cadel_slope(CadelPoint a, CadelPoint b)
{
    return (float)(b.y - a.y) / (b.x - a.x);
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

void cadel_rasterize_sloped_line(CadelDisplay *display, CadelPoint a,
        CadelPoint b)
{
    // If +b+ is to the right of +a+, just swap them and render it.
    // This lets us assume we're always going left-to-right later on.
    if (a.x > b.x) {
        cadel_rasterize_sloped_line(display, b, a);
        return;
    }

    // To generate the +y+ coordinate that goes with a given +x+ coordinate,
    // use the slope-intercept form of a linear equation:
    //   y = mx+b
    // which can be rewritten as:
    //   y = (slope * x) + y_intercept

    float slope = cadel_slope(a, b);
    int64_t y_intercept = cadel_y_intercept(slope, a);

    CadelPoint last = {a.x, a.y};
    int64_t y;
    for (int64_t x = a.x; x <= b.x; x++) {
        y = cadel_y(slope, x, y_intercept);

        if (cadel_abs(last.y - y) <= 1) {
            cadel_set_pixel(display, x, y);
        } else {
            uint8_t old_blah = blah;
            blah = blah + ('A' - '0') - 1;

            cadel_set_pixel(display, x, y);

            blah = old_blah;
        }

        last.x = x;
        last.y = y;
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
