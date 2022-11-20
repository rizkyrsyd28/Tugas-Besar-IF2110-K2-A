#include "nTree.h"
#include <stdio.h>

Address newTree(ID id){
/* Mengembalikan address dari alogasi elemen id dan alokasi
child default (nchild = 1)*/
    Address p = (Address) malloc (sizeof (TreeNode));
    Parent(p) = id;
    NChild(p) = defN;
    Childs(p) = (Address*) malloc (defN * sizeof(Address));
    return p;
}

void CreateTree(NTree *T){
/* I.S. T terdefinisi */
/* F.S. semua child T kosong Child(T,i) = 0 */
    for (int i = 0; i < NChild(*T); i++){
        Child(*T,i) = NULL; 
    }
}

void makeBranch(NTree *T, int nchild){
/* I.S. T dan nchild terdefinisi */
/* F.S. Alokasi elemen sebanyak nchild, child masih kosong */
    free(Childs(*T));
    NChild(*T) = nchild;
    Childs(*T) = (Address*) malloc (nchild * sizeof(Address));
    CreateTree(T);
}
/* Buat Node Tree baru dengan Id id dengan info jumlah child */

void deallocTreeNode (Address p){
/* I.S. p terdefinisi
F.S. p di dealokasikan kembali ke sistem */
    free(p);
}

void addChild(NTree *T, ID id){
/* I.S. T dan id terdefinisi */
/* F.S. mengalokasi elemen id dan menambahkan pada Tree 
sebagai child */
    Address p = newTree(id);
    for(int i = 0; i < NChild(*T); i++){
        if (Child(*T, i) == NULL){
            Child(*T, i) = p;
            CreateTree(&p);
            return;
        }
    }
}

boolean isEmptyTree(NTree T){
/* Mengembalikan true jika T = NULL */
    return (T == NULL);
}

boolean isOneElmt(NTree p){
/* Mengembalikan true jika  semua child bernilai Nil */
    boolean status = true;
    for (int i = 0; i = NChild(p); i++){
        if (Child(p,i) != NULL){
            return false;
        }
    }
    return false; 
}

boolean isChildOf(NTree T, ID id){
/* mengembalikan true jika id merupakan child dari T */
    for (int i = 0; i < NChild(T); i++){
        if (Parent(Child(T,i)) == id){
            return true;
        }
    }
    return false;
}

void printTreeLevel(NTree T, int h, int l){
/*I.S. T terdefinisi  
F.S. Mencetak tree sesuai level secara rekursif*/
    int N;

    if (!isEmptyTree(T)){
        N = h * l;

        while (N > 0){
            printf(" ");
            N--;
        }
        
        printf("%d\n", Parent(T));

        if  (Child(T, 0) != NULL){
            for (int i = 0; i < NChild(T); i++){
                printTreeLevel(Child(T, i), h, l + 1);
            }
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
/* I.S. T terdefinisi, h indentasi  >  0 */
/* F.S. Mencetak Tree, contoh : 
    A 
        B
        C
 */

    printTreeLevel(T, h, 0);
}

void checkMerge(NTree *T, NTree B){
/*I.S. T dan B terdefinisi 
F.S. Mengembalikan T yang diperpanjang dengan B, jika B merupakan child T.*/
    
    if (Parent(*T) == Parent(B) && Child(*T, 0) == NULL){
        *T = B;
    }
    else if (Child(*T, 0) != NULL) {
        for (int i = 0; i < NChild(*T); i++){
            checkMerge(&Child(*T, i), B);
        }
    }
}

int depth(Address T){
/* mengembalikan nilai integer kedalaman dari T */
    int count = 0; 

    if (isEmptyTree(T)){
        return 0;
    }
    else {
         count += 1 + depth(Child(T, 0));
    }

    return count;
}
