/* DEKLARASI ADT MAKANAN */

#include <stdio.h>
#include "../boolean.h"

typedef struct {
    int id;
    char name[100];
    Time expired;
    char action[100];
    Time delivery;
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
void isActionSame(Makanan m1, Makanan m2);
// Mengirimkan true bila action yang dibutuhkan m1 dan m2 sama
void isExpiryGreater(Makanan m1, Makanan m2);
// Mengirimkan true bila expiry m1 lebih besar dari m2
void isExpiryLower(Makanan m1, Makanan m2);
// Mengirimkan true bila expiry m1 lebih kecil dari m2
void isDeliveryGreater(Makanan m1, Makanan m2);
// Mengirimkan true bila delivery m1 lebih besar dari m2
void isDeliveryLower(Makanan m1, Makanan m2);
// Mengirimkan true bila delivery m1 lebih kecil dari m2
