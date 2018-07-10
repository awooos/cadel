#//\
    cd $(dirname $0) && clang -std=c11 -pedantic-errors -Wall -I../include simple.c ../src/*.c -o example-simple && ./example-simple && rm example-simple; exit $?

#include <cadel.h>
#include <stdio.h>

int main()
{
    CadelDisplay display = cadel_display(20, 10);

    CadelObject triangle = {
        display.dimensions,
        4,
        { {15, 2}, {2, 6}, {18, 6},
          {15, 2} }
    };

    cadel_render(&display, &triangle);

    for (size_t y = 0; y < display.dimensions.height; y++) {
        for (size_t x = 0; x < display.dimensions.width; x++) {
            if (cadel_get_pixel(&display, x, y) == 0) {
                printf("-");
            } else {
                printf("X");
            }
        }
        printf("\n");
    }

    return 0;
}
