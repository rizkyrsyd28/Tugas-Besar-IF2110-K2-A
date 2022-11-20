#include "matrix.h"
#include <stdio.h>

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk Matrix *** */
void createMatrix(int nRows, int nCols, Matrix *m) {
/* Membentuk sebuah Matrix "kosong" yang siap diisi berukuran nRow x nCol di "ujung kiri" memori */
/* I.S. nRow dan nCol adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks m sesuai dengan definisi di atas terbentuk */
	int i,j;
	ROW_EFF(*m) = nRows;
	COL_EFF(*m) = nCols;
	for (i = 0; i < nRows; i++) {
        for (j = 0; j < nCols; j++) {
            ELMTMAT(*m, i, j) = '*';
        }
    }
}

/* *** Selektor "Dunia Matrix" *** */
boolean isMatrixIdxValid(int i, int j) {
/* Mengirimkan true jika i, j adalah index yang valid untuk matriks apa pun */
	return (i >= 0 && i < ROW_CAP && j >= 0 && j < COL_CAP);
}

IdxType getLastIdxRow(Matrix m) {
/* Mengirimkan Index baris terbesar m */
	return (ROW_EFF(m)-1);
}

IdxType getLastIdxCol(Matrix m) {
/* Mengirimkan Index kolom terbesar m */
	return (COL_EFF(m)-1);
}

boolean isMatIdxEff(Matrix m, IdxType i, IdxType j) {
/* Mengirimkan true jika i, j adalah Index efektif bagi m */
	return (i >= 0 && i < ROW_EFF(m) && j >= 0 && j < COL_EFF(m));
}


/* ********** Assignment  Matrix ********** */
void copyMatrix(Matrix mIn, Matrix *mOut) {
/* Melakukan assignment mOut <- mIn */
	*mOut = mIn;
}


/* ********** KELOMPOK BACA/TULIS ********** */
void displayMatrix(Matrix m) {
/* I.S. m terdefinisi */
/* F.S. Nilai ELMTMAT(M, i, j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
   dipisahkan sebuah spasi. Baris terakhir tidak diakhiri dengan newline */
/* Proses: Menulis nilai setiap elemen m ke layar dengan traversal per baris dan per kolom */
	int i, j;
	for (i = 0; i < ROW_EFF(m); i++) {
		for (j = 0; j < COL_EFF(m); j++) {
			printf("%c", ELMTMAT(m, i, j));
			if (j != COL_EFF(m)-1) {
				printf(" ");
			}
		}
		printf("\n");
	}
}

/* ********** KELOMPOK TEST TERHADAP Matrix ********** */
boolean isSquare(Matrix m) {
/* Mengirimkan true jika m adalah matriks dg ukuran baris dan kolom sama */
	return (ROW_EFF(m) == COL_EFF(m));
}

boolean isSymmetric(Matrix m) {
/* Mengirimkan true jika m adalah matriks simetri : isSquare(m) 
   dan untuk setiap elemen m, ELMTMAT(M, i, j) = ELMTMAT(M, j, i) */
	int i, j;
	
	if (isSquare(m)) {
		for (i = 0; i < ROW_EFF(m); i++) {
			for (j = 0; j < COL_EFF(m); j++) {
				if (ELMTMAT(m, i, j) != ELMTMAT(m, j, i)) {
					return false;
				}
			}
		}
		return true;
	} else {
		return false;
	}
}

POINT searchCharInMatrix(Matrix m, char c){
/* Mengembalikan index posisi dari char C pada matrix M dalam bentuk POINT*/
	int i, j;
	POINT result;
	for (i = 0; i < ROW_EFF(m); i++){
		for (j =0; j < COL_EFF(m); j++){
			if (ELMTMAT(m, i, j) == c){
				Absis(result) = i;
				Ordinat(result) = j;
			}
		}
	}
	return result;
}


/*								--------------------------------ADT TAMBAHAN UNTUK PROSES MOVE DLL ITU---------------------------------------------------				*/
boolean isCan(Matrix m, int i, int j,char c)
/* Mengembalikan apakah simulator dapat melakukan sesuatu (dalam artian berada disebelah petak spesial untuk melakukan sesuatu)*/
{
	// Cari dahulu char C ada di petak apa
	int row, col;
	POINT loc = searchCharInMatrix(m, c);
	
	// Ditukar karena row adalah sumbu y dan col adalah sumbu x
	row = Ordinat(loc);
	col = Absis(loc);

	// Cek apakah bersebelahan
	if (i == row){
		return (j == col-1 || j == col+1);
	} else if (j == col){
		return (i == row-1 || i == row+1);
	} else {
		return false;
	}

	
}

boolean canSwap(Matrix m, POINT des){
// mengembalikan true jika elemen matrix pada des adalah ' ' (artinya bisa bergerak/bukan obstacle)
	return ELMTMAT(m, Ordinat(des), Absis(des)) == ' ';
}

void swapElmt(Matrix * m, POINT *src, POINT des){
/* I.S. m, src, des = terdefinisi */
/* F.S. jika dapat ditukar (canSwap = true) elemen pada src bertukar dengan elemen pada des, 
jika tidak dapat ditukar maka tidak melakukan apa-apa */
	if (canSwap(*m, des)){
		char temp = ELMTMAT(*m, Ordinat(des), Absis(des));
		ELMTMAT(*m, Ordinat(des), Absis(des)) = ELMTMAT(*m, Ordinat(*src), Absis(*src));
		ELMTMAT(*m, Ordinat(*src), Absis(*src)) = temp;
		*src = des;
		printf("Simulator telah bergerak ke arah yang diinginkan.\n");
	}
	else { 
		printf("Simulator tidak bisa masuk ke petak tersebut.\n");
	}
}

//Disini misal mau ngecek bisa fry atau boil atau buy apapun itu caranya kalo perintah Buy maka harus ada program yang ngaish tau kalo perintah buy
//Char yang harus dikeluarkan T baru char itu masukin sini 


