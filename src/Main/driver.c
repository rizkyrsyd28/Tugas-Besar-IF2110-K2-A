#include <stdio.h>
#include <stdlib.h>
#include "parser.c"


int main(){
    // konfigMap();
    //konfigMakanan();
    // ASCIIArt();

    // NTree * Trees = konfigResep(Trees);

    // for (int i = 0;  i < 4; i++){
    //     printTree(Trees[i], 2);
    //     printf("\nDepth : %d\n", depth(Trees[i]));
    // }
    POINT p;
	Matrix m = konfigMap();

	CreatePoint(&p, 1, 1);

	swapElmt(&m, &p, NextX(p));
    TulisPOINT(p);
    
	displayMatrix(m);
    // ----
	swapElmt(&m, &p, NextY(p));
    TulisPOINT(p);

	displayMatrix(m);
    // ----
	swapElmt(&m, &p, BackY(p));
    TulisPOINT(p);

	displayMatrix(m);

    // return 0;
}