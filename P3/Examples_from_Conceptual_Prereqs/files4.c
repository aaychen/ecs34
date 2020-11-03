#include <stdio.h>

int main()
{
    FILE* fp = fopen("tmp/output", "w");
    fputs("Hi there\n", fp);
    fprintf(fp, "%s %d %f\n", "blah", 53, 8.2);
    fclose(fp);
}
