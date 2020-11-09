#include "prog3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assume file contains 1 integer per line
int parseForHighest(const char* filename, int* highest) {
    if (!filename || !highest) return -1;
    FILE* fp = fopen(filename, "r"); // create file pointer
    if (!fp) return -2;
    char buf[BUF_LEN]; // must do this to ensure enough space for file input
    int isFirst = 1, tempMax;
    while (fgets(buf, MAX_LINE_LEN, fp)) { // fgets() returns NULL when nothing left to read
        if (isFirst) {
            isFirst = 0;
            goto newMax;
        }
        if (atoi(buf) > tempMax) {
            newMax: 
            tempMax = atoi(buf);
        }
    }
    fclose(fp);
    *highest = tempMax;
    return 0;
}

int* getAllHigherThan(const int* arr, unsigned arrlen, int threshold, unsigned* newArrlen) {
    if (!arr || !newArrlen) return NULL;
    int arrSize = 1;
    int* resArr = malloc(arrSize * sizeof(int));
    int count = 0;
    // iterate through arr backwards and store into resArr
    for (int i = arrlen-1; i >= 0; i--) {
        int temp = arr[i];
        if (temp > threshold)
            resArr[count++] = temp;
        if (count == arrSize) { // need to resize and allocate more space
            arrSize *= 2;
            resArr = realloc(resArr, arrSize * sizeof(int)); // realloc preserves memory
        }
    }
    *newArrlen = count;
    return resArr;
}

char* strtok_c(const char* str, const char* delim) {
    static const char* searchPtr = NULL;
    static int maxLen = 0; // length of original string to tokenize
    static int currIndex = 0;
    if (str) {
        maxLen = strlen(str);
        currIndex = 0;
        searchPtr = &str[currIndex];
    }
    if (currIndex >= maxLen) {
        return NULL;
    }
    int tempIndex = 0;
    int isStart = 1; // flag for finding non-delimiter to start at
    char* tempTok = calloc(strlen(searchPtr) + 1, sizeof(char));
    for (int i = currIndex; i < maxLen; i++) {
        for (int j = 0; j < strlen(delim); j++) {
            if (searchPtr[i] == delim[j]) {
                if (isStart) goto nextChar;
                currIndex++;
                goto exitLoop;
            }
        }
        if (isStart) isStart = 0;
        tempTok[tempIndex++] = searchPtr[currIndex];
        nextChar:
        currIndex++;
    }
    exitLoop:
    if (!strlen(tempTok)) {
        free(tempTok);
        return NULL;
    }
    char* tok = calloc((strlen(tempTok) + 1), sizeof(char));
    strcpy(tok, tempTok);
    free(tempTok);
    return tok;
}

struct Student* loadStudent(const char* studentFilename) {
    if (!studentFilename) return NULL; // if studentFilename == NULL
    FILE* fp = fopen(studentFilename, "r");
    if (!fp) return NULL; // if file can't be opened
    struct Student* studentPtr = (struct Student*)malloc(sizeof(struct Student));
    char buf[BUF_LEN];
    for (int i = 1; i <= 4; i++) {
        fgets(buf, MAX_LINE_LEN, fp);
        if (i == 1) {
            studentPtr->name = calloc(strlen(buf), sizeof(char)); // zero value for char type is null byte
            strncpy(studentPtr->name, buf, strlen(buf)-1); // ignore newline character in name line read
        }
        else if (i == 2) {
            studentPtr->numCurrCourses = atoi(buf);
            studentPtr->currCourses = malloc(studentPtr->numCurrCourses * sizeof(char*));
            for (int i = 0; i < studentPtr->numCurrCourses; i++) {
                fgets(buf, MAX_LINE_LEN, fp);
                studentPtr->currCourses[i] = calloc(strlen(buf), sizeof(char)); // zero value for char type is null byte
                strncpy(studentPtr->currCourses[i], buf, strlen(buf)-1); // ignore newline character in name line read
            }
        }
        // else if (i == 3) {} // blank line
        else if (i == 4) {
            studentPtr->numPrevCourses = atoi(buf);
            studentPtr->prevCourses = malloc(studentPtr->numPrevCourses * sizeof(char*));
            for (int i = 0; i < studentPtr->numPrevCourses; i++) {
                fgets(buf, MAX_LINE_LEN, fp);
                studentPtr->prevCourses[i] = calloc(strlen(buf), sizeof(char)); // zero value for char type is null byte
                strncpy(studentPtr->prevCourses[i], buf, strlen(buf)-1); // ignore newline character in name line read
            }
        }
    }
    fclose(fp);
    return studentPtr;
}

void printStudent(const struct Student* s) {
    if (!s) return;
    printf("Name: %s\n", s->name);
    printf("Current courses:\n");
    for (int i = 0; i < s->numCurrCourses; i++) {
        printf("%s\n", s->currCourses[i]);
    }
    printf("Previous courses:\n");
    for (int i = 0; i < s->numPrevCourses; i++) {
        printf("%s\n", s->prevCourses[i]);
    }
    return;
}

void freeStudent(struct Student** s) {
    if(*s) { // if student != NULL, can access all attributes
        for(int i = 0; i < (*s)->numPrevCourses; i++) {
            free((*s)->prevCourses[i]);
        }
        for (int i = 0; i < (*s)->numCurrCourses; i++) {
            free((*s)->currCourses[i]);
        }
        free((*s)->prevCourses);
        free((*s)->currCourses);
        free((*s)->name);
    }
    free(*s); // frees the student pointer
    return;
}

int areClassmates(const struct Student* s1, const struct Student* s2) {
    if (!s1 || !s2) return 0; // if either student is NULL
    for (int i = 0; i < s1->numCurrCourses; i++) {
        for (int j = 0; j < s2->numCurrCourses; j++) {
            if (strcmp(s1->currCourses[i], s2->currCourses[j]) == 0)
                return 1;
        }
    }
    return 0;
}