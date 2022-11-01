#include <stdio.h>
#include <stdlib.h>
#include "parser.c"


int main(){
    // konfigMap();
    // konfigMakanan();
    // ASCIIArt();

    Cookbook cb = konfigResep();

    for (int i = 0;  i < 6; i++){
        printTree(Resep(cb, i), 2);
    }

    return 0;
}