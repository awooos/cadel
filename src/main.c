#include <cadel.h>

CadelMemoryManagerFunctions mmfns;

void cadel_init(CadelMallocFn *mallocfn, CadelFreeFn *freefn)
{
    mmfns.malloc = mallocfn;
    mmfns.free = freefn;

//    cadel_platform_init(&mmfns);
}
