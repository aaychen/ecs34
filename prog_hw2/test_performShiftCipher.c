#include <stdio.h>

#include "prog2.h"

int main()
{
    char str[] = "Hi there";
    int retval = performShiftCipher(str, 3);
    printf("str=%s, retval=%d\n", str, retval ? 1 : 0);
    retval = performShiftCipher(str, -3);
    printf("str=%s, retval=%d\n", str, retval ? 1 : 0);
    retval = performShiftCipher(NULL, 10);
    printf("str=%s, retval=%d\n", str, retval ? 1 : 0);
    retval = performShiftCipher(str, 500);
    printf("str=%s, retval=%d\n", str, retval ? 1 : 0);
    char str2[] = "56@$aBc* 4Zy";
    retval = performShiftCipher(str2, 9);
    printf("str2=%s, retval=%d\n", str2, retval ? 1 : 0);
    retval = performShiftCipher(str2, -9);
    printf("str2=%s, retval=%d\n", str2, retval ? 1 : 0);
    // char str[] = "5";
    // int retval = performShiftCipher(str, 9);
    // printf("str=%s, retval=%d\n", str, retval ? 1 : 0);
}
