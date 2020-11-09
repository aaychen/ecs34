#include "prog3.h"

#include <stdio.h>
#include <stdlib.h>

#include <assert.h>

void reportIfClassmates(const struct Student *s1,
                        const struct Student *s2)
{
    char* tmp = "";
    if (!areClassmates(s1, s2))
        tmp = "not ";
    printf("%s and %s are %sclassmates.\n", s1->name, s2->name, tmp);
}

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        fprintf(stderr,
                "%s requires three file names as command-line arguments.\n",
                argv[0]);
        exit(1);
    }
    struct Student* s1 = loadStudent(argv[1]);
    printStudent(s1);
    struct Student* s2 = loadStudent(argv[2]);
    printStudent(s2);
    reportIfClassmates(s1, s2);
    struct Student* s3 = loadStudent(argv[3]);
    printStudent(s3);
    reportIfClassmates(s1, s3);
    reportIfClassmates(s2, s3);
    freeStudent(&s1);
    freeStudent(&s2);
    freeStudent(&s3);

    // own tests
    printf("===\n");
    s1 = NULL;
    printStudent(s1);
    if (s1 == NULL) printf("(null pointer)\n");
    s2 = loadStudent(argv[2]);
    assert(areClassmates(s1, s2) == 0);
    freeStudent(&s1);
    freeStudent(&s2);
    
    printf("===\n");
    s1 = loadStudent("nonexistentFile.txt");
    printStudent(s1);
    if (s1 == NULL) printf("(null pointer)\n");
    freeStudent(&s1);

    printf("===\n");
    s1 = loadStudent("student_files/student1.txt");
    printStudent(s1);
    s2 = loadStudent("student_files/student2.txt");
    printStudent(s2);
    s3 = loadStudent("student_files/student3.txt");
    printStudent(s3);
    reportIfClassmates(s1, s2);
    reportIfClassmates(s2, s3);
    reportIfClassmates(s1, s3);
    freeStudent(&s1);
    freeStudent(&s2);
    freeStudent(&s3);
}
