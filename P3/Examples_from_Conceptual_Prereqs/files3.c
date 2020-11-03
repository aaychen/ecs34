#include <stdio.h>

#define BUF_LEN 15

int main()
{   
    FILE* fp = fopen("goo.txt", "r");
    char buf[BUF_LEN];
    int a, b;
    fscanf(fp, "%s %d %d", buf, &a, &b);
    printf("s=%s, a=%d, b=%d\n", buf, a, b);
    fclose(fp);
    return 0;
}
