#//\
    cd $(dirname $0) && clang -std=c11 -pedantic-errors -Wall -I../include simple.c ../src/*.c -o example-simple && ./example-simple && rm example-simple; exit $?

#include <cadel.h>
#include <stdio.h>

int main()
{
    CadelDisplay display = cadel_display(10, 20);

    CadelGraph triangle = (CadelGraph){
        display.dimensions,
        4,
        { {2, 15}, {6, 2}, {6, 18},
          {2, 15} }
    };

    for (size_t i = 0; i < triangle.size; i++) {
        CadelPoint *point = &(triangle.points[i]);
        printf("triangle.points[%lu] = {%lu, %lu}\n", i, point->x, point->y);
    }

    cadel_rasterize(&display, &triangle);

    for (size_t x = 0; x < display.dimensions.width; x++) {
        for (size_t y = 0; y < display.dimensions.height; y++) {
            if (display.data[x + (y * triangle.dimensions.width)] == 0) {
                printf("-");
            } else {
                printf("X");
            }
        }
        printf("\n");
    }

    return 0;
}
