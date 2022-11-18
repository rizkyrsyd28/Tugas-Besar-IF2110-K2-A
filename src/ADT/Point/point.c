// File : point.c
// Nama : Rizky Abdillah Rasyid
// NIM : 13521109
// Tanggal : 5 September 2022

// Implementasi ADT POINT

#include <stdio.h>
#include <math.h>
#include "point.h"

/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk POINT *** */
void CreatePoint (POINT * P, int X, int Y){
/* Membentuk sebuah POINT dari komponen-komponennya */
    Absis(*P) = X;
    Ordinat(*P) = Y;
}
/* *** KELOMPOK Interaksi dengan I/O device, BACA/TULIS  *** */                                                 
void BacaPOINT (POINT * P){
/* Membaca nilai absis dan ordinat dari keyboard dan membentuk 
   POINT P berdasarkan dari nilai absis dan ordinat tersebut */
/* I.S. Sembarang */
/* F.S. P terdefinisi */
    
    // KAMUS 
    int X, Y;

    //ALGORITMA
    scanf("%d %d", &X, &Y);
    CreatePoint(P, X, Y); ////
}

void TulisPOINT (POINT P){
/* Nilai P ditulis ke layar dengan format "(X,Y)" 
   tanpa spasi, enter, atau karakter lain di depan, belakang, 
   atau di antaranya 
   Output X dan Y harus dituliskan dalam bilangan riil dengan 2 angka di belakang koma.
*/
/* I.S. P terdefinisi */
/* F.S. P tertulis di layar dengan format "(X,Y)" */                

    // ALGORTIMA
    printf("(%d, %d)\n", Absis(P), Ordinat(P));
}

/* *** Kelompok operasi relasional terhadap POINT *** */
boolean EQ (POINT P1, POINT P2){
/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
    return (Absis(P1) == Absis(P2) && Ordinat(P1) == Ordinat(P2));
}

boolean NEQ (POINT P1, POINT P2){
/* Mengirimkan true jika P1 tidak sama dengan P2 */
    return(!EQ(P1,P2));
}
/* *** Kelompok menentukan di mana P berada *** */
boolean IsOrigin (POINT P){
/* Menghasilkan true jika P adalah titik origin */
    return(Absis(P) == 0 && Ordinat(P) == 0);
}
boolean IsOnSbX (POINT P){
/* Menghasilkan true jika P terletak Pada sumbu X */
    return(Ordinat(P) == 0);
}
boolean IsOnSbY (POINT P){
/* Menghasilkan true jika P terletak pada sumbu Y */
    return(Absis(P) == 0);
}
int Kuadran (POINT P){
/* Menghasilkan kuadran dari P: 1, 2, 3, atau 4 */
/* Prekondisi : P bukan titik origin, */
/*              dan P tidak terletak di salah satu sumbu */

    // ALGORITMA

    if (Absis(P) > 0)
    {
        if (Ordinat(P) > 0) return 1;
        else return 4;
    }
    else
    {
        if (Ordinat(P) > 0) return 2;
        else return 3;
    }
}
/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */                           
POINT NextX (POINT P){
/* Mengirim salinan P dengan absis ditambah satu */              
    
    // ALGORTIMA
    Absis(P)++;

    return P;
}
POINT NextY (POINT P){
/* Mengirim salinan P dengan ordinat ditambah satu */
    
    // ALGORITMA
    Ordinat(P)--;

    return P;
}

POINT BackX (POINT P){
/* Mengirim salinan P dengan absis ditambah satu */              
    
    // ALGORTIMA
    Absis(P)--;

    return P;
}
POINT BackY (POINT P){
/* Mengirim salinan P dengan ordinat ditambah satu */
    
    // ALGORITMA
    Ordinat(P)++;

    return P;
}

POINT PlusDelta (POINT P, int deltaX, int deltaY){
/* Mengirim salinan P yang absisnya adalah Absis(P) + deltaX dan ordinatnya adalah Ordinat(P) + deltaY */

    // ALGORTIMA
    Absis(P) += deltaX;
    Ordinat(P) += deltaY;

    return(P);
}
POINT MirrorOf (POINT P, boolean SbX){
/* Menghasilkan salinan P yang dicerminkan terhadap salah satu sumbu */
/* Jika SbX bernilai true, maka dicerminkan terhadap sumbu X */
/* Jika SbX bernilai false, maka dicerminkan terhadap sumbu Y */
    // ALGORITMA
    if(SbX)
    {
        Ordinat(P) *= -1;
    }
    else
    {
        Absis(P) *= -1;
    }

    return P;
}

void Geser (POINT *P, int deltaX, int deltaY){
/* I.S. P terdefinisi */
/* F.S. P digeser, absisnya sebesar deltaX dan ordinatnya sebesar deltaY */
    // ALGORITMA
    Absis(*P) += deltaX;
    Ordinat(*P) += deltaY;
}
void GeserKeSbX (POINT *P){
/* I.S. P terdefinisi */
/* F.S. P berada pada sumbu X dengan absis sama dengan absis semula. */
    Ordinat(*P) = 0;
/* Proses : P digeser ke sumbu X. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (9,0) */
}
void GeserKeSbY (POINT *P){
/* I.S. P terdefinisi*/
/* F.S. P berada pada sumbu Y dengan ordinat yang sama dengan semula. */
    Absis(*P) = 0;
/* Proses : P digeser ke sumbu Y. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (0,9) */
}
void Mirror (POINT *P, boolean SbX){
/* I.S. P terdefinisi */
/* F.S. P dicerminkan tergantung nilai SbX atau SbY */
    // ALGORITMA
    if (SbX)
    {
        Ordinat(*P) *= -1;
    }
    else
    {
        Absis(*P) *= -1;
    }
/* Jika SbX true maka dicerminkan terhadap sumbu X */
/* Jika SbX false maka dicerminkan terhadap sumbu Y */
}
