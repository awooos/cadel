#include <cadel.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

int32_t cadel_abs(int32_t n)
{
    return ((n < 0) ? -n : n);
}

bool cadel_on_line(CadelLine line, CadelPoint point)
{
    CadelPoint a = line.a;
    CadelPoint b = line.b;

    int32_t dxc = point.x - a.x;
    int32_t dyc = point.y - a.y;

    int32_t dxl = b.x - a.x;
    int32_t dyl = b.y - a.y;

    int32_t cross = dxc * dyl - dyc * dxl;

    if (cross != 0) {
        return false;
    }

    if (cadel_abs(dxl) >= cadel_abs(dyl)) {
        return (dxl > 0) ?
            (a.x <= point.x && point.x <= b.x) :
            (b.x <= point.x && point.x <= a.x);
    } else {
        return (dyl > 0) ?
            (a.y <= point.y && point.y <= b.y) :
            (b.y <= point.y && point.y <= a.y);
    }
}

void cadel_rasterize(CadelDisplay *display, CadelGraph *graph)
{
    uint8_t *dpy = display->data;
    CadelDimensions dimensions = display->dimensions;
    size_t size = dimensions.width * dimensions.height;
    CadelPoint *points = graph->points;

    for (size_t y = 0; y < dimensions.height; y++) {
        for (size_t x = 0; x < dimensions.width; x++) {
            CadelPoint point = cadel_point(x, y);
            for (size_t gidx = 1; gidx < graph->size; gidx++) {
                CadelLine line = cadel_line(points[gidx - 1], points[gidx]);

                if (cadel_on_line(line, point)) {
                    printf("{(%u, %u), (%u, %u)} does     have (%u, %u)\n",
                            line.a.x,
                            line.a.y,
                            line.b.x,
                            line.b.y,
                            point.x,
                            point.y);
                    dpy[((y - 1) * dimensions.width) + x] = 1;
                } else {
                    printf("{(%u, %u), (%u, %u)} does not have (%u, %u)\n",
                            line.a.x,
                            line.a.y,
                            line.b.x,
                            line.b.y,
                            point.x,
                            point.y);
                }
            }
        }
    }
}
