#include "prog2.h"
#include <stdio.h>

int strLen(char* seq);

void sum3(int a, int b, int c, int *sum) {
    if (sum) *sum = a+b+c; // dereference sum and assign
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
    if (!text || !(-500 <= k && k <= 500)) return 0;
    // loop until null terminator reached
    int i = 0;
    char currentChar = text[i];
    int minASCII = '0', maxASCII = '0';
    while (currentChar != '\0') {
        // check if item is a number, lowercase letter, or uppercase letter using ASCII values
        if ('0' <= currentChar && currentChar <= '9') {
            minASCII = '0';
            maxASCII = '9';
        } else if ('a' <= currentChar && currentChar <= 'z') {
            minASCII = 'a';
            maxASCII = 'z';
        } else if ('A' <= currentChar && currentChar <= 'Z') {
            minASCII = 'A';
            maxASCII = 'Z';
        } else goto nextChar;

        int range = maxASCII - minASCII + 1;
        int numShift = k % range;
        int shiftASCII = currentChar + numShift;
        // Check for positive or negative k
        if (k > 0) {
            // Check for wrapping
            if (shiftASCII > maxASCII) {
                int lastWrap = shiftASCII - maxASCII; // # of shifts past maxASCII, 1 means wrap to minASCII
                text[i] = minASCII + lastWrap - 1;

            } else text[i] += numShift;
        } else if (k < 0) {
            if (shiftASCII < minASCII) {
                int lastWrap = minASCII - shiftASCII; // # of shifts past minASCII, 1 means wrap to maxASCII
                text[i] = maxASCII - lastWrap + 1; 
            } else text[i] += numShift;
        } // else k == 0, do nothing

        nextChar:
        currentChar = text[++i];
    }
    return 1;
}

char* strrstr(char* haystack, char* needle) {
    int lenHaystack = strLen(haystack);
    int lenNeedle = strLen(needle);
    int needleIndex = lenNeedle - 1;
    // iterate through haystack backwards and compare chars with needle
    for (int i = lenHaystack - 1; i >= 0; i--) {
        // if charHaystack == charNeedle, decrement needleIndex
        // if charHaystack != charNeedle, reset needleIndex
        needleIndex = (haystack[i] == needle[needleIndex]) ? (needleIndex - 1) : (lenNeedle - 1);
        // if needleIndex == -1, return a pointer to wherever i is in haystack
        if (needleIndex == -1) {
            return &haystack[i];
        }
    }
    return NULL;
}

int eachContains(char** strings, char target, unsigned numStrings, char** firstOffending) {
    char strTarget[] = {target, '\0'}; // turn target into a string to use strrstr() function
    // iterate over each item in strings
    for (int i = 0; i < numStrings; i++) {
        if (strrstr(strings[i], strTarget) == NULL) { // no null terminator for target
            *firstOffending = strings[i];
            return 0;
        }
    }
    return 1;
}

int strLen(char* seq) {
    if (!seq) return 0;
    int i = 0;
    char ch = seq[i];
    while (ch != '\0') {
        ch = seq[++i];
    }
    return i;
}