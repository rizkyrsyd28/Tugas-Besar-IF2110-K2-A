/* DEKLARASI ADT MAKANAN */

#include <stdio.h>
#include "../boolean.h"
#include "../MesinKata/wordmachine.h"
#include "../Time/time.h"

#ifndef MAKANAN_H
#define MAKANAN_H

typedef struct {
    int id;
    char name[100];
    TIME expired;
    char action[100];
    TIME delivery;
} Makanan;

// SELEKTOR
#define idMkn(M) (M).id;
#define nameMkn(M) (M).name;
#define expMkn(M) (M).expired;
#define actMkn(M) (M).action;
#define dlvMkn(M) (M).delivery;


// OPERASI PERBANDINGAN
void isIDGreater(Makanan m1, Makanan m2);
// Mengirimkan true bila ID m1 lebih besar dari ID m2
void isIDLower(Makanan m1, Makanan m2);
// Mengirimkan true bila ID m1 lebih kecil dari ID m2
boolean isIdentical(Makanan m1, Makanan m2);
// Mengirimkan true bila kontent makanan sama persis

#endif