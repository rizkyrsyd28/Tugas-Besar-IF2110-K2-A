#include <stdio.h>
#include <stdlib.h>
#include "parser.c"
#include "../ADT/Simulator/simulator.c"
// #include "../ADT/piroqueue/piroqueue.c"


int main(){
    // konfigMap();
    //konfigMakanan();
    // ASCIIArt();

    // NTree * Trees = konfigResep(Trees);

    // for (int i = 0;  i < 4; i++){
    //     printTree(Trees[i], 2);
    //     printf("\nDepth : %d\n", depth(Trees[i]));
    // }
    Cookbook c = konfigResep();
    ListStatik foods = konfigMakanan();
    PrioQueueTime pq;

    MakeEmptyQueue(&pq, 18);

    for (int i = 0; i < listLength(foods); i++){
        if (idMkn(ELMTLIST(foods, i)) != 11){
            AddMakanan(&pq, ELMTLIST(foods, i));
        }
        else{
            AddMakanan(&pq, ELMTLIST(foods, i-1));
        }
    }

    PrintPrioQueueTime(pq);
    // Liststatik foods = 
    printResep(c, foods);

    if (canMake(c, ELMTLIST(foods, 15), pq)){
        printf("true bang\n");
    }
    else {
        printf("debug lagi jing\n");
    }

    return 0;

    // return 0;
}