#include <stdio.h>
#include "simulator.h"

void CreateSimulator(Simulator *S, Word nama, POINT P, PrioQueueTime Q,PrioQueueTime D,PrioQueueTime PL){
/* I.S. Sembarang
F.S. Simulator terdefinisi dengan spesifikasi sesuai parameter yang diinputkan*/
    Nama(*S)= nama;
    Lokasi(*S)=P;
    Inventory(*S) = Q;
    Delivery(*S) = D;
    ProcessList(*S) = PL;
}

void ReadSimulator(Simulator *S){
    /* I.S. sembarang
F.S. Simulator terdefinisi, membuat simulator sesuai input dari pengguna*/
    Word nama;
    POINT P;
    PrioQueueTime Q;
    PrioQueueTime D;
    PrioQueueTime PL;
    MakeEmptyQueue(&Q,100);
    MakeEmptyQueue(&D,100);
    MakeEmptyQueue(&PL,100);
    int idx;
    // Menginputkan nama Simulator
    printf("Input nama Simulator: ");
    char temp[100]="\0";
    fgets(temp, 100, stdin);

    // Mengubah nilai '\n' menjadi '\0' dan menambahkan MARK
    temp[lengthString(temp)-1] = '\0';
    appendChar(temp,'.');

    STARTWORD(temp,&idx);
    nama = currentWord;

    Absis(P) = 1;
    Ordinat(P) = 1;
    CreateSimulator(S,nama,P,Q,D,PL);
}

void DisplaySimulator(Simulator S){
/* I.S. S terdefinisi
F.S. Menampilkan nama dan posisi simulator */
    DisplayNama(S);
    printf(" di posisi: ");
    DisplayLokasi(S);
    printf("\n");
}

void DisplayNama(Simulator S)
{
/* I.S. S terdefinisi
F.S. Nama Simulator ditampilkan*/
    printWord(Nama(S));
}

void DisplayLokasi(Simulator S){
/* I.S. S terdefinisi
F.S. Lokasi Simulator ditampilkan */
    printf("(%d,%d)", Absis(Lokasi(S))-1, Ordinat(Lokasi(S))-1);
}

void DisplayInventory (Simulator S)
/* I.S. S terdefinisi
F.S. INventory Simulator ditampilkan */
{
    printf("List Makanan di Inventory:\n");
    printf("(No - Nama - Waktu Sisa Kadaluwarsa)\n");
    PrintPrioQueueTimeInventory(Inventory(S));
}

void MixOlahInventory(PrioQueueTime *Q, PrioQueueTime *DestQ, Cookbook cb, ID id, int idx, ListStatik fs){
/* I.S. Semua parameter prosedur terdefinisi
F.S. Mengeluarkan bahan yang dimasak dari Inventory, memasukan bahan yang ingin dibuat ke process list*/
    Makanan m;
    int ids;

    m = getMakanan(id, fs);
    for (int i = 0; i < NChild(Resep(cb, idx)); i++){
        ids = Parent(Child(Resep(cb, idx), i));
        RemoveMakanan(Q, getMakanan(ids, fs));
    }
    EnqueueDelivery(DestQ, m);
}

void ChopOlahInventory (PrioQueueTime *Q, PrioQueueTime *DestQ, Makanan X1, Makanan X2){
/* I.S. Semua parameter prosedur terdefinisi
F.S. Mengeluarkan bahan yang dimasak dari Inventory, memasukan bahan yang ingin dibuat ke process list*/
    RemoveMakanan(Q,X1);
    EnqueueDelivery(DestQ,X2);
}

void FryOlahInventory(PrioQueueTime *Q, PrioQueueTime *DestQ, Cookbook cb, ID id, int idx, ListStatik fs){
/* I.S. Semua parameter prosedur terdefinisi
F.S. Mengeluarkan bahan yang dimasak dari Inventory, memasukan bahan yang ingin dibuat ke process list*/
    MixOlahInventory(Q, DestQ,  cb, id, idx, fs);
}

void BoilOlahInventory(PrioQueueTime *Q, PrioQueueTime *DestQ, Cookbook cb, ID id, int idx, ListStatik fs){
/* I.S. Semua parameter prosedur terdefinisi
F.S. Mengeluarkan bahan yang dimasak dari Inventory, memasukan bahan yang ingin dibuat ke process list*/
    MixOlahInventory(Q, DestQ, cb, id, idx, fs);
}

void RemoveMakanan(PrioQueueTime *Q,Makanan M){
/* I.S. *Q terdefinisi
F.S. DequeueAt makanan pada inventory. Makanan dikeluarkan dari inventory*/
    Makanan X;
    DequeueAt(Q,M,&X);
}


void GeserLokasi (Simulator *S,int arah){
/* I.S. *S terdefinisi
F.S. *S bergerak ke arah yang diinginkan oleh user */
    if (arah==1){//MOVE NORTH
        Absis(Lokasi(*S))-=1;
    }
    else if (arah ==2){//MOVE EAST
        Ordinat(Lokasi(*S))+=1;
    }
    else if (arah ==3){//MOVE WEST
        Ordinat(Lokasi(*S))-=1;
    }
    else if (arah ==4){//MOVE SOUTH
        Absis(Lokasi(*S))+=1;
    }
}

void CreateSimulatorUndo (Simulator *S, Word nama, POINT P, PrioQueueTime invent,PrioQueueTime DeliveryList, PrioQueueTime ProcessList){
 /* I.S. Sembarang
 F.S. Dibuat Createsimulatordummy supaya isi dari stack undo tidak terpengaruh oleh pengurangan waktu yang ada */
    PrioQueueTime Q;
    PrioQueueTime D;
    PrioQueueTime PL;
    MakeEmptyQueue(&Q,100);
    MakeEmptyQueue(&D,100);
    MakeEmptyQueue(&PL,100);
    Head(Q) = Head(invent);
    Tail(Q) = Tail(invent);
    Head(D) = Head(DeliveryList);
    Tail(D) = Tail(DeliveryList);
    Head(PL) = Head(ProcessList);
    Tail(PL) = Tail(ProcessList);
    for (int i =0;i<100;i++){
        Elmt(Q,i) = Elmt(invent,i);
    }
    for (int i =0;i<100;i++){
        Elmt(D,i) = Elmt(DeliveryList,i);
    }
    for (int i =0;i<100;i++){
        Elmt(PL,i) = Elmt(ProcessList,i);
    }
    Nama(*S)= nama;
    Lokasi(*S)=P;
    Inventory(*S) = Q;
    Delivery(*S) = D;
    ProcessList(*S) = PL;
}