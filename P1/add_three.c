#include <stdio.h>

void addThree();

int main() {
    addThree();
    return 0;
}

void addThree() {
    int num1, num2, num3;
    printf("Enter first integer: ");
    scanf("%d", &num1);
    printf("Enter second integer: ");
    scanf("%d", &num2);
    printf("Enter third integer: ");
    scanf("%d", &num3);
    printf("The sum is: %d\n", num1+num2+num3);
    return;
}