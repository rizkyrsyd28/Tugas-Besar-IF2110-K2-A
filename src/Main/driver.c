#include <stdio.h>
#include <stdlib.h>
#include "parser.c"


int main(){
    //konfigMap();
    //konfigMakanan();
    // ASCIIArt();

    NTree * Trees = konfigResep(Trees);

    for (int i = 0;  i < 4; i++){
        printTree(Trees[i], 2);
        printf("\nDepth : %d\n", depth(Trees[i]));
    }

    return 0;
}