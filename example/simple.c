#//\
    cd $(dirname $0) && clang -std=c11 -pedantic-errors -Wall -I../include simple.c ../src/*.c -o example-simple && ./example-simple && rm example-simple; exit $?

#include <cadel.h>
#include <stdio.h>

int main()
{
    CadelImage image = cadel_image(20, 10);

    CadelObject triangle = cadel_object(
        {15, 2},
        {2, 6},
        {18, 6},
        {15, 2});

    cadel_clear(image);
    cadel_render(image, triangle);

    for (size_t y = 0; y < image.height; y++) {
        for (size_t x = 0; x < image.width; x++) {
            if (cadel_get_pixel(image, x, y) == 0) {
                printf("-");
            } else {
                printf("X");
            }
        }
        printf("\n");
    }

    return 0;
}
