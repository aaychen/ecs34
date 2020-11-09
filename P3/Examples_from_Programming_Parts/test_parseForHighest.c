#include "prog3.h"

#include <stdio.h>

int main()
{
    int highest = 0, retval = 0;
    retval = parseForHighest("values1.txt", &highest);
    printf("retval: %d\n", retval);
    printf("highest: %d\n", highest);
    retval = parseForHighest(NULL, &highest);
    printf("retval: %d\n", retval);
    retval = parseForHighest("values1.txt", NULL);
    printf("retval: %d\n", retval);


    // own tests
    highest = 0;
    retval = parseForHighest("values2.txt", &highest);
    printf("retval: %d\n", retval);
    printf("highest: %d\n", highest);

    highest = 0;
    retval = parseForHighest("nonexistentFile.txt", &highest);
    printf("retval: %d\n", retval);
    printf("highest: %d\n", highest);
}
