#include <stdio.h>
#include "kulkas.h"

/* ========= Konstruktor ========= */
void CreateKulkas(Kulkas *k)
/* Membuat isi kulkas kosong*/
/* Kulkas kosong adalah setiap elemen pada K adalah FOODMARK untuk makanan dan -1 untuk identifier */
{
    int i;
    int j;
    for ( i = 0 ; i < MaxRow ; i++){
        for ( j = 0; j < MaxCol ; j++){
            IsiMknn(*k, i, j) = FoodMark;
            IsiIdnt(*k, i, j) = -1;
        }
    }
}

/* ========= Operasi ========= */

boolean isIsiKulkasEmpty (IsiKulkas isi)
/* Melakukan cek apakah isiKulas kosong */
{
    return (isi.identifier == -1);
}

void DisplayIsiKulkas (IsiKulkas isi){
/* Menampilkan isi Kulkas */
/* Format yang digunakan adalah <ID Makanan,Identifer>*/
/* Jika isiKulkas kosong, maka menapilkan "Kosong" (blank)*/
    if (isIsiKulkasEmpty(isi)){
        printf("Kosong");
    } else {
    printf("<");
    printf("%d", idMkn(isi.makanan));
    printf(",");
    printf("%d", isi.identifier);
    printf(">");
    }
}

void DisplayKulkas (Kulkas k)
/* Menampilkan kulkas */
/* Digunakan untuk command 'KULKAS SHOW' */
/* Isi Kulkas akan ditampilkan seperti :
    [ X | X | X | X | .......... ]
    [ X | X | X | X | .......... ]
    dengan X = <ID Makanan,Identifier> */
{
    int i;
    int j;
    for (i = 0 ; i < MaxRow ; i++){
        printf("[ ");
        for (j = 0; j < MaxCol; j++){
            DisplayIsiKulkas(Isi(k,i,j));
            if (j != MaxCol-1){
                printf(" | ");
            }

        }
        printf(" ]\n");
    }
}