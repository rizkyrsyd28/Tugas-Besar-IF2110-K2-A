#include <stdio.h>
#include <stdlib.h>
#include "../Matrix/matrix.h"
#include "../Makanan/makanan.h"
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

void DisplayIsiKulkas (IsiKulkas isi);
/* Menampilkan isi Kulkas */
/* Format yang digunakan adalah <ID Makanan,Identifer>*/

/* ========= Operasi ========= */
void DisplayKulkas (Kulkas k);
/* Menampilkan kulkas */
/* Digunakan untuk command 'KULKAS SHOW' */
/* Isi Kulkas akan ditampilkan seperti :
    [ X | X | X | X | .......... ]
    [ X | X | X | X | .......... ]
    dengan X = <ID Makanan,Identifier> */

#endif