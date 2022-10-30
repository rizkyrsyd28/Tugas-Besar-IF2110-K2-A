#include "nTree.h"
#include <stdio.h>

NTree newTree(ID id){
    Address p = (Address) malloc (sizeof (TreeNode));
    Parent(p) = id;
    NChild(p) = defN;
    Childs(p) = (Address*) malloc (defN * sizeof(Address));
    return p;
}

void makeBranch(NTree *T, int nchild){
    free(Childs(*T));
    NChild(*T) = nchild;
    Childs(*T) = (Address*) malloc (nchild * sizeof(Address));
    CreateTree(T);
}
/* Buat Node Tree baru dengan Id id dengan info jumlah child */

void CreateTree(NTree *T){
    /* prekondisi aman */
    for (int i = 0; i < NChild(*T); i++){
        Child(*T,i) = NULL; 
    }
}
/* List Kososng*/

void mergeTree(NTree *T, NTree T1){
    for(int i = 0; i < NChild(*T); i++){
        if (Parent(Child(*T, i)) == Parent(T1) || Child(*T, i) == NULL){
            Child(*T, i) = T1;
            return;
        }
    }
}

void addChild(NTree *T, ID id){
    Address p = newTree(id);
    for(int i = 0; i < NChild(*T); i++){
        if (Child(*T, i) == NULL){
            Child(*T, i) = p;
            CreateTree(&p);
            return;
        }
    }
}

void deallocTreeNode (Address p){
    free(p);
}

boolean isEmptyTree(NTree T){
    return (T == NULL);
}

boolean isOneElmt(NTree p){
    boolean status = true;
    for (int i = 0; i = NChild(p); i++){
        if (Child(p,i) != NULL){
            return false;
        }
    }
    return false; 
}

void printTreeLevel(NTree T, int h, int l){
    int N;

    if (!isEmpty(T)){
        N = h * l;

        while (N > 0){
            printf(" ");
            N--;
        }
        
        printf("%d\n", Parent(T));

        for (int i = 0; i < NChild(T); i++){
            printTreeLevel(Child(T, i), h, l + 1);

        }
    }
    else {
        N = h * l;

        while (N > 0){
            printf(" ");
            N--;
        }
        
        printf("NULL\n");
    }
}

void printTree(NTree T, int h){
    printTreeLevel(T, h, 0);
}

void checkMerge(NTree *T, NTree B){
    
    if (Parent(*T) == Parent(B) && Child(*T, 0) == NULL){
        *T = B;
    }
    else if (Child(*T, 0) != NULL) {
        for (int i = 0; i < NChild(*T); i++){
            checkMerge(&Child(*T, i), B);
        }
    }
}