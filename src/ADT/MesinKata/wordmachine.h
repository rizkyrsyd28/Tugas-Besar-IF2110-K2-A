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

void IgnoreBlanks();
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang
   F.S. : CC ≠ BLANK atau CC = MARK */

void STARTWORD();
/* I.S. : CC sembarang
   F.S. : EndWord = true, dan CC = MARK;
          atau EndWord = false, CWord adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
          
void StartInput();
/* Endword = true ketika berujung di BLANK
void ADVWORD();
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi
   F.S. : CWord adalah kata terakhir yang sudah diakuisisi,
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndWord = true.
   Proses : Akuisisi kata menggunakan procedure SalinWord */

void CopyWord();
/* Mengakuisisi kata, menyimpan dalam CWord
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CWord berisi kata yang sudah diakuisisi;
          CC = BLANK atau CC = MARK;
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */

int WordToInt(Word word);
// Konversi tipe word kata ke integer

void printWord(Word word);
// Melakukan print untuk kata yang telah disimpan 

boolean isWordEqual(Word word1, Word word2);
// Memeriksa apakah dua buah word adalah word yang sama

boolean isWordStringEqual(Word w, char* c);
// Memeriksa apakah sebuah word mengandung kata yang sama dengan string c

Word appendWord(Word w1, Word w2);
// Menggabungkan w2 dan w1 menjadi satu word

#endif