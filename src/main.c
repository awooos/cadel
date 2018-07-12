#include <cadel.h>
#include <stdint.h>

void cadel_clear(CadelCanvas canvas)
{
    for (int64_t i = 0; i < (canvas.width * canvas.height); i++) {
        canvas.data[i] = 0;
    }
}

// Get the value of the pixel at +(x, y)+ on +canvas+.
uint8_t cadel_get_pixel(CadelCanvas canvas, int64_t x, int64_t y)
{
    return canvas.data[(y * canvas.width) + x];
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
    int64_t b = (int64_t)(l.y - (m * l.x));

    for (int64_t x = l.x + 1; x <= r.x; x++) {
        int64_t last_y = (int64_t)((m * (x - 1)) + b);
        int64_t y = (int64_t)((m * x) + b);

        int64_t low  = (y > last_y) ? last_y : (y + 1);
        int64_t high = (y > last_y) ? y : (last_y + 1);
        if (low != high) {
            low++;
        }

        for (int64_t new_y = low; new_y <= high; new_y++) {
            canvas.data[(new_y * canvas.width) + x] = 1;
        }
    }
}

void cadel_render_object(CadelCanvas canvas, CadelObject points)
{
    for (uint64_t idx = 1; !points[idx].terminus; idx++) {
        cadel_render_line(canvas, points[idx - 1], points[idx]);
    }
}
