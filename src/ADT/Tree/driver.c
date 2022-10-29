#include "nTree.c"
#include <stdio.h>

int main(){
    NTree T;

    T = newTree(20);

    CreateTree(&T);

    makeBranch(&T, 3);

    addChild(&T, 199);
    addChild(&T, 5);
    addChild(&T, 1);


    printf("%d\n", Parent(T));
    printf("%d\n", Parent(Child(T, 0)));
    printf("p = %d\n", Parent(Child(T, 1)));
    printf("%d\n", Parent(Child(T, 2)));

    printf("\n===\n");

    NTree p = Child(T, 1);

    makeBranch(&p, 4);

    addChild(&p, 41);
    addChild(&p, 14);
    // addChild(&p, 94);
    addChild(&p, 4);

    printf("%d\n", Parent(p));
    printf("%d\n", Parent(Child(p, 0)));
    printf("%d\n", Parent(Child(p, 1)));
    printf("%d\n", Parent(Child(p, 2)));
    if (Child(p, 3) != NULL)
        printf("%p\n", Parent(Child(p, 3)));
    else
        printf("HAH KOSONG???\n\n");

    
    printTree(T, 2);


    free(T);
    free(p); 

    return 0;
}