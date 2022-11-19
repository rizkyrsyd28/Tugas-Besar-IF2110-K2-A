/* DEKLARASI ADT MAKANAN */

#include <stdio.h>
#include "../boolean.h"
#include "../MesinKata/wordmachine.h"
#include "../Time/time.h"

#ifndef MAKANAN_H
#define MAKANAN_H



typedef struct {
    int xSize;
    int ySize;
} Size;

typedef struct {
    int id;
    Word name;
    TIME expired;
    Word action;
    Size area;
    TIME delivery;
} Makanan;

Makanan FoodMark = {-1, {"Empty", 0}, {-1, -1, -1}, {"Empty", 0}, {0, 0}, {-1, -1, -1}};

// SELEKTOR
#define idMkn(M) (M).id
#define nameMkn(M) (M).name
#define expMkn(M) (M).expired
#define actMkn(M) (M).action
#define sizeMkn(M) (M).area
#define xSizeMkn(M) (M).area.xSize
#define ySizeMkn(M) (M).area.ySize
#define dlvMkn(M) (M).delivery

// KONSTRUKTOR
void CreateEmptyMakanan (Makanan *mkn);
/* I.S. Makanan tidak terdefinisi 
F.S. Makanan terdefinisi sebagai FoodMark 
Digunakan untuk mempersiapkan tipe bentukan Makanan sebelum dimasukkan data yang valid */

// TULIS
void printMakanan (Makanan mkn);
/* I.S. Makanan terdefinisi, mungkin bisa saja merupakan FoodMark 
F.S. Makanan ditampilkan dengan format (ID) - (Nama makanan) - <waktu delivery> - <ukuran makanan> - <waktu pemrosesan> - (aksi yang dibutuhkan). 
Prosedur ini digunakan untuk menampilkan data makanan secara lengkap*/

void printCatalog (Makanan mkn);
/* I.S. Makanan terdefinisi, mungkin bisa saja merupakan FoodMark 
F.S. Makanan ditampilkan dengan format (Nama makanan) - (waktu delivery) - (aksi yang dibutuhkan) - (waktu processing) 
Prosedur ini digunakan untuk menampilkan makanan pada catalog (tidak semua data makanan ditampilkan) */


// OPERASI PERBANDINGAN
boolean isIDGreater(Makanan m1, Makanan m2);
// Mengirimkan true bila ID m1 lebih besar dari ID m2
boolean isIDLower(Makanan m1, Makanan m2);
// Mengirimkan true bila ID m1 lebih kecil dari ID m2


#endif