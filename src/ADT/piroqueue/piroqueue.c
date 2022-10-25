#include "piroqueue.h"
#include <stdio.h>

/* ********* Prototype ********* */
boolean IsEmpty (PrioQueueTime Q){
    return (Head(Q) == Nil && Tail(Q) == Nil);
}
/* Mengirim true jika Q kosong: lihat definisi di atas */
boolean IsFull (PrioQueueTime Q){
    return (NBElmt(Q) == MaxEl(Q));
}
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
int NBElmt (PrioQueueTime Q){
    if(IsEmpty(Q)){
        return 0;
    }
    else{
        if (Tail(Q) >= Head(Q))
            return Tail(Q) - Head(Q) + 1;
        else
            return Tail(Q) - Head(Q) + MaxEl(Q) + 1;
    }
}
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */

/* *** Kreator *** */
void MakeEmpty (PrioQueueTime * Q, int Max){
    MaxEl(*Q) = Max;
    (*Q).T = (infotype *) malloc (Max * sizeof(infotype));
    Head(*Q) = Nil;
    Tail(*Q) = Nil;
}
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */

/* *** Destruktor *** */
void DeAlokasi(PrioQueueTime * Q){
    free((*Q).T);
    MaxEl(*Q) = 0;
}
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */

/* *** Primitif Add/Delete *** */
void Enqueue (PrioQueueTime * Q, infotype X){
    if (IsEmpty(*Q)){
        Head(*Q) = 0;
        Tail(*Q) = 0;
        InfoTail(*Q) = X;
    }
    else {
        Tail(*Q) = (Tail(*Q) + 1) % MaxEl(*Q);
        InfoTail(*Q) = X;
        
        int i = Tail(*Q);
        infotype Temp;

        while (i != Head(*Q)){
            int idx = (i - 1 + MaxEl(*Q)) % MaxEl(*Q);
            if (Time(Elmt(*Q, i)) < Time(Elmt(*Q, idx))){
                Temp = Elmt(*Q, i);
                Elmt(*Q, i) = Elmt(*Q, idx);
                Elmt(*Q, idx) = Temp;
            }
            i = idx;
        }

    }
}
/* Proses: Menambahkan X pada Q dengan aturan priority queue, terurut membesar berdasarkan time */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X disisipkan pada posisi yang tepat sesuai dengan prioritas,
        TAIL "maju" dengan mekanisme circular buffer; */
void Dequeue (PrioQueueTime * Q, infotype * X){
    *X = InfoTail(*Q);
    if (NBElmt(*Q) == 1){
        Head(*Q) = Nil;
        Tail(*Q) = Nil;
    }
    else {
        if (Head(*Q) == MaxEl(*Q) - 1)
            Head(*Q) = 1;
        else
            Head(*Q)++;

    }
}
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer;
        Q mungkin kosong */

/* Operasi Tambahan */
void PrintPrioQueueTime (PrioQueueTime Q){
    if (!IsEmpty(Q))
    {
        if (Tail(Q) > Head(Q)){
            for (int i = Head(Q); i <= Tail(Q); i++){
                printf("%c %d\n", Time(Elmt(Q, i)), Info(Elmt(Q, i)));
            }
        }
        else {
            for(int i = Head(Q); i < MaxEl(Q); i++){
                printf("%c %d\n", Time(Elmt(Q, i)), Info(Elmt(Q, i)));
            }
            for (int i = 0; i <= Tail(Q); i++){
                printf("%c %d\n", Time(Elmt(Q, i)), Info(Elmt(Q, i)));
            }
        }
    }
    print("#\n");
}
/* Mencetak isi queue Q ke layar */
/* I.S. Q terdefinisi, mungkin kosong */
/* F.S. Q tercetak ke layar dengan format:
<time-1> <elemen-1>
...
<time-n> <elemen-n>
#
*/