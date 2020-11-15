#include "library.h"
#include "circular_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

#define MAX_LINE_LEN 300
#define BUF_LEN (MAX_LINE_LEN + 2)

//  FILE #2 TO SUBMIT

int readFlags(char* flagArg, int format);
struct FileRecord* loadRecord(const char* fileName);
int printFileRecord(struct FileRecord* fr, char format);
int freeFileRecord(struct FileRecord* frPtr);

struct FileRecord {
    char* fileName;
    int numChars;
    int numWords;
    int numLines;
};

int seenCharsFlag = 0, seenWordsFlag = 0, seenLinesFlag = 0;

// NEED TO ADD TEST CASES
    // REMOVE TEST CASES WHEN SUBMITTING FILE
// flags can be:
    // -m
    // -mw
    // -m -w
    // --chars --words
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "No file provided.\n");
        return 2;
    }
    int isSuccess = 1, seenFile = 0;
    int outputFormat = 0;
    for (int i = 1; i < argc; i++) {
        char *temp = argv[i];
        if (!seenFile && temp[0] == '-') { // if item starts with '-', flag
            outputFormat += readFlags(temp, outputFormat);
        }
        else { // if no '-', file name
            seenFile = 1;
            struct FileRecord* frPtr = loadRecord(temp);
            if (!frPtr) isSuccess = 0;
            printFileRecord(frPtr, outputFormat);
            freeFileRecord(&frPtr);
        }
    }
    if (!seenFile) {
        fprintf(stderr, "No file provided.\n");
        return 2;
    }
    if (!isSuccess) return 1;
    return 0;
}

int readFlags(char* flagArg, int format) {
    int resFormat = format;
    if (flagArg[1] != '-') {
        for (int j = 1; j < strlen(flagArg); j++) {
            if (!seenCharsFlag && flagArg[j] == 'm') {
                resFormat += 1;
                seenCharsFlag = 1;
            } else if (seenWordsFlag && flagArg[j] == 'w') {
                resFormat += 2;
                seenWordsFlag = 1;
            } else if (seenLinesFlag && flagArg[j] == 'l') {
                resFormat += 4;
                seenLinesFlag = 1;
            }
        }
    } else {
        if (!seenCharsFlag && !strcmp(flagArg, "--chars")) {
            resFormat += 1;
            seenCharsFlag = 1;
        } else if (seenWordsFlag && !strcmp(flagArg, "--words")) {
            resFormat += 2;
            seenWordsFlag = 1;
        } else if (seenLinesFlag && !strcmp(flagArg, "--lines")) {
            resFormat += 4;
            seenLinesFlag = 1;
        }
    }
    return resFormat;
}

struct FileRecord* loadRecord(const char* fileName) {
    if (!fileName) {
        // need perror() ??
        return NULL;
    }
    FILE* fp = fopen(fileName, "r");
    if (!fp) {
        perror("fopen");
        return NULL;
    }
    struct FileRecord* frPtr = malloc(sizeof(struct FileRecord));
    frPtr->fileName = malloc((strlen(fileName) + 1) * sizeof(char));
    strcpy(fileName, frPtr->fileName);
    char ch;
    int prevIsSpace = 0;
    int numLines = 0, numWords = 0, numChars = 0;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') numLines++;
        numChars++;
        if (isspace(ch)) {
            if (!prevIsSpace) {
                numWords++;
                prevIsSpace = 1;
            }
        } else prevIsSpace = 0;
    }
    frPtr->numLines = numLines;
    frPtr->numWords = numWords;
    frPtr->numChars = numChars;
    fclose(fp);
    return frPtr;
}

// default print format: numLines numWords numChars fileName
// -m or --chars for # of chars (001 = 1)
// -w or --words for # of words (010 = 2)
// -l or --lines for # of lines (100 = 4)
int printFileRecord(struct FileRecord* frPtr, char format) {
    if (!frPtr) return 1;
    switch (format) {
        case 1: // case 'm'
            printf("%s: %d", frPtr->fileName, frPtr->numChars);
            break;
        case 2: // case 'w'
            printf("%s: %d", frPtr->fileName, frPtr->numWords);
            break;
        case 4: // case 'l'
            printf("%s: %d", frPtr->fileName, frPtr->numLines);
            break;
        case 3: // -mw
            break;
        case 5: // -ml
            break;
        case 6: // -wl
            break;
        default: // no flags, or all flags
            printf("%s: %d %d %d\n", frPtr->fileName, frPtr->numLines, frPtr->numWords, frPtr->numChars);
            break;
    }
    return 0;
}

int freeFileRecord(struct FileRecord** frPtr) {
    if (!*frPtr) return 0;
    free(*frPtr->fileName);
    free(*frPtr);
    *frPtr = NULL;
    return 1;
}
