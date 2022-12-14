#include <stdio.h>
#include <stdlib.h>
#include "wordmachine.h"
#include "charmachine.c"
#include "../String/string.c"


// =========================== IMPLEMENTASI ADT UNTUK WORD ===========================

boolean endWord;
Word currentWord;

void IgnoreBlanks(char* str, int *idx)
{
    /* Mengabaikan satu atau beberapa BLANK
       I.S. : currentChar sembarang
       F.S. : currentChar ≠ BLANK atau currentChar = MARK */
    while (str[*idx] == BLANK)
    {
        //printf("%d\n", *idx);
        ADV(idx);
    }
}

void STARTWORD(char* str, int *idx)
{
    /* I.S. : currentChar sembarang
       F.S. : endWord = true, dan currentChar = MARK;
              atau endWord = false, currentWord adalah kata yang sudah diakuisisi,
              currentChar karakter pertama sesudah karakter terakhir kata */
    START(str, idx);
    IgnoreBlanks(str, idx);
    if (str[*idx] == MARK){
        endWord = true;
    } else {
        endWord = false;
        CopyWord(str, idx);
    }
}

void ADVWORD(char* str, int *idx)
{
    /* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi
       F.S. : currentWord adalah kata terakhir yang sudah diakuisisi,
              currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
              Jika currentChar = MARK, endWord = true.
       Proses : Akuisisi kata menggunakan procedure CopyWord */
    IgnoreBlanks(str, idx);
    if (str[*idx] == MARK){
        endWord = true;
    }else {
        CopyWord(str, idx);
        IgnoreBlanks(str, idx);
    }
}

void CopyWord(char* str, int *idx)
{
    /* Mengakuisisi kata, menyimpan dalam currentWord
       I.S. : currentChar adalah karakter pertama dari kata
       F.S. : currentWord berisi kata yang sudah diakuisisi;
              currentChar = BLANK atau currentChar = MARK;
              currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
              Jika panjang kata melebihi CAPACITY, maka sisa kata terpotong */
    currentWord.Length = 0;
    while (str[*idx] != BLANK && str[*idx] != MARK)
    {
        if (currentWord.Length < NMax)
        { // jika lebih akan terpotong
            currentWord.TabWord[currentWord.Length++] = str[*idx];
            ADV(idx);
        }
        else
            break;
    }
}

int WordToInt(Word word){
/* Mengembalikan integer hasil konversi word ke integer */
    int sum = 0;
    int i;
    for (i = 0; i < word.Length; i++){
        sum = sum*10 + (word.TabWord[i]- 48);
    }
    return sum;
}

void printWord(Word word){
/* I.S. word terdefinisi
F.S. menampilkan kata yang ditampung pada word */
    int i;
    for (i = 0; i < word.Length; i++){
        printf("%c", word.TabWord[i]);
    }
}

boolean isWordEqual(Word word1, Word word2)
/* Mengembalikan true apabila kedua word adalah berisikan karakter yang sama dan memiliki panjang yang sama */
{
    if (word1.Length != word2.Length){
        return false;
    } else {
        int i;
        for (i = 0; i < word1.Length; i++){
            if (word1.TabWord[i] != word2.TabWord[i]){
                return false;
            }
        }
        return true;
    }
}

boolean isWordStringEqual(Word w, char* c)
/* Mengembalikan true apabila kata yang dikandung pada c berisikan karakter yang sama pada array of char yang dikandung oleh w */
{
    if (w.Length != lengthString(c)){
        return false;
    } else {
        int i;
        for (i=0; i < w.Length; i++){
            if (w.TabWord[i] != c[i]){
                return false;
            }
        }
        return true;
    }
}

boolean isWordAllIntegers(Word w)
/* Mengembalikan true apabila semua karakter yang dikandung pada array of char pada w merupakan angka sehingga dapat diubah menjadi integer */
{
    int i;
    for (i = 0; i < w.Length; i++){
        if (str(w)[i] < 48 || str(w)[i] > 57){
            return false;
        }
    }
    return true;
}

Word appendWord(Word w1, Word w2)
/* Mengembalikan word yang merupakan penggabungan Word w2 setelah Word w1 */
{
    Word w;
    w.Length = w1.Length + w2.Length;
    int i, j;
    int count = 0;
    for (i=0; i < w1.Length; i++){
        w.TabWord[count] = w1.TabWord[i];
        count++;
    }
    for (j=0; j < w2.Length; j++){
        w.TabWord[count] = w2.TabWord[j];
        count++;
    }
    return w;
}


