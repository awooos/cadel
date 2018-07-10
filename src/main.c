#include <cadel.h>
#include <stdint.h>

void cadel_clear(CadelCanvas canvas)
{
    for (uint64_t i = 0; i < (canvas.width * canvas.height); i++) {
        canvas.data[i] = 0;
    }
}

// Get the value of the pixel at +(x, y)+ on +canvas+.
uint8_t cadel_get_pixel(CadelCanvas canvas, int64_t x, int64_t y)
{
    return canvas.data[(y * canvas.width) + x];
}

// Set the value of the pixel at +(x, y)+ on +canvas+ to +val+.
void cadel_set_pixel(CadelCanvas canvas, int64_t x, int64_t y, int8_t val)
{
    canvas.data[(y * canvas.width) + x] = val;
}

// Renders a vertical line to a CadelCanvas.
void cadel_render_vertical_line(CadelCanvas canvas,
        int64_t x, int64_t y, int64_t length)
{
    // If we get a negative length, then invert
    // the y coordinate and negate the length.
    if (length < 0) {
        length = -length;
        y = y - length + 1;
    }

    for (int64_t idx = 0; idx < length; idx++) {
        cadel_set_pixel(canvas, x, y + idx, 1);
    }
}

void cadel_render_line(CadelCanvas canvas, CadelPoint l, CadelPoint r)
{
    // Ensure +l+ is to the left of +r+ by swapping argument order if needed.
    if (l.x > r.x) {
        cadel_render_line(canvas, r, l);
        return;
    }

    // Use the slope-intercept form of a linear equation (y = mx + b)
    // to generate +y+ coordinates for a given +x+ coordinate.
    double  m = (double)(r.y - l.y) / (r.x - l.x);
    int64_t b = l.y - (m * l.x);

    for (int64_t x = l.x; x <= r.x; x++) {
        int64_t last_y = (m * (x - 1)) + b;
        int64_t y = (m * x) + b;

        // Draw the exact pixel.
        cadel_set_pixel(canvas, x, y, 1);
        // Draw adjacent pixels if needed.
        cadel_render_vertical_line(canvas, x, y, last_y - y);
    }
}

void cadel_render_object(CadelCanvas canvas, CadelObject points)
{
    for (uint64_t idx = 1; !points[idx].terminus; idx++) {
        cadel_render_line(canvas, points[idx - 1], points[idx]);
    }
}
