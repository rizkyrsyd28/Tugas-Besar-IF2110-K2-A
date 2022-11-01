#include "liststatik.h"
#include <stdio.h>

Makanan FoodMark = {-1, {"Empty", 0}, {-1, -1, -1}, {"Empty", 0}, {0, 0},{-1, -1, -1}};

boolean timeEqual(TIME a, TIME b) {
    return ((Day(a) == Day(b)) && (Minute(a) == Minute(b)) && (Hour(a) == Hour(b)));
}

boolean isMark(ElTypeList a) {
    return (a.id == -1) && timeEqual(a.expired, FoodMark.expired) && timeEqual(a.delivery, FoodMark.delivery) && (a.action.Length == FoodMark.action.Length) && (a.name.Length == FoodMark.name.Length);
}

boolean different(ElTypeList a, ElTypeList b) {
    return (a.id == b.id) && timeEqual(a.expired, b.expired) && timeEqual(a.delivery, b.delivery) && (a.action.Length == b.action.Length) && (a.name.Length == b.name.Length);    
}

Makanan getMakanan(ID id, ListStatik foods) {
    for (int i = 0; i < listLength(foods); i++) {
        if (idMkn(ELMTLIST(foods, i)) == id) {
            return ELMTLIST(foods, i);
        }
    }
    return FoodMark;
}


/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create List kosong  */
void CreateListStatik(ListStatik *l)
/* I.S. l sembarang */
/* F.S. Terbentuk List l kosong dengan kapasitas CAPACITY */
/* Proses: Inisialisasi semua elemen List l dengan MARK */
{
    /* Kamus Lokal */
    int i;
    /* Algoritma */
    for (i = 0; i < CAPACITY; i++) {
        ELMTLIST(*l, i) = FoodMark;
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
    while (i < CAPACITY && !isMark(ELMTLIST(l, i))) {
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
// void readList(ListStatik *l)
// /* I.S. l sembarang */
// /* F.S. List l terdefinisi */
// /* Proses: membaca banyaknya elemen l dan mengisi nilainya */
// /* 1. Baca banyaknya elemen diakhiri enter, misalnya n */
// /*    Pembacaan diulangi sampai didapat n yang benar yaitu 0 <= n <= CAPACITY */
// /*    Jika n tidak valid, tidak diberikan pesan kesalahan */
// /* 2. Jika 0 < n <= CAPACITY; Lakukan n kali:
//           Baca elemen mulai dari indeks 0 satu per satu diakhiri enter */
// /*    Jika n = 0; hanya terbentuk List kosong */
// {
//     /* Kamus Lokal */
//     int idx, i = 0;
//     /* Algoritma */
//     CreateListStatik(l);
//     do
//     {
//         scanf("%d", &idx);
//     } while (idx < 0 || idx > CAPACITY);
    
//     for (i; i < idx; i++) {
//         scanf("%d", &(ELMTLIST(*l, i)));
//     }
// }
// void printList(ListStatik l)
// /* Proses : Menuliskan isi List dengan traversal, List ditulis di antara kurung
//    siku; antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan
//    karakter di depan, di tengah, atau di belakang, termasuk spasi dan enter */
// /* I.S. l boleh kosong */
// /* F.S. Jika l tidak kosong: [e1,e2,...,en] */
// /* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
// /* Jika List kosong : menulis [] */
// {
//     /* Kamus Lokal */
//     int i = 0;
//     /* Algoritma */
//     printf("[");
//     for (i; isIdxEff(l, i); i++) {
//         if (i != 0) {
// 			printf(",");
// 		}
// 		printf("%d", ELMTLIST(l,i));
//     }
//     printf("]\n");
// }

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
//             ELMTLIST(l, i) = ELMTLIST(l1, i) + ELMTLIST(l2, i);
//         } else {
//             ELMTLIST(l, i) = ELMTLIST(l1, i) - ELMTLIST(l2, i);
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
            if (different(ELMTLIST(l1, i), ELMTLIST(l2, i))) {
                return false;
            }
        }
        return true;
    }
    return false;
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : List boleh kosong!! *** */
int indexOf(ListStatik l, ElTypeList val)
/* Search apakah ada elemen List l yang bernilai val */
/* Jika ada, menghasilkan indeks i terkecil, dengan ELMTLIST(l,i) = val */
/* Jika tidak ada atau jika l kosong, mengirimkan IDX_UNDEF */
/* Skema Searching yang digunakan bebas */
{
    /* Kamus Lokal */
    int i = 0;
    /* Algoritma */
    while (i < listLength(l) && different(ELMTLIST(l, i), val)) {
        i = i + 1;
    }
    if (i < listLength(l)) {
        return i;
    } else {
        return IDX_UNDEF;
    }
}

/* ********** NILAI EKSTREM ********** */
// void extremeFoodId(ListStatik l, ElTypeList *max, ElTypeList *min)
// /* I.S. List l tidak kosong */
// /* F.S. Max berisi nilai terbesar dalam l;
//         Min berisi nilai terkecil dalam l */
// {   /* Kamus Lokal */
//     int i = 1;
//     /* Algoritma */
//     *max = ELMTLIST(l, 0);
//     *min = ELMTLIST(l, 0);
//     for (i; i < listLength(l); i++) {
//         if (IDX(l, i) > (*max).id) {
//             *max = ELMTLIST(l, i);
//         }
//         if (IDX(l, i) < (*min).id) {
//             *min = ELMTLIST(l, i);
//         }
//     }
// }

// void extremeFoodExp(ListStatik l, ElTypeList *max, ElTypeList *min)
// /* I.S. List l tidak kosong */
// /* F.S. Max berisi nilai terbesar dalam l;
//         Min berisi nilai terkecil dalam l */
// {   /* Kamus Lokal */
//     int i = 1;
//     /* Algoritma */
//     *max = ELMTLIST(l, 0);
//     *min = ELMTLIST(l, 0);
//     for (i; i < listLength(l); i++) {
//         if (TGT(EXP(l, i), (*max).expired)) {
//             *max = ELMTLIST(l, i);
//         }
//         if (TLT(EXP(l, i), (*min).expired)) {
//             *min = ELMTLIST(l, i);
//         }
//     }
// }

// void extremeFoodDlv(ListStatik l, ElTypeList *max, ElTypeList *min)
// /* I.S. List l tidak kosong */
// /* F.S. Max berisi nilai terbesar dalam l;
//         Min berisi nilai terkecil dalam l */
// {   /* Kamus Lokal */
//     int i = 1;
//     /* Algoritma */
//     *max = ELMTLIST(l, 0);
//     *min = ELMTLIST(l, 0);
//     for (i; i < listLength(l); i++) {
//         if (TGT(DLV(l, i), (*max).delivery)) {
//             *max = ELMTLIST(l, i);
//         }
//         if (TLT(DLV(l, i), (*min).delivery)) {
//             *min = ELMTLIST(l, i);
//         }
//     }
// }

/* ********** MENAMBAH ELEMEN ********** */
/* *** Menambahkan elemen terakhir *** */
void insertFirst(ListStatik *l, ElTypeList val)
/* Proses: Menambahkan val sebagai elemen pertama List */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen pertama l yang baru */
{   /* Kamus Lokal */
    int i = getLastIdx(*l) + 1, firstIndex = 0;
    /* Algoritma */
    for (i; i > 0; i--) {
        ELMTLIST(*l, i) = ELMTLIST(*l, i - 1);
    }
    ELMTLIST(*l, 0) = val;
}
/* *** Menambahkan elemen pada index tertentu *** */
void insertAt(ListStatik *l, ElTypeList val, IdxType idx)
/* Proses: Menambahkan val sebagai elemen pada index idx List */
/* I.S. List l tidak kosong dan tidak penuh, idx merupakan index yang valid di l */
/* F.S. val adalah elemen yang disisipkan pada index idx l */
/* *** Menambahkan elemen terakhir *** */
{   /* Kamus Lokal */
    int i = getLastIdx(*l) + 1;
    /* Algoritma */    
    for (i; i > idx; i--) {
        ELMTLIST(*l, i) = ELMTLIST(*l, i - 1);
    }
    ELMTLIST(*l, idx) = val;
}
void insertLast(ListStatik *l, ElTypeList val)
/* Proses: Menambahkan val sebagai elemen terakhir List */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */
{   /* Kamus Lokal */
    /* Algoritma */
    if (isEmpty(*l)){
        insertFirst(l, val);
    } else {
        ELMTLIST(*l, listLength(*l)) = val;
    }
}

// void insertFood(ListStatik *l, Makanan val, int Idx) {
//     Item a;
//     a.itemInfo.m = val;
//     a.type = 1;
//     if (isEmpty(*l)) {
//         insertFirst(l, a);
//     } else if (isIdxEff(*l, Idx)) {
//         insertAt(l, a, Idx);
//     }
// }

/* ********** MENGHAPUS ELEMEN ********** */
/* *** Menghapus elemen pertama *** */
void deleteFirst(ListStatik *l, ElTypeList *val) 
/* Proses : Menghapus elemen pertama List */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen pertama l sebelum penghapusan, */
/*      Banyaknya elemen List berkurang satu */
/*      List l mungkin menjadi kosong */
{   /* Kamus Lokal */
    int i = 0, j = listLength(*l) - 1;
    /* Algoritma */
    *val = ELMTLIST(*l, 0);
    for (i; i < j; i++) {
        ELMTLIST(*l, i) = ELMTLIST(*l, i + 1);
    }
    ELMTLIST(*l, listLength(*l) - 1) = FoodMark;
}
/* *** Menghapus elemen pada index tertentu *** */
void deleteAt(ListStatik *l, ElTypeList *val, IdxType idx)
/* Proses : Menghapus elemen pada index idx List */
/* I.S. List tidak kosong, idx adalah index yang valid di l */
/* F.S. val adalah nilai elemen pada index idx l sebelum penghapusan, */
/*      Banyaknya elemen List berkurang satu */
/*      List l mungkin menjadi kosong */
/* *** Menghapus elemen terakhir *** */
{   /* Kamus Lokal */
    int i = idx;
    /* Algoritma */
    *val = ELMTLIST(*l, idx);
    ELMTLIST(*l, idx) = FoodMark;
    for (i; i < listLength(*l) - 1; i++) {
        ELMTLIST(*l, i) = ELMTLIST(*l, i + 1);
    }
    ELMTLIST(*l, listLength(*l)) = FoodMark;
}
void deleteLast(ListStatik *l, ElTypeList *val)
/* Proses : Menghapus elemen terakhir List */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen List berkurang satu */
/*      List l mungkin menjadi kosong */
{   /* Kamus Lokal */
    /* Algoritma */
    *val = ELMTLIST(*l, getLastIdx(*l));
    ELMTLIST(*l, getLastIdx(*l)) = FoodMark;
}

// /* ********** SORTING ********** */
// void sortFoodId(ListStatik *l, boolean asc)
// /* I.S. l boleh kosong */
// /* F.S. Jika asc = true, l terurut membesar */
// /*      Jika asc = false, l terurut mengecil */
// /* Proses : Mengurutkan l dengan salah satu algoritma sorting,
//    algoritma bebas */
// {   /* Kamus Lokal */
//     if (TYPE(*l) == 1) {
//         int i = getFirstIdx(*l), j;
//         Makanan temp;
//         /* Algoritma */
//         if (!isEmpty(*l)) {
//             if (asc) {
//                 for (i; i<=getLastIdx(*l) - 1; i++) {
//                     j = i + 1;
//                     for (j; j <= getLastIdx(*l); j++) {
//                         if (IDX(*l, i) > IDX(*l, j)) {
//                             temp = ELMTLIST(*l, i);
//                             ELMTLIST(*l, i) = ELMTLIST(*l, j);
//                             ELMTLIST(*l, j) = temp;
//                         }
//                     }
//                 }
//             } else if (!asc){
//                 i = getFirstIdx(*l);
//                 for (i; i<=getLastIdx(*l) - 1; i++) {
//                     j = i + 1;
//                     for (j; j <= getLastIdx(*l); j++) {
//                         if (IDX(*l, i) < IDX(*l, j)) {
//                             temp = ELMTLIST(*l, i);
//                             ELMTLIST(*l, i) = ELMTLIST(*l, j);
//                             ELMTLIST(*l, j) = temp;
//                         }
//                     }
//                 }
//             }
//         }
//     }
// }

// void sortFoodExp(ListStatik *l, boolean asc)
// /* I.S. l boleh kosong */
// /* F.S. Jika asc = true, l terurut membesar */
// /*      Jika asc = false, l terurut mengecil */
// /* Proses : Mengurutkan l dengan salah satu algoritma sorting,
//    algoritma bebas */
// {   /* Kamus Lokal */
//     if (TYPE(*l) == 1) {
//         int i = getFirstIdx(*l), j;
//         Makanan temp;
//         /* Algoritma */
//         if (!isEmpty(*l)) {
//             if (asc) {
//                 for (i; i <= getLastIdx(*l) - 1; i++) {
//                     j = i + 1;
//                     for (j; j <= getLastIdx(*l); j++) {
//                         if (TGT(EXP(*l, i), EXP(*l, j))) {
//                             temp = ELMTLIST(*l, i);
//                             ELMTLIST(*l, i) = ELMTLIST(*l, j);
//                             ELMTLIST(*l, j) = temp;
//                         }
//                     }
//                 }
//             } else if (!asc){
//                 i = getFirstIdx(*l);
//                 for (i; i <= getLastIdx(*l) - 1; i++) {
//                     j = i + 1;
//                     for (j; j <= getLastIdx(*l); j++) {
//                         if (TLT(EXP(*l, i), EXP(*l, j))) {
//                             temp = ELMTLIST(*l, i);
//                             ELMTLIST(*l, i) = ELMTLIST(*l, j);
//                             ELMTLIST(*l, j) = temp;
//                         }
//                     }
//                 }
//             }
//         }
//     }
// }

// void sortFoodDlv(ListStatik *l, boolean asc)
// /* I.S. l boleh kosong */
// /* F.S. Jika asc = true, l terurut membesar */
// /*      Jika asc = false, l terurut mengecil */
// /* Proses : Mengurutkan l dengan salah satu algoritma sorting,
//    algoritma bebas */
// {   /* Kamus Lokal */
//     if (TYPE(*l) == 1) {
//         int i = getFirstIdx(*l), j;
//         Makanan temp;
//         /* Algoritma */
//         if (!isEmpty(*l)) {
//             if (asc) {
//                 for (i; i<=getLastIdx(*l) - 1; i++) {
//                     j = i + 1;
//                     for (j; j <= getLastIdx(*l); j++) {
//                         if (TGT(DLV(*l, i), DLV(*l, j))) {
//                             temp = ELMTLIST(*l, i);
//                             ELMTLIST(*l, i) = ELMTLIST(*l, j);
//                             ELMTLIST(*l, j) = temp;
//                         }
//                     }
//                 }
//             } else if (!asc){
//                 i = getFirstIdx(*l);
//                 for (i; i<=getLastIdx(*l) - 1; i++) {
//                     j = i + 1;
//                     for (j; j <= getLastIdx(*l); j++) {
//                         if (TLT(DLV(*l, i), DLV(*l, j))) {
//                             temp = ELMTLIST(*l, i);
//                             ELMTLIST(*l, i) = ELMTLIST(*l, j);
//                             ELMTLIST(*l, j) = temp;
//                         }
//                     }
//                 }
//             }
//         }
//     }
// }