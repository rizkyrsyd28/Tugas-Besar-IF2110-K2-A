// PARSING TXT FILE

#include <stdio.h>
#include <stdlib.h>
#include "../ADT/MesinKata/wordmachine.c"

// char *readFile (char *filename){
//     FILE *file;
    
//     file = fopen(filename, "r"); // reading file
//     if (file == NULL) return NULL; 

//     fseek(file, 0, SEEK_END);
//     int length = ftell(file);
//     fseek(file, 0, SEEK_SET);

//     char *string = malloc(sizeof(char) * (length+1));

//     char c;
//     int i = 0;
//     while ( (c = fgetc(file)) != EOF)
//     {
//         string[i] = c;
//         i++;
//     }

//     string[i] = '\0';

//     fclose(file);

//     return string;
// }


int main (){
    char *makananPath = "../TextFile/makanan.txt";
    // char *petapath = "../TextFile/peta.txt";
    // char *reseppath = "../TextFile/resep.txt";

    FILE *makananFile;

    int bufferLength = 30;
    char buffer[bufferLength];

    makananFile = fopen(makananPath, "r");
    if (makananFile == NULL){
        return 1;
    }
    while (fgets(buffer, bufferLength, makananFile)){
        buffer[lengthString(buffer)-1] = '.';
        buffer[lengthString(buffer)] = '\0';
        //appendChar(buffer, '.');
        // int length = lengthString(buffer);
        // int i;
        // for (i =0; i < length; i++){
        //     printf("%c,", buffer[i]);
        // }
        printf("%s\n", buffer);
    }
    // // Baca baris pertama
    // fgets(buffer, bufferLength, makananFile);
    // int n = stringToInt(buffer);

    // int i;
    // for (i = 0; i < n; i++){
    //     // ID
    //     fgets(buffer, bufferLength, makananFile);
    //     int id = stringToInt(buffer);
    //     // Nama
    //     fgets(buffer, bufferLength, makananFile);
    //     char *name = buffer;

    //     // Expiry
    //     fgets(buffer, bufferLength, makananFile);
    //     appendChar(buffer, '.');
    //     printf("%s\n", buffer);

        
    //     // Delivery
    //     fgets(buffer, bufferLength, makananFile);

    //     // Action
    //     fgets(buffer, bufferLength, makananFile);
    //     char *action = buffer;

    // }

    fclose(makananFile);


    return 0;
}