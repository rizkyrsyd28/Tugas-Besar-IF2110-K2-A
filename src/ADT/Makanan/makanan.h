/* DEKLARASI ADT MAKANAN */

#include <stdio.h>
#include "../boolean.h"
#include "../MesinKata/wordmachine.h"
#include "../Time/time.h"

#ifndef MAKANAN_H
#define MAKANAN_H

typedef struct {
    int id;
    Word name;
    TIME expired;
    Word action;
    TIME delivery;
} Makanan;

// SELEKTOR
#define idMkn(M) (M).id
#define nameMkn(M) (M).name
#define expMkn(M) (M).expired
#define actMkn(M) (M).action
#define dlvMkn(M) (M).delivery

// KONSTRUKTOR
void CreateEmptyMakanan (Makanan *mkn);
// Membuat tipe bentukan makanan, yaitu makanan kosong
// Dapat berfungsi sebagai MARK atau Makanan yang invalid

// TULIS
void printMakanan (Makanan mkn);
// Melakukan print makanan agar pada terminal
// e.g. [11,Ayam Mentah,<0,0,1>,<0,2,0>,FRY]

// OPERASI PERBANDINGAN
boolean isIDGreater(Makanan m1, Makanan m2);
// Mengirimkan true bila ID m1 lebih besar dari ID m2
boolean isIDLower(Makanan m1, Makanan m2);
// Mengirimkan true bila ID m1 lebih kecil dari ID m2
boolean isIdentical(Makanan m1, Makanan m2);
// Mengirimkan true bila kontent makanan sama persis

#endif