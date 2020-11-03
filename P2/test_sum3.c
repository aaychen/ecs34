#include "prog2.h"

#include <stdio.h>

int main()
{
    int s;
    sum3(4, 10, -1, &s);
    printf("%d\n", s);
    sum3(0, 2, -10, &s);
    printf("%d\n", s);
}
