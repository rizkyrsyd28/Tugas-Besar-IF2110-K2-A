#include <stdio.h>
#include <string.h>


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

const char* getFilePath(){
    char filename[100];
    printf("File: ");
    scanf("%s", filename);
    char additionalPath[] = "../TextFile/";
    return (strcat(additionalPath, filename));

}

int main (){
    char *filepath;
    *filepath = getFilePath();

    return 0;
}