#include "library.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// FILE #1 TO SUBMIT

/**
 * Creates instances of Book and stores them into an array of Books as an 
 * attribute of Library. This function assumes the first line in filename 
 * is the number of books and is >=1. It also assumes all records are in 
 * the proper format: [title],[author],[year of book].
 * 
 * @param fileName The name of the file in interest
 * @return Reference to a Library instance
 */
struct Library* loadLibrary(const char* filename) {
    if (!filename) return NULL;
    FILE* fp = fopen(filename, "r");
    if (!fp) return NULL;

    char buf[BUF_LEN];
    fgets(buf, MAX_LINE_LEN, fp); // buf contains # of books after this
    struct Library* libraryPtr = (struct Library*)malloc(sizeof(struct Library));
    libraryPtr->numBooks = atoi(buf);
    libraryPtr->books = malloc(libraryPtr->numBooks * sizeof(struct Book));

    int bookIndex = 0;
    while (fgets(buf, MAX_LINE_LEN, fp)) { // read in filename until nothing left to read
        // char *title, *author;
        // int year;
        // filename is a CSV file -> tokenize by comma
        struct Book book; // create instances of Book and store in books attribute of libraryPtr (books = array of Book instances)
        for (int i = 0; i < 3; i++) {
            char* tok = i == 0 ? strtok(buf, ",") : strtok(NULL, ",");
            switch (i) {
                case 0:
                    // title = calloc(strlen(tok) + 1, sizeof(char));
                    // strcpy(title, tok);
                    book.title = calloc(strlen(tok) + 1, sizeof(char));
                    strcpy(book.title, tok);
                    break;
                case 1:
                    // author = calloc(strlen(tok) + 1, sizeof(char));
                    // strcpy(author, tok);
                    book.author = calloc(strlen(tok) + 1, sizeof(char));
                    strcpy(book.author, tok);
                    break;
                case 2:
                    // year = atoi(strtok(tok, "\n")); // strip newline character of year token
                    book.year = atoi(strtok(tok, "\n")); // strip newline character of year token
                    break;
            }
        }
        libraryPtr->books[bookIndex++] = book;
    }
    fclose(fp); // if don't close file, will have memory leak reported (will say still reachable)
    return libraryPtr;
}

/**
 * Prints out each Book's details using the array of Books that's an attribute
 * of Library.
 * 
 * @param library References a Library instance
 * @return 0 if library is NULL; 1 otherwise
 */
int printLibrary(const struct Library* library) {
    if (!library) return 0;
    for (int i = 0; i < library->numBooks; i++) {
        // -> used with pointers
        // dot notation used with instances
        struct Book tempBook = library->books[i];
        printf("%s by %s (%d)\n", tempBook.title, tempBook.author, tempBook.year);
    }
    return 1;
}

// Assume the same title never appears twice in a given file
/**
 * Counts the number of common titles between two Library instances. This function 
 * assumes that the same title never appears twice in a given file.
 * 
 * @param lib1 Reference to first Library instance
 * @param lib2 Reference to second Library instance
 * @return 0 if either lib1 or lib2 is NULL; number of common titles otherwise
 */
int countCommonTitles(const struct Library* lib1, const struct Library* lib2) {
    if (!lib1 || !lib2) return 0;
    int count = 0;
    for (int i = 0; i < lib1->numBooks; i++) {
        for (int j = 0; j < lib2->numBooks; j++) {
            if (strcmp(lib1->books[i].title, lib2->books[j].title) == 0) {
                count++;
                break;
            }
        }
    }
    return count;
    
    // try implementing with hash table
}

/**
 * Deallocates all space associated with library.
 * 
 * @param library References a Library instance
 * @return 0 if library is NULL; 1 otherwise
 */
int freeLibrary(struct Library* library) {
    if (!library) return 0;
    // free title and author of every book
    for (int i = 0; i < library->numBooks; i++) {
        free(library->books[i].title);
        free(library->books[i].author);
    }
    free(library->books);
    free(library);
    return 1;
}