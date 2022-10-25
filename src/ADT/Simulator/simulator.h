#ifndef Simulator_H
#define Simulator_H

#include "boolean.h"
#include "prioqueuetime.h"
#include "point.h"

typedef struct {
    char name[100];
    POINT P;
    PrioQueueTime Q;
}Simulator;

#define Nama(S) (S).name[100]
#define Lokasi(S) (S).P
#define Inventory(S) (S).Q


void CreateSimulator(Simulator *S, POINT P, PrioQueueTime Q);

void ReadSimulator (Simulator *S);
//Membaca Simulator

void DisplaySimulator(Simulator S);
//Menampilkan Simulator

void DisplayName (Simulator S);
//Menampilkan nama

void DisplayLokasi (Simulator S);
//Menampilkan koordinat lokasi

void GeserLokasi (Simulator *S,int arah);
//Mengubah koordinat lokasi

#endif