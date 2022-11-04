#include "../Stack/stack.c"
#include "simulator.c"
#include "../Point/point.c"
#include "../piroqueue/piroqueue.c"
#include "../MesinKata/wordmachine.c"
#include"../Makanan/makanan.c"
#include <stdio.h>

int main()
{
    Simulator S;
    ReadSimulator(&S);
    Makanan Ayam;
    Makanan Sapi;
    Makanan Minyak;
    Makanan Sayur;
    CreateEmptyMakanan(&Ayam);
    CreateEmptyMakanan(&Sapi);
    CreateEmptyMakanan(&Minyak);
    CreateEmptyMakanan(&Sayur);
    Word namasayur;
    int idx;
    char temp[100]="\0";
    printf("Masukan kata Sayur : ");
    fgets(temp, 100, stdin);

    // Mengubah nilai '\n' menjadi '\0' dan menambahkan MARK
    temp[lengthString(temp)-1] = '\0';
    appendChar(temp,'.');

    STARTWORD(temp,&idx);
    namasayur = currentWord;
    nameMkn(Sayur) = namasayur;

    


    //Display
    printf("-----------------------DISPLAY----------------------\n");
    printf("Display Simulator :\n");
    DisplaySimulator(S);
    printf("\n");
    printf("Display Nama : \n");
    DisplayNama(S);
    printf("\n");
    printf("Display Lokasi : \n");
    DisplayLokasi(S);
    printf("\n");
    //printf("Display Inventory : \n");
    //DisplayInventory(S);
    //printf("\n");


    //Gerak lokasi
    printf("-----------------------GESER LOKASI----------------------\n");
    GeserLokasi(&S,2);
    printf("\n");
    printf("Move EAST 1 : \n");
    DisplayLokasi(S);
    printf("\n");

    //Olah Makanan Inventory
    printf("-----------------------OLAH MAKANAN INVENTORY----------------------\n");
    //Enqueue(&Inventory(S),Ayam);
    OlahMakananInventory(&Inventory(S),5,0,Sayur,Sapi,Minyak,Sayur);
    printf("\n");
    printf("Inventory masuk \n");
    DisplayInventory(S);
    printf("\n");
    Makanan X;
    OlahMakananInventory(&Inventory(S),4,0,Sayur,Sapi,Minyak,Sayur); //DequeueAt Sayur, Enqueue Sayur
    DisplayInventory(S);
    printf("\n");

    //Kedaluwarsa Inventory
    printf("-----------------------Kedaluwarsa INVENTORY----------------------\n");
    KedaluwarsaInventory(&Inventory(S));
    printf("\n");
    DisplayInventory(S);
}
