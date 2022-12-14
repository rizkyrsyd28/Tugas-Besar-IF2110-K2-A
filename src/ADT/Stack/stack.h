/* File : stack.h */
/* deklarasi stack yang diimplementasi dengan tabel kontigu dan ukuran sama */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */
#ifndef stackt_H
#define stackt_H

#include "../boolean.h"
#include "../Makanan/makanan.h"
#include "../Simulator/simulator.h"
#include "../Time/time.h"
#include "../piroqueue/piroqueue.h"
#include "../Matrix/matrix.h"
#include "../Point/point.h"


#define Nil -1
#define MaxStack 100
/* Nil adalah stack dengan elemen kosong . */

typedef struct {
  Simulator sub1;
  TIME sub2;
  Word sub3;
}state;

/* Contoh deklarasi variabel bertype stack dengan ciri TOP : */
/* Versi I : dengan menyimpan tabel dan alamat top secara eksplisit*/
typedef struct { 
  state T[MaxStack]; /* tabel penyimpan elemen */
  address TOP;  /* alamat TOP: elemen puncak */
} Stack;
/* Definisi stack S kosong : S.TOP = Nil */
/* Elemen yang dipakai menyimpan nilai Stack T[0]..T[MaxEl-1] */
/* Jika S adalah Stack maka akses elemen : */
   /* S.T[(S.TOP)] untuk mengakses elemen TOP */
   /* S.TOP adalah alamat elemen TOP */

/* Definisi akses dengan Selektor : Set dan Get */
#define Top(S) (S).TOP
#define InfoTop(S) (S).T[(S).TOP]

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmpty(Stack *S);
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxEl */
/* jadi indeksnya antara 0.. MaxEl */
/* Ciri stack kosong : TOP bernilai Nil */

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push(Stack * S, state X);
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */

/* ************ Menghapus sebuah elemen Stack ************ */
void Pop(Stack * S, state* X);
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */

void displayStack(Stack S);
/* I.S. S terdefinisi
F.S. Menampilkan isi Stack S*/

void Undo(Stack *S_undo,Stack *S_redo, state *currentState, int totalcommand, POINT src);
//Undo gerakan, mengembalikan simulator,waktu,dan peta sebelum

void Redo(Stack *S_undo,Stack *S_redo, state *currentState, int totalundo, POINT src);
//Redo gerakan, mengembalikan simulator,waktu,dan peta sesudah

#endif
