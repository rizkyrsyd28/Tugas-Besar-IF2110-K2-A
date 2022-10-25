// PARSING TXT FILE

#include <stdio.h>
#include <stdlib.h>
// #include "../ADT/Makanan/makanan.c"
#include "../ADT/MesinKata/wordmachine.c"

void giveMark(char* str){
    // str[lengthString(str)-1] = '\0'; digunakan untuk menghilangkan \n pada string yang dibaca
    // str[lengthString(str)] = '.'; digunakan untuk menambahkan MARK pada string yang dibaca
    str[lengthString(str)-1] = '\0';
    str[lengthString(str)] = '.';
}

void konfigMakanan (){
    char *makananPath = "../TextFile/makanan.txt";

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

        // =============== BACA ID ===============
        fgets(buffer, bufferLength, makananFile);
        buffer[lengthString(buffer)-1] = '\0';
        buffer[lengthString(buffer)] = '.';
        STARTWORD(buffer, &idx);
        while (!endWord){
            id = WordToInt(currentWord);
            ADVWORD(buffer, &idx);
        }
        printf("%d\n", id);

        // =============== BACA NAMA ===============
        fgets(buffer, bufferLength, makananFile);
        buffer[lengthString(buffer)-1] = '\0';
        char *name = buffer;
        printf("%s\n", name);

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
        printf("%d %d %d\n", day, hour, minute);

        // Delivery
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
        printf("%d %d %d\n", day, hour, minute);

        // Action
        if (i == n-1){
            // untuk paling terakhir, karakter trakhir dari string tidak ada '\n', jadi tidak perlu diubah.
            fgets(buffer, bufferLength, makananFile);
            char *action = buffer;
            printf("%s\n", action);
        } else {
            fgets(buffer, bufferLength, makananFile);
            buffer[lengthString(buffer)-1] = '\0';
            char *action = buffer;
            printf("%s\n", action);
        }

    }
    fclose(makananFile);
}

//Menampilkan ASCIIArt dibagian awal
void ASCIIArt()
{
	FILE * fPointer;
	fPointer = fopen("ASCIIArt.txt", "r");
	char singleLine[150];
	
	while(!feof(fPointer))
	{
		fgets(singleLine, 150, fPointer);
		puts(singleLine);
	}
	fclose(fPointer);
}

