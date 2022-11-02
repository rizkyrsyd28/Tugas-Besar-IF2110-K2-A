#include <stdio.h>
#include "simulator.h"

void CreateSimulator(Simulator *S, Word nama, POINT P, PrioQueueTime Q){
    Nama(*S)= nama;
    Lokasi(*S)=P;
    Inventory(*S) = Q;
}

void ReadSimulator(Simulator *S){
    //Membaca Simulator
    Word nama;
    POINT P;
    PrioQueueTime Q;
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
    CreateSimulator(S,nama,P,Q);
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
    printf("(nama - waktu sisa kedaluwarsa)\n");
    PrintPrioQueueTime(Inventory(S));
}

void OlahMakananInventory(Simulator *S, int command,int jumlah, Makanan X1, Makanan X2,Makanan X3, Makanan X4){
    //X4 itu buat yang diadd, X1,X2,X3 yang diremove. Kalo yang diremove ga sampe 3, isi asal aja yg ga kepake
    if (command==1){//MIX
        MixOlahInventory(S,jumlah,X1,X2,X3,X4);
    }
    else if(command==2){//CHOP
        ChopOlahInventory(S,X1,X4);
    }
    else if (command==3){//FRY
        FryOlahInventory(S,jumlah,X1,X2,X4);
    }
    else if(command==4){//BOIL
        BoilOlahInventory(S,X1,X4);
    }
    else if (command ==5){
        BuyOlahInventory(S,X4);
    }
    //masukin makanan
}

void MixOlahInventory(Simulator *S, int jumlah, Makanan X1, Makanan X2, Makanan X3, Makanan X4){
    if (jumlah==2){
        RemoveMakanan(S,X1);
        RemoveMakanan(S,X2);
        AddMakanan(S,X4);
    }
    else if(jumlah==3){
        RemoveMakanan(S,X1);
        RemoveMakanan(S,X2);
        RemoveMakanan(S,X3);
        AddMakanan(S,X4);
    }
}

void ChopOlahInventory (Simulator *S, Makanan X1, Makanan X2){
    RemoveMakanan(S,X1);
    AddMakanan(S,X2);
}

void FryOlahInventory(Simulator *S,int jumlah, Makanan X1, Makanan X2, Makanan X3){
    if (jumlah==1){
        RemoveMakanan(S,X1);
        AddMakanan(S,X3);
    }
    else if (jumlah==2){
        RemoveMakanan(S,X1);
        RemoveMakanan(S,X2);
        AddMakanan(S,X3);
    }
}

void BoilOlahInventory(Simulator *S, Makanan X1, Makanan X2){
    RemoveMakanan(S,X1);
    AddMakanan(S,X2);
}

void BuyOlahInventory(Simulator *S,Makanan X1){
    AddMakanan(S,X1);
}

void RemoveMakanan(Simulator *S,Makanan M){
    PrioQueueTime Q = Inventory(*S);
    Makanan X;
    DequeueAt(&Q,M,&X);
}

void AddMakanan(Simulator *S, Makanan X){
    PrioQueueTime Q = Inventory(*S);
    Enqueue(&Q,X);
}

void KedaluwarsaInventory(Simulator *S)
{
    int i = 0;
    PrioQueueTime Q = Inventory(*S);
    for(i;i<NBElmt(Q);i++){
        Makanan M = Elmt(Q,i);
        PrevMinute(expMkn(M));
        if (Day(expMkn(M))<=0 && Hour(expMkn(M))<=0 && Minute(expMkn(M))<=0 ){
            RemoveMakanan(S,M);
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

