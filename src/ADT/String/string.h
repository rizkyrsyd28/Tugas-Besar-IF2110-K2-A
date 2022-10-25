// =========================== IMPLEMENTASI ADT UNTUK STRING ===========================

#include <stdio.h>
#include <stdlib.h>
#include "../boolean.h"

#ifndef STRING_H
#define STRING_H

void createEmpty(char* str);
// Membuat string (kembali) menjadi string kosong

int MakeCharToInt(char c);
// Konversi tipe Char ke Integer
// Diasumsikan input selalu benar (merupakan suatu angka)

boolean isBlank (char c);
// Memeriksa apakah karakter C adalah blank

int stringToInt (char* str);
// Konversi tipe string menjadi integer
// Diasumsikan input selalu benar (merupakan suatu angka)

int lengthString(char *str);
// Mengembalikan panjang sebuah string

boolean isStringEqual (char *str1, char *str2);
// Memeriksa apakah kedua buah string adalah string yang sama

void appendChar(char* str, char c);
// Menggabungkan char dibagian belakang string str
// Kondisi string di declare dengan str[], bukan str*

void appendString(char* c1, char* c2);
// Menggabungkan memasukkan char ke dalam suatu string 
// Diasumsikan c1 tidak kosong

#endif