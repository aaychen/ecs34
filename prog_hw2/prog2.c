#include "prog2.h"
#include <stdio.h>
#include <stdbool.h>

void sum3(int a, int b, int c, int *sum) {
    if (sum) {
        *sum = a+b+c; // dereference sum and assign
    }
    return;
}


void replaceIfHigher(long* arr, unsigned len) {
    long userInput;
    for (int i = 0; i < len; i++) {
        scanf("%ld", &userInput);
        if (userInput > arr[i]) {
            arr[i] = userInput;
        }
    }
    return;
}


int performShiftCipher(char* text, int k) {
    if (!text || !(-500 <= k && k <= 500)) {
        return 0;
    }
    // loop until null terminator reached
    int i = 0;
    char currentChar = text[i];
    int minASCII = '0', maxASCII = '0';
    while (currentChar != '\0') {
        // check if item is a number, lowercase letter, or uppercase letter using ascii values

        if ('0' <= currentChar && currentChar <= '9') {
            minASCII = '0';
            maxASCII = '9';
        } else if ('a' <= currentChar && currentChar <= 'z') {
            minASCII = 'a';
            maxASCII = 'z';
        } else if ('A' <= currentChar && currentChar <= 'Z') {
            minASCII = 'A';
            maxASCII = 'Z';
        } else goto increment;

        // check for positive or negative k
        if (k > 0) {
            // check for wrapping
            if (currentChar + k > maxASCII) { 
                int range = maxASCII - minASCII + 1; // takes range # of shifts to get back to currentChar
                int excessShift = k % range; // excessShift < range
                if (currentChar + excessShift > maxASCII) {
                    // text[i] = minASCII + (currentChar + excessShift - maxASCII); // works for most letters
                    int lastWrap = currentChar + excessShift - maxASCII; // # of shifts past maxASCII, 1 means wrap to minASCII
                    text[i] = minASCII + lastWrap - 1; // works for all letters and numbers
                } else text[i] += excessShift;
            } else text[i] += k;
        } else if (k < 0) {
            if (currentChar + k < minASCII) {
                int range = maxASCII - minASCII + 1;
                int excessShift = k % range; // excessShift < range in magnitude and excessShift <= 0
                if (currentChar + excessShift < minASCII) {
                    // text[i] = maxASCII - (minASCII - (currentChar + excessShift)); // works for most letters
                    int lastWrap = minASCII - (currentChar + excessShift); // # of shifts past minASCII, 1 means wrap to maxASCII
                    text[i] = maxASCII - lastWrap + 1; // works for all letters and numbers
                } else text[i] += excessShift;
            } else text[i] += k;
        } // else k == 0, do nothing

        increment:
        i++;
        currentChar = text[i];
    }
    return 1;
}

/*
char* strrstr(char* haystack, char* needle) {
    return;
}

int eachContains(char** strings, char target, unsigned numStrings, char** firstOffending) {

}*/