#ifndef Simulator_H
#define Simulator_H

#include "../boolean.h"
#include "../piroqueue/piroqueue.h"
#include "../Point/point.h"
#include "../MesinKata/wordmachine.h"
#include "../MesinKata/charmachine.h"
#include "../Makanan/makanan.h"
#include "../Stack/stack.h"
#include "../Time/time.h"
#include "../String/string.h"

typedef struct {
    Word Nama;
    POINT P;
    PrioQueueTime Q;
}Simulator;

#define Nama(S) (S).Nama
#define Lokasi(S) (S).P
#define Inventory(S) (S).Q


void CreateSimulator(Simulator *S, Word nama, POINT P, PrioQueueTime Q);

void ReadSimulator (Simulator *S);
//Membaca Simulator

void DisplaySimulator(Simulator S);
//Menampilkan Simulator

void DisplayNama (Simulator S);
//Menampilkan nama

void DisplayLokasi (Simulator S);
//Menampilkan koordinat lokasi

void DisplayInventory (Simulator S);
//Menampilkan list inventory

void OlahMakananInventory(Simulator *S, int command,int jumlah, Makanan X1, Makanan X2,Makanan X3, Makanan X4);

void MixOlahInventory(Simulator *S, int jumlah, Makanan X1, Makanan X2, Makanan X3, Makanan X4);

void ChopOlahInventory (Simulator *S, Makanan X1, Makanan X2);

void FryOlahInventory(Simulator *S,int jumlah, Makanan X1, Makanan X2, Makanan X3);

void BoilOlahInventory(Simulator *S, Makanan X1, Makanan X2);

void BuyOlahInventory(Simulator *S,Makanan X1);

void RemoveMakanan(Simulator *S, Makanan M);

void AddMakanan(Simulator *S, Makanan X);

void KedaluwarsaInventory(Simulator *S);

void GeserLokasi (Simulator *S,int arah);
//Mengubah koordinat lokasi

void DeliveryReady(Simulator *S, PrioQueueTime *D);

void RemoveDated(Simulator *S);

#endif
