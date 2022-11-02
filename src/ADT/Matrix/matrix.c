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
void readMatrix(Matrix *m, int nRow, int nCol) {
	int i, j;
	createMatrix(nRow, nCol, m);
	for (i = 0; i < nRow; i++) {
		for (j = 0; j < nCol; j++) {
			scanf("%c", &ELMTMAT(*m, i, j));
		}
	}
}

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


/*								--------------------------------ADT TAMBAHAN UNTUK PROSES MOVE DLL ITU---------------------------------------------------				*/
boolean isCan(Matrix m, int i, int j,char c)				//i dan j adalah posisi nilai yang kita ingin cek	
{
	// Cari dahulu char C ada di petak apa
	int x, y, row, col;
	for (x = 0; x < ROW_EFF(m); x++){
		for (y = 0; y < COL_EFF(m); y++){
			if (ELMTMAT(m, x, y) == c){
				// Ditukar karena baris adalah sumbu y dan kolom adalah sumbu x
				row = y;
				col = x;
			}
		}
	}

	// Cek apakah bersebelahan
	if (i == row){
		return (j == col-1 || j == col+1);
	} else if (j == col){
		return (i == row-1 || i == row+1);
	} else {
		return false;
	}


	// //Mengirimkan true jika S ada di sekitar T dimana T untuk telepon
	// int Row = i - 1;
	// int Col;
    // boolean valid = false;

    // /* Algoritma */
    // while (Row <= i+1 && !valid) {
    //     if (Row == i) {
    //         Col = j - 1;
    //         while (Col <= j + 1 && !valid) {
    //             if (isMatIdxEff(m, Row, Col)) {
    //                 if (ELMTMAT(m, Row, Col) ==  c) {
    //                     valid = true;
    //                 }
    //                 else {
    //                     Col++;
    //                 }
    //             }
    //             else {
    //                Col++;
    //             }
    //         }
    //         Row++;
    //     }
    //     else {
    //         if (isMatIdxEff(m, Row, j)) {
    //             if (ELMTMAT(m, Row, j) == c) {
    //                 valid = true;
    //             }
    //             else {
    //                 Row++;
    //             }
    //         }
    //         else {
    //             Row++;
    //         }
    //     }
    // }

    // return valid;
	
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
	}
	else { 
		printf("Simulator tidak bisa masuk ke petak tersebut.\n");
	}
}

//Disini misal mau ngecek bisa fry atau boil atau buy apapun itu caranya kalo perintah Buy maka harus ada program yang ngaish tau kalo perintah buy
//Char yang harus dikeluarkan T baru char itu masukin sini 


