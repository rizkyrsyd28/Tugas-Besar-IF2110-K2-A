#ifndef MATRIX_H
#define MATRIX_H

#include "../boolean.h"
#include "../Point/point.c"
#include "../ListStatik/liststatik.h"

/* Ukuran maksimum baris dan kolom */
#define ROW_CAP 100
#define COL_CAP 100

typedef int ElType;
typedef struct
{
   ElType mem[ROW_CAP][COL_CAP];
   int rowEff; /* banyaknya/ukuran baris yg terdefinisi */
   int colEff; /* banyaknya/ukuran kolom yg terdefinisi */
} Matrix;

/* *** Selektor *** */
#define ROW_EFF(M) (M).rowEff
#define COL_EFF(M) (M).colEff
#define ELMTMAT(M, i, j) (M).mem[(i)][(j)]

/* *** Konstruktor membentuk Matrix *** */
void createMatrix(int nRows, int nCols, Matrix *m);
/* Membentuk sebuah Matrix "kosong" yang siap diisi berukuran nRow x nCol di "ujung kiri" memori */
/* I.S. nRow dan nCol adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks m sesuai dengan definisi di atas terbentuk */

/* *** Selektor "Dunia Matrix" *** */
boolean isMatrixIdxValid(int i, int j);
/* Mengirimkan true jika i, j adalah index yang valid untuk matriks apa pun */

/* *** Selektor: Untuk sebuah matriks m yang terdefinisi: *** */
IdxType getLastIdxRow(Matrix m);
/* Mengirimkan Index baris terbesar m */
IdxType getLastIdxCol(Matrix m);
/* Mengirimkan Index kolom terbesar m */
boolean isMatIdxEff(Matrix m, IdxType i, IdxType j);
/* Mengirimkan true jika i, j adalah Index efektif bagi m */

/* ********** Assignment  Matrix ********** */
void copyMatrix(Matrix mIn, Matrix *mOut);
/* Melakukan assignment mOut <- mIn */

/* ********** KELOMPOK BACA/TULIS ********** */
void displayMatrix(Matrix m);
/* I.S. m terdefinisi */
/* F.S. Nilai m(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
   dipisahkan sebuah spasi. Baris terakhir tidak diakhiri dengan newline */
/* Proses: Menulis nilai setiap elemen m ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/



/* ********** KELOMPOK TEST TERHADAP Matrix ********** */
boolean isSquare(Matrix m);
/* Mengirimkan true jika m adalah matriks dg ukuran baris dan kolom sama */
boolean isSymmetric(Matrix m);
/* Mengirimkan true jika m adalah matriks simetri : isSquare(m) 
   dan untuk setiap elemen m, m(i,j)=m(j,i) */

POINT searchCharInMatrix(Matrix m, char c);
/* Mengembalikan index posisi dari char C pada matrix M dalam bentuk POINT*/

boolean isCan(Matrix M, int i, int j,char c);
//Untuk memeriksa apakah berada dalam suatu daerah di map jika ya maka dapat melakukan perintah

boolean canSwap(Matrix m, POINT des);
// mengembalikan true jika elemen matrix pada des adalah ' ' (artinya bisa bergerak/bukan obstacle)

void swapElmt(Matrix * m, POINT *src, POINT des);
/* I.S. m, src, des = terdefinisi */
/* F.S. jika dapat ditukar (canSwap = true) elemen pada src bertukar dengan elemen pada des, 
jika tidak dapat ditukar maka tidak melakukan apa-apa */

#endif
