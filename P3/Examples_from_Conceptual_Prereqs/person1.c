#include <stdio.h>

struct Person
{
    int age;
    char* firstName;
    char* lastName;
};

void printFullName(struct Person p)
{
    printf("Full name: %s %s\n", p.firstName, p.lastName);
}

int main()
{
    struct Person p1 = {35, "John", "Johnson"};
    printf("%d %s %s\n", p1.age, p1.firstName, p1.lastName);
    printFullName(p1);
    struct Person p2 = {48, "Rich", "Richards"};
    printFullName(p2);
}
