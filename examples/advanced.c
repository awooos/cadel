#define __USE_BSD
#define _DEFAULT_SOURCE

#include <cadel.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_canvas(CadelCanvas canvas) {
    for (size_t y = 0; y < canvas.height; y++) {
        for (size_t x = 0; x < canvas.width; x++) {
            if (cadel_get_pixel(canvas, x, y) == 0) {
                printf(" ");
            } else {
                printf("X");
            }
        }
        printf("\n");
    }
}

#define rows 40
#define cols 79

CadelPoint a = {10, 30};
CadelPoint b = {40, 10};
CadelPoint c = {77, 12};

void draw(CadelCanvas canvas, size_t m)
{
    a.x += m;
    a.y -= m;

    b.x -= m;
    b.y += m;

    c.x -= m;
    c.y += m;

    CadelObject triangle = cadel_object(a, b, c, a);

    cadel_clear(canvas);
    cadel_render_object(canvas, triangle);
    print_canvas(canvas);

    sleep(1);
}

int main(int argc, const char *argv[])
{
    CadelCanvas canvas = cadel_canvas(cols, rows);
    size_t max = 20;

    size_t x = 0;
    while (1) {
        for (; x < max; x++) {
            draw(canvas, +1);
        }
        for (; x > -max; x--) {
            draw(canvas, -1);
        }
    }

    return 0;
}
