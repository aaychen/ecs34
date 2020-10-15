#include <stdio.h>

void getThree();

int main() {
    getThree();
    return 0;
}

void getThree() {
    char ch1, ch2, ch3;
    printf("Enter first character: ");
    scanf(" %c", &ch1);
    printf("You just entered %c. Enter second character: ", ch1);
    scanf(" %c", &ch2);
    printf("You just entered %c. Enter third character: ", ch2);
    scanf(" %c", &ch3);
    printf("Backwards, the three characters are %c%c%c.\n", ch3, ch2, ch1);
    return;
}