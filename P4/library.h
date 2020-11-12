#ifndef LIBRARY_H
#define LIBRARY_H

#define MAX_LINE_LEN 300

// Additional space for newline character and null byte.
#define BUF_LEN (MAX_LINE_LEN + 2)

struct Book
{
    char* title;
    char* author;  // or authors
    int year;  // of publishing
};

struct Library
{
    struct Book* books;
    int numBooks;
};

struct Library* loadLibrary(const char* filename);

int printLibrary(const struct Library* library);

int countCommonTitles(const struct Library* lib1,
                      const struct Library* lib2);

int freeLibrary(struct Library* library);

#endif // LIBRARY_H
