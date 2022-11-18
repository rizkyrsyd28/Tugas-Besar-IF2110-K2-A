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
    Top(*S)++; 
    InfoTop(*S) = X;
    
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

void displayStack(Stack S){
    //Untuk memperlihatkan Stack
    state X;
    int i = 0; 
    // ALGORITMA
    for (int i = Top(S); i >= 0; i--){
        Pop(&S, &X);
        printf("Simulator : \n");
        DisplaySimulator(X.sub1);
        printf("\n");
        printf("Inventory : \n");
        DisplayInventory(X.sub1);
        printf("\n");
        printf("Waktu : \n");
        TulisTIME(X.sub2);
        printf("\n");
        printf("Delivery : \n");
        PrintPrioQueueTimeDelivery(X.sub1.D);
        printf("\n");
        printf("Process : \n");
        PrintPrioQueueTimeProcess(X.sub1.PL);
        printf("\n");
        printWord(X.sub3);
        printf("\n");
    }
}

void Undo(Stack *S_undo,Stack *S_redo, state *currentState, int totalcommand, POINT src){
    //Undo gerakan, mengembalikan simulator,waktu,dan peta sebelum
    
    if (totalcommand >0){
        //CreateSimulatorUndo(&currentState->sub1,currentState->sub1.Nama,currentState->sub1.P,currentState->sub1.Q);
        Push(S_redo, *currentState);
        if (src.X>=1 && src.Y>=1){
            InfoTop(*S_redo).sub1.P=src;
        }
        Pop (S_undo,currentState);
    }
    
}

void Redo(Stack *S_undo,Stack *S_redo, state *currentState, int totalundo, POINT src){
    //Redo gerakan, mengembalikan simulator,waktu,dan peta sesudah
    if(totalundo>0){
        //CreateSimulatorUndo(&currentState->sub1,currentState->sub1.Nama,currentState->sub1.P,currentState->sub1.Q);
        Push(S_undo, *currentState);
        if (src.X>=1 && src.Y>=1){
            InfoTop(*S_undo).sub1.P=src;
        }
        Pop (S_redo, currentState);
    }
}
