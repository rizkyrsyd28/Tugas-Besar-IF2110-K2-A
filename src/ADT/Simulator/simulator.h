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
/* I.S. Sembarang
F.S. Simulator terdefinisi dengan spesifikasi sesuai parameter yang diinputkan*/

void ReadSimulator (Simulator *S);
/* I.S. sembarang
F.S. Simulator terdefinisi, membuat simulator sesuai input dari pengguna*/

void DisplaySimulator(Simulator S);
/* I.S. S terdefinisi
F.S. Menampilkan nama dan posisi simulator */

void DisplayNama(Simulator S);
/* I.S. S terdefinisi
F.S. Nama Simulator ditampilkan*/

void DisplayLokasi(Simulator S);
/* I.S. S terdefinisi
F.S. Lokasi Simulator ditampilkan */

void DisplayInventory(Simulator S);
/* I.S. S terdefinisi
F.S. INventory Simulator ditampilkan */

void MixOlahInventory(PrioQueueTime *Q, PrioQueueTime *DestQ, Cookbook cb, ID id, int idx, ListStatik fs);
/* I.S. Semua parameter prosedur terdefinisi
F.S. Mengeluarkan bahan yang dimasak dari Inventory, memasukan bahan yang ingin dibuat ke process list*/

void ChopOlahInventory (PrioQueueTime *Q, PrioQueueTime *DestQ, Makanan X1, Makanan X2);
/* I.S. Semua parameter prosedur terdefinisi
F.S. Mengeluarkan bahan yang dimasak dari Inventory, memasukan bahan yang ingin dibuat ke process list*/

void FryOlahInventory(PrioQueueTime *Q, PrioQueueTime *DestQ, Cookbook cb, ID id, int idx, ListStatik fs);
/* I.S. Semua parameter prosedur terdefinisi
F.S. Mengeluarkan bahan yang dimasak dari Inventory, memasukan bahan yang ingin dibuat ke process list*/

void BoilOlahInventory(PrioQueueTime *Q, PrioQueueTime *DestQ, Cookbook cb, ID id, int idx, ListStatik fs);
/* I.S. Semua parameter prosedur terdefinisi
F.S. Mengeluarkan bahan yang dimasak dari Inventory, memasukan bahan yang ingin dibuat ke process list*/

void RemoveMakanan(PrioQueueTime *Q, Makanan M);
/* I.S. *Q terdefinisi
F.S. DequeueAt makanan pada inventory. Makanan dikeluarkan dari inventory*/

void GeserLokasi (Simulator *S,int arah);
/* I.S. *S terdefinisi
F.S. *S bergerak ke arah yang diinginkan oleh user */

void CreateSimulatorUndo (Simulator *S, Word nama, POINT P, PrioQueueTime invent,PrioQueueTime DeliveryList, PrioQueueTime ProcessList);
 /* I.S. Sembarang
 F.S. Dibuat Createsimulatordummy supaya isi dari stack undo tidak terpengaruh oleh pengurangan waktu yang ada */

#endif
