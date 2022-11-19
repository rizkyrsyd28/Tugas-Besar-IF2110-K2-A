/* IMPLEMENTASI ADT MAKANAN */

#include <stdio.h>
#include "makanan.h"
#include <stdlib.h>
#include "../Time/time.c"


// KONSTRUKTOR
void CreateEmptyMakanan (Makanan *mkn){
/* I.S. Makanan tidak terdefinisi 
F.S. Makanan terdefinisi sebagai FoodMark 
Digunakan untuk mempersiapkan tipe bentukan Makanan sebelum dimasukkan data yang valid */
    *mkn = FoodMark;
}

// TULIS
void printMakanan (Makanan mkn){
/* I.S. Makanan terdefinisi, mungkin bisa saja merupakan FoodMark 
F.S. Makanan ditampilkan dengan format (ID) - (Nama makanan) - <waktu delivery> - <ukuran makanan> - <waktu pemrosesan> - (aksi yang dibutuhkan). 
Prosedur ini digunakan untuk menampilkan data makanan secara lengkap*/

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
/* I.S. Makanan terdefinisi, mungkin bisa saja merupakan FoodMark 
F.S. Makanan ditampilkan dengan format (Nama makanan) - (waktu delivery) - (aksi yang dibutuhkan) - (waktu processing) 
Prosedur ini digunakan untuk menampilkan makanan pada catalog (tidak semua data makanan ditampilkan) */
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
    for (i = 0; i < len(actMkn(mkn)); i++){
    printf("%c", str(actMkn(mkn))[i]);
	}
	printf(" - ");
    TulisTIMEString(dlvMkn(mkn));
    
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



