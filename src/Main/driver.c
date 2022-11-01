#include <stdio.h>
#include <stdlib.h>
#include "parser.c"


int main(){
    //konfigMap();
    ListStatik l;
    l = konfigMakanan();
    int len;
    len = listLength(l);
    int i;
    for (i = 0; i < len; i++){
        Makanan mkn = GETFOOD(l, i);
        printMakanan(mkn);
    }
    // ASCIIArt();

    // NTree * Trees = konfigResep(Trees);

    // for (int i = 0;  i < 4; i++){
    //     printTree(Trees[i], 2);
    //     printf("\nDepth : %d\n", depth(Trees[i]));
    // }

    return 0;
}