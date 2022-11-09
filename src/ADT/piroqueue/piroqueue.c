#include "piroqueue.h"
#include <stdio.h>
#include <stdlib.h>

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
void EnqueueInventory (PrioQueueTime * Q, Makanan M){
/* Proses: Menambahkan X pada Q dengan aturan priority queue, terurut membesar berdasarkan expiry time */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X disisipkan pada posisi yang tepat sesuai dengan prioritas,
    TAIL "maju" dengan mekanisme circular buffer; */
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

void EnqueueDelivery (PrioQueueTime * Q, Makanan M){
/* Proses: Menambahkan X pada Q dengan aturan priority queue, terurut membesar berdasarkan delivery time */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X disisipkan pada posisi yang tepat sesuai dengan prioritas,
    TAIL "maju" dengan mekanisme circular buffer; */
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
            if (TLT(dlvMkn(Elmt(*Q, i)), dlvMkn(Elmt(*Q, idx)))){
                Temp = Elmt(*Q, i);
                Elmt(*Q, i) = Elmt(*Q, idx);
                Elmt(*Q, idx) = Temp;
            }
            i = idx;
        }

    }
}

void Dequeue (PrioQueueTime * Q, Makanan * X){
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer;
        Q mungkin kosong */
    *X = InfoHead(*Q);
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


/* Operasi Tambahan */

void PrintPrioQueueTimeInventory (PrioQueueTime Q){
/* Mencetak isi queue Q ke layar untuk menunjukkan isi inventory*/
    if (!IsEmptyQueue(Q))
    {
        int nomor = 1;
        if (Tail(Q) >= Head(Q)){
            for (int i = Head(Q); i <= Tail(Q); i++){
                printf("%d. ", nomor);
                nomor+=1;
                printWord(nameMkn(Elmt(Q, i)));
                printf(" - ");
                TulisTIMEKadaluarsa(expMkn(Elmt(Q, i)));
                printf("\n");
                // printf("%c %d\n", expMkn(Elmt(Q, i)), idMkn(Elmt(Q, i)));
            }
        }
        else {
            for(int i = Head(Q); i < MaxEl(Q); i++){
                printf("%d. ", nomor);
                nomor+=1;
                printWord(nameMkn(Elmt(Q, i)));
                printf(" - ");
                TulisTIMEKadaluarsa(expMkn(Elmt(Q, i)));
                printf("\n");
            }
            for (int i = 0; i <= Tail(Q); i++){
                printf("%d. ", nomor);
                nomor+=1;
                printWord(nameMkn(Elmt(Q, i)));
                printf(" - ");
                TulisTIMEKadaluarsa(expMkn(Elmt(Q, i)));
                printf("\n");
            }
        }
    }
    printf("\n");
}

void PrintPrioQueueTimeDelivery (PrioQueueTime Q){
/* Mencetak isi queue Q ke layar untuk menunjukkan isi delivery*/
    if (!IsEmptyQueue(Q))
    {
        int nomor = 1;
        if (Tail(Q) >= Head(Q)){
            for (int i = Head(Q); i <= Tail(Q); i++){
                printf("%d. ", nomor);
                nomor+=1;
                printWord(nameMkn(Elmt(Q, i)));
                printf(" - ");
                TulisTIMEKadaluarsa(dlvMkn(Elmt(Q, i)));
                printf("\n");
                // printf("%c %d\n", expMkn(Elmt(Q, i)), idMkn(Elmt(Q, i)));
            }
        }
        else {
            for(int i = Head(Q); i < MaxEl(Q); i++){
                printf("%d. ", nomor);
                nomor+=1;
                printWord(nameMkn(Elmt(Q, i)));
                printf(" - ");
                TulisTIMEKadaluarsa(dlvMkn(Elmt(Q, i)));
                printf("\n");
            }
            for (int i = 0; i <= Tail(Q); i++){
                printf("%d. ", nomor);
                nomor+=1;
                printWord(nameMkn(Elmt(Q, i)));
                printf(" - ");
                TulisTIMEKadaluarsa(dlvMkn(Elmt(Q, i)));
                printf("\n");
            }
        }
    }
    printf("\n");
}

void PrintPrioQueueTimeProcess (PrioQueueTime Q){
/* Mencetak isi queue Q ke layar untuk menunjukkan isi delivery*/
    if (!IsEmptyQueue(Q))
    {
        int nomor = 1;
        if (Tail(Q) >= Head(Q)){
            for (int i = Head(Q); i <= Tail(Q); i++){
                printf("%d. ", nomor);
                nomor+=1;
                printWord(nameMkn(Elmt(Q, i)));
                printf(" - ");
                TulisTIMEKadaluarsa(dlvMkn(Elmt(Q, i)));
                printf(" - ");
                printWord(actMkn(Elmt(Q,i)));
                printf("\n");
                // printf("%c %d\n", expMkn(Elmt(Q, i)), idMkn(Elmt(Q, i)));
            }
        }
        else {
            for(int i = Head(Q); i < MaxEl(Q); i++){
                printf("%d. ", nomor);
                nomor+=1;
                printWord(nameMkn(Elmt(Q, i)));
                printf(" - ");
                TulisTIMEKadaluarsa(dlvMkn(Elmt(Q, i)));
                printf(" - ");
                printWord(actMkn(Elmt(Q,i)));
                printf("\n");
            }
            for (int i = 0; i <= Tail(Q); i++){
                printf("%d. ", nomor);
                nomor+=1;
                printWord(nameMkn(Elmt(Q, i)));
                printf(" - ");
                TulisTIMEKadaluarsa(dlvMkn(Elmt(Q, i)));
                printf(" - ");
                printWord(actMkn(Elmt(Q,i)));
                printf("\n");
            }
        }
    }
    printf("\n");
}

int PencariMakanan(PrioQueueTime *Q, Makanan M){
/* Menemukan index dari makanan pada prioqueue*/
    int i = Head(*Q);
    boolean found = false;
    while(!found && i<=Tail(*Q)){
        Makanan m2 = Elmt(*Q,i);
        if(idMkn(m2)==idMkn(M)){
            found = true;
        }
        else {
            i= (i+1)%MaxEl(*Q);
        }
    }
    if (!found){
        i=-1;
    }
    return i;
}

void DequeueAt(PrioQueueTime *Q, Makanan M, Makanan *X){
    int index = PencariMakanan(Q,M);
    if(index==-1){
        printf("Bahan Makanan tidak ada di Inventory\n");
    }
    else {
        if(index==Head(*Q)){
            Dequeue(Q,X);
        }
        else {
            *X=Elmt(*Q,index);
            for (index;index<NBElmt(*Q);index++){
                Elmt(*Q,index) = Elmt(*Q,index+1);
            }
            Tail(*Q) = (Tail(*Q) - 1) % MaxEl(*Q);
        }
    }
}

void decrementNExp(PrioQueueTime *Q, int N) {
/* Mengurangi setiap waktu expiry pada queue sebesar N menit*/
    if (!IsEmptyQueue(*Q)) {
        if (Tail(*Q) >= Head(*Q)){
            for (int i = Head(*Q); i <= Tail(*Q); i++){
                expMkn(Elmt(*Q, i)) = PrevNMinute(expMkn(Elmt(*Q, i)), N);
            }
        }
        else {
            for(int i = Head(*Q); i < MaxEl(*Q); i++){
                expMkn(Elmt(*Q, i)) = PrevNMinute(expMkn(Elmt(*Q, i)), N);
            }
            for (int i = 0; i <= Tail(*Q); i++){
                expMkn(Elmt(*Q, i)) = PrevNMinute(expMkn(Elmt(*Q, i)), N);
            }
        }
    }
}

void incrementNExp(PrioQueueTime *Q, int N) {
/* Mengurangi setiap waktu expiry pada queue sebesar N menit*/
    if (!IsEmptyQueue(*Q)) {
        if (Tail(*Q) >= Head(*Q)){
            for (int i = Head(*Q); i <= Tail(*Q); i++){
                expMkn(Elmt(*Q, i)) = NextNMinute(expMkn(Elmt(*Q, i)), N);
            }
        }
        else {
            for(int i = Head(*Q); i < MaxEl(*Q); i++){
                expMkn(Elmt(*Q, i)) = NextNMinute(expMkn(Elmt(*Q, i)), N);
            }
            for (int i = 0; i <= Tail(*Q); i++){
                expMkn(Elmt(*Q, i)) = NextNMinute(expMkn(Elmt(*Q, i)), N);
            }
        }
    }
}

void decrementHMExp(PrioQueueTime *Q, int hours, int minutes) {
/* Mengurangi setiap waktu expiry pada queue sebesar 'hours' jam dan 'minutes' menit*/
    if (!IsEmptyQueue(*Q)) {
        int totalMinuteDecrement = (hours * 60) + minutes;
        decrementNExp(Q, totalMinuteDecrement);
    }
}

void decrementNDel(PrioQueueTime *Q, int N) {
/* Mengurangi setiap waktu delivery pada queue sebesar N menit*/
    if (!IsEmptyQueue(*Q)) {
        if (Tail(*Q) >= Head(*Q)){
            for (int i = Head(*Q); i <= Tail(*Q); i++){
                dlvMkn(Elmt(*Q, i)) = PrevNMinute(dlvMkn(Elmt(*Q, i)), N);
            }
        }
        else {
            for(int i = Head(*Q); i < MaxEl(*Q); i++){
                dlvMkn(Elmt(*Q, i)) = PrevNMinute(dlvMkn(Elmt(*Q, i)), N);
            }
            for (int i = 0; i <= Tail(*Q); i++){
                dlvMkn(Elmt(*Q, i)) = PrevNMinute(dlvMkn(Elmt(*Q, i)), N);
            }
        }
    }
}

void incrementNDel(PrioQueueTime *Q, int N) {
/* Mengurangi setiap waktu delivery pada queue sebesar N menit*/
    if (!IsEmptyQueue(*Q)) {
        if (Tail(*Q) >= Head(*Q)){
            for (int i = Head(*Q); i <= Tail(*Q); i++){
                dlvMkn(Elmt(*Q, i)) = NextNMinute(dlvMkn(Elmt(*Q, i)), N);
            }
        }
        else {
            for(int i = Head(*Q); i < MaxEl(*Q); i++){
                dlvMkn(Elmt(*Q, i)) = NextNMinute(dlvMkn(Elmt(*Q, i)), N);
            }
            for (int i = 0; i <= Tail(*Q); i++){
                dlvMkn(Elmt(*Q, i)) = NextNMinute(dlvMkn(Elmt(*Q, i)), N);
            }
        }
    }
}

void decrementHMDel(PrioQueueTime *Q, int hours, int minutes) {
/* Mengurangi setiap waktu delivery pada queue sebesar 'hours' jam dan 'minutes' menit*/
    if (!IsEmptyQueue(*Q)) {
        int totalMinuteDecrement = (hours * 60) + minutes;
        decrementNDel(Q, totalMinuteDecrement);
    }
}
