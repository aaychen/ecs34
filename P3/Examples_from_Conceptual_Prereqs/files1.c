#include <stdio.h>

// Effectively means 98, because of the newline character (which fgets() reads)
// and the null terminator.
#define MAX_LINE_SIZE 100

int main()
{
    FILE* fp = fopen("poem.txt", "r");
    char buf[MAX_LINE_SIZE];
    int lineCounter = 0;
    while (fgets(buf, MAX_LINE_SIZE, fp))
    {
        // No newline character at end of format string because fgets() already
        // put the newline character at the end of buf.
        printf("Line #%d: %s", lineCounter, buf);
        lineCounter += 1;
    }
    fclose(fp);
    return 0;
}
