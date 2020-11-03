#include <stdio.h>

#define BUF_LEN 15

int main()
{
    FILE* fp = fopen("values.txt", "r");
    int x, numRead;
    float y;
    char z, buf[BUF_LEN];
    numRead = fscanf(fp, "%d %s %f", &x, buf, &y);
    printf("numRead: %d\n", numRead);
    printf("x: %d\n", x);
    printf("buf: %s\n", buf);
    printf("y: %f\n", y);
    printf("===\n");
    // Note leading whitespace in format string
    // since reading character and want to ignore
    // whitespace.
    numRead = fscanf(fp, " %c", &z);  
    printf("numRead: %d\n", numRead);
    printf("z: %c\n", z);
    printf("===\n");
    numRead = fscanf(fp, "%s", buf);
    printf("numRead: %d\n", numRead);
    printf("buf: %s\n", buf);
    printf("===\n");
    // Leading whitespace in format string
    // for reading the character.
    numRead = fscanf(fp, " %c %d", &z, &x);
    printf("numRead: %d\n", numRead);
    printf("z: %c\n", z);
    printf("x: %d\n", x);
    printf("===\n");
    // fscanf() returns EOF when end-of-file is reached.
    // EOF is likely -1, but you should not depend on that and should
    // instead use EOF.
    // fscanf() returns 0 if it tries to read a value that does not match
    // the format specifier, but that is different from reaching the end
    // of the file.
    numRead = fscanf(fp, "%d", &x);  // no more to read
    printf("numRead: %d\n", numRead);
    fclose(fp);
}
