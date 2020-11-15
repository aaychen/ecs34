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

int readFlags(char* flagArg);
struct FileRecord* loadRecord(const char* fileName);
int printFileRecord(struct FileRecord* fr, int format);
void printTotal(int format);
int freeFileRecord(struct FileRecord** frPtr);

struct FileRecord {
    char* fileName;
    int numChars;
    int numWords;
    int numLines;
};

int seenCharsFlag = 0, seenWordsFlag = 0, seenLinesFlag = 0;
int totalChars = 0, totalWords = 0, totalLines = 0;

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
    int outputFormat = 0, numFiles = 0;
    for (int i = 1; i < argc; i++) {
        char *temp = argv[i];
        if (!seenFile && temp[0] == '-') { // if item starts with '-', flag
            outputFormat += readFlags(temp);
        }
        else { // if no '-', file name
            seenFile = 1;
            struct FileRecord* frPtr = loadRecord(temp);
            numFiles++;
            if (frPtr) {
                totalChars += frPtr->numChars;
                totalWords += frPtr->numWords;
                totalLines += frPtr->numLines;
            } else isSuccess = 0;
            printFileRecord(frPtr, outputFormat);
            freeFileRecord(&frPtr);
        }
    }
    if (numFiles > 1) printTotal(outputFormat);
    if (!seenFile) {
        fprintf(stderr, "No file provided.\n");
        return 2;
    }
    if (!isSuccess) return 1;
    return 0;
}

int readFlags(char* flagArg) {
    int res = 0;
    if (strlen(flagArg) > 1 && flagArg[1] != '-') {
        for (int j = 1; j < strlen(flagArg); j++) {
            if (!seenCharsFlag && flagArg[j] == 'm') {
                res += 1;
                seenCharsFlag = 1;
            } else if (!seenWordsFlag && flagArg[j] == 'w') {
                res += 2;
                seenWordsFlag = 1;
            } else if (!seenLinesFlag && flagArg[j] == 'l') {
                res += 4;
                seenLinesFlag = 1;
            }
        }
    } else {
        if (!seenCharsFlag && !strcmp(flagArg, "--chars")) {
            res += 1;
            seenCharsFlag = 1;
        } else if (!seenWordsFlag && !strcmp(flagArg, "--words")) {
            res += 2;
            seenWordsFlag = 1;
        } else if (!seenLinesFlag && !strcmp(flagArg, "--lines")) {
            res += 4;
            seenLinesFlag = 1;
        }
    }
    return res;
}

// when is the "Permission denied" error message??
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
    strcpy(frPtr->fileName, fileName);
    char ch = fgetc(fp);
    if (!ch) {
        perror("fopen");
        return frPtr;
    }
    int prevIsSpace = 0;
    int numLines = 0, numWords = 0, numChars = 0;
    while (ch != EOF) {
        if (ch == '\n') numLines++;
        numChars++;
        if (isspace(ch)) {
            if (!prevIsSpace) {
                numWords++;
                prevIsSpace = 1;
            }
        } else prevIsSpace = 0;
        ch = fgetc(fp);
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
int printFileRecord(struct FileRecord* frPtr, int format) {
    if (!frPtr) return 1;
    switch (format) {
        case 1: // case 'm'
            printf("%s: %d\n", frPtr->fileName, frPtr->numChars);
            break;
        case 2: // case 'w'
            printf("%s: %d\n", frPtr->fileName, frPtr->numWords);
            break;
        case 4: // case 'l'
            printf("%s: %d\n", frPtr->fileName, frPtr->numLines);
            break;
        case 3: // -wm
            printf("%s: %d %d\n", frPtr->fileName, frPtr->numWords, frPtr->numChars);
            break;
        case 5: // -lm
            printf("%s: %d %d\n", frPtr->fileName, frPtr->numLines, frPtr->numChars);
            break;
        case 6: // -lw
            printf("%s: %d %d\n", frPtr->fileName, frPtr->numLines, frPtr->numWords);
            break;
        default: // no flags, or all flags
            printf("%s: %d %d %d\n", frPtr->fileName, frPtr->numLines, frPtr->numWords, frPtr->numChars);
            break;
    }
    return 0;
}

void printTotal(int format) {
    switch (format) {
        case 1: // case 'm'
            printf("total: %d\n", totalChars);
            break;
        case 2: // case 'w'
            printf("total: %d\n", totalWords);
            break;
        case 4: // case 'l'
            printf("total: %d\n", totalLines);
            break;
        case 3: // -wm
            printf("total: %d %d\n", totalWords, totalChars);
            break;
        case 5: // -lm
            printf("total: %d %d\n", totalLines, totalChars);
            break;
        case 6: // -lw
            printf("total: %d %d\n", totalLines, totalWords);
            break;
        default: // no flags, or all flags
            printf("total: %d %d %d\n", totalLines, totalWords, totalChars);
            break;
    }
    return;
}

int freeFileRecord(struct FileRecord** frPtr) {
    if(!*frPtr) return 0;
    free((*frPtr)->fileName);
    free(*frPtr);
    *frPtr = NULL;
    return 1;
}
