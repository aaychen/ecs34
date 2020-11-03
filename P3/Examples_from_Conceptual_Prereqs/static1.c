#include <stdio.h>

void foo(void)
{
    int x = 0;
    static int y = 0;
    printf("x=%d, y=%d\n", x, y);
    x += 1;
    y += 1;
}

int main()
{
    foo();
    foo();
    foo();
}
