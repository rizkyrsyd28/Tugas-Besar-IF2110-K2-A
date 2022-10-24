#include <stdio.h>
#include "wordmachine.c"


int main () {
    // STARTWORD();

    // Word w1 = currentWord;
    // ADVWORD();
    // Word w2 = currentWord;
    
    // Word w3 = appendWord(w1, w2);
    // printWord(w3);

    // while (!endWord){
    //     ADVWORD();
    // }

    int num;
    char str1[] = "haha";
    char str2[] = "test";
    char c = 'a';
    num = lengthString(str1);
    printf("%d\n", num);

    appendChar(str1, '#');
    printf("%s", str1);

    return 0;

}


