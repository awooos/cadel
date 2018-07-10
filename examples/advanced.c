#include <cadel.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
#define cols 134

CadelPoint a = { 10, 30};
CadelPoint b = { 65, 10};
CadelPoint c = {110, 12};

void draw(CadelCanvas canvas, size_t x)
{
    a.x += x;
    a.y -= x / 2;
    b.x += x;
    b.y -= x / 4;
    c.x += x;
    c.y -= x / 2;

    CadelObject triangle = cadel_object(a, b, c, a);

    cadel_clear(canvas);
    cadel_render_object(canvas, triangle);
    print_canvas(canvas);

    nanosleep({0, 200000}, NULL);
}

int main(int argc, const char *argv[])
{
    CadelCanvas canvas = cadel_canvas(cols, rows);
    size_t max = 20;

    size_t x = 0;
    while (1) {
        for (; x < max; x++) {
            draw(canvas, x);
        }
        for (; x > -max; x--) {
            draw(canvas, x);
        }
    }

    return 0;
}
