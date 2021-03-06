#include <cadel.h>
#include <stdio.h>

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

int main()
{
    CadelCanvas canvas = cadel_canvas(20, 10);

    CadelObject triangle = cadel_object(
            {15, 2},
            { 2, 6},
            {18, 6},
            {15, 2});

    CadelObject parallelogram = cadel_object(
            { 6, 1},
            {18, 1},
            {11, 8},
            { 0, 8},
            { 6, 1});

    printf("Triangle:\n");
    printf("  (15, 2) - (2, 6) - (18, 6) - (15, 2)\n");
    cadel_clear(canvas);
    cadel_render_object(canvas, triangle);
    print_canvas(canvas);

    printf("Parallelogram:\n");
    printf("  (6, 1) - (18, 1) - (11, 8) - (0, 8) - (6, 1)\n");
    cadel_clear(canvas);
    cadel_render_object(canvas, parallelogram);
    print_canvas(canvas);

    printf("Clusterfuck (aka \"all of the above\"):\n");
    cadel_render_object(canvas, triangle);
    print_canvas(canvas);

    return 0;
}
