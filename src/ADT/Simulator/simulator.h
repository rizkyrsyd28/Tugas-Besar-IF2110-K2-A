#ifndef Simulator_H
#define Simulator_H

#include "../boolean.h"
#include "../piroqueue/piroqueue.h"
#include "../Point/point.h"
#include "../MesinKata/wordmachine.h"
#include "../MesinKata/charmachine.h"
#include "../Makanan/makanan.h"
#include "../Resep/resep.h"
// #include "../Stack/stack.h"
#include "../Time/time.h"
#include "../String/string.h"

typedef struct {
    Word Nama;
    POINT P;
    PrioQueueTime Q;//inventory
    PrioQueueTime D;//deliverylist
    PrioQueueTime PL;//processlist
}Simulator;

#define Nama(S) (S).Nama
#define Lokasi(S) (S).P
#define Inventory(S) (S).Q
#define Delivery(S) (S).D
#define ProcessList(S) (S).PL


void CreateSimulator(Simulator *S, Word nama, POINT P, PrioQueueTime Q, PrioQueueTime D, PrioQueueTime PL);
//Membuat simulator

void ReadSimulator (Simulator *S);
//Membaca Simulator

void DisplaySimulator(Simulator S);
//Menampilkan Simulator

void DisplayNama(Simulator S);
//Menampilkan nama

void DisplayLokasi(Simulator S);
//Menampilkan koordinat lokasi

void DisplayInventory(Simulator S);
//Menampilkan list inventory

void OlahMakananInventory(PrioQueueTime *Q, int command,int jumlah, Makanan X1, Makanan X2,Makanan X3, Makanan X4);
//Mengupdate isi inventory. X4 itu buat yang diadd, X1,X2,X3 yang diremove. Kalo yang diremove ga sampe 3, isi asal aja yg ga kepake

// void MixOlahInventory(PrioQueueTime *Q, int jumlah, Makanan X1, Makanan X2, Makanan X3, Makanan X4);
void MixOlahInventory(PrioQueueTime *Q, Cookbook cb, ID id, int idx, ListStatik fs);

void ChopOlahInventory (PrioQueueTime *Q, Makanan X1, Makanan X2);
//Mengupdate isi inventory jika melakukan Chop

void FryOlahInventory(PrioQueueTime *Q,int jumlah, Makanan X1, Makanan X2, Makanan X3);
//Mengupdate isi inventory jika melakukan Fry

void BoilOlahInventory(PrioQueueTime *Q, Makanan X1, Makanan X2);
//Mengupdate isi inventory jika melakukan Boil

void BuyOlahInventory(PrioQueueTime *Q,Makanan X1);
//Mengupdate isi inventory jika melakukan Buy

void RemoveMakanan(PrioQueueTime *Q, Makanan M);
//DequeueAt makanan pada inventory

void AddMakanan(PrioQueueTime *Q, Makanan X);
//enqueueinventory makanan pada inventory

void KedaluwarsaInventory(PrioQueueTime *Q);
//mengurangi waktu kedaluwarsa makanan pada inventory dan membuangnya jika sudah kedaluwarsa

void GeserLokasi (Simulator *S,int arah);
//Mengubah koordinat lokasi

void DeliveryReady(Simulator *S, PrioQueueTime *D);

void RemoveDated(Simulator *S);

void CreateSimulatorUndo (Simulator *S, Word nama, POINT P, PrioQueueTime invent,PrioQueueTime DeliveryList, PrioQueueTime ProcessList);

#endif
