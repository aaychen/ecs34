#include "prog2.h"

#include <stdio.h>

int main()
{
    char* strings[] = {"abcde", "hi there aaron", "apple", "banana"};
    char* firstOffending;
    if (eachContains(strings, 'a', 4, &firstOffending))
        printf("AAA\n");
    else
        printf("firstOffending: %s\n", firstOffending);
    if (eachContains(strings, 'b', 4, &firstOffending))
        printf("BBB\n");
    else
        printf("firstOffending: %s\n", firstOffending);
    if (eachContains(strings, 'e', 4, &firstOffending))
        printf("CCC\n");
    else
        printf("firstOffending: %s\n", firstOffending);
}
