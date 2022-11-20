#ifndef NTREE_H
#define NTREE_H

#include "../boolean.h"
#include "stdlib.h"

#define defN 1

typedef int ID;
typedef struct treeNode* Address;
typedef struct treeNode{
    ID Id;
    int nChild;
    Address * Childs;
} TreeNode;

typedef Address NTree;

#define Parent(T) (T)->Id
#define NChild(T) (T)->nChild
#define Childs(T) (T)->Childs
#define Child(T, i) (T)->Childs[i]

Address newTree(ID id);
/* Mengembalikan address dari alogasi elemen id dan alokasi
child default (nchild = 1)*/

void CreateTree(NTree *T);
/* I.S. T terdefinisi */
/* F.S. semua child T kosong Child(T,i) = 0 */

void makeBranch(NTree *T, int nchild);
/* I.S. T dan nchild terdefinisi */
/* F.S. Alokasi elemen sebanyak nchild, child masih kosong */

void deallocTreeNode (Address p);
/* I.S. p terdefinisi
F.S. p di dealokasikan kembali ke sistem */

void addChild(NTree *T, ID id);
/* I.S. T dan id terdefinisi */
/* F.S. mengalokasi elemen id dan menambahkan pada Tree 
sebagai child */

boolean isEmptyTree(NTree T);
/* Mengembalikan true jika T = NULL */

boolean isOneElmt(NTree p);
/* Mengembalikan true jika  semua child bernilai Nil */

boolean isChildOf(NTree T, ID id);
/* mengembalikan true jika id merupakan child dari T */

void printTreeLevel(NTree T, int h, int l);
/*I.S. T terdefinisi  
F.S. Mencetak tree sesuai level secara rekursif*/

void printTree(NTree T, int h);
/* I.S. T terdefinisi, h indentasi  >  0 */
/* F.S. Mencetak Tree, contoh : 
    A 
        B
        C
 */

void checkMerge(NTree *T, NTree B);
/*I.S. T dan B terdefinisi 
F.S. Mengembalikan T yang diperpanjang dengan B, jika B merupakan child T.*/

int depth(Address T);
/* mengembalikan nilai integer kedalaman dari T */

#endif