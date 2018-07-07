#//\
    cd $(dirname $0) && clang -std=c11 -I../include simple.c ../src/*.c -o example-simple && ./example-simple && rm example-simple; exit $?

#include <cadel.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    cadel_init(&malloc, &free);

    //CadelGraph triangle = cadel_graph({10, 10}, 3, {0, 1}, {1,2}, {3,4});
    CadelGraph triangle = (CadelGraph){
        {10, 10},
        3,
        { {2, 5}, {6, 2}, {6, 9} }
    };

    printf("triangle.size       = %u\n", triangle.size);
    for (uint32_t i = 0; i < triangle.size; i++) {
        CadelPoint *point = &(triangle.points[i]);
        printf("triangle.points[%u] = {%u, %u}\n", i, point->x, point->y);
    }

    uint8_t dpy[10 * 10] = {0,};

    cadel_rasterize((CadelDimensions){10, 10}, dpy, &triangle);

    for (size_t x = 0; x < 10; x++) {
        for (size_t y = 0; y < 10; y++) {
            printf("%s", (dpy[x + (y * triangle.dimensions.width)] == 0) ? "-" : "X");
        }
        printf("\n");
    }

    return 0;
}
