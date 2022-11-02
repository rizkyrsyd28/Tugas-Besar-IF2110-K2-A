
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "parser.c"
#include "../ADT/Simulator/simulator.c"
#include "../ADT/piroqueue/piroqueue.c"

#define MAX_COMMAND 30

void getInput(char* string){
    // Fungsi untuk meminta input oleh user
    fgets(string, MAX_COMMAND, stdin);
    upper(string);
    // Procedure giveMark dilakukan karena diujung string ada '\n' dan perlu diberikan '.' sebagai MARK.
    giveMark(string);
}

int main () {
    char command[MAX_COMMAND] = "\0";
    boolean program = true;
    int idx;

    ASCIIArt();
    printf("Input 'START' untuk melakukan program.\n");
    getInput(command);

    // Menggunakan mesin kata untuk membaca
    STARTWORD(command, &idx);
    /* Karena hanya satu kata (hanya menerima 'START'), 
    cukup STARTWORD saja yang dijalankan */

    while (!isWordStringEqual(currentWord, "START")){
        printf("Input selain 'START' tidak diterima.\n");
        getInput(command);
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
    ListStatik foodList;
    foodList = konfigMakanan();
    int foodListLength = listLength(foodList);
    printf("-> Konfigurasi Makanan - DONE\n");
    
    // Konfigurasi Resep
    Cookbook bukuResep;
    bukuResep = konfigResep();
    printf("-> Konfigurasi Resep - DONE\n");

    // Konfigurasi Peta
    Matrix map;
    map = konfigMap();
    POINT startLoc = searchCharInMatrix(map, 'S');
    Absis(Lokasi(sim)) = Ordinat(startLoc);
    Ordinat(Lokasi(sim)) = Absis(startLoc);
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

    // Konfigurasi variabel global
    int i;
    int count;
    boolean subprogram = false;
    int idxFood;


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
        getInput(command);
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

            POINT src = Lokasi(sim);
            ADVWORD(command, &idx);

            if (isWordStringEqual(currentWord, "NORTH")){
                swapElmt(&map, &Lokasi(sim), NextY(src));

            }
            else if (isWordStringEqual(currentWord, "EAST")){
                swapElmt(&map, &Lokasi(sim), NextX(src));

            } 
            else if (isWordStringEqual(currentWord, "SOUTH")){
                swapElmt(&map, &Lokasi(sim), BackY(src));

            }
            else if (isWordStringEqual(currentWord, "WEST")){
                swapElmt(&map, &Lokasi(sim), BackX(src));

            } else {
                printf("Input selain 'NORTH', 'SOUTH', 'WEST', dan 'EAST' tidak diterima.\n");
            }

            if (NEQ(src, Lokasi(sim))){
                validAction = true;
            }
            else{
                validAction = false;
            }

        }
        else if (isWordStringEqual(currentWord, "BUY")){
            printf("====================================================\n");
            printf("===============         BUY          ===============\n");
            printf("====================================================\n");

            // Program akan di loop pada sesi Buy
            if (!isCan(map, Absis(Lokasi(sim)), Ordinat(Lokasi(sim)), 'T')){
                printf("Simulator tidak bersebelahan dengan tempat melakukan BUY.\n");
                printf("Pastikan Simulator berada di sebelah petak 'T'\n");
                validAction = false;
            } else {
                subprogram = true;
                while (subprogram){
                
                    printf("List Bahan Makanan yang Bisa Dibuat: \n");
                    count = 0;
                    for (i=0; i < foodListLength; i++){
                        if (isWordStringEqual(actMkn(ELMTLIST(foodList,i)), "BUY")){
                            count++;
                            printf("%d. ", count);
                            printWord(nameMkn(ELMTLIST(foodList, i)));
                            printf("\n");
                        }
                    }

                    // Handle jika konfigurasinya diganti
                    if (count == 0){
                        printf("Tidak ada bahan makanan yang bisa dibuat.\n");
                    };

                    printf("Ketik 0 untuk kembali ke Main Menu.\n");
                
                    // Meminta input dari pengguna
                    printf("Command: ");
                    getInput(command);
                    STARTWORD(command, &idx);
                    
                    // Handle untuk input tidak integer atau integer yang tidak valid
                    while (!isWordAllIntegers(currentWord) || WordToInt(currentWord) < 0 || WordToInt (currentWord) > count){
                        printf("Invalid input. Input bukanlah integer atau integer tersebut tidaklah valid.\n");
                        printf("Command: ");
                        getInput(command);
                        STARTWORD(command, &idx);
                    }
                    if (WordToInt(currentWord) == 0){
                        subprogram = false;
                        validAction = false; // Karena tidak melakukan apa-apa
                    } else {
                        // Inputnya telah sesuai dengan penomoran 
                        // Mencari idx makanan pada list makanan sesuai penomoran input user
                        idxFood = searchIndexOlahMakanan(foodList, "BUY", WordToInt(currentWord));
                        printMakanan(ELMTLIST(foodList, idxFood)); printf("\n");
                    }
                }
            }

        }

        else if (isWordStringEqual(currentWord, "MIX")){
            printf("====================================================\n");
            printf("===============         MIX          ===============\n");
            printf("====================================================\n");

            // Program akan di loop pada sesi Mix
            if (!isCan(map, Absis(Lokasi(sim)), Ordinat(Lokasi(sim)), 'M')){
                printf("Simulator tidak bersebelahan dengan tempat melakukan MIX.\n");
                printf("Pastikan Simulator berada di sebelah petak 'M'\n");
                validAction = false;
            } else {
                subprogram = true;
                while (subprogram){
                
                    printf("List Bahan Makanan yang Bisa Dibuat: \n");
                    count = 0;
                    for (i=0; i < foodListLength; i++){
                        if (isWordStringEqual(actMkn(ELMTLIST(foodList,i)), "MIX")){
                            count++;
                            printf("%d. ", count);
                            printWord(nameMkn(ELMTLIST(foodList, i)));
                            printf("\n");
                        }
                    }

                    // Handle jika konfigurasinya diganti
                    if (count == 0){
                        printf("Tidak ada bahan makanan yang bisa dibuat.\n");
                    };

                    printf("Ketik 0 untuk kembali ke Main Menu.\n");
                
                    // Meminta input dari pengguna
                    printf("Command: ");
                    getInput(command);
                    STARTWORD(command, &idx);
                    
                    // Handle untuk input tidak integer atau integer yang tidak valid
                    while (!isWordAllIntegers(currentWord) || WordToInt(currentWord) < 0 || WordToInt (currentWord) > count){
                        printf("Invalid input. Input bukanlah integer atau integer tersebut tidaklah valid.\n");
                        printf("Command: ");
                        getInput(command);
                        STARTWORD(command, &idx);
                    }
                    if (WordToInt(currentWord) == 0){
                        subprogram = false;
                        validAction = false; // Karena tidak melakukan apa-apa
                    } else {
                        // Inputnya telah sesuai dengan penomoran 
                        // Mencari idx makanan pada list makanan sesuai penomoran input user
                        idxFood = searchIndexOlahMakanan(foodList, "MIX", WordToInt(currentWord));
                        printMakanan(ELMTLIST(foodList, idxFood)); printf("\n");
                    }
                }
            }
        }

        else if (isWordStringEqual(currentWord, "CHOP")){
            printf("====================================================\n");
            printf("===============         CHOP         ===============\n");
            printf("====================================================\n");

            // Program akan di loop pada sesi Chop
            if (!isCan(map, Absis(Lokasi(sim)), Ordinat(Lokasi(sim)), 'C')){
                printf("Simulator tidak bersebelahan dengan tempat melakukan CHOP.\n");
                printf("Pastikan Simulator berada di sebelah petak 'C'\n");
                validAction = false;
            } else {
                subprogram = true;
                while (subprogram){
                
                    printf("List Bahan Makanan yang Bisa Dibuat: \n");
                    count = 0;
                    for (i=0; i < foodListLength; i++){
                        if (isWordStringEqual(actMkn(ELMTLIST(foodList,i)), "CHOP")){
                            count++;
                            printf("%d. ", count);
                            printWord(nameMkn(ELMTLIST(foodList, i)));
                            printf("\n");
                        }
                    }

                    // Handle jika konfigurasinya diganti
                    if (count == 0){
                        printf("Tidak ada bahan makanan yang bisa dibuat.\n");
                    };

                    printf("Ketik 0 untuk kembali ke Main Menu.\n");
                
                    // Meminta input dari pengguna
                    printf("Command: ");
                    getInput(command);
                    STARTWORD(command, &idx);
                    
                    // Handle untuk input tidak integer atau integer yang tidak valid
                    while (!isWordAllIntegers(currentWord) || WordToInt(currentWord) < 0 || WordToInt (currentWord) > count){
                        printf("Invalid input. Input bukanlah integer atau integer tersebut tidaklah valid.\n");
                        printf("Command: ");
                        getInput(command);
                        STARTWORD(command, &idx);
                    }
                    if (WordToInt(currentWord) == 0){
                        subprogram = false;
                        validAction = false; // Karena tidak melakukan apa-apa
                    } else {
                        // Inputnya telah sesuai dengan penomoran 
                        // Mencari idx makanan pada list makanan sesuai penomoran input user
                        idxFood = searchIndexOlahMakanan(foodList, "CHOP", WordToInt(currentWord));
                        printMakanan(ELMTLIST(foodList, idxFood)); printf("\n");
                    }
                }
            }
        }

        
        else if (isWordStringEqual(currentWord, "FRY")){
            printf("====================================================\n");
            printf("===============         FRY          ===============\n");
            printf("====================================================\n");
            
            // Program akan di loop pada sesi Fry
            if (!isCan(map, Absis(Lokasi(sim)), Ordinat(Lokasi(sim)), 'F')){
                printf("Simulator tidak bersebelahan dengan tempat melakukan FRY.\n");
                printf("Pastikan Simulator berada di sebelah petak 'F'\n");
                validAction = false;
            } else {
                subprogram = true;
                while (subprogram){
                
                    printf("List Bahan Makanan yang Bisa Dibuat: \n");
                    count = 0;
                    for (i=0; i < foodListLength; i++){
                        if (isWordStringEqual(actMkn(ELMTLIST(foodList,i)), "FRY")){
                            count++;
                            printf("%d. ", count);
                            printWord(nameMkn(ELMTLIST(foodList, i)));
                            printf("\n");
                        }
                    }

                    // Handle jika konfigurasinya diganti
                    if (count == 0){
                        printf("Tidak ada bahan makanan yang bisa dibuat.\n");
                    };

                    printf("Ketik 0 untuk kembali ke Main Menu.\n");
                
                    // Meminta input dari pengguna
                    printf("Command: ");
                    getInput(command);
                    STARTWORD(command, &idx);
                    
                    // Handle untuk input tidak integer atau integer yang tidak valid
                    while (!isWordAllIntegers(currentWord) || WordToInt(currentWord) < 0 || WordToInt (currentWord) > count){
                        printf("Invalid input. Input bukanlah integer atau integer tersebut tidaklah valid.\n");
                        printf("Command: ");
                        getInput(command);
                        STARTWORD(command, &idx);
                    }
                    if (WordToInt(currentWord) == 0){
                        subprogram = false;
                        validAction = false; // Karena tidak melakukan apa-apa
                    } else {
                        // Inputnya telah sesuai dengan penomoran 
                        // Mencari idx makanan pada list makanan sesuai penomoran input user
                        idxFood = searchIndexOlahMakanan(foodList, "FRY", WordToInt(currentWord));
                        printMakanan(ELMTLIST(foodList, idxFood)); printf("\n");
                    }
                }
            }
        }

        else if (isWordStringEqual(currentWord, "BOIL")){
            printf("====================================================\n");
            printf("===============         BOIL         ===============\n");
            printf("====================================================\n");

            // Program akan di loop pada sesi Chop
            if (!isCan(map, Absis(Lokasi(sim)), Ordinat(Lokasi(sim)), 'B')){
                printf("Simulator tidak bersebelahan dengan tempat melakukan BOIL.\n");
                printf("Pastikan Simulator berada di sebelah petak 'B'\n");
                validAction = false;
            } else {
                subprogram = true;
                while (subprogram){
                
                    printf("List Bahan Makanan yang Bisa Dibuat: \n");
                    count = 0;
                    for (i=0; i < foodListLength; i++){
                        if (isWordStringEqual(actMkn(ELMTLIST(foodList,i)), "BOIL")){
                            count++;
                            printf("%d. ", count);
                            printWord(nameMkn(ELMTLIST(foodList, i)));
                            printf("\n");
                        }
                    }

                    // Handle jika konfigurasinya diganti
                    if (count == 0){
                        printf("Tidak ada bahan makanan yang bisa dibuat.\n");
                    };

                    printf("Ketik 0 untuk kembali ke Main Menu.\n");
                
                    // Meminta input dari pengguna
                    printf("Command: ");
                    getInput(command);
                    STARTWORD(command, &idx);
                    
                    // Handle untuk input tidak integer atau integer yang tidak valid
                    while (!isWordAllIntegers(currentWord) || WordToInt(currentWord) < 0 || WordToInt (currentWord) > count){
                        printf("Invalid input. Input bukanlah integer atau integer tersebut tidaklah valid.\n");
                        printf("Command: ");
                        getInput(command);
                        STARTWORD(command, &idx);
                    }
                    if (WordToInt(currentWord) == 0){
                        subprogram = false;
                        validAction = false; // Karena tidak melakukan apa-apa
                    } else {
                        // Inputnya telah sesuai dengan penomoran 
                        // Mencari idx makanan pada list makanan sesuai penomoran input user
                        idxFood = searchIndexOlahMakanan(foodList, "BOIL", WordToInt(currentWord));
                        printMakanan(ELMTLIST(foodList, idxFood)); printf("\n");
                    }
                }
            }
        }

        
        else if (isWordStringEqual(currentWord, "CATALOG")){
            printf("====================================================\n");
            printf("===============       CATALOG        ===============\n");
            printf("====================================================\n");
            validAction = false; // Action ini tidak menghabiskan waktu
			//Note : Aku bikin fungsi baru printCatalog di makanan.c
			printf("List Makanan");
			printf("\n");
			printf("(nama - durasi kedaluwarsa - aksi yang diperlukan - delivery time)");
			printf("\n");
			for (i = 0; i < foodListLength; i++){
            	printf("%d. ",i+1);
                printCatalog(ELMTLIST(foodList, i));
                printf("\n");
            }

            // Boleh panggil aja procedure printMakanan, udah dibikin di ADT Makanan

        }

        else if (isWordStringEqual(currentWord, "COOKBOOK")){
            printf("====================================================\n");
            printf("===============       COOKBOOK       ===============\n");
            printf("====================================================\n");
            validAction = false; // Action ini tidak menghabiskan waktu
			printf("List Resep");
			printf("\n");
			printf("(aksi yang diperlukan - bahan...)\n");
            printResep(bukuResep, foodList);
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

            boolean allInteger = true, xint = false, yint = false;
            int waitHour, waitMinute, totalWaitMinute;

            // JANGAN LUPA BIKIN HANDLE KALAU INPUTNYA HANYA 1 INTEGER, BUKAN 2 INTEGER

            // Cek terlebih dahulu apakah input valid (x dan y adalah integer)
            ADVWORD(command, &idx);
            if (isWordAllIntegers(currentWord)){
                 waitHour = WordToInt(currentWord);
                 xint = true;
            } else {
                allInteger = false;
            }

            ADVWORD(command, &idx);
            if (isWordAllIntegers(currentWord)){
                waitMinute = WordToInt(currentWord);
                yint = true;
            } else {
                allInteger = false;
            }
            
            if (allInteger){
                printf("Menunggu ");
                if (waitHour != 0) {
                    printf("%d jam ", waitHour);
                }
                if (waitMinute != 0) {
                    printf("%d menit", waitMinute);
                }
                totalWaitMinute = (waitHour * 60) + waitMinute;
                currentTime = NextNMinute(currentTime, totalWaitMinute);
                decrementHMExp(&(Inventory(sim)), waitHour, waitMinute);
                decrementHMDel(&deliveryList, waitHour, waitMinute);
                // Bikin notifikasi
                RemoveDated(&sim);
                DeliveryReady(&sim, &deliveryList);
            } else if (!yint) {
                printf("Masukan tidak valid. Y bukan sebuah integer.\n");
            } else if (!xint) {
                printf("Masukan tidak valid. X bukan sebuah integer.\n");
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
            printf("BOIL            - Proses perebusan Makanan\n");
            printf("CATALOG         - Melihat data list makanan yang valid\n");
            printf("COOKBOOK        - Melihat data list resep yang valid\n");
            printf("INVENTORY       - Membuka inventory yang dimiliki oleh simulator\n");
            printf("DELIVERY        - Membuka tampilan list makanan yang sedang dikirim\n");
            printf("WAIT (x) (y)    - Mempercepat time selama x jam dan y menit\n");
            printf("UNDO            - Mengembalikan kondisi sebelum terlaksananya action terakhir\n");
            printf("REDO            - Melakukan kembali action yang telah di-undo\n");
            printf("FRIDGE SHOW     - Menampilkan isi kulkas\n");
            printf("FRIDGE TAKE     - Mengambil isi kulkas\n");
            validAction = false; // Action ini tidak menghabiskan waktu
        }
        else if (isWordStringEqual(currentWord, "FRIDGE")){
            printf("====================================================\n");
            printf("===============        FRIDGE        ===============\n");
            printf("====================================================\n");

            while (!endWord){ 
                ADVWORD(command, &idx);
            }

            if (!isCan(map, Absis(Lokasi(sim)), Ordinat(Lokasi(sim)), 'K')){
                printf("Simulator tidak bersebelahan dengan tempat FRIDGE.\n");
                printf("Pastikan Simulator berada di sebelah petak 'K'\n");
                validAction = false;
            }
            else {
                if (isWordStringEqual(currentWord, "SHOW")){
                    validAction = false; // Melihat isi kulkas tidak membuang waktu
                    printf("SHOW\n");
                }
                else if (isWordStringEqual(currentWord, "TAKE")){
                    printf("TAKE\n");
                } 
                else if (isWordStringEqual(currentWord, "PUT")){
                    printf("PUT\n");
                } else {
                    printf("Input selain 'SHOW', 'TAKE', dan 'PUT' tidak diterima.\n");
                    validAction = false; // Invalid Input
                }
            }


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
