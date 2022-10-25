// PARSING TXT FILE

#include <stdio.h>
#include <stdlib.h>
// #include "../ADT/Makanan/makanan.c"
#include "../ADT/String/string.c"

void konfigMakanan (){
    char *makananPath = "../TextFile/makanan.txt";
    // char *petapath = "../TextFile/peta.txt";
    // char *reseppath = "../TextFile/resep.txt";

    FILE *makananFile;

    int bufferLength = 30;
    char buffer[bufferLength];

    makananFile = fopen(makananPath, "r");
    if (makananFile == NULL){
        printf("File tersebut gagal dibaca!\n");
    }

    // Baca baris pertama
    fgets(buffer, bufferLength, makananFile);
    buffer[lengthString(buffer)-1] = '\0';
    // buffer[lengthString(buffer)-1] = '\0' digunakan untuk menghilangkan \n pada string buffer
    int n = stringToInt(buffer);
    printf("%d\n", n);

    int i;
    int j;
    int count;
    boolean check;
    int hour, day, minute;
    for (i = 0; i < n; i++){
        // ID
        fgets(buffer, bufferLength, makananFile);
        buffer[lengthString(buffer)-1] = '\0';
        int id = stringToInt(buffer);
        printf("%d\n", id);

        // Nama
        fgets(buffer, bufferLength, makananFile);
        buffer[lengthString(buffer)-1] = '\0';
        char *name = buffer;
        printf("%s\n", name);

        // Expiry
        fgets(buffer, bufferLength, makananFile);
        buffer[lengthString(buffer)-1] = '.';
        buffer[lengthString(buffer)] = '\0';
        j = 0;
        count = 1;
        check = true;
        char temp[30] = "";
        while (check){
            if (buffer[j] == '.'){
                minute = stringToInt(temp);
                check = false;
            }
            else if (isBlank(buffer[j]) && count == 1){
                day = stringToInt(temp);
                count++;
                createEmpty(temp);
            } else if (isBlank(buffer[j]) && count == 2){
                hour = stringToInt(temp);
                count++;
                createEmpty(temp);
            } else {
                appendChar(temp, buffer[j]);
            }

            j++;
        }
        printf("%d %d %d\n", day, hour, minute);

        // Delivery
        fgets(buffer, bufferLength, makananFile);
        buffer[lengthString(buffer)-1] = '.';
        buffer[lengthString(buffer)] = '\0';
        j = 0;
        count = 1;
        check = true;
        createEmpty(temp);
        while (check){
            if (buffer[j] == '.'){
                minute = stringToInt(temp);
                check = false;
            }
            else if (isBlank(buffer[j]) && count == 1){
                day = stringToInt(temp);
                count++;
                createEmpty(temp);
            } else if (isBlank(buffer[j]) && count == 2){
                hour = stringToInt(temp);
                count++;
                createEmpty(temp);
            } else {
                appendChar(temp, buffer[j]);
            }

            j++;
        }
        printf("%d %d %d\n", day, hour, minute);

        // Action
        fgets(buffer, bufferLength, makananFile);
        buffer[lengthString(buffer)-1] = '\0';
        char *action = buffer;
        printf("%s\n", action);

    }

    fclose(makananFile);
}