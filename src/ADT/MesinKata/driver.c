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
    int idx;
    char str1[] = "haha nyobain xixixixi.";
    STARTWORD(str1, &idx);
    printWord(currentWord);
    ADVWORD(str1,&idx);
    if (isWordStringEqual(currentWord, "nyobain")){
        printf("Test\n");
    }
    printWord(currentWord);
    // while (!endWord){
    //     printWord(currentWord);
    //     ADVWORD(str1, &idx);
    // }

    return 0;

}


