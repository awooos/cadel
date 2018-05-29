#ifndef CADEL_H
#define CADEL_H

#include <stddef.h>
#include <stdint.h>

typedef void *(CadelMallocFn)(size_t size);
typedef void (CadelFreeFn)(void *ptr);

typedef struct cadel_memory_manager_functions_s {
    CadelMallocFn *malloc;
    CadelFreeFn *free;
} CadelMemoryManagerFunctions;

typedef struct cadel_point_s {
    uint32_t x;
    uint32_t y;
} CadelPoint;

typedef CadelPoint CadelGraph[1024];

void cadel_init(CadelMallocFn *mallocfn, CadelFreeFn *freefn);

#define cadel_graph(...) ((CadelGraph){__VA_ARGS__})

#endif
