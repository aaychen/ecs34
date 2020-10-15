#include "prog2.h"

#include <stdio.h>

int main()
{
    long vals[] = {583, 3000000000, 14, 6};
    replaceIfHigher(vals, 4);
    printf("=== vals ===\n");
    for (unsigned i = 0; i < 4; ++i)
        printf("vals[ %u ] is %ld\n", i, vals[i]);
}
