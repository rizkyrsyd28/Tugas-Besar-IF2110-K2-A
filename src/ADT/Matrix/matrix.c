#include "matrix.h"
#include <stdio.h>

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk Matrix *** */
void createMatrix(int nRows, int nCols, Matrix *m) {
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
	return (i >= 0 && i < ROW_CAP && j >= 0 && j < COL_CAP);
}

IdxType getLastIdxRow(Matrix m) {
	return (ROW_EFF(m)-1);
}

IdxType getLastIdxCol(Matrix m) {
	return (COL_EFF(m)-1);
}

boolean isMatIdxEff(Matrix m, IdxType i, IdxType j) {
	return (i >= 0 && i < ROW_EFF(m) && j >= 0 && j < COL_EFF(m));
}


/* ********** Assignment  Matrix ********** */
void copyMatrix(Matrix mIn, Matrix *mOut) {
	*mOut = mIn;
}


/* ********** KELOMPOK BACA/TULIS ********** */
void displayMatrix(Matrix m) {
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
	return (ROW_EFF(m) == COL_EFF(m));
}

boolean isSymmetric(Matrix m) {
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
boolean isCan(Matrix m, int i, int j,char c)				//i dan j adalah posisi nilai yang kita ingin cek	
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
	return ELMTMAT(m, Ordinat(des), Absis(des)) == ' ';
}

void swapElmt(Matrix * m, POINT *src, POINT des){
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


