#//\
    cd $(dirname $0) && clang -std=c11 -pedantic-errors -Wall -I../include simple.c ../src/*.c -o example-simple && ./example-simple && rm example-simple; exit $?

#include <cadel.h>
#include <stdio.h>

int main()
{
    CadelCanvas canvas = cadel_canvas(20, 10);

    CadelObject triangle = cadel_object(
            {15, 2},
            {2, 6},
            {18, 6},
            {15, 2});

    cadel_clear(canvas);
    cadel_render_object(canvas, triangle);

    for (size_t y = 0; y < canvas.height; y++) {
        for (size_t x = 0; x < canvas.width; x++) {
            if (cadel_get_pixel(canvas, x, y) == 0) {
                printf("-");
            } else {
                printf("X");
            }
        }
        printf("\n");
    }

    return 0;
}
