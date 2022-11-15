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

boolean isKulkasEmpty (Kulkas k)
/* Melakukan cek apakah kulkas kosong*/
{
    int i;
    int j;
    for (i = 0; i < MaxRow ; i++){
        for (j = 0; j < MaxCol; j++){
            if (!isIsiKulkasEmpty(Isi(k, i, j))){
                return false;
            }
        }
    }
    return true;
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
    printf("Makanan ditulis dalam format < ID Makanan, Identifier >\n");
    printf("Bari yang valid pada kulkas adalah 0..%d dan kolom yang valid pada kulkas adalah 0..%d\n", (MaxRow-1), (MaxCol-1));
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

boolean isMakananInKulkas (Kulkas k, Makanan mkn)
/* Melakukan cek apakah makanan serupa sudah ada pada kulkas*/
{
    int i;
    int j;
    for (i = 0; i < MaxRow; i++){
        for (j =0 ; j < MaxCol; j++){
            if (idMkn(IsiMknn(k, i, j)) == idMkn(mkn)){
                return true;
            }
        }
    }
    return false;
}
int getLastIdentifier(Kulkas k)
/* Mengembalikan nilai Identifier paling besar*/
{
    int idnt = 0; 
    /*Defaultnya adalah 0, bila kosong dan tidak ada identifier yang dapat dibandingkan, 
    maka mengembalikan 0 */
    int i;
    int j;
    for (i =0; i < MaxRow; i++){
        for (j = 0; j < MaxCol; j++){
            if (IsiIdnt(k, i, j) > idnt){
                idnt = IsiIdnt(k,i,j);
            }
        }
    }
    return idnt;
}

int getValidIdentifier(Kulkas k, int lastIdnt)
/* Mengembalikan nilai Identifier yang valid untuk digunakan
untuk memasukkan makanan */
{
    int idnt = 0; // nilai default untuk identifier
    int i;
    int j;
    for (idnt =  0;  idnt <= lastIdnt; idnt++){
        boolean found = false;
        // Melakukan cek untuk setiap isi kulkas, apakah identifier tertentu sudah dipakai
        for (i = 0 ; i < MaxRow; i++){
            for (j = 0; j < MaxCol; j++){
                if (idnt == IsiIdnt(k, i, j)){
                    found = true;
                }
            }
        }
        if (!found) {
            // jika tidak ditemukan idnt tersebut, maka itu akan menjadi idnt yang valid
            return idnt;
        }
    }
    return idnt; 
    /* jika identifier 0 hingga lastIdnt ada pada k (tidak ada yang bolong),
    maka mengembalikan identifier + 1 (identifier baru) (for loop akan berhenti di k + 1)*/

}

boolean isPutAvailable(Kulkas k, POINT p, Makanan mkn)
/* Mengembalikan apakah memasukkan makanan pada kulkas 
pada koordinat tertentu dapat dilakukan*/
/* Mengembalikan iya bila bisa, tidak juga tidak bisa*/
{
    int rowStart = Absis(p);
    int colStart = Ordinat(p);
    int i;
    int j;
    int sizeX = xSizeMkn(mkn);
    int sizeY = ySizeMkn(mkn);
    // check bila POINT berada di luar petak
    if (rowStart < 0 || rowStart > MaxRow || colStart < 0 || colStart > MaxCol) {
        return false;
    } else if ( rowStart + sizeY > MaxRow || colStart + sizeX > MaxCol){
        // Check bila setelah ujung penambahannnya di luar petak
        return false;
    } else {
        // maka mulai dari awal hingga ujung petak makanan bersifat valid
        for (i = rowStart; i < rowStart + sizeY; i++){
            for ( j = colStart; j < colStart + sizeX; j++){
                // Jika selama pengecekan ada yang tidak kosong
                if (IsiIdnt(k, i, j) != -1){
                    return false;
                }
            }
        }
        // mengembalikan true bila semuanya range petak tersebut kosong
        return true;
    }
}

void putMakananKulkas(Kulkas *k, POINT p, Makanan mkn)
/* Memasukkan makanan pada Kulkas*/
{
    if (isPutAvailable(*k, p, mkn)){
        int lastIdnt = getLastIdentifier(*k); 
        int validIdnt = getValidIdentifier(*k, lastIdnt); 
        int rowStart = Absis(p);
        int colStart = Ordinat(p);
        int i;
        int j;
        int sizeX = xSizeMkn(mkn);
        int sizeY = ySizeMkn(mkn);
        for (i = rowStart; i < rowStart+sizeY ; i++ ){
            for (j = colStart; j < colStart+sizeX; j++){
                IsiMknn(*k, i, j) = mkn;
                IsiIdnt(*k, i, j) = validIdnt;
            }
        }
        // Menuliskan pada user kalau makanan telah dimasukkan
        printf("Makanan "); printWord(nameMkn(mkn)); printf(" telah dimasukkan ke dalam kulkas \n");
    } else {
        printf("Makanan tidak bisa dimasukkan pada petak tersebut.\n");
    }
}

void getMakananKulkas(Kulkas *k, POINT p, Makanan *mkn)
/* Mengambil makanan dari Kulkas*/
{
    // check apakah pada petak point, terisi oleh makanan
    int rowStart = Absis(p);
    int colStart = Ordinat(p);
    if (IsiIdnt(*k, rowStart, colStart) != -1){
        // Jika petak tersebut benar diisi oleh maknaan
        *mkn = IsiMknn(*k, rowStart, colStart);
        int tempIdnt = IsiIdnt(*k, rowStart, colStart);
        int i;
        int j;
        for (i = 0; i < MaxRow; i++){
            for (j =0; j < MaxCol; j++){
                if (IsiIdnt(*k, i, j) == tempIdnt){
                    // menghapus semua makanan dengan idnt yang ingin dihapus
                    IsiMknn(*k, i, j) = FoodMark;
                    IsiIdnt(*k, i, j) = -1;
                }
            }
        }                            
        printf("Makanan "); printWord(nameMkn(*mkn)); printf(" telah diambil dari kulkas \n");
    } else {
        printf("Tidak ada makanan pada petak tersebut.\n");
    }
}