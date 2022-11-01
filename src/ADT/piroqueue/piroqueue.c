#include "piroqueue.h"
#include <stdio.h>

/* ********* Prototype ********* */
boolean IsEmptyQueue (PrioQueueTime Q){
    return (Head(Q) == Nil && Tail(Q) == Nil);
}
/* Mengirim true jika Q kosong: lihat definisi di atas */
boolean IsFullQueue (PrioQueueTime Q){
    return (NBElmt(Q) == MaxEl(Q));
}
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
int NBElmt (PrioQueueTime Q){
    if(IsEmptyQueue(Q)){
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
void MakeEmptyQueue (PrioQueueTime * Q, int Max){
    MaxEl(*Q) = Max;
    (*Q).T = (Makanan *) malloc (Max * sizeof(Makanan));
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
void Enqueue (PrioQueueTime * Q, Makanan M){
    if (IsEmptyQueue(*Q)){
        Head(*Q) = 0;
        Tail(*Q) = 0;
        InfoTail(*Q) = M;
    }
    else {
        Tail(*Q) = (Tail(*Q) + 1) % MaxEl(*Q);
        InfoTail(*Q) = M;
        
        int i = Tail(*Q);
        Makanan Temp;

        while (i != Head(*Q)){
            int idx = (i - 1 + MaxEl(*Q)) % MaxEl(*Q);
            if (TLT(expMkn(Elmt(*Q, i)), expMkn(Elmt(*Q, idx)))){
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
void Dequeue (PrioQueueTime * Q, Makanan * X){
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
    if (!IsEmptyQueue(Q))
    {
        int nomor = 1;
        if (Tail(Q) > Head(Q)){
            for (int i = Head(Q); i <= Tail(Q); i++){
                printf("%d. ", nomor);
                nomor+=1;
                printWord(nameMkn(Elmt(Q, i)));
                print(" - ");
                TulisTIMEKadaluarsa(expMkn(Elmt(Q, i)));
                printf('\n');
                // printf("%c %d\n", expMkn(Elmt(Q, i)), idMkn(Elmt(Q, i)));
            }
        }
        else {
            for(int i = Head(Q); i < MaxEl(Q); i++){
                printf("%d. ", nomor);
                nomor+=1;
                printWord(nameMkn(Elmt(Q, i)));
                print(" - ");
                TulisTIMEKadaluarsa(expMkn(Elmt(Q, i)));
                printf('\n');
            }
            for (int i = 0; i <= Tail(Q); i++){
                printf("%d. ", nomor);
                nomor+=1;
                printWord(nameMkn(Elmt(Q, i)));
                print(" - ");
                TulisTIMEKadaluarsa(expMkn(Elmt(Q, i)));
                printf('\n');
            }
        }
    }
    printf("\n");
}
/* Mencetak isi queue Q ke layar */
/* I.S. Q terdefinisi, mungkin kosong */
/* F.S. Q tercetak ke layar dengan format:
<time-1> <elemen-1>
...
<time-n> <elemen-n>
#
*/

int PencariMakanan(PrioQueueTime *Q, Makanan M){
    int i = 0;
    boolean found = false;
    while(!found && i<NBElmt(*Q)){
        Makanan m2 = Elmt(*Q,i);
        if(idMkn(m2)==idMkn(M)){
            found = true;
        }
        i + (i+1)%MaxEl(*Q);
    }
    return i;
}

void DequeueAt(PrioQueueTime *Q, Makanan M, Makanan *X){
    int index = PencariMakanan(&*Q,M);
    if(index==Head(*Q)){
        Dequeue(Q,X);
    }
    else {
        *X=Elmt(*Q,index);
        for (index;index<NBElmt(*Q);index++){
            Elmt(*Q,index) = Elmt(*Q,index+1);
        }
        Tail(*Q) = (Tail(*Q) - 1) % MaxEl(*Q);//mod
    }
}

void printExp(PrioQueueTime Q, int idx) {
    TIME exp = roundToEvenHours(expMkn(Elmt(Q, idx)));
    printf("%d jam", Hour(exp));
}