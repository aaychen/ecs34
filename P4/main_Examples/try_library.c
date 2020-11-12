#include "library.h"

#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Did not provide two library files.\n");
        return 1;
    }
    char* filename1 = argv[1];
    char* filename2 = argv[2];
    struct Library* lib1 = loadLibrary(filename1);
    struct Library* lib2 = loadLibrary(filename2);
    printf("=== Library 1 ===\n");
    printLibrary(lib1);
    printf("=== Library 2 ===\n");
    printLibrary(lib2);
    printf("\nNo. common titles: %d\n", countCommonTitles(lib1, lib2));
    freeLibrary(lib1);
    freeLibrary(lib2);
}
