#include "prog3.h"

#include <stdio.h>
#include <stdlib.h>

#define NULL_PTR_STR "(null pointer)"

int main()
{
    /**
     * Simple example.
     */
    char s1[] = "Hi there friend";  // Could use char* since the string
                                    // shouldn't be mutated anyways.
    char* tok1 = strtok_c(s1, " ");
    char* tok2 = strtok_c(NULL, " ");
    char* tok3 = strtok_c(NULL, " ");
    char* tok4 = strtok_c(NULL, " ");
    printf("s1: %s\n", s1);
    printf("tok1: %s\n", tok1);
    printf("tok2: %s\n", tok2);
    printf("tok3: %s\n", tok3);
    printf("tok4: %s\n", tok4 ? tok4 : NULL_PTR_STR);
    free(tok1);
    free(tok2);
    free(tok3);

    /**
     * Multiple delimiters.
     */
    char s2[] = "abracadabra";
    tok1 = strtok_c(s2, "db");
    tok2 = strtok_c(NULL, "db");
    tok3 = strtok_c(NULL, "db");
    tok4 = strtok_c(NULL, "db");
    char* tok5 = strtok_c(NULL, "db");
    printf("s2: %s\n", s2);
    printf("tok1: %s\n", tok1);
    printf("tok2: %s\n", tok2);
    printf("tok3: %s\n", tok3);
    printf("tok4: %s\n", tok4);
    printf("tok5: %s\n", tok5 ? tok5 : NULL_PTR_STR);
    free(tok1);
    free(tok2);
    free(tok3);
    free(tok4);

    /**
     * Tokenizing same string multiple times.
     */
    char s3[] = "How are you?";
    tok1 = strtok_c(s3, "er");
    tok2 = strtok_c(NULL, "o");  // Starts at 'e', but if we had used the
                                 // same delimiters as before, it would start
                                 // at ' '.
    tok3 = strtok_c(s3, "w?");
    printf("s3: %s\n", s3);
    printf("tok1: %s\n", tok1);
    printf("tok2: %s\n", tok2);
    printf("tok3: %s\n", tok3);
    free(tok1);
    free(tok2);
    free(tok3);

    /**
     * This is similar to the example I mentioned where I talk about no empty
     * tokens in the directions.
     */
    char s4[8] = "abcde";  // must be char[] since mutating two lines later
    tok1 = strtok_c(s4, "x");
    s4[5] = 'f';
    s4[6] = 'g';  // s4[7] is already a null byte
    tok2 = strtok_c(NULL, "x");  // Will return NULL since last strtok_c() call
                                 // reached what was the end of s4 at the time.
    printf("s4: %s\n", s4);
    printf("tok1: %s\n", tok1);
    printf("tok2: %s\n", tok2 ? tok2 : NULL_PTR_STR);
    free(tok1);
    free(tok2);

    /**
     * Example in which the tokens have to have their start points moved up
     * so as to avoid starting on delimiters.
     */
    char s5[] = "aabcdaaaefghaaiaaajklaa";
    tok1 = strtok_c(s5, "?!a");
    tok2 = strtok_c(NULL, "?!a");
    tok3 = strtok_c(NULL, "?!a");
    tok4 = strtok_c(NULL, "?!a");
    tok5 = strtok_c(NULL, "?!a");
    char* tok6 = strtok_c(NULL, "?!a");
    printf("s5: %s\n", s5);
    printf("tok1: %s\n", tok1);
    printf("tok2: %s\n", tok2);
    printf("tok3: %s\n", tok3);
    printf("tok4: %s\n", tok4);
    printf("tok5: %s\n", tok5 ? tok5 : NULL_PTR_STR);
    printf("tok6: %s\n", tok6 ? tok6 : NULL_PTR_STR);
    free(tok1);
    free(tok2);
    free(tok3);
    free(tok4);

    // own tests
    char s6[] = "";
    tok1 = strtok_c(s6, "?!a");
    tok2 = strtok_c(NULL, "?!a");
    printf("s6: %s\n", s6);
    printf("tok1: %s\n", tok1 ? tok1 : NULL_PTR_STR);
    printf("tok2: %s\n", tok2 ? tok2 : NULL_PTR_STR);

    char s7[] = "a";
    tok1 = strtok_c(s7, "?!a");
    tok2 = strtok_c(NULL, "?!a");
    printf("s7: %s\n", s7);
    printf("tok1: %s\n", tok1 ? tok1 : NULL_PTR_STR);
    printf("tok2: %s\n", tok2 ? tok2 : NULL_PTR_STR);

    char s8[] = "?!a?!";
    tok1 = strtok_c(s8, "?!a");
    tok2 = strtok_c(NULL, "?!a");
    printf("s8: %s\n", s8);
    printf("tok1: %s\n", tok1 ? tok1 : NULL_PTR_STR);
    printf("tok2: %s\n", tok2 ? tok2 : NULL_PTR_STR);

    char s9[] = "abcde";
    tok1 = strtok_c(s9, "");
    tok2 = strtok_c(NULL, "");
    tok3 = strtok_c(NULL, "");
    printf("s9: %s\n", s9);
    printf("tok1: %s\n", tok1);
    printf("tok2: %s\n", tok2 ? tok2 : NULL_PTR_STR);
    printf("tok3: %s\n", tok3 ? tok3 : NULL_PTR_STR);
    free(tok1);

    char s10[] = "";
    tok1 = strtok_c(s10, "");
    tok2 = strtok_c(NULL, "");
    printf("s10: %s\n", s10);
    printf("tok1: %s\n", tok1 ? tok1 : NULL_PTR_STR);
    printf("tok2: %s\n", tok2 ? tok2 : NULL_PTR_STR);
}
