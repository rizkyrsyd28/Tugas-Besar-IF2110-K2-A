#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "submain.c"


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
    TIME boundariesTime; Day(boundariesTime) = 0; Hour(boundariesTime) = 0; Minute(boundariesTime) = 0;
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

    // Konfigurasi Inventory
    //MakeEmptyQueue(&Inventory(sim), 100);
    /*PrioQueueTime deliveryList;
    MakeEmptyQueue(&deliveryList, 100);
    printf("-> Konfigurasi Inventory - DONE\n");
    PrioQueueTime processList;
    MakeEmptyQueue(&processList, 100);*/

    // Konfigurasi Stack
    Stack SUndo, SRedo;
    CreateEmpty(&SRedo);
    CreateEmpty(&SUndo);
    printf("-> Konfigurasi Stack - DONE\n");

    //Konfigurasi state
    state currentState;
    initState(&currentState,sim,currentTime);
    printf("-> Konfigurasi State - DONE\n");

    // Dummy (untuk mencegah error)
    fgets(command, MAX_COMMAND, stdin);

    // Konfigurasi variabel global
    int i;
    int count;
    int totalcommand = 0;
    int totalundo = 0;
    boolean subprogram = false;
    int idxFood;
    Makanan dumpMkn;


    // =========== PENJALANAN PROGRAM UTAMA ===========
    while(program){
        printf("====================================================\n");
        printf("==============       MAIN MENU       ===============\n");
        printf("====================================================\n");

        // Display simulator dan map
        DisplaySimulator(currentState.sub1);
        printf("Waktu: ");
        TulisTIME(currentState.sub2); 
        printf("Notifikasi : \n"); // Ini nanti ditambahin seiring berjalan waktu
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
            ADVWORD(command, &idx);
            if (endWord){
                printf("====================================================\n");
                printf("===============        EXIT          ===============\n");
                printf("====================================================\n");
                printf("Yahh kok udahan... :(\n");
                program = false;
            } else {
                getInvalidRespond();
                validAction = false;
            }
        }
        else if (isWordStringEqual(currentWord, "MOVE")){
            printf("====================================================\n");
            printf("===============         MOVE         ===============\n");
            printf("====================================================\n");

            while (!endWord){ 
                ADVWORD(command, &idx);
            }

            POINT src = Lokasi(currentState.sub1);
            ADVWORD(command, &idx);

            if (isWordStringEqual(currentWord, "NORTH")){
                //Push ke Stack
                //DisplayInventory(currentState.sub1);
                CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q,currentState.sub1.D,currentState.sub1.PL);
                Push(&SUndo, currentState);
                CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q,currentState.sub1.D,currentState.sub1.PL);
                totalcommand ++;
                swapElmt(&map, &Lokasi(currentState.sub1), NextY(src));
            }
            else if (isWordStringEqual(currentWord, "EAST")){
                //Push ke Stack
                //DisplayInventory(currentState.sub1);
                CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q,currentState.sub1.D,currentState.sub1.PL);
                Push(&SUndo, currentState);
                CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q,currentState.sub1.D,currentState.sub1.PL);
                totalcommand ++;
                swapElmt(&map, &Lokasi(currentState.sub1), NextX(src));
            } 
            else if (isWordStringEqual(currentWord, "SOUTH")){
                //Push ke Stack
                //DisplayInventory(currentState.sub1);
                CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q,currentState.sub1.D,currentState.sub1.PL);
                Push(&SUndo, currentState);
                CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q,currentState.sub1.D,currentState.sub1.PL);
                totalcommand ++;
                swapElmt(&map, &Lokasi(currentState.sub1), BackY(src));
            }
            else if (isWordStringEqual(currentWord, "WEST")){
                //Push ke Stack
                //DisplayInventory(currentState.sub1);
                CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q,currentState.sub1.D,currentState.sub1.PL);
                Push(&SUndo, currentState);
                CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q,currentState.sub1.D,currentState.sub1.PL);
                totalcommand ++;
                swapElmt(&map, &Lokasi(currentState.sub1), BackX(src));
            } else {
                printf("Input selain 'NORTH', 'SOUTH', 'WEST', dan 'EAST' tidak diterima.\n");
            }

            if (NEQ(src, Lokasi(currentState.sub1))){
                validAction = true;
            }
            else{
                validAction = false;
                //Gajadi push ke Stack
                Pop (&SUndo, &currentState);
                totalcommand--;
            }

        }
        else if (isWordStringEqual(currentWord, "BUY")){
            printf("====================================================\n");
            printf("===============         BUY          ===============\n");
            printf("====================================================\n");

            // Program akan di loop pada sesi Buy
            if (!isCan(map, Absis(Lokasi(currentState.sub1)), Ordinat(Lokasi(currentState.sub1)), 'T')){
                printf("Simulator tidak bersebelahan dengan tempat melakukan BUY.\n");
                printf("Pastikan Simulator berada di sebelah petak 'T'\n");
                validAction = false;
            } else {
                subprogram = true;
                while (subprogram){
                
                    count = countAndPrintAvailableFood(foodList, foodListLength, "BUY");
                
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
                        //Push ke Stack
                        //DisplayInventory(currentState.sub1);
                        CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q,currentState.sub1.D,currentState.sub1.PL);
                        Push(&SUndo, currentState);
                        CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q,currentState.sub1.D,currentState.sub1.PL);
                        totalcommand ++;
                        // Inputnya telah sesuai dengan penomoran 
                        // Mencari idx makanan pada list makanan sesuai penomoran input user
                        idxFood = searchIndexOlahMakanan(foodList, "BUY", WordToInt(currentWord));
                        EnqueueDelivery(&currentState.sub1.D, ELMTLIST(foodList, idxFood));

                        // Mengeluarkan pesan bahwa sudah dipesan.
                        printWord(nameMkn(ELMTLIST(foodList, idxFood)));
                        printf(" berhasil dipesan. Makanan akan diantar dalam ");
                        TulisTIMEString(dlvMkn(ELMTLIST(foodList, idxFood)));
                        printf("\n");
                        subprogram = false;
                    }
                }
            }

        }

        else if (isWordStringEqual(currentWord, "MIX")){
            printf("====================================================\n");
            printf("===============         MIX          ===============\n");
            printf("====================================================\n");

            // Program akan di loop pada sesi Mix
            if (!isCan(map, Absis(Lokasi(currentState.sub1)), Ordinat(Lokasi(currentState.sub1)), 'M')){
                printf("Simulator tidak bersebelahan dengan tempat melakukan MIX.\n");
                printf("Pastikan Simulator berada di sebelah petak 'M'\n");
                validAction = false;
            } else {
                subprogram = true;
                while (subprogram){
                
                    count = countAndPrintAvailableFood(foodList, foodListLength, "MIX");
                
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
                        //Push ke Stack
                        CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q,currentState.sub1.D,currentState.sub1.PL);
                        Push(&SUndo, currentState);
                        totalcommand ++;
                        CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q,currentState.sub1.D,currentState.sub1.PL);
                        // Inputnya telah sesuai dengan penomoran 
                        // Mencari idx makanan pada list makanan sesuai penomoran input user
                        idxFood = searchIndexOlahMakanan(foodList, "MIX", WordToInt(currentWord));
                        printMakanan(ELMTLIST(foodList, idxFood)); printf("\n");

                        // BIKIN ALGORITMA HANDLE BILA BAHAN DI INVENTORY GA CUKUP BUAT BIKIN FOOD TERTENTU

                        // // INI NANTI DI UN-COMMENT KALAU HANDLENYA UDAH SELESAI
                        // // INI ALGORITMA BUAT MASUKIN MAKANAN KE PROCESSLIST
                        // // Mencari idx makanan pada list makanan sesuai penomoran input user
                        // idxFood = searchIndexOlahMakanan(foodList, "MIX", WordToInt(currentWord));
                        // EnqueueDelivery(&processList, ELMTLIST(foodList, idxFood));

                        // // Mengeluarkan pesan bahwa sudah diproses.
                        // printWord(nameMkn(ELMTLIST(foodList, idxFood)));
                        // printf(" berhasil diproses. Makanan akan diproses dalam ");
                        // TulisTIMEString(dlvMkn(ELMTLIST(foodList, idxFood)));
                        // printf("\n");
                        // subprogram = false;
                    }
                }
            }
        }

        else if (isWordStringEqual(currentWord, "CHOP")){
            printf("====================================================\n");
            printf("===============         CHOP         ===============\n");
            printf("====================================================\n");

            // Program akan di loop pada sesi Chop
            if (!isCan(map, Absis(Lokasi(currentState.sub1)), Ordinat(Lokasi(currentState.sub1)), 'C')){
                printf("Simulator tidak bersebelahan dengan tempat melakukan CHOP.\n");
                printf("Pastikan Simulator berada di sebelah petak 'C'\n");
                validAction = false;
            } else {
                subprogram = true;
                while (subprogram){
                
                    count = countAndPrintAvailableFood(foodList, foodListLength, "CHOP");
                
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
                        //Push ke Stack
                        CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q,currentState.sub1.D,currentState.sub1.PL);
                        Push(&SUndo, currentState);
                        totalcommand ++;
                        CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q,currentState.sub1.D,currentState.sub1.PL);
                        // Inputnya telah sesuai dengan penomoran 
                        // Mencari idx makanan pada list makanan sesuai penomoran input user
                        idxFood = searchIndexOlahMakanan(foodList, "CHOP", WordToInt(currentWord));
                        printMakanan(ELMTLIST(foodList, idxFood)); printf("\n");

                        // BIKIN ALGORITMA HANDLE BILA BAHAN DI INVENTORY GA CUKUP BUAT BIKIN FOOD TERTENTU

                        // // INI NANTI DI UN-COMMENT KALAU HANDLENYA UDAH SELESAI
                        // // INI ALGORITMA BUAT MASUKIN MAKANAN KE PROCESSLIST
                        // // Mencari idx makanan pada list makanan sesuai penomoran input user
                        // idxFood = searchIndexOlahMakanan(foodList, "CHOP", WordToInt(currentWord));
                        // EnqueueDelivery(&processList, ELMTLIST(foodList, idxFood));

                        // // Mengeluarkan pesan bahwa sudah diproses.
                        // printWord(nameMkn(ELMTLIST(foodList, idxFood)));
                        // printf(" berhasil diproses. Makanan akan diproses dalam ");
                        // TulisTIMEString(dlvMkn(ELMTLIST(foodList, idxFood)));
                        // printf("\n");
                        // subprogram = false;
                    }
                }
            }
        }

        
        else if (isWordStringEqual(currentWord, "FRY")){
            printf("====================================================\n");
            printf("===============         FRY          ===============\n");
            printf("====================================================\n");
            
            // Program akan di loop pada sesi Fry
            if (!isCan(map, Absis(Lokasi(currentState.sub1)), Ordinat(Lokasi(currentState.sub1)), 'F')){
                printf("Simulator tidak bersebelahan dengan tempat melakukan FRY.\n");
                printf("Pastikan Simulator berada di sebelah petak 'F'\n");
                validAction = false;
            } else {
                subprogram = true;
                while (subprogram){
                
                    count = countAndPrintAvailableFood(foodList, foodListLength, "FRY");
                
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
                        //Push ke Stack
                        CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q,currentState.sub1.D,currentState.sub1.PL);
                        Push(&SUndo, currentState);
                        totalcommand ++;
                        CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q,currentState.sub1.D,currentState.sub1.PL);
                        // Inputnya telah sesuai dengan penomoran 
                        // Mencari idx makanan pada list makanan sesuai penomoran input user
                        idxFood = searchIndexOlahMakanan(foodList, "FRY", WordToInt(currentWord));
                        printMakanan(ELMTLIST(foodList, idxFood)); printf("\n");

                        // BIKIN ALGORITMA HANDLE BILA BAHAN DI INVENTORY GA CUKUP BUAT BIKIN FOOD TERTENTU

                        // // INI NANTI DI UN-COMMENT KALAU HANDLENYA UDAH SELESAI
                        // // INI ALGORITMA BUAT MASUKIN MAKANAN KE PROCESSLIST
                        // // Mencari idx makanan pada list makanan sesuai penomoran input user
                        // idxFood = searchIndexOlahMakanan(foodList, "FRY", WordToInt(currentWord));
                        // EnqueueDelivery(&processList, ELMTLIST(foodList, idxFood));

                        // // Mengeluarkan pesan bahwa sudah diproses.
                        // printWord(nameMkn(ELMTLIST(foodList, idxFood)));
                        // printf(" berhasil diproses. Makanan akan diproses dalam ");
                        // TulisTIMEString(dlvMkn(ELMTLIST(foodList, idxFood)));
                        // printf("\n");
                        // subprogram = false;
                    }
                }
            }
        }

        else if (isWordStringEqual(currentWord, "BOIL")){
            printf("====================================================\n");
            printf("===============         BOIL         ===============\n");
            printf("====================================================\n");

            // Program akan di loop pada sesi Chop
            if (!isCan(map, Absis(Lokasi(currentState.sub1)), Ordinat(Lokasi(currentState.sub1)), 'B')){
                printf("Simulator tidak bersebelahan dengan tempat melakukan BOIL.\n");
                printf("Pastikan Simulator berada di sebelah petak 'B'\n");
                validAction = false;
            } else {
                subprogram = true;
                while (subprogram){
                
                    count = countAndPrintAvailableFood(foodList, foodListLength, "BOIL");
                
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
                        //Push ke Stack
                        CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q,currentState.sub1.D,currentState.sub1.PL);
                        Push(&SUndo, currentState);
                        totalcommand ++;
                        CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q,currentState.sub1.D,currentState.sub1.PL);
                        // Inputnya telah sesuai dengan penomoran 
                        // Mencari idx makanan pada list makanan sesuai penomoran input user
                        idxFood = searchIndexOlahMakanan(foodList, "BOIL", WordToInt(currentWord));
                        printMakanan(ELMTLIST(foodList, idxFood)); printf("\n");

                        // BIKIN ALGORITMA HANDLE BILA BAHAN DI INVENTORY GA CUKUP BUAT BIKIN FOOD TERTENTU

                        // // INI NANTI DI UN-COMMENT KALAU HANDLENYA UDAH SELESAI
                        // // INI ALGORITMA BUAT MASUKIN MAKANAN KE PROCESSLIST
                        // // Mencari idx makanan pada list makanan sesuai penomoran input user
                        // idxFood = searchIndexOlahMakanan(foodList, "BOIL", WordToInt(currentWord));
                        // EnqueueDelivery(&processList, ELMTLIST(foodList, idxFood));

                        // // Mengeluarkan pesan bahwa sudah diproses.
                        // printWord(nameMkn(ELMTLIST(foodList, idxFood)));
                        // printf(" berhasil diproses. Makanan akan diproses dalam ");
                        // TulisTIMEString(dlvMkn(ELMTLIST(foodList, idxFood)));
                        // printf("\n");
                        // subprogram = false;
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
            printListCatalog(foodList, foodListLength);
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

            if (IsEmptyQueue(Inventory(currentState.sub1))){
                printf("Tidak ada makanan pada inventory.\n");
            } else {
                DisplayInventory(currentState.sub1);
            }
        }

        else if (isWordStringEqual(currentWord, "DELIVERY")){
            printf("====================================================\n");
            printf("===============       DELIVERY       ===============\n");
            printf("====================================================\n");
            validAction = false; // Action ini tidak menghabiskan waktu

            if (IsEmptyQueue(currentState.sub1.D)){
                printf("Tidak ada makanan pada list delivery.\n");
            } else {
                printf("List Makanan di Delivery List:\n");
                printf("No - Nama - Waktu Sisa Delivery\n");
                PrintPrioQueueTimeDelivery(currentState.sub1.D);
            }
        }

        else if (isWordStringEqual(currentWord, "PROCESS")){
            printf("====================================================\n");
            printf("===============       PROCESS       ===============\n");
            printf("====================================================\n");
            validAction = false; // Action ini tidak menghabiskan waktu

            if (IsEmptyQueue(currentState.sub1.PL)){
                printf("Tidak ada makanan pada list process.\n");
            } else {
                printf("List Makanan di Process List:\n");
                printf("No - Nama - Waktu Sisa Process\n");
                PrintPrioQueueTimeProcess(currentState.sub1.PL);
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

            // Cek terlebih dahulu apakah input valid (x dan y adalah integer)
            ADVWORD(command, &idx);
            if (isWordAllIntegers(currentWord)){
                 waitHour = WordToInt(currentWord);
                 xint = true;
            } else {
                allInteger = false;
            }
            
            ADVWORD(command, &idx);
            if (endWord){
                printf("Command wait membutuhkan 2 integer, X dan Y\n");
            }
            else {
                if (isWordAllIntegers(currentWord)){
                    waitMinute = WordToInt(currentWord);
                    yint = true;
                } else {
                    allInteger = false;
                }
                
                if (allInteger){
                    if (waitHour == 0 && waitMinute == 0){
                        printf("Untuk apa dilakukan? Untuk apa? :(\n");
                    } else {
                        // Menunggu 0 0 boleh saja, tapi tidak melakukan perubahan apa apa
                        //Push ke Stack
                        //DisplayInventory(currentState.sub1);
                        CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q,currentState.sub1.D,currentState.sub1.PL);
                        Push(&SUndo, currentState);
                        CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q,currentState.sub1.D,currentState.sub1.PL);
                        totalcommand ++;
                        printf("Menunggu ");
                        if (waitHour != 0) {
                            printf("%d jam ", waitHour);
                        }
                        if (waitMinute != 0){
                            printf("%d menit", waitMinute);
                        }
                        printf("\n");

                        totalWaitMinute = (waitHour * 60) + waitMinute;
                        currentState.sub2 = NextNMinute(currentState.sub2, totalWaitMinute);

                        decrementNExp(&(Inventory(currentState.sub1)), totalWaitMinute);
                        decrementNDel(&currentState.sub1.D, totalWaitMinute);
                        
                        printf("Waktu pada Delivery List dan Inventory telah disesuaikan.\n");
                    }
                    
                } else if (!yint) {
                    printf("Masukan tidak valid. Y bukan sebuah integer.\n");
                } else if (!xint) {
                    printf("Masukan tidak valid. X bukan sebuah integer.\n");
                } else {
                    printf("Masukan tidak valid. X dan Y hanya diperbolehkan memiliki tipe integer.\n");
                }
            }
        }

        else if (isWordStringEqual(currentWord, "UNDO")){
            printf("====================================================\n");
            printf("===============         UNDO         ===============\n");
            printf("====================================================\n");
            validAction = false;
            if(totalcommand>0){
                POINT srcdummy;
                CreatePoint(&srcdummy,-50,-50);
                POINT lokasisekarang = Lokasi(currentState.sub1);
                //CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q,currentState.sub1.D,currentState.sub1.PL);
                Undo(&SUndo,&SRedo,&currentState,totalcommand,srcdummy);
                if (totalcommand>0){
                    totalcommand --;
                    totalundo++;
                }
                POINT lokasiundo = Lokasi(currentState.sub1);
                //CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q,currentState.sub1.D,currentState.sub1.PL);
                Redo(&SUndo,&SRedo,&currentState,totalundo,srcdummy);
                if (totalundo>0){
                    totalcommand++;
                    totalundo--;
                }

                POINT src = Lokasi(currentState.sub1);
                if (lokasisekarang.X>lokasiundo .X){
                    swapElmt(&map, &Lokasi(currentState.sub1), BackX(src));
                }
                else if (lokasisekarang.X<lokasiundo .X){
                    swapElmt(&map, &Lokasi(currentState.sub1), NextX(src));
                }
                else if (lokasisekarang.Y>lokasiundo .Y){
                    swapElmt(&map, &Lokasi(currentState.sub1), NextY(src));
                }
                else if (lokasisekarang.Y<lokasiundo .Y){
                    swapElmt(&map, &Lokasi(currentState.sub1), BackY(src));
                }
                i = 0;
                //PrioQueueTime dummy1 = Inventory(currentState.sub1);
                CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q,currentState.sub1.D,currentState.sub1.PL);
                Undo(&SUndo,&SRedo,&currentState,totalcommand,src);
                if (totalcommand>0){
                    totalcommand --;
                    totalundo++;
                }
                //PrioQueueTime dummy2 = Inventory(currentState.sub1);
                //if (TEQ(dummy1.T->expired,dummy2.T->expired)){
                //    incrementNExp(&Inventory(currentState.sub1),1);
            // }
            }
        }

        else if (isWordStringEqual(currentWord, "REDO")){
            printf("====================================================\n");
            printf("===============         REDO         ===============\n");
            printf("====================================================\n");

            validAction = false;
            if (totalundo>0){
                POINT srcdummy;
                CreatePoint(&srcdummy,-50,-50);
                POINT lokasisekarang = Lokasi(currentState.sub1);
                Redo(&SUndo,&SRedo,&currentState,totalundo,srcdummy);
                if (totalundo>0){
                    totalcommand++;
                    totalundo--;
                }
                POINT lokasiredo = Lokasi(currentState.sub1);
                Undo(&SUndo,&SRedo,&currentState,totalcommand,srcdummy);
                if (totalcommand>0){
                    totalcommand --;
                    totalundo++;
                }
                POINT src = Lokasi(currentState.sub1);
                if (lokasisekarang.X>lokasiredo.X){
                    swapElmt(&map, &Lokasi(currentState.sub1), BackX(src));
                }
                else if (lokasisekarang.X<lokasiredo .X){
                    swapElmt(&map, &Lokasi(currentState.sub1), NextX(src));
                }
                else if (lokasisekarang.Y>lokasiredo .Y){
                    swapElmt(&map, &Lokasi(currentState.sub1), NextY(src));
                }
                else if (lokasisekarang.Y<lokasiredo .Y){
                    swapElmt(&map, &Lokasi(currentState.sub1), BackY(src));
                }
                CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q,currentState.sub1.D,currentState.sub1.PL);
                Redo(&SUndo,&SRedo,&currentState,totalundo,src);
                if (totalundo>0){
                    totalcommand++;
                    totalundo--;
                }
            }
        }

        else if (isWordStringEqual(currentWord, "HELP")){
            getHelp();
            validAction = false; // Action ini tidak menghabiskan waktu
        }
        else if (isWordStringEqual(currentWord, "FRIDGE")){
            printf("====================================================\n");
            printf("===============        FRIDGE        ===============\n");
            printf("====================================================\n");

            while (!endWord){ 
                ADVWORD(command, &idx);
            }

            if (!isCan(map, Absis(Lokasi(currentState.sub1)), Ordinat(Lokasi(currentState.sub1)), 'K')){
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
                    //Push ke Stack
                    Push(&SUndo, currentState);
                    totalcommand ++;
                    printf("TAKE\n");
                } 
                else if (isWordStringEqual(currentWord, "PUT")){
                    //Push ke Stack
                    Push(&SUndo, currentState);
                    totalcommand ++;
                    printf("PUT\n");
                } else {
                    printf("Input selain 'SHOW', 'TAKE', dan 'PUT' tidak diterima.\n");
                    validAction = false; // Invalid Input
                }
            }
        }

        else {
            getInvalidRespond();
            validAction = false;
        }

        // ================= AFTER ACTION ALGORITHM =================
        printf("---------------------- STACK UNDO-----------------------------\n");
        displayStack(SUndo);
        printf("\n");

        printf("---------------------- STACK REDO-----------------------------\n");
        displayStack(SRedo);
        printf("\n");

        if (validAction){
            // Waktu hanya ditambahkan bila action yang dilakukan valid
            currentState.sub2 = NextMinute(currentState.sub2);
            
            // Mengurangi waktu di delivery list dan inventory
            decrementNDel(&currentState.sub1.D, 1);
            decrementNExp(&Inventory(currentState.sub1), 1);
        }

        // Tetap bisa dilakukan meski ValidAction = false (contohnya menggunakan WAIT)
        // Mengeluarkan dari Delivery List, memasukan ke inventory (bila sampai)
        if (!IsEmptyQueue(currentState.sub1.D)){
            while ((!TGT(dlvMkn(InfoHead(currentState.sub1.D)), boundariesTime)) && (NBElmt(currentState.sub1.D) > 1)){
                Dequeue(&currentState.sub1.D, &dumpMkn);
                // Mengurangi waktu kadaluarsa sesuai dengan sisa pada delivery
                int remainder = TIMEtoint(dlvMkn(dumpMkn));
                TIME newExpiry = inttoTIME(TIMEtoint(expMkn(dumpMkn)) + remainder);
                expMkn(dumpMkn) = newExpiry;
                EnqueueInventory(&Inventory(currentState.sub1), dumpMkn);
            }
            if (!TGT(dlvMkn(InfoHead(currentState.sub1.D)), boundariesTime)){
                Dequeue(&currentState.sub1.D, &dumpMkn);
                // Mengurangi waktu kadaluarsa sesuai dengan sisa pada delivery
                int remainder = TIMEtoint(dlvMkn(dumpMkn));
                TIME newExpiry = inttoTIME(TIMEtoint(expMkn(dumpMkn)) + remainder);
                expMkn(dumpMkn) = newExpiry;
                EnqueueInventory(&Inventory(currentState.sub1), dumpMkn);
            }
        }

        // Mengeluarkan dari Process List, memasukan ke inventory (bila selesai process)
        if (!IsEmptyQueue(currentState.sub1.PL)){
            while ((!TGT(dlvMkn(InfoHead(currentState.sub1.PL)), boundariesTime)) && (NBElmt(currentState.sub1.PL) > 1)){
                Dequeue(&currentState.sub1.PL, &dumpMkn);
                // Mengurangi waktu kadaluarsa sesuai dengan sisa pada process time
                int remainder = TIMEtoint(dlvMkn(dumpMkn));
                TIME newExpiry = inttoTIME(TIMEtoint(expMkn(dumpMkn)) + remainder);
                expMkn(dumpMkn) = newExpiry;
                EnqueueInventory(&Inventory(currentState.sub1), dumpMkn);
            }
            if (!TGT(dlvMkn(InfoHead(currentState.sub1.PL)), boundariesTime)){
                Dequeue(&currentState.sub1.PL, &dumpMkn);
                // Mengurangi waktu kadaluarsa sesuai dengan sisa pada process time
                int remainder = TIMEtoint(dlvMkn(dumpMkn));
                TIME newExpiry = inttoTIME(TIMEtoint(expMkn(dumpMkn)) + remainder);
                expMkn(dumpMkn) = newExpiry;
                EnqueueInventory(&Inventory(currentState.sub1), dumpMkn);
            }
        }

        // Mengeluarkan dari inventory ( bila kadaluarsa)
        if (!IsEmptyQueue(Inventory(currentState.sub1))){
            // Menghapus sampai bersisa 1
            while ((!TGT(expMkn(InfoHead(Inventory(currentState.sub1))), boundariesTime)) && (NBElmt(Inventory(currentState.sub1)) > 1)){
                Dequeue(&Inventory(currentState.sub1), &dumpMkn);
            }
            // Menghapus makanan terakhir bila bersisa 1
            if (!TGT(expMkn(InfoHead(Inventory(currentState.sub1))), boundariesTime)){
                Dequeue(&Inventory(currentState.sub1), &dumpMkn);
            }
        }
    }
    return 0;
}