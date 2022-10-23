#include <stdio.h>
#include "wordmachine.h"
#include "charmachine.c"
#include <stdlib.h>
boolean endWord;
Word currentWord;

void IgnoreBlanks()
{
    /* Mengabaikan satu atau beberapa BLANK
       I.S. : currentChar sembarang
       F.S. : currentChar ≠ BLANK atau currentChar = MARK */
    while (currentChar == BLANK)
    {
        ADV();
    }
}

void STARTWORD()
{
    /* I.S. : currentChar sembarang
       F.S. : endWord = true, dan currentChar = MARK;
              atau endWord = false, currentWord adalah kata yang sudah diakuisisi,
              currentChar karakter pertama sesudah karakter terakhir kata */
    START();
    IgnoreBlanks();
    if (currentChar == MARK)
    {
        endWord = true;
    }
    else
    {
        endWord = false;
        CopyWord();
    }
}

void ADVWORD()
{
    /* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi
       F.S. : currentWord adalah kata terakhir yang sudah diakuisisi,
              currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
              Jika currentChar = MARK, endWord = true.
       Proses : Akuisisi kata menggunakan procedure CopyWord */
    IgnoreBlanks();
    if (currentChar == MARK)
    {
        endWord = true;
    }
    else
    {
        CopyWord();
        IgnoreBlanks();
    }
}

void CopyWord()
{
    /* Mengakuisisi kata, menyimpan dalam currentWord
       I.S. : currentChar adalah karakter pertama dari kata
       F.S. : currentWord berisi kata yang sudah diakuisisi;
              currentChar = BLANK atau currentChar = MARK;
              currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
              Jika panjang kata melebihi CAPACITY, maka sisa kata terpotong */
    currentWord.Length = 0;
    while (currentChar != BLANK && currentChar != MARK)
    {
        if (currentWord.Length < NMax)
        { // jika lebih akan terpotong
            currentWord.TabWord[currentWord.Length++] = currentChar;
            ADV();
        }
        else
            break;
    }
}

int lengthString(char *str)
{
	char *String1;
    int result;

    String1 = str;
    for (result = 0; *String1; result++)
        String1++;
    return result;
}

int StringsNotEqual(Word str1, char *str2)
{
	int length1;
    char *String1;
    char *String2;

    length1 = str1.Length;
    if (length1 != lengthString(str2))
        return 1;

    String1 = str1.TabWord;
    String2 = str2;
    if (*String1)
    {
        while ((*String1 == *String2))
        {
            length1--;
            String1++;
            String2++;
            if (!length1)
                return 0;
        }
        return 1;
    }
    return 0;
}

int StringsEqualChar(char *str1, char *str2)
{
	char *String1;
    char *String2;
    int length1;

    length1 = lengthString(str1);
    if (length1 != lengthString(str2))
        return 0;

    String1 = str1;
    String2 = str2;
    if (*String1)
    {
        while ((*String1 == *String2))
        {
            String2++;
            String1++;
            if (!*String1)
                return 1;
        }
        return 0;
    }
    return 1;
}

