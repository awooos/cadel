#include <cadel.h>

uint8_t cadel_between(uint32_t a, uint32_t b, uint32_t c)
{
    return ( ((c >= (a - 1)) && (c <= (b - 1))) ||
             ((c <= (a - 1)) && (c >= (b - 1))) ) ? 1 : 0;
}

void cadel_rasterize(CadelDisplay *display, CadelGraph *graph)
{
    uint8_t *dpy = display->data;
    CadelDimensions dimensions = display->dimensions;
    size_t size = dimensions.width * dimensions.height;

    for (size_t y = 0; y < dimensions.height; y++) {
        for (size_t x = 0; x < dimensions.width; x++) {
            for (size_t gidx = 1; gidx < graph->size; gidx++) {
                CadelPoint *prev = &(graph->points[gidx - 1]);
                CadelPoint *curr = &(graph->points[gidx]);

                if (cadel_between(prev->x, curr->x, x) &&
                        cadel_between(prev->y, curr->y, y)) {
                    dpy[(y * dimensions.width) + x] = 1;
                }
            }
        }
    }

/*        size_t x = prev->x;
        size_t y = prev->y;
        while (1) {
            printf("%u, %u\n", x, y);
            //dpy[(x * dimensions.width) + y] = 1;
            dpy[(dimensions.width * x) + y] = 1;

            if ( (x == curr->x) && (y == curr->y) ) {
                break;
            }

            if (x < curr->x) {
                x++;
            } else if (x > curr->x) {
                x--;
            }
            if (y < curr->y) {
                y++;
            } else if (y > curr->y) {
                y--;
            }
        }
    }*/
}
