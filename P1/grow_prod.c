#include <stdio.h>

void growProd();

int main() {
    growProd();
    return 0;
}

void growProd() {
    int num1, num2, num3, prod;
    int count = 0; // to keep track of whether to reassign num1 or num2's value
    printf("Enter first integer: ");
    scanf("%d", &num1);
    printf("Enter second integer: ");
    scanf("%d", &num2);
    do {
        prod = num1 * num2;
        printf("Enter another integer: ");
        scanf("%d", &num3);
        count++;
        // Reassign num1 or num2 accordingly
        if (count % 2 == 1) {
            num1 = num3;
        } else {
            num2 = num3;
        }
    } while (num3 > prod); // Prompt for integer until input is not greater than the product of last 2 integers
    return;
}