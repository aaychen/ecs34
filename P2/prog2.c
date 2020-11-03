#include "prog2.h"
#include <stdio.h>

int strLen(char* seq);

/**
 * Computes sum of a, b, and c and assigns to variable referenced by sum.
 * If sum is null, do nothing.
 * 
 * @param a First addend
 * @param b Second addend
 * @param c Third addend
 * @param sum Pointer to be used to store result of a+b+c
 */
void sum3(int a, int b, int c, int *sum) {
    if (sum) *sum = a+b+c; // dereference sum and assign
    return;
}

/**
 * Replaces corresponding long integers in arr if user inputted a larger long.
 * 
 * @param arr Array of long integers potentially to be replaced
 * @param len The length of arr
 */
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

/**
 * Implements shift/Caesar cipher, a symmetric algorithm of cryptography. Shifts digits, 
 * lowercase characters, uppercase characters in text by k amount. Characters wrap around 
 * if target range of ASCII values (digit/lowercase/uppercase) is exceeded.
 * 
 * @param text The string of characters to be encrypted/decrypted
 * @param k Number of shifts to make; must be in range [-500, 500]
 * @return 1 if encryption/decryption is successful; else 0
 */
int performShiftCipher(char* text, int k) {
    if (!text || !(-500 <= k && k <= 500)) return 0;
    int textLen = strLen(text);
    char currentChar;
    int minASCII, maxASCII;
    // iterate over each char in text
    for (int i = 0; i < textLen; i++) {
        currentChar = text[i];
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
        } else continue;

        int range = maxASCII - minASCII + 1;
        int numShift = k % range;
        int shiftASCII = currentChar + numShift; // shiftASCII -> position after shifting by numShift
        // check for positive or negative k
        if (k > 0) {
            // check for wrapping
            if (shiftASCII > maxASCII) {
                int lastWrap = shiftASCII - maxASCII; // # of shifts past maxASCII, 1 means wrap to minASCII
                text[i] = minASCII + lastWrap - 1;
            } else text[i] += numShift;
        } else if (k < 0) {
            if (shiftASCII < minASCII) {
                int lastWrap = minASCII - shiftASCII;
                text[i] = maxASCII - lastWrap + 1; 
            } else text[i] += numShift;
        } // else k == 0, do nothing
    }
    return 1;
}

/**
 * Finds the last occurrence of needle in haystack and returns it.
 * 
 * @param haystack The string to search through
 * @param needle The targeted string to search for
 * @return a pointer to last occurrence of needle in haystack; NULL if no occurrence
 */
char* strrstr(char* haystack, char* needle) {
    int haystackLen = strLen(haystack);
    int needleLen = strLen(needle);
    int needleIndex = needleLen - 1;
    // iterate through haystack backwards and compare chars with needle
    for (int i = haystackLen - 1; i >= 0; i--) {
        // if charHaystack == charNeedle, needleIndex--; else reset needleIndex
        needleIndex = (haystack[i] == needle[needleIndex]) ? (needleIndex - 1) : (needleLen - 1);
        if (needleIndex == -1) { // if needle's found, return the position
            return &haystack[i];
        }
    }
    return NULL;
}

/**
 * Determines if each string in strings contains target. The first string that does not
 * contain target will be stored in the char pointer referenced by firstOffending.
 * 
 * @param strings The array of strings to search
 * @param target The character to look for in each string
 * @param numStrings Length of strings
 * @param firstOffending Reference to char pointer used to store first string that fails
 * @return 1 if all strings contain target; 0 if one doesn't
 */
int eachContains(char** strings, char target, unsigned numStrings, char** firstOffending) {
    char strTarget[] = {target, '\0'}; // turn target into a string to use strrstr() function
    // iterate over each item in strings
    for (int i = 0; i < numStrings; i++) {
        if (strrstr(strings[i], strTarget) == NULL) {
            *firstOffending = strings[i];
            return 0;
        }
    }
    return 1;
}

/**
 * Returns length of seq.
 * 
 * @param seq String in question
 * @return the length of seq
 */
int strLen(char* seq) {
    if (!seq) return 0;
    int i = 0;
    char ch = seq[i];
    while (ch != '\0') {
        ch = seq[++i];
    }
    return i;
}