#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int num = atoi(argv[1]);
    if (num < 100)
        printf("Less than 100.\n");
    else
        printf("Greater than or equal to 100.\n");
}
