// PARSING TXT FILE

#include <stdio.h>
#include <stdlib.h>
#include "../ADT/Makanan/makanan.c"
//#include "../ADT/ListStatik/liststatik.c"
#include "../ADT/MesinKata/wordmachine.c"
#include "../ADT/Matrix/matrix.c"
#include "../ADT/Resep/resep.c"
#include "../ADT/boolean.h"

void giveMark(char* str){
    // str[lengthString(str)-1] = '\0'; digunakan untuk menghilangkan \n pada string yang dibaca
    // str[lengthString(str)] = '.'; digunakan untuk menambahkan MARK pada string yang dibaca
    str[lengthString(str)-1] = '\0';
    str[lengthString(str)] = '.';
}

void konfigMakanan (){
    char *makananPath = "../TextFile/makanan.txt";

    Makanan Mkn;
    FILE *makananFile;

    int bufferLength = 30;
    char buffer[bufferLength];
    int idx;

    makananFile = fopen(makananPath, "r");
    if (makananFile == NULL){
        printf("File tersebut gagal dibaca!\n");
    }

    // BACA KALIMAT PERTAMA
    fgets(buffer, bufferLength, makananFile);
    giveMark(buffer);


    STARTWORD(buffer, &idx);
    int n;
    while (!endWord){
        n = WordToInt(currentWord);
        ADVWORD(buffer, &idx);
    }
    printf("%d\n", n);

    int i;
    int j;
    int id;
    int count;
    boolean check;
    int hour, day, minute;
    for (i = 0; i < n; i++){
        CreateEmptyMakanan(&Mkn);

        // =============== BACA ID ===============
        fgets(buffer, bufferLength, makananFile);
        buffer[lengthString(buffer)-1] = '\0';
        buffer[lengthString(buffer)] = '.';
        STARTWORD(buffer, &idx);
        while (!endWord){
            id = WordToInt(currentWord);
            ADVWORD(buffer, &idx);
        }
        idMkn(Mkn) = id;

        // =============== BACA NAMA ===============
        fgets(buffer, bufferLength, makananFile);
        buffer[lengthString(buffer)-1] = '\0';
        copyString(buffer, str(nameMkn(Mkn)));
        len(nameMkn(Mkn)) = lengthString(buffer);

        // =============== BACA EXPIRY ===============
        fgets(buffer, bufferLength, makananFile);
        giveMark(buffer);
        count = 1;
        STARTWORD(buffer, &idx);
        while (!endWord){
            if ( count == 1){
                day = WordToInt(currentWord);
                count++;
            } else if (count == 2){
                hour = WordToInt(currentWord);
                count++;
            } else if (count == 3){
                minute = WordToInt(currentWord);
                count++;
            }
            ADVWORD(buffer, &idx);
        }
        Day(expMkn(Mkn)) = day;
        Hour(expMkn(Mkn)) = hour;
        Minute(expMkn(Mkn)) = minute;

        // =============== BACA DELIVERY ===============
        fgets(buffer, bufferLength, makananFile);
        giveMark(buffer);
        count = 1;
        STARTWORD(buffer, &idx);
        while (!endWord){
            if ( count == 1){
                day = WordToInt(currentWord);
                count++;
            } else if (count == 2){
                hour = WordToInt(currentWord);
                count++;
            } else if (count == 3){
                minute = WordToInt(currentWord);
                count++;
            }
            ADVWORD(buffer, &idx);
        }
        Day(dlvMkn(Mkn)) = day;
        Hour(dlvMkn(Mkn)) = hour;
        Minute(dlvMkn(Mkn)) = minute;

        // =============== BACA ACTION ===============
        if (i == n-1){
            // untuk paling terakhir, karakter trakhir dari string tidak ada '\n', jadi tidak perlu diubah.
            fgets(buffer, bufferLength, makananFile);
            copyString(buffer, str(actMkn(Mkn)));
            len(actMkn(Mkn)) = lengthString(buffer);
        } else {
            fgets(buffer, bufferLength, makananFile);
            buffer[lengthString(buffer)-1] = '\0';
            copyString(buffer, str(actMkn(Mkn)));
            len(actMkn(Mkn)) = lengthString(buffer);
        }

        printMakanan(Mkn); printf("\n");
    }
    fclose(makananFile);
}

//Menampilkan ASCIIArt dibagian awal
void ASCIIArt()
{
	FILE * fPointer;
	fPointer = fopen("../TextFile/ASCIIArt.txt", "r");
	char singleLine[150];
	
	while(!feof(fPointer))
	{
		fgets(singleLine, 150, fPointer);
		puts(singleLine);
	}
	fclose(fPointer);
}

Matrix konfigMap(){
    FILE * fMap;
    
    int bufferLength = 30;
    char buffer[bufferLength];
    int idx;

    fMap = fopen("../TextFile/peta.txt", "r");
    if (fMap == NULL){
        printf("File Tersebut gagal dibaca!");
    }    

    fgets(buffer, bufferLength, fMap);
    giveMark(buffer);

    STARTWORD(buffer, &idx);
    int n = -1, m = -1;

    while(!endWord){
        if (n == -1){
            n = WordToInt(currentWord);
            ADVWORD(buffer, &idx);
        }
        if (m == -1){
            m = WordToInt(currentWord);
            ADVWORD(buffer, &idx);
        }
    }
    Matrix Map; 
    createMatrix(n + 2, m + 2, &Map);

    for (int i = 1; i < n + 1; i++){
        fgets(buffer, bufferLength, fMap);
        giveMark(buffer);
        STARTWORD(buffer, &idx);
        while(!endWord){
            for (int j = 1; j < m + 1; j++){
                if (currentWord.TabWord[j-1] == '#'){
                    ELMT(Map, i, j) = ' ';
                }
                else{
                    ELMT(Map, i, j) = currentWord.TabWord[j-1];
                }
            }
            ADVWORD(buffer, &idx);
        }
    }
    
    //displayMatrix(Map);
    return Map;
}

Cookbook konfigResep(){
    Cookbook C;
    FILE * fResep;
    
    int bufferLength = 30;
    char buffer[bufferLength];
    int idx;

    fResep = fopen("../TextFile/resep.txt", "r");
    if (fResep == NULL){
        printf("File Tersebut gagal dibaca!");
    }  

    fgets(buffer, bufferLength, fResep);
    giveMark(buffer);

    STARTWORD(buffer, &idx);
    int t = -1;

    while(!endWord){
        if (t == -1){
            t = WordToInt(currentWord);
            ADVWORD(buffer, &idx);
        }
    }    

    NTree * Trees = (NTree*) malloc (t * sizeof(NTree));

    for (int i = 0; i < t; i++){

        int bufferLength = 30;
        char buffer[bufferLength];
        int idx;
        
        if (i == t - 1){
            fgets(buffer, bufferLength, fResep);
            buffer[lengthString(buffer)] = '.';
        }
        else{
            fgets(buffer, bufferLength, fResep);
            giveMark(buffer);
        }

        int count = 0;
        STARTWORD(buffer, &idx);
        while(!endWord){
            if (count == 0){
                Trees[i] = newTree(WordToInt(currentWord));
                count++;
            }
            else if (count == 1){
                makeBranch(&Trees[i], WordToInt(currentWord));
                count++;
            }
            else{
                addChild(&Trees[i], WordToInt(currentWord));
            }
            ADVWORD(buffer, &idx);
        }
    }

    // checking
    for (int i = 0; i < t; i++){
        for (int j = 0; j < t; j++){
            if (i != j){
                checkMerge(&Trees[i], Trees[j]);
            }
        }
    }

    NResep(C) = t;
    Resep(C) = Trees;
    return C;
}
