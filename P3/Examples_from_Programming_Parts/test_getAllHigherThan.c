#include "prog3.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int arr[] = {18, 12, 22, 37, 15};
    unsigned newArrlen = 0;
    int* higherThan = getAllHigherThan(arr, 5, 15, &newArrlen);
    for (unsigned i = 0; i < newArrlen; ++i)
        printf("Index %u: %d\n", i, higherThan[i]);
    free(higherThan);
    printf("===\n");
    int arr2[] = {38, 15, 16, 22, 9, 32, 25, 20};
    higherThan = getAllHigherThan(arr2, 8, 19, &newArrlen);
    for (unsigned i = 0; i < newArrlen; ++i)
        printf("Index %u: %d\n", i, higherThan[i]);
    free(higherThan);
}
