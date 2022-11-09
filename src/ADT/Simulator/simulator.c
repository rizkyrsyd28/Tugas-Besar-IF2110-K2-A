#include <stdio.h>
#include "simulator.h"

void CreateSimulator(Simulator *S, Word nama, POINT P, PrioQueueTime Q,PrioQueueTime D,PrioQueueTime PL){
    //Membuat simulator
    Nama(*S)= nama;
    Lokasi(*S)=P;
    Inventory(*S) = Q;
    Delivery(*S) = D;
    ProcessList(*S) = PL;
}

void ReadSimulator(Simulator *S){
    //Membaca Simulator
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
    //Menampilkan Simulator
    DisplayNama(S);
    printf(" di posisi: ");
    DisplayLokasi(S);
    printf("\n");
}

void DisplayNama(Simulator S)
{
    //Menampilkan nama
    printWord(Nama(S));
}

void DisplayLokasi(Simulator S){
    //Menampilkan koordinat lokasi
    printf("(%d,%d)", Absis(Lokasi(S))-1, Ordinat(Lokasi(S))-1);
}

void DisplayInventory (Simulator S)
//Menampilkan list inventory
{
    printf("List Makanan di Inventory:\n");
    printf("(No - Nama - Waktu Sisa Kadaluwarsa)\n");
    PrintPrioQueueTimeInventory(Inventory(S));
}

void OlahMakananInventory(PrioQueueTime *Q, int command,int jumlah, Makanan X1, Makanan X2,Makanan X3, Makanan X4){
    //Mengupdate isi inventory. X4 itu buat yang diadd, X1,X2,X3 yang diremove. Kalo yang diremove ga sampe 3, isi asal aja yg ga kepake
    if (command==1){//MIX
        // MixOlahInventory(Q,jumlah,X1,X2,X3,X4);
    }
    else if(command==2){//CHOP
        ChopOlahInventory(Q,X1,X4);
    }
    else if (command==3){//FRY
        FryOlahInventory(Q,jumlah,X1,X2,X4);
    }
    else if(command==4){//BOIL
        BoilOlahInventory(Q,X1,X4);
    }
    else if (command ==5){
        BuyOlahInventory(Q,X4);
    }
    //masukin makanan
}

void MixOlahInventory(PrioQueueTime *Q, Cookbook cb, ID id, int idx, ListStatik fs){
    Makanan m;
    int ids;

    m = getMakanan(id, fs);
    for (int i = 0; i < NChild(Resep(cb, idx)); i++){
        ids = Parent(Child(Resep(cb, idx), i));
        RemoveMakanan(Q, getMakanan(ids, fs));
    }
    AddMakanan(Q, m);
}

void ChopOlahInventory (PrioQueueTime *Q, Makanan X1, Makanan X2){
    //Mengupdate isi inventory jika melakukan Chop
    RemoveMakanan(Q,X1);
    AddMakanan(Q,X2);
}

void FryOlahInventory(PrioQueueTime *Q,int jumlah, Makanan X1, Makanan X2, Makanan X3){
    //Mengupdate isi inventory jika melakukan Fry
    if (jumlah==1){
        RemoveMakanan(Q,X1);
        AddMakanan(Q,X3);
    }
    else if (jumlah==2){
        RemoveMakanan(Q,X1);
        RemoveMakanan(Q,X2);
        AddMakanan(Q,X3);
    }
}

void BoilOlahInventory(PrioQueueTime *Q, Makanan X1, Makanan X2){
    //Mengupdate isi inventory jika melakukan Boil
    RemoveMakanan(Q,X1);
    AddMakanan(Q,X2);
}

void BuyOlahInventory(PrioQueueTime *Q,Makanan X1){
    //Mengupdate isi inventory jika melakukan Buy
    AddMakanan(Q,X1);
}

void RemoveMakanan(PrioQueueTime *Q,Makanan M){
    //DequeueAt makanan pada inventory
    Makanan X;
    DequeueAt(Q,M,&X);
}

void AddMakanan(PrioQueueTime *Q, Makanan X){
    //enqueueinventory makanan pada inventory
    EnqueueInventory(Q,X);
}

void KedaluwarsaInventory(PrioQueueTime *Q)
{
    //mengurangi waktu kedaluwarsa makanan pada inventory dan membuangnya jika sudah kedaluwarsa
    int i = 0;
    for(i;i<NBElmt(*Q);i++){
        Makanan M = Elmt(*Q,i);
        PrevMinute(expMkn(M));
        if (Day(expMkn(M))==0 && Hour(expMkn(M))==0 && Minute(expMkn(M))<=0 ){
            RemoveMakanan(Q,M);
        }
    }
}

void GeserLokasi (Simulator *S,int arah){
    //Mengubah koordinat lokasi
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

// change log AddMakanan param S -> D
void DeliveryReady(Simulator *S, PrioQueueTime *D) {
    int i;
    for (i = 0; i < NBElmt(*D); i++){
        Makanan M = Elmt(*D,i), temp;
        if (Day(dlvMkn(M))<=0 && Hour(dlvMkn(M))<=0 && Minute(dlvMkn(M))<=0 ){
            AddMakanan(D, M);
            DequeueAt(D, M, &temp);
        }
    }
}
// change log RemoveMakanan param S -> &Q
void RemoveDated(Simulator *S) {
    int i;
    PrioQueueTime Q = Inventory(*S);
    for(i = 0;i<NBElmt(Q);i++){
        Makanan M = Elmt(Q,i);
        if (Day(expMkn(M))<=0 && Hour(expMkn(M))<=0 && Minute(expMkn(M))<=0 ){
            RemoveMakanan(&Q,M);
        }
    }
}

void CreateSimulatorUndo (Simulator *S, Word nama, POINT P, PrioQueueTime invent,PrioQueueTime DeliveryList, PrioQueueTime ProcessList){
    //Createsimulatordummy supaya isi dari stack undo tidak terpengaruh oleh pengurangan waktu yang ada
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