/* File: mesinkata.h */
/* Definisi Mesin Word: Model Akuisisi Versi I */

// =========================== IMPLEMENTASI ADT UNTUK WORD ===========================

#ifndef __MESINKATA_H__
#define __MESINKATA_H__

#include "../boolean.h"
#include "charmachine.h"

#define NMax 100
#define BLANK ' '

typedef struct
{
   char TabWord[NMax]; /* container penyimpan kata, indeks yang dipakai [0..NMax-1] */
   int Length;
} Word;

#define len(w) (w).Length
#define str(w) (w).TabWord

/* State Mesin Word */
extern boolean endWord;
extern Word currentWord;

void IgnoreBlanks(char* str, int *idx);
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang
   F.S. : CC ≠ BLANK atau CC = MARK */

void STARTWORD(char* str, int *idx);
/* I.S. : CC sembarang
   F.S. : EndWord = true, dan CC = MARK;
          atau EndWord = false, CWord adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
          

void ADVWORD(char* str, int *idx);
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi
   F.S. : CWord adalah kata terakhir yang sudah diakuisisi,
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndWord = true.
   Proses : Akuisisi kata menggunakan procedure SalinWord */

void CopyWord(char* str, int *idx);
/* Mengakuisisi kata, menyimpan dalam CWord
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CWord berisi kata yang sudah diakuisisi;
          CC = BLANK atau CC = MARK;
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */

int WordToInt(Word word);
/* Mengembalikan integer hasil konversi word ke integer */

void printWord(Word word);
/* I.S. word terdefinisi
F.S. menampilkan kata yang ditampung pada word */

boolean isWordEqual(Word word1, Word word2);
/* Mengembalikan true apabila kedua word adalah berisikan karakter yang sama dan memiliki panjang yang sama */

boolean isWordStringEqual(Word w, char* c);
/* Mengembalikan true apabila kata yang dikandung pada c berisikan karakter yang sama pada array of char yang dikandung oleh w */

boolean isWordAllIntegers(Word w);
/* Mengembalikan true apabila semua karakter yang dikandung pada array of char pada w merupakan angka sehingga dapat diubah menjadi integer */

Word appendWord(Word w1, Word w2);
/* Mengembalikan word yang merupakan penggabungan Word w2 setelah Word w1 */



#endif