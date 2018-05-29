#//\
    cd $(dirname $0) && clang -std=c11 -I../include simple.c ../src/*.c -o example-simple && ./example-simple && rm example-simple; exit $?

#include <cadel.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    cadel_init(&malloc, &free);

    CadelGraph triangle = cadel_graph({0, 1}, {1,2}, {3,4});

    printf("triangle[0] = {%u, %u}\n", triangle[0].x, triangle[0].y);
    printf("triangle[1] = {%u, %u}\n", triangle[1].x, triangle[1].y);
    printf("triangle[2] = {%u, %u}\n", triangle[2].x, triangle[2].y);

    return 0;
}
