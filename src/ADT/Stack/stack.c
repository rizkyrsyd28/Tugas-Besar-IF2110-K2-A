#include "stack.h"
#include <stdio.h>

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmpty(Stack *S){
    Top(*S) = Nil;
}
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxEl */
/* jadi indeksnya antara 0.. MaxEl */
/* Ciri stack kosong : TOP bernilai Nil */

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
/*boolean IsEmpty(Stack S){
    return Top(S) == Nil;
}*/
/* Mengirim true jika Stack kosong: lihat definisi di atas */
/*boolean IsFull(Stack S){
    return Top(S) == MaxEl-1;
}*/
/* Mengirim true jika tabel penampung nilai elemen stack penuh */

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push(Stack * S, state X){
    /*if (i==1){
        decrementNExp(&Inventory(X.sub1),1);
        decrementNDel(&X.sub3,1);
    }*/
    Top(*S)++; 
    InfoTop(*S) = X;
    /*if (i==1){
        incrementNExp(&Inventory(X.sub1),1);
        incrementNDel(&X.sub3,1);
    }*/
    
}
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */

/* ************ Menghapus sebuah elemen Stack ************ */
void Pop(Stack * S, state *X){
    *X = InfoTop(*S);
    Top(*S)--;
}
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */


// TAMBAHAN
/*void inverseStack(Stack * S){
    Stack tempS;
    state X;
    CreateEmpty(&tempS);

    for (int i = Top(*S); i >= 0; i--){
        Pop(S, &X);
        Push(&tempS, X);
    }

    *S = tempS;
}

Stack merge(Stack S1, Stack S2){
    Stack output = S1;
    state x;
    inverseStack(&S2);

    while(Top(S2) != Nil){
        Pop(&S2, &x);
        Push(&output, x);
    }
    return output;
}*/

void displayStack(Stack S){
    //Untuk memperlihatkan Stack
    state X;
    int i = 0; 
    // ALGORITMA
    for (int i = Top(S); i >= 0; i--){
        Pop(&S, &X);
        printf("%d\n", X);
    }

}

void Undo(Stack *S_undo,Stack *S_redo, state *currentState, int totalcommand, POINT src){
    //Undo gerakan, mengembalikan simulator,waktu,dan peta sebelum
    if (totalcommand >0){
        Push(S_redo, *currentState);
        if (src.X>=1 && src.Y>=1){
            InfoTop(*S_redo).sub1.P=src;
        }
        Pop (S_undo,currentState);
    }
    else {
        printf("Tidak bisa undo\n");
    }
    
}

void Redo(Stack *S_undo,Stack *S_redo, state *currentState, int totalundo, POINT src){
    //Redo gerakan, mengembalikan simulator,waktu,dan peta sesudah
    if(totalundo>0){
        Push(S_undo, *currentState);
        if (src.X>=1 && src.Y>=1){
            InfoTop(*S_undo).sub1.P=src;
        }
        Pop (S_redo, currentState);
    }
    else {
        printf("Tidak bisa redo\n");
    }
}
