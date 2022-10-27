#include "liststatik.h"
#include <stdio.h>

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create List kosong  */
void CreateListStatik(ListStatik *l)
/* I.S. l sembarang */
/* F.S. Terbentuk List l kosong dengan kapasitas CAPACITY */
/* Proses: Inisialisasi semua elemen List l dengan MARK */
{
    /* Kamus Lokal */
    int i = 0;
    /* Algoritma */
    for (i; i < CAPACITY; i++) {
        ELMT(*l, i) = MARK;
    }
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int listLength(ListStatik l)
/* Mengirimkan banyaknya elemen efektif List */
/* Mengirimkan nol jika List kosong */
{
    /* Kamus Lokal */
    int i = 0, len = 0;
    /* Algoritma */
    while (i < CAPACITY && !isIdentical(ELMT(l, i), MARK)) {
        len = len + 1;
        i = i + 1;
    }
    return len;
}

/* *** Selektor INDEKS *** */
IdxType getFirstIdx(ListStatik l)
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l pertama */
{
    /* Kamus Lokal */
    /* Algoritma */
    return 0;
}
IdxType getLastIdx(ListStatik l)
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l terakhir */
{
    /* Kamus Lokal */
    /* Algoritma */
    return listLength(l) - 1;
}

/* ********** Test Indeks yang valid ********** */
boolean isIdxValid(ListStatik l, IdxType i)
/* Mengirimkan true jika i adalah indeks yang valid utk kapasitas List l */
/* yaitu antara indeks yang terdefinisi utk container*/
{
    /* Kamus Lokal */
    /* Algoritma */
    return (i >= 0 && i < CAPACITY);
}
boolean isIdxEff(ListStatik l, IdxType i)
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk List l */
/* yaitu antara 0..length(l)-1 */
{
    /* Kamus Lokal */
    /* Algoritma */
    return (i >= 0 && i < listLength(l));
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test List kosong *** */
boolean isEmpty(ListStatik l)
/* Mengirimkan true jika List l kosong, mengirimkan false jika tidak */
/* *** Test List penuh *** */
{
    /* Kamus Lokal */
    /* Algoritma */
    return listLength(l) == 0;
}
boolean isFull(ListStatik l)
/* Mengirimkan true jika List l penuh, mengirimkan false jika tidak */
{
    /* Kamus Lokal */
    /* Algoritma */
    return listLength(l) == CAPACITY;
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi List dari pembacaan *** */
void readList(ListStatik *l)
/* I.S. l sembarang */
/* F.S. List l terdefinisi */
/* Proses: membaca banyaknya elemen l dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya n */
/*    Pembacaan diulangi sampai didapat n yang benar yaitu 0 <= n <= CAPACITY */
/*    Jika n tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < n <= CAPACITY; Lakukan n kali:
          Baca elemen mulai dari indeks 0 satu per satu diakhiri enter */
/*    Jika n = 0; hanya terbentuk List kosong */
{
    /* Kamus Lokal */
    int idx, i = 0;
    /* Algoritma */
    CreateListStatik(l);
    do
    {
        scanf("%d", &idx);
    } while (idx < 0 || idx > CAPACITY);
    
    for (i; i < idx; i++) {
        scanf("%d", &(ELMT(*l, i)));
    }
}
void printList(ListStatik l)
/* Proses : Menuliskan isi List dengan traversal, List ditulis di antara kurung
   siku; antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan
   karakter di depan, di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. l boleh kosong */
/* F.S. Jika l tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika List kosong : menulis [] */
{
    /* Kamus Lokal */
    int i = 0;
    /* Algoritma */
    printf("[");
    for (i; isIdxEff(l, i); i++) {
        if (i != 0) {
			printf(",");
		}
		printf("%d", ELMT(l,i));
    }
    printf("]\n");
}

// /* ********** OPERATOR ARITMATIKA ********** */
// /* *** Aritmatika List : Penjumlahan, pengurangan, perkalian, ... *** */
// ListStatik plusMinusList(ListStatik l1, ListStatik l2, boolean plus)
// /* Prekondisi : l1 dan l2 berukuran sama dan tidak kosong */
// /* Jika plus = true, mengirimkan  l1+l2, yaitu setiap elemen l1 dan l2 pada
//        indeks yang sama dijumlahkan */
// /* Jika plus = false, mengirimkan l1-l2, yaitu setiap elemen l1 dikurangi
//        elemen l2 pada indeks yang sama */
// {
//     /* Kamus Lokal */
//     int i = 0;
//     ListStatik l;
//     /* Algoritma */
//     CreateListStatik(&l);
//     for (i; i < listLength(l1); i++) {
//         if (plus) {
//             ELMT(l, i) = ELMT(l1, i) + ELMT(l2, i);
//         } else {
//             ELMT(l, i) = ELMT(l1, i) - ELMT(l2, i);
//         }
//     }
//     return l;
// }

/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan List: *** */
boolean isListEqual(ListStatik l1, ListStatik l2)
/* Mengirimkan true jika l1 sama dengan l2 yaitu jika ukuran l1 = l2 dan semua
   elemennya sama */
{
    /* Kamus Lokal */
    int i = 0;
    /* Algoritma */
    if (listLength(l1) == listLength(l2)) {
        for (i; i < listLength(l1); i++) {
            if (!isIdentical(ELMT(l1, i), ELMT(l2, i))) {
                return false;
            }
        }
        return true;
    }
    return false;
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : List boleh kosong!! *** */
int indexOf(ListStatik l, ElType val)
/* Search apakah ada elemen List l yang bernilai val */
/* Jika ada, menghasilkan indeks i terkecil, dengan ELMT(l,i) = val */
/* Jika tidak ada atau jika l kosong, mengirimkan IDX_UNDEF */
/* Skema Searching yang digunakan bebas */
{
    /* Kamus Lokal */
    int i = 0;
    /* Algoritma */
    while (i < listLength(l) && !isIdentical(ELMT(l, i), val)) {
        i = i + 1;
    }
    if (i < listLength(l)) {
        return i;
    } else {
        return IDX_UNDEF;
    }
}

/* ********** NILAI EKSTREM ********** */
void extremeFoodId(ListStatik l, ElType *max, ElType *min)
/* I.S. List l tidak kosong */
/* F.S. Max berisi nilai terbesar dalam l;
        Min berisi nilai terkecil dalam l */
{   /* Kamus Lokal */
    int i = 1;
    /* Algoritma */
    *max = ELMT(l, 0);
    *min = ELMT(l, 0);
    for (i; i < listLength(l); i++) {
        if (IDX(l, i) > (*max).id) {
            *max = ELMT(l, i);
        }
        if (IDX(l, i) < (*min).id) {
            *min = ELMT(l, i);
        }
    }
}

void extremeFoodExp(ListStatik l, ElType *max, ElType *min)
/* I.S. List l tidak kosong */
/* F.S. Max berisi nilai terbesar dalam l;
        Min berisi nilai terkecil dalam l */
{   /* Kamus Lokal */
    int i = 1;
    /* Algoritma */
    *max = ELMT(l, 0);
    *min = ELMT(l, 0);
    for (i; i < listLength(l); i++) {
        if (TGT(EXP(l, i), (*max).expired)) {
            *max = ELMT(l, i);
        }
        if (TLT(EXP(l, i), (*min).expired)) {
            *min = ELMT(l, i);
        }
    }
}

void extremeFoodDlv(ListStatik l, ElType *max, ElType *min)
/* I.S. List l tidak kosong */
/* F.S. Max berisi nilai terbesar dalam l;
        Min berisi nilai terkecil dalam l */
{   /* Kamus Lokal */
    int i = 1;
    /* Algoritma */
    *max = ELMT(l, 0);
    *min = ELMT(l, 0);
    for (i; i < listLength(l); i++) {
        if (TGT(DLV(l, i), (*max).delivery)) {
            *max = ELMT(l, i);
        }
        if (TLT(DLV(l, i), (*min).delivery)) {
            *min = ELMT(l, i);
        }
    }
}

/* ********** MENAMBAH ELEMEN ********** */
/* *** Menambahkan elemen terakhir *** */
void insertFirst(ListStatik *l, ElType val)
/* Proses: Menambahkan val sebagai elemen pertama List */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen pertama l yang baru */
{   /* Kamus Lokal */
    int i = getLastIdx(*l) + 1, firstIndex = 0;
    /* Algoritma */
    for (i; i > 0; i--) {
        ELMT(*l, i) = ELMT(*l, i - 1);
    }
    ELMT(*l, 0) = val;
}
/* *** Menambahkan elemen pada index tertentu *** */
void insertAt(ListStatik *l, ElType val, IdxType idx)
/* Proses: Menambahkan val sebagai elemen pada index idx List */
/* I.S. List l tidak kosong dan tidak penuh, idx merupakan index yang valid di l */
/* F.S. val adalah elemen yang disisipkan pada index idx l */
/* *** Menambahkan elemen terakhir *** */
{   /* Kamus Lokal */
    int i = getLastIdx(*l) + 1;
    /* Algoritma */    
    for (i; i > idx; i--) {
        ELMT(*l, i) = ELMT(*l, i - 1);
    }
    ELMT(*l, idx) = val;
}
void insertLast(ListStatik *l, ElType val)
/* Proses: Menambahkan val sebagai elemen terakhir List */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */
{   /* Kamus Lokal */
    /* Algoritma */
    ELMT(*l, listLength(*l)) = val;
}

/* ********** MENGHAPUS ELEMEN ********** */
/* *** Menghapus elemen pertama *** */
void deleteFirst(ListStatik *l, ElType *val) 
/* Proses : Menghapus elemen pertama List */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen pertama l sebelum penghapusan, */
/*      Banyaknya elemen List berkurang satu */
/*      List l mungkin menjadi kosong */
{   /* Kamus Lokal */
    int i = 0, j = listLength(*l) - 1;
    /* Algoritma */
    *val = ELMT(*l, 0);
    for (i; i < j; i++) {
        ELMT(*l, i) = ELMT(*l, i + 1);
    }
    ELMT(*l, listLength(*l) - 1) = MARK;
}
/* *** Menghapus elemen pada index tertentu *** */
void deleteAt(ListStatik *l, ElType *val, IdxType idx)
/* Proses : Menghapus elemen pada index idx List */
/* I.S. List tidak kosong, idx adalah index yang valid di l */
/* F.S. val adalah nilai elemen pada index idx l sebelum penghapusan, */
/*      Banyaknya elemen List berkurang satu */
/*      List l mungkin menjadi kosong */
/* *** Menghapus elemen terakhir *** */
{   /* Kamus Lokal */
    int i = idx;
    /* Algoritma */
    *val = ELMT(*l, idx);
    ELMT(*l, idx) = MARK;
    for (i; i < listLength(*l) - 1; i++) {
        ELMT(*l, i) = ELMT(*l, i + 1);
    }
    ELMT(*l, listLength(*l)) = MARK;
}
void deleteLast(ListStatik *l, ElType *val)
/* Proses : Menghapus elemen terakhir List */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen List berkurang satu */
/*      List l mungkin menjadi kosong */
{   /* Kamus Lokal */
    /* Algoritma */
    *val = ELMT(*l, getLastIdx(*l));
    ELMT(*l, getLastIdx(*l)) = MARK;
}

/* ********** SORTING ********** */
void sortFoodId(ListStatik *l, boolean asc)
/* I.S. l boleh kosong */
/* F.S. Jika asc = true, l terurut membesar */
/*      Jika asc = false, l terurut mengecil */
/* Proses : Mengurutkan l dengan salah satu algoritma sorting,
   algoritma bebas */
{   /* Kamus Lokal */
    int i = getFirstIdx(*l), j;
    Makanan temp;
    /* Algoritma */
    if (!isEmpty(*l)) {
        if (asc) {
            for (i; i<=getLastIdx(*l) - 1; i++) {
                j = i + 1;
                for (j; j <= getLastIdx(*l); j++) {
                    if (IDX(*l, i) > IDX(*l, j)) {
                        temp = ELMT(*l, i);
                        ELMT(*l, i) = ELMT(*l, j);
                        ELMT(*l, j) = temp;
                    }
                }
            }
        } else if (!asc){
            i = getFirstIdx(*l);
            for (i; i<=getLastIdx(*l) - 1; i++) {
                j = i + 1;
                for (j; j <= getLastIdx(*l); j++) {
                    if (IDX(*l, i) < IDX(*l, j)) {
                        temp = ELMT(*l, i);
                        ELMT(*l, i) = ELMT(*l, j);
                        ELMT(*l, j) = temp;
                    }
                }
            }
        }
    }
}

void sortFoodExp(ListStatik *l, boolean asc)
/* I.S. l boleh kosong */
/* F.S. Jika asc = true, l terurut membesar */
/*      Jika asc = false, l terurut mengecil */
/* Proses : Mengurutkan l dengan salah satu algoritma sorting,
   algoritma bebas */
{   /* Kamus Lokal */
    int i = getFirstIdx(*l), j;
    Makanan temp;
    /* Algoritma */
    if (!isEmpty(*l)) {
        if (asc) {
            for (i; i<=getLastIdx(*l) - 1; i++) {
                j = i + 1;
                for (j; j <= getLastIdx(*l); j++) {
                    if (TGT(EXP(*l, i), EXP(*l, j))) {
                        temp = ELMT(*l, i);
                        ELMT(*l, i) = ELMT(*l, j);
                        ELMT(*l, j) = temp;
                    }
                }
            }
        } else if (!asc){
            i = getFirstIdx(*l);
            for (i; i<=getLastIdx(*l) - 1; i++) {
                j = i + 1;
                for (j; j <= getLastIdx(*l); j++) {
                    if (TLT(EXP(*l, i), EXP(*l, j))) {
                        temp = ELMT(*l, i);
                        ELMT(*l, i) = ELMT(*l, j);
                        ELMT(*l, j) = temp;
                    }
                }
            }
        }
    }
}

void sortFoodDlv(ListStatik *l, boolean asc)
/* I.S. l boleh kosong */
/* F.S. Jika asc = true, l terurut membesar */
/*      Jika asc = false, l terurut mengecil */
/* Proses : Mengurutkan l dengan salah satu algoritma sorting,
   algoritma bebas */
{   /* Kamus Lokal */
    int i = getFirstIdx(*l), j;
    Makanan temp;
    /* Algoritma */
    if (!isEmpty(*l)) {
        if (asc) {
            for (i; i<=getLastIdx(*l) - 1; i++) {
                j = i + 1;
                for (j; j <= getLastIdx(*l); j++) {
                    if (TGT(DLV(*l, i), DLV(*l, j))) {
                        temp = ELMT(*l, i);
                        ELMT(*l, i) = ELMT(*l, j);
                        ELMT(*l, j) = temp;
                    }
                }
            }
        } else if (!asc){
            i = getFirstIdx(*l);
            for (i; i<=getLastIdx(*l) - 1; i++) {
                j = i + 1;
                for (j; j <= getLastIdx(*l); j++) {
                    if (TLT(DLV(*l, i), DLV(*l, j))) {
                        temp = ELMT(*l, i);
                        ELMT(*l, i) = ELMT(*l, j);
                        ELMT(*l, j) = temp;
                    }
                }
            }
        }
    }
}