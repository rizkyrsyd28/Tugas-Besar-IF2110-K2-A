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

NTree newTree(ID id);
/* Buat Node Tree baru dengan Id id dengan info jumlah child */

void deallocTreeNode (Address p);

void CreateTree(NTree *T);
/* List Kososng*/

boolean isEmptyTree(NTree T);

boolean isOneElmt(NTree p);

#endif