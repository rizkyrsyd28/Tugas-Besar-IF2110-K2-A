#include "string.c"
#include <stdio.h>

int main () {
    char test[] = "";
    char huhu[] = "XixIxIXixiXI";
    upper(huhu);
    printf("%s\n", huhu);
    char haha[] = "XIXIXIXIXIXI";
    if(isStringEqual(huhu,haha)){
        printf("test\n");
    }
    // int n = stringToInt(test);
    // printf("%d\n", n);

    // char haha = '.';

    // int l = lengthString(test);
    // printf("%d\n", l);
    // appendChar(test, '.');
    // printf("%s\n", test);

    return 0;
}