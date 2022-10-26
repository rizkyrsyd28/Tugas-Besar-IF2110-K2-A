#include <stdio.h>
#include "simulator.h"

void CreateSimulator(Simulator *S, POINT P, PrioQueueTime Q){
    Nama(*S)="BNMO";
    Lokasi(*S)=P;
    Inventory(*S) = Q;
}

void ReadSimulator(Simulator *S){
    //Membaca Simulator
    POINT P;
    PrioQueueTime Q;
    Absis(P) = 0;
    Ordinat(P) = 0;
    CreateSimulator(S,P,Q);
}

void DisplaySimulator(Simulator S){
    //Menampilkan Simulator
    DisplayNama(S);
    print(" di posisi: ");
    DisplayLokasi(S);
    printf("\n");
}

void DisplayName(Simulator S)
{
    //Menampilkan nama
    printf("%s", Nama(S));
}

void DisplayLokasi(Simulator S){
    //Menampilkan koordinat lokasi
    printf("(%.0f,%.0f)", Absis(Lokasi(S)), Ordinat(Lokasi(S)));
}

void GeserLokasi (Simulator *S,int arah){
    //Mengubah koordinat lokasi
    if (arah==1){//NORTH
        Absis(Lokasi(*S)) -=1;
    }
    else if (arah ==2){//EAST
        Ordinat(Lokasi(*S))+=1;
    }
    else if (arah ==3){//WEST
        Ordinat(Lokasi(*S))-=1;
    }
    else if (arah ==4){//SOUTH
        Absis(Lokasi(*S))+=1;
    }
}