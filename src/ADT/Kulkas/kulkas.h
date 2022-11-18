#include <stdio.h>
#include <stdlib.h>
#include "../Matrix/matrix.h"
#include "../Makanan/makanan.h"
#include "../Point/point.h"
#include "../boolean.h"

#ifndef KULKAS_H
#define KULKAS_H

#define MaxRow 5
#define MaxCol 10

typedef struct{
    Makanan makanan;
    int identifier;
} IsiKulkas;

typedef struct
{
   IsiKulkas mat[MaxRow][MaxCol];
} Kulkas;


/* ========= Selektor ========= */
#define Isi(M, i, j) (M).mat[i][j]
#define IsiMknn(M,i,j) ((M).mat[i][j]).makanan
#define IsiIdnt(M, i, j) ((M).mat[i][j]).identifier

/* ========= Konstruktor ========= */
void CreateKulkas(Kulkas *k);
/* Membuat isi kulkas kosong*/
/* Kulkas kosong adalah setiap elemen isikulkas pada K adalah FOODMARK untuk makanan dan -1 untuk identifier */

/* ========= Operasi ========= */
boolean isIsiKulkasEmpty (IsiKulkas isi);
/* Melakukan cek apakah isiKulas kosong */

boolean isKulkasEmpty (Kulkas k);
/* Melakukan cek apakah kulkas kosong*/

void DisplayIsiKulkas (IsiKulkas isi);
/* Menampilkan isi Kulkas */
/* Format yang digunakan adalah <ID Makanan,Identifer>*/

void DisplayKulkas (Kulkas k);
/* Menampilkan kulkas */
/* Digunakan untuk command 'KULKAS SHOW' */
/* Isi Kulkas akan ditampilkan seperti :
    [ X | X | X | X | .......... ]
    [ X | X | X | X | .......... ]
    dengan X = <ID Makanan,Identifier> */

boolean isMakananInKulkas (Kulkas K, Makanan mkn);
/* Melakukan cek apakah makanan serupa sudah ada pada kulkas*/

int getLastIdentifier(Kulkas K);
/* Mengembalikan nilai Identifier paling besar*/

int getValidIdentifier(Kulkas K, int lastIdnt);
/* Mengembalikan nilai Identifier yang valid untuk digunakan
untuk memasukkan makanan */

boolean isPutAvailable(Kulkas k, POINT p, Makanan mkn);
/* Mengembalikan apakah memasukkan makanan pada kulkas 
pada koordinat tertentu dapat dilakukan*/
/* Mengembalikan iya bila bisa, tidak juga tidak bisa*/

void putMakananKulkas(Kulkas *k, POINT p, Makanan mkn);
/* Memasukkan makanan pada Kulkas*/

void getMakananKulkas(Kulkas *k, POINT p, Makanan *mkn);
/* Mengambil makanan dari Kulkas*/


#endif