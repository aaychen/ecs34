#include <stdio.h>

#include "prog2.h"

int main()
{
    // One way to set up the call.
    char* ptr = strrstr("abcdabcb", "abc");
    printf("%s\n", ptr);
  
    // Could also set it up this way. (If strrstr() were to modify either string,
    // then I think that the above way would be prohibited because the literals
    // are likely placed in read-only memory.)
    char s1[] = "123ab67890123cd432123ef";
    ptr = strrstr(s1, "123");
    printf("%s\n", ptr);
    printf("%p %p\n", s1 + 18, ptr);
}
