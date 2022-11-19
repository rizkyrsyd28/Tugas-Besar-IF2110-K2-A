

#include <stdio.h>
#include <stdlib.h>
#include "string.h"

// KONSTRUKTOR
void createStringEmpty(char* str){
// Membuat string (kembali) menjadi string kosong
    int length = lengthString(str);
    int i;
    for (i = 0; i < length; i++){
        str[i] = '\0';
    }
}

// Fungsi dan Prosedur lain
void upper(char*str)
// Mengembalikan string dengan huruf kapital
{
    int i;
    for(i = 0; i < lengthString(str); i++){
        if (str[i] >= 97 && str[i] <=122){
            // ASCII 97-122 adalah huruf kecil
            // ASCII 65-90 adalah huruf kapital
            str[i] = str[i] - 32;
        }
    }
}

boolean isBlank (char c){
// Memeriksa apakah karakter C adalah blank
    return (c == ' ');
}

int MakeCharToInt (char c){
// Konversi tipe Char ke Integer
// Diasumsikan input selalu benar (merupakan suatu angka)
    return (c - 48);
}

int stringToInt (char* str){
    int sum = 0;
    int length = lengthString(str);
    int i;
    for (i = 0; i < length; i++){
        sum = sum*10 + MakeCharToInt(str[i]);
    }
    return sum;
}

int lengthString(char *str)
// Mengembalikan panjang sebuah string
{
	char *String1;
    int result;

    String1 = str;
    for (result = 0; *String1; result++)
        String1++;
    return result;
}

boolean isStringEqual(char *str1, char *str2)
// Memeriksa apakah kedua buah string adalah string yang sama
{

    if (lengthString(str1) != lengthString(str2))
        return false;
    else {
        int i;
        for (i = 0; i < lengthString(str1); i++){
            if (str1[i] != str2[i]){
                return false;
            }
        }
        return true;
    }
}

void appendChar(char* str, char c)
// Menggabungkan char dibagian belakang string str
// Kondisi string di declare dengan str[], bukan str*
{
    int length = lengthString(str);
    str[length] = c;
    str[length+1] = '\0';
}

void appendString(char* str1, char* str2)
// Menggabungkan memasukkan char ke dalam suatu string 
// Diasumsikan c1 tidak kosong
{
    int i;
    int j = lengthString(str2);

    for (i = 0; str2[i] != '\0'; i++){
        str1[i+j] = str2[i];
    }
    str1[i+j] = '\0';
    
}

void copyString(char* str1, char* str2){
// Membuat str2 menjadi string yang sama dengan str1
    int i;
    int length = lengthString(str1);
    for(i=0; i < length; i++){
        str2[i] = str1[i];
    }
}