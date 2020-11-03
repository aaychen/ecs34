#include <stdio.h>

void snackMachine();

int main() {
    snackMachine();
    return 0;
}

void snackMachine() {
    float total = 0;
    char ch;
    while (1) {
        printf("Machine currently has $%.2f in it.\n", total);
        printf("Enter: ");
        scanf(" %c", &ch);

        // if user enters 's', terminate loop
        if (ch == 's') {
            printf("Have a nice day.\n");
            break;
        }

        switch (ch) {
            case 'q':
                total += 0.25;
                break;
            case 'd':
                total += 0.10;
                break;
            case 'n':
                total += 0.05;
                break;
            case 'p':
                total += 0.01;
                break;
            case 'l':
                if (total >= 2.00) {
                    printf("Enjoy your Lay's chips.\n");
                    total -= 2.00;
                } else {
                    printf("You need $%.2f more to afford Lay's chips.\n", 2.00-total);
                }
                break;
            case 'r':
                if (total >= 2.25) {
                    printf("Enjoy your Ruffles chips.\n");
                    total -= 2.25;
                } else {
                    printf("You need $%.2f more to afford Ruffles chips.\n", 2.25-total);
                }
                break;
            case 'k':
                if (total >= 1.50) {
                    printf("Enjoy your Kit Kat candy.\n");
                    total -= 1.50;
                } else {
                    printf("You need $%.2f more to afford a Kit Kat.\n", 1.50-total);
                }
                break;
            default:
                printf("Invalid input.\n");
                break;
            }
    }
    return;
}