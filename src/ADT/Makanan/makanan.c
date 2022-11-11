/* IMPLEMENTASI ADT MAKANAN */

#include <stdio.h>
#include "makanan.h"
#include <stdlib.h>
#include "../Time/time.c"


// KONSTRUKTOR
void CreateEmptyMakanan (Makanan *mkn){
// Membuat tipe bentukan makanan, yaitu makanan kosong
// Dapat berfungsi sebagai MARK atau Makanan yang invalid
    *mkn = FoodMark;
}

// TULIS
void printMakanan (Makanan mkn){
// Melakukan print makanan agar pada terminal
// e.g. [11,Ayam Mentah,<0,0,1>,<0,2,0>,FRY]
    printf("%d - ", idMkn(mkn));
    int i;
    for (i = 0; i < len(nameMkn(mkn)); i++){
        if (i == len(nameMkn(mkn))-1 ){
            printf("%c - ", str(nameMkn(mkn))[i]);
        } else {
            printf("%c", str(nameMkn(mkn))[i]);
        }
    }
    TulisTIMEString(expMkn(mkn));
    printf(" - ");
    TulisTIMEString(dlvMkn(mkn));
    printf(" - ");
    printf("<%d,%d> - ", sizeMkn(mkn).xSize, sizeMkn(mkn).ySize);
    for (i = 0; i < len(actMkn(mkn)); i++){
        printf("%c", str(actMkn(mkn))[i]);
    }
}


void printCatalog (Makanan mkn){
// Melakukan print makanan agar pada terminal
// e.g. [11,Ayam Mentah,<0,0,1>,<0,2,0>,FRY]
    int i;
    for (i = 0; i < len(nameMkn(mkn)); i++){
        if (i == len(nameMkn(mkn))-1 ){
            printf("%c - ", str(nameMkn(mkn))[i]);
        } else {
            printf("%c", str(nameMkn(mkn))[i]);
        }
    }
    TulisTIMEKadaluarsa(expMkn(mkn));
    printf(" - ");
    for (i = 0; i < len(actMkn(mkn)); i++){
    printf("%c", str(actMkn(mkn))[i]);
	}
	printf(" - ");
    TulisTIMEKadaluarsa(dlvMkn(mkn));
    
}


// OPERASI PERBANDINGAN
boolean isIDGreater(Makanan m1, Makanan m2)
// Mengirimkan true bila ID m1 lebih besar dari ID m2
{
    return (idMkn(m1) > idMkn(m2));
}
boolean isIDLower(Makanan m1, Makanan m2)
// Mengirimkan true bila ID m1 lebih kecil dari ID m2
{
    return (idMkn(m1) < idMkn(m2));
}


// boolean isIdentical(Makanan m1, Makanan m2) {
//     //Mengirimkan true apabila kedua makanan sama
//     return (m1.id == m2.id && m1.action == m2.action && TEQ(m1.delivery, m2.delivery) && TEQ(m1.expired, m2.expired) && (m1.name == m2.name));
// }
