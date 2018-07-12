#define __USE_BSD
#define _DEFAULT_SOURCE

#include <cadel.h>
#include <stdio.h>
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

#define rows 39
#define cols 79

CadelPoint a = {10, 20};
CadelPoint b = {40, 10};
CadelPoint c = {57, 12};

CadelPoint rotate(CadelCanvas cs, CadelPoint p)
{
    if (p.y <= (cs.height / 2)) { // top half.
        if (p.x < (cs.width / 2)) {
            // top-left quadrant.
            if (p.x > 0) {
                p.x--;
            }
            p.y++;
        } else {
            // top-right quadrant.
            if (p.x < cs.width) {
                p.x--;
            }
            if (p.y > 1) {
                p.y--;
            }
        }
    } else { // bottom half.
        if (p.x < (cs.width / 2)) {
            // bottom-left quadrant.
            p.x++;
            if (p.y < (cs.height - 1)) {
                p.y++;
            }
        } else {
            // bottom-right quadrant.
            if (p.x < (cs.width - 1)) {
                p.x++;
            } else {
                p.x--;
            }
            if (p.y < (cs.height * 4 / 3)) {
                p.y--;
            } else {
                p.y++;
            }
        }
    }

    return p;
}

void draw(CadelCanvas canvas)
{
    a = rotate(canvas, a);
    b = rotate(canvas, b);
    c = rotate(canvas, c);

    CadelObject triangle = cadel_object(a, b, c, a);

    cadel_clear(canvas);
    cadel_render_object(canvas, triangle);
    print_canvas(canvas);

    usleep(30000);
}

int main(int argc, const char *argv[])
{
    CadelCanvas canvas = cadel_canvas(cols, rows);

    while (1) {
        draw(canvas);
    }

    return 0;
}
