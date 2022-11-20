/* MODUL LIST INTEGER STATIK DENGAN ELEMEN POSITIF */
/* Berisi definisi dan semua primitif pemrosesan list integer statik dengan elemen positif */
/* Penempatan elemen selalu rapat kiri */
/* Banyaknya elemen didefinisikan secara implisit, memori list statik */

#ifndef LISTSTATIK_H
#define LISTSTATIK_H

#include <stdlib.h>
#include "../boolean.h"
#include "../Makanan/makanan.h"
#include "../Time/time.h"
#include "../MesinKata/wordmachine.h"
#include "../Tree/nTree.h"

/*  Kamus Umum */
#define CAPACITY 1000
#define IDX_MIN 0
#define IDX_UNDEF -1

/* Nilai elemen tak terdefinisi*/

/* Definisi elemen dan koleksi objek */
typedef int IdxType;
typedef Makanan ElTypeList;  /* type elemen List */
typedef struct {
   ElTypeList contents[CAPACITY]; /* memori tempat penyimpan elemen (container) */
} ListStatik;

#define ELMTLIST(l, i) (l).contents[(i)]
#define CONT(l, i) ((l).contents[(i)]).itemInfo



/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create List kosong  */
/* I.S. l sembarang */
/* F.S. Terbentuk List l kosong dengan kapasitas CAPACITY */
/* Proses: Inisialisasi semua elemen List l dengan MARK */
void CreateListStatik(ListStatik *l);

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int listLength(ListStatik l);
/* Mengirimkan banyaknya elemen efektif List */
/* Mengirimkan nol jika List kosong */  

/* *** Selektor INDEKS *** */
IdxType getFirstIdx(ListStatik l);
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l pertama */
IdxType getLastIdx(ListStatik l);
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l terakhir */

/* ********** Test Indeks yang valid ********** */
boolean isIdxValid(ListStatik l, IdxType i);
/* Mengirimkan true jika i adalah indeks yang valid utk kapasitas List l */
/* yaitu antara indeks yang terdefinisi utk container*/
boolean isIdxEff(ListStatik l, IdxType i);
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk List l */
/* yaitu antara 0..length(l)-1 */

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test List kosong *** */
boolean isEmpty(ListStatik l);
/* Mengirimkan true jika List l kosong, mengirimkan false jika tidak */
/* *** Test List penuh *** */
boolean isFull(ListStatik l);
/* Mengirimkan true jika List l penuh, mengirimkan false jika tidak */


/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan List: *** */
boolean isListEqual(ListStatik l1, ListStatik l2);
/* Mengirimkan true jika l1 sama dengan l2 yaitu jika ukuran l1 = l2 dan semua 
   elemennya sama */

/* ********** SEARCHING ********** */
/* ***  Perhatian : List boleh kosong!! *** */
int indexOf(ListStatik l, ElTypeList val);
/* Search apakah ada elemen List l yang bernilai val */
/* Jika ada, menghasilkan indeks i terkecil, dengan ELMTLIST(l,i) = val */
/* Jika tidak ada atau jika l kosong, mengirimkan IDX_UNDEF */
/* Skema Searching yang digunakan bebas */

/* ********** NILAI EKSTREM ********** */
// void extremeValues(ListStatik l, ElTypeList *max, ElTypeList *min);
/* I.S. List l tidak kosong */
/* F.S. Max berisi nilai terbesar dalam l;
        Min berisi nilai terkecil dalam l */

/* ********** MENAMBAH ELEMEN ********** */
/* *** Menambahkan elemen terakhir *** */
void insertFirst(ListStatik *l, ElTypeList val);
/* Proses: Menambahkan val sebagai elemen pertama List */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen pertama l yang baru */
/* *** Menambahkan elemen pada index tertentu *** */
void insertAt(ListStatik *l, ElTypeList val, IdxType idx);
/* Proses: Menambahkan val sebagai elemen pada index idx List */
/* I.S. List l tidak kosong dan tidak penuh, idx merupakan index yang valid di l */
/* F.S. val adalah elemen yang disisipkan pada index idx l */
/* *** Menambahkan elemen terakhir *** */
void insertLast(ListStatik *l, ElTypeList val);
/* Proses: Menambahkan val sebagai elemen terakhir List */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */

/* ********** MENGHAPUS ELEMEN ********** */
/* *** Menghapus elemen pertama *** */
void deleteFirst(ListStatik *l, ElTypeList *val);
/* Proses : Menghapus elemen pertama List */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen pertama l sebelum penghapusan, */
/*      Banyaknya elemen List berkurang satu */
/*      List l mungkin menjadi kosong */
/* *** Menghapus elemen pada index tertentu *** */
void deleteAt(ListStatik *l, ElTypeList *val, IdxType idx);
/* Proses : Menghapus elemen pada index idx List */
/* I.S. List tidak kosong, idx adalah index yang valid di l */
/* F.S. val adalah nilai elemen pada index idx l sebelum penghapusan, */
/*      Banyaknya elemen List berkurang satu */
/*      List l mungkin menjadi kosong */
/* *** Menghapus elemen terakhir *** */
void deleteLast(ListStatik *l, ElTypeList *val);
/* Proses : Menghapus elemen terakhir List */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen List berkurang satu */
/*      List l mungkin menjadi kosong */

int searchIndexOlahMakanan(ListStatik l, char* command, int count);
/* Mengembalikan index dari makanan pada list makanan sesuai yang dibutuhkan oleh fungsi pengolahan makanan
    Fungsi yang dimaksud adalah Buy, Mix, Chop, Fry, dan Boil */
    
/* ********** SORTING ********** */
// void sortList(ListStatik *l, boolean asc);
/* I.S. l boleh kosong */
/* F.S. Jika asc = true, l terurut membesar */
/*      Jika asc = false, l terurut mengecil */
/* Proses : Mengurutkan l dengan salah satu algoritma sorting,
   algoritma bebas */

boolean isMark(ElTypeList a);
/* Mengembalikan true jika a adalah FoodMark*/

boolean different(ElTypeList a, ElTypeList b);
/* Melakukan cek apakah kedua ElTypeList (Makanan). 
Mengembalikan true bila keduanya adalah sama*/

Makanan getMakanan(ID id, ListStatik foods);
/* Mengembalikan makanan berdasarkan ID yang diinputkan
Bila tidak ditemukan, maka mengembalikan FoodMark*/

#endif