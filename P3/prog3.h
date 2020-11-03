#ifndef PROG3_H  // we'll talk about "header guards" later
#define PROG3_H

#define MAX_LINE_LEN 40

/**
 * Question for the student: It is good form to put parentheses around the
 * macro's value when that value is an arithmetic expression.
 * Why do you suppose this is? Think about where such a macro (not necessarily
 * BUF_LEN below) could possibly be used, and remember that macros perform
 * a textual substitution akin to find-and-replace without consideration
 * of the textual context.
 */
#define BUF_LEN (MAX_LINE_LEN + 2)

int parseForHighest(const char* filename, int* highest);

int* getAllHigherThan(const int* arr, unsigned arrlen,
                      int threshold, unsigned* newArrlen);

char* strtok_c(const char* str, const char* delim);

struct Student
{
    char* name;
    unsigned numCurrCourses;
    char** currCourses;
    unsigned numPrevCourses;
    char** prevCourses;
};

struct Student* loadStudent(const char* studentFilename);

void printStudent(const struct Student* s);

void freeStudent(struct Student** s);

int areClassmates(const struct Student* s1, const struct Student* s2);

#endif // PROG3_H
