
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "parser.c"
#include "../ADT/Simulator/simulator.c"
#include "../ADT/piroqueue/piroqueue.c"

#define MAX_COMMAND 30


int main () {
    char command[MAX_COMMAND] = "\0";
    boolean program = true;
    int idx;

    ASCIIArt();
    printf("Input 'START' untuk melakukan program.\n");
    fgets(command, MAX_COMMAND, stdin);
    upper(command);
    giveMark(command);
    // Procedure giveMark dilakukan karena diujung string ada '\n' dan perlu diberikan '.' sebagai MARK.

    // Menggunakan mesin kata untuk membaca
    STARTWORD(command, &idx);
    /* Karena hanya satu kata (hanya menerima 'START'), 
    cukup STARTWORD saja yang dijalankan */

    while (!isWordStringEqual(currentWord, "START")){
        printf("Input selain 'START' tidak diterima.\n");
        fgets(command, MAX_COMMAND, stdin);
        upper(command);
        giveMark(command);
        STARTWORD(command, &idx);
    }

    // ==== Mulai Konfigurasi ====

    printf("====================================================\n");
    printf("==============      KONFIGURASI      ===============\n");
    printf("====================================================\n");

    // Konfigurasi Simulator
    Simulator sim;
    ReadSimulator(&sim);
    printf("-> Konfigurasi Simulator - DONE\n");

    // Konfigurasi Waktu
    TIME currentTime;
    printf("Masukkan waktu awal dalam format (<hari> <jam> <menit>)\n");
    BacaTIME(&currentTime);
    printf("-> Konfigurasi Waktu - DONE\n");

    // Konfigurasi Makanan
    ListStatik listMakanan;
    listMakanan = konfigMakanan();
    printf("-> Konfigurasi Makanan - DONE\n");

    // Konfigurasi Peta
    Matrix map;
    map = konfigMap();
    printf("-> Konfigurasi Peta - DONE\n");

    // Konfigurasi Resep 

    // Konfigurasi Inventory
    PrioQueueTime inventory;
    MakeEmptyQueue(&inventory, 100);
    PrioQueueTime deliveryList;
    MakeEmptyQueue(&deliveryList, 100);
    printf("-> Konfigurasi Inventory - DONE\n");

    // Dummy (untuk mencegah error)
    fgets(command, MAX_COMMAND, stdin);


    // =========== PENJALANAN PROGRAM UTAMA ===========
    while(program){
        printf("====================================================\n");
        printf("==============       MAIN MENU       ===============\n");
        printf("====================================================\n");

        // Display simulator dan map
        DisplaySimulator(sim);
        printf("Waktu: ");
        TulisTIME(currentTime); 
        displayMatrix(map);

        // validAction digunakan untuk menandakan apakah suatu aksi menghabiskan waktu
        // Beberapa action dianggap tidak menghabiskan waktu
        boolean validAction = true;

        printf("Silahkan masukkan command yang ingin dilakukan.\n");
        printf("Masukkan 'HELP' untuk melihat list command yang dapat digunakan.\n");
        printf("Command: ");
        
        // Meminta input command setelah program dimulai
        fgets(command, MAX_COMMAND, stdin);
        upper(command);
        giveMark(command);
        STARTWORD(command, &idx);

        if (isWordStringEqual(currentWord, "EXIT")){
            printf("====================================================\n");
            printf("===============        EXIT          ===============\n");
            printf("====================================================\n");
            printf("Yahh kok udahan... :(\n");
            program = false;
        }
        else if (isWordStringEqual(currentWord, "MOVE")){
            printf("====================================================\n");
            printf("===============         MOVE         ===============\n");
            printf("====================================================\n");

            while (!endWord){ 
                ADVWORD(command, &idx);
            }
            if (isWordStringEqual(currentWord, "NORTH")){
                printf("north\n");
            }
            else if (isWordStringEqual(currentWord, "EAST")){
                printf("east\n");
            } 
            else if (isWordStringEqual(currentWord, "SOUTH")){
                printf("north\n");
            }
            else if (isWordStringEqual(currentWord, "WEST")){
                printf("west\n");
            } else {
                printf("Input selain 'NORTH', 'SOUTH', 'WEST', dan 'EAST' tidak diterima.\n");
            }

        }
        else if (isWordStringEqual(currentWord, "BUY")){
            printf("====================================================\n");
            printf("===============         BUY          ===============\n");
            printf("====================================================\n");

        }

        else if (isWordStringEqual(currentWord, "MIX")){
            printf("====================================================\n");
            printf("===============         MIX          ===============\n");
            printf("====================================================\n");

        }

        else if (isWordStringEqual(currentWord, "CHOP")){
            printf("====================================================\n");
            printf("===============         CHOP         ===============\n");
            printf("====================================================\n");

        }

        
        else if (isWordStringEqual(currentWord, "FRY")){
            printf("====================================================\n");
            printf("===============         FRY          ===============\n");
            printf("====================================================\n");

        }

        
        else if (isWordStringEqual(currentWord, "CATALOG")){
            printf("====================================================\n");
            printf("===============       CATALOG        ===============\n");
            printf("====================================================\n");
            validAction = false; // Action ini tidak menghabiskan waktu

            // Boleh panggil aja procedure printMakanan, udah dibikin di ADT Makanan

        }

        else if (isWordStringEqual(currentWord, "COOKBOOK")){
            printf("====================================================\n");
            printf("===============       COOKBOOK       ===============\n");
            printf("====================================================\n");
            validAction = false; // Action ini tidak menghabiskan waktu
        }

        else if (isWordStringEqual(currentWord, "INVENTORY")){
            printf("====================================================\n");
            printf("===============      INVENTORY       ===============\n");
            printf("====================================================\n");
            validAction = false; // Action ini tidak menghabiskan waktu

            if (IsEmptyQueue(inventory)){
                printf(" Tidak ada makanan pada inventory.\n");
            } else {
                PrintPrioQueueTime(inventory);
            }
        }

        else if (isWordStringEqual(currentWord, "DELIVERY")){
            printf("====================================================\n");
            printf("===============       DELIVERY       ===============\n");
            printf("====================================================\n");
            validAction = false; // Action ini tidak menghabiskan waktu

            if (IsEmptyQueue(deliveryList)){
                printf(" Tidak ada makanan pada list delivery.\n");
            } else {
                PrintPrioQueueTime(deliveryList);
            }
        }

        else if (isWordStringEqual(currentWord, "WAIT")){
            printf("====================================================\n");
            printf("===============         WAIT         ===============\n");
            printf("====================================================\n");

            // Action ini dianggap tidak menghabiskan waktu untuk menghindari penambahan waktu ganda
            // Setelah penambahan waktu oleh command WAIT, tidak perlu lagi dilakukan penambahan waktu 1 menit
            validAction = false; 

            boolean allInteger = true;
            int waitHour, waitMinute;

            // JANGAN LUPA BIKIN HANDLE KALAU INPUTNYA HANYA 1 INTEGER, BUKAN 2 INTEGER

            // Cek terlebih dahulu apakah input valid (x dan y adalah integer)
            ADVWORD(command, &idx);
            if (isWordAllIntegers(currentWord)){
                 waitHour = WordToInt(currentWord);
            } else {
                allInteger = false;
            }

            ADVWORD(command, &idx);
            if (isWordAllIntegers(currentWord)){
                waitMinute = WordToInt(currentWord);
            } else {
                allInteger = false;
            }
            
            if (allInteger){
                printf("%d %d\n", waitHour, waitMinute);
            } else {
                printf("Masukan tidak valid. X dan Y hanya diperbolehkan memiliki tipe integer.\n");
            }

        }

        else if (isWordStringEqual(currentWord, "UNDO")){
            printf("====================================================\n");
            printf("===============         UNDO         ===============\n");
            printf("====================================================\n");

        }

        else if (isWordStringEqual(currentWord, "REDO")){
            printf("====================================================\n");
            printf("===============         REDO         ===============\n");
            printf("====================================================\n");

        }

        else if (isWordStringEqual(currentWord, "HELP")){
            printf("====================================================\n");
            printf("===============        HELP          ===============\n");
            printf("====================================================\n");
            printf("Berikut adalah command yang dapat dimasukkan:\n");
            printf("MOVE NORTH      - Menggerakan simulator ke petak sebelah atas\n");
            printf("MOVE EAST       - Menggerakan simulator ke petak sebelah kanan\n");
            printf("MOVE SOUTH      - Menggerakan simulator ke petak sebelah bawah\n");
            printf("MOVE WEST       - Menggerakan simulator ke petak sebelah kiri\n");
            printf("BUY             - Proses pembelian Makanan\n");
            printf("MIX             - Proses pencampuran Makanan\n");
            printf("FRY             - Proses penggorengan Makanan\n");
            printf("CHOP            - Proses pemotongan Makanan\n");
            printf("CATALOG         - Melihat data list makanan yang valid\n");
            printf("COOKBOOK        - Melihat data list resep yang valid\n");
            printf("INVENTORY       - Membuka inventory yang dimiliki oleh simulator\n");
            printf("DELIVERY        - Membuka tampilan list makanan yang sedang dikirim\n");
            printf("WAIT (x) (y)    - Mempercepat time selama x jam dan y menit\n");
            printf("UNDO            - Mengembalikan kondisi sebelum terlaksananya action terakhir\n");
            printf("REDO            - Melakukan kembali action yang telah di-undo\n");
            validAction = false; // Action ini tidak menghabiskan waktu
        }

        else {
            printf("====================================================\n");
            printf("===============     INVALID INPUT    ===============\n");
            printf("====================================================\n");
            printf("Input tidak valid. Silahkan inputkan command yang valid.\n");
            validAction = false;
        }


        // ================= AFTER ACTION ALGORITHM =================
        if (validAction){
            // Waktu hanya ditambahkan bila action yang dilakukan valid
            currentTime = NextMinute(currentTime);
        }
    }
}