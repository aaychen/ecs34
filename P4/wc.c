#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LEN 300
#define BUF_LEN (MAX_LINE_LEN + 2)

//  FILE #2 TO SUBMIT

// NEED TO ADD TEST CASES
    // REMOVE TEST CASES WHEN SUBMITTING FILE

int readFlags(int argc, char *argv[]);
struct FileRecord* loadRecord(const char* fileName);
int printFileRecord(struct FileRecord* frPtr, int format);
void printTotal(int format);
int freeFileRecord(struct FileRecord* frPtr);

struct FileRecord {
    char* fileName;
    int numChars;
    int numWords;
    int numLines;
};

int totalChars = 0, totalWords = 0, totalLines = 0;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "No file provided.\n");
        return 2;
    }
    int isSuccess = 1, seenFile = 0;
    int outputFormat = 0, numFiles = 0;
    outputFormat = readFlags(argc, argv);
    for (int i = 1; i < argc; i++) {
        char *temp = argv[i];
        if (temp[0] != '-') {
            seenFile = 1;
            struct FileRecord* frPtr = loadRecord(temp);
            numFiles++;
            if (frPtr) {
                totalChars += frPtr->numChars;
                totalWords += frPtr->numWords;
                totalLines += frPtr->numLines;
            } else isSuccess = 0;
            printFileRecord(frPtr, outputFormat);
            freeFileRecord(frPtr);
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

/**
 * Parses command line arguments for flags and determines which output format to use 
 * when printing out details of the file.
 * 
 * @param argc Length of argv
 * @param argv Array of command line arguments
 * @return Output format
 */
int readFlags(int argc, char *argv[]) {
    int format = 0;
    int seenCharsFlag = 0, seenWordsFlag = 0, seenLinesFlag = 0;
    for (int i = 1; i < argc; i++) {
        char *temp = argv[i];
        if (temp[0] == '-') {
            if (strlen(temp) > 1 && temp[1] != '-') {
                for (int j = 1; j < strlen(temp); j++) {
                    if (!seenCharsFlag && temp[j] == 'm') {
                        format += 1;
                        seenCharsFlag = 1;
                    } else if (!seenWordsFlag && temp[j] == 'w') {
                        format += 2;
                        seenWordsFlag = 1;
                    } else if (!seenLinesFlag && temp[j] == 'l') {
                        format += 4;
                        seenLinesFlag = 1;
                    }
                }
            } else {
                if (!seenCharsFlag && !strcmp(temp, "--chars")) {
                    format += 1;
                    seenCharsFlag = 1;
                } else if (!seenWordsFlag && !strcmp(temp, "--words")) {
                    format += 2;
                    seenWordsFlag = 1;
                } else if (!seenLinesFlag && !strcmp(temp, "--lines")) {
                    format += 4;
                    seenLinesFlag = 1;
                }
            }
        }
    }
    return format;
}

/**
 * Finds the number of lines, words and characters and creates a pointer to an 
 * instance of FileRecord to store the details and the file name.
 * 
 * @param fileName The name of the file of interest
 * @return NULL if fileName is NULL or does not exist; otherwise, pointer to 
 * the FileRecord instance
 */
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
    int prevIsSpace = 1;
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

/**
 * Prints the details of the FileRecord instance that's referenced by frPtr according 
 * to the format specified by flags the user provided.
 * 
 * @param frPtr References the FileRecord instance
 * @param format The output format to follow
 * @return 1 if frPtr is NULL; 0 otherwise
 */
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

/**
 * Prints all files' details combined according to the format specified by the flags 
 * the user provided.
 * 
 * @param format The output format to follow
 */
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

/**
 * Deallocates all space associated with frPtr.
 * 
 * @param frPtr The reference to the FileRecord instance
 * @return 0 if frPtr is NULL; 1 otherwise
 */
int freeFileRecord(struct FileRecord* frPtr) {
    if (!frPtr) return 0;
    free(frPtr->fileName);
    free(frPtr);
    return 1;
}
