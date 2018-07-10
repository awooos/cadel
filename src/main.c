#include <cadel.h>
#include <stdint.h>
#include <stddef.h>

uint64_t cadel_pixel_index(CadelDisplay *display, int64_t x, int64_t y)
{
    // We use a one-dimensional array to index a two-dimensional plane.
    // Multiply the vertical coordinate by the width to account for this.
    uint64_t y_idx = y * display->dimensions.width;

    return y_idx + x;
}

// Get the value of the pixel at +(x, y)+ on +display+.
uint8_t cadel_get_pixel(CadelDisplay *display, int64_t x, int64_t y)
{
    return display->data[cadel_pixel_index(display, x, y)];
}

// Set the pixel at +(x, y)+ on +display+ to +val+.
void cadel_set_pixel(CadelDisplay *display, int64_t x, int64_t y, int8_t val)
{
    display->data[cadel_pixel_index(display, x, y)] = val;
}

// Renders a vertical line to a CadelDisplay.
void cadel_render_vertical_line(CadelDisplay *display,
        int64_t x, int64_t y, int64_t length)
{
    int64_t offset = (length > 0) ? +1 : -1;

    for (int64_t i = 0; i != length; i += offset) {
        cadel_set_pixel(display, x, y + i, 1);
    }
}

void cadel_render_line(CadelDisplay *display, CadelPoint l, CadelPoint r)
{
    // If +l+ is to the right of +r+, just swap them and render it.
    // This lets us assume we're always going left-to-right later on.
    if (l.x > r.x) {
        cadel_render_line(display, r, l);
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

        cadel_set_pixel(display, x, y, 1);
        cadel_render_vertical_line(display, x, y, last_y - y);
    }
}

void cadel_clear(CadelDisplay *display)
{
    for (int64_t y = 0; y < display->dimensions.height; y++) {
        for (int64_t x = 0; x < display->dimensions.width; x++) {
            cadel_set_pixel(display, x, y, 0);
        }
    }
}

void cadel_render(CadelDisplay *display, CadelGraph *graph)
{
    CadelPoint *points = graph->points;

    for (size_t idx = 1; idx < graph->size; idx++) {
        cadel_render_line(display, points[idx - 1], points[idx]);
    }
}
