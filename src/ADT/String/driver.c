#include "string.c"
#include <stdio.h>

int main () {
    char test[] = "";
    // int n = stringToInt(test);
    // printf("%d\n", n);

    char haha = '.';

    int l = lengthString(test);
    printf("%d\n", l);
    appendChar(test, '.');
    printf("%s\n", test);

    return 0;
}