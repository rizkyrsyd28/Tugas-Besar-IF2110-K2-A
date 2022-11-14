/* File : prioqueuetime.h */
/* Definisi ADT Priority Queue Time dengan representasi array secara eksplisit dan alokasi dinamik */
/* Model Implementasi Versi III dengan circular buffer */
/* Elemen queue terurut membesar berdasarkan elemen time */

#ifndef prioqueuetime_H
#define prioqueuetime_H

#include "../boolean.h"
#include "../Makanan/makanan.h"

#define Nil -1
/* Konstanta untuk mendefinisikan address tak terdefinisi */

typedef int address;   
/* indeks tabel */
/* Contoh deklarasi variabel bertype PrioQueueTime : */
/* Versi I : tabel dinamik, Head dan Tail eksplisit, ukuran disimpan */
typedef struct {
    Makanan * T;   /* tabel penyimpan elemen */
    address HEAD;  /* alamat penghapusan */
    address TAIL;  /* alamat penambahan */
    int MaxEl;     /* Max elemen queue */
} PrioQueueTime;
/* Definisi PrioQueueTime kosong: HEAD=Nil; TAIL=Nil. */
/* Catatan implementasi: T[0] tidak pernah dipakai */

/* ********* AKSES (Selektor) ********* */
/* Jika e adalah infotype dan Q adalah PrioQueueTime, maka akses elemen : */
#define Head(Q)     (Q).HEAD
#define Tail(Q)     (Q).TAIL
#define InfoHead(Q) (Q).T[(Q).HEAD]
#define InfoTail(Q) (Q).T[(Q).TAIL]
#define MaxEl(Q)    (Q).MaxEl
#define Elmt(Q,i)   (Q).T[(i)]

/* ********* Prototype ********* */
boolean IsEmptyQueue (PrioQueueTime Q);
/* Mengirim true jika Q kosong: lihat definisi di atas */
boolean IsFullQueue (PrioQueueTime Q);
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
int NBElmt (PrioQueueTime Q);
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */

/* *** Kreator *** */
void MakeEmptyQueue (PrioQueueTime * Q, int Max);
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */

/* *** Destruktor *** */
void DeAlokasi(PrioQueueTime * Q);
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */

/* *** Primitif Add/Delete *** */
void EnqueueInventory (PrioQueueTime * Q, Makanan M);
/* Proses: Menambahkan X pada Q dengan aturan priority queue, terurut membesar berdasarkan expiry time */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X disisipkan pada posisi yang tepat sesuai dengan prioritas,
        TAIL "maju" dengan mekanisme circular buffer; */

void EnqueueDelivery (PrioQueueTime * Q, Makanan M);
/* Proses: Menambahkan X pada Q dengan aturan priority queue, terurut membesar berdasarkan delivery time */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X disisipkan pada posisi yang tepat sesuai dengan prioritas,
    TAIL "maju" dengan mekanisme circular buffer; */

void Dequeue (PrioQueueTime * Q, Makanan * M);
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer;
        Q mungkin kosong */

/* Operasi Tambahan */
void PrintPrioQueueTimeInventory (PrioQueueTime Q);
/* Mencetak isi queue Q ke layar untuk menunjukkan isi inventory*/

void PrintPrioQueueTimeDelivery (PrioQueueTime Q);
/* Mencetak isi queue Q ke layar untuk menunjukkan isi delivery*/

int PencariMakanan(PrioQueueTime *Q, Makanan M);
/* Menemukan index dari makanan pada prioqueue*/

void DequeueAt(PrioQueueTime *Q, Makanan M, Makanan *X);
/* Mengeluarkan makanan tertentu pada prioqueue*/


void decrementNExp(PrioQueueTime *Q, int N);
/* Mengurangi setiap waktu expiry pada queue sebesar N menit*/

void incrementNExp(PrioQueueTime *Q, int N);
/* Menambahi setiap waktu expiry pada queue sebesar N menit*/

void decrementHMExp(PrioQueueTime *Q, int hours, int minutes);
/* Mengurangi setiap waktu expiry pada queue sebesar 'hours' jam dan 'minutes' menit*/

void decrementNDel(PrioQueueTime *Q, int N);
/* Mengurangi setiap waktu delivery pada queue sebesar N menit*/

void incrementNDel(PrioQueueTime *Q, int N);
/* Menamabah setiap waktu delivery pada queue sebesar N menit*/

void decrementHMDel(PrioQueueTime *Q, int hours, int minutes);
/* Mengurangi setiap waktu delivery pada queue sebesar 'hours' jam dan 'minutes' menit*/

void DequeueAtIndex(PrioQueueTime *Q, int idx, Makanan *m);
/* Menghapus makanan pada index tertentu di prioqueuetime */

#endif
