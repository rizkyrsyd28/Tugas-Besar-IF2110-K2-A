#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// #include "parser.c"
// #include "../ADT/Simulator/simulator.c"
// #include "../ADT/piroqueue/piroqueue.c"
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
    MakeEmptyQueue(&Inventory(sim), 100);
    PrioQueueTime deliveryList;
    MakeEmptyQueue(&deliveryList, 100);
    printf("-> Konfigurasi Inventory - DONE\n");
    PrioQueueTime processList;
    MakeEmptyQueue(&processList, 100);

    // Dummy (untuk mencegah error)
    fgets(command, MAX_COMMAND, stdin);

    // Konfigurasi variabel global
    int i;
    int count;
    boolean subprogram = false;
    int idxFood;
    Makanan dumpMkn;


    // =========== PENJALANAN PROGRAM UTAMA ===========
    while(program){
        printf("====================================================\n");
        printf("==============       MAIN MENU       ===============\n");
        printf("====================================================\n");

        // Display simulator dan map
        DisplaySimulator(sim);
        printf("Waktu: ");
        TulisTIME(currentTime); 
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
                        // Inputnya telah sesuai dengan penomoran 
                        // Mencari idx makanan pada list makanan sesuai penomoran input user
                        idxFood = searchIndexOlahMakanan(foodList, "BUY", WordToInt(currentWord));
                        EnqueueDelivery(&deliveryList, ELMTLIST(foodList, idxFood));

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
            if (!isCan(map, Absis(Lokasi(sim)), Ordinat(Lokasi(sim)), 'M')){
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
            if (!isCan(map, Absis(Lokasi(sim)), Ordinat(Lokasi(sim)), 'C')){
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
                        idxFood = searchIndexOlahMakanan(foodList, "CHOP", WordToInt(currentWord));
                        if (canMake(bukuResep, ELMTLIST(foodList, idxFood), Inventory(sim))){
                            int idPar, idChld;
                            for (int i = 0; i < NResep(bukuResep); i++){
                                if (Parent(Resep(bukuResep, i)) == idMkn(ELMTLIST(foodList, idxFood))){
                                    idPar = Parent(Resep(bukuResep, i));
                                    idChld = Parent(Child(Resep(bukuResep, i), 0));
                                }
                            }
                            ChopOlahInventory(&Inventory(sim), getMakanan(idChld, foodList), getMakanan(idPar, foodList));
                            printMakanan(ELMTLIST(foodList, idxFood)); printf("\n");
                        }
                        else {
                            printf("Kamu tidak punya bahannya");
                        }
                        // Inputnya telah sesuai dengan penomoran 
                        // Mencari idx makanan pada list makanan sesuai penomoran input user
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
            if (!isCan(map, Absis(Lokasi(sim)), Ordinat(Lokasi(sim)), 'B')){
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

            if (IsEmptyQueue(Inventory(sim))){
                printf("Tidak ada makanan pada inventory.\n");
            } else {
                DisplayInventory(sim);
            }
        }

        else if (isWordStringEqual(currentWord, "DELIVERY")){
            printf("====================================================\n");
            printf("===============       DELIVERY       ===============\n");
            printf("====================================================\n");
            validAction = false; // Action ini tidak menghabiskan waktu

            if (IsEmptyQueue(deliveryList)){
                printf("Tidak ada makanan pada list delivery.\n");
            } else {
                printf("List Makanan di Delivery List:\n");
                printf("No - Nama - Waktu Sisa Delivery\n");
                PrintPrioQueueTimeDelivery(deliveryList);
            }
        }

        else if (isWordStringEqual(currentWord, "PROCESS")){
            printf("====================================================\n");
            printf("===============       PROCESS       ===============\n");
            printf("====================================================\n");
            validAction = false; // Action ini tidak menghabiskan waktu

            if (IsEmptyQueue(processList)){
                printf("Tidak ada makanan pada list process.\n");
            } else {
                printf("List Makanan di Process List:\n");
                printf("No - Nama - Waktu Sisa Process\n");
                PrintPrioQueueTimeProcess(processList);
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
                        printf("Menunggu ");
                        if (waitHour != 0) {
                            printf("%d jam ", waitHour);
                        }
                        if (waitMinute != 0){
                            printf("%d menit", waitMinute);
                        }
                        printf("\n");

                        totalWaitMinute = (waitHour * 60) + waitMinute;
                        currentTime = NextNMinute(currentTime, totalWaitMinute);

                        decrementNExp(&(Inventory(sim)), totalWaitMinute);
                        decrementNDel(&deliveryList, totalWaitMinute);
                        
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

        }

        else if (isWordStringEqual(currentWord, "REDO")){
            printf("====================================================\n");
            printf("===============         REDO         ===============\n");
            printf("====================================================\n");

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
            getInvalidRespond();
            validAction = false;
        }

        // ================= AFTER ACTION ALGORITHM =================
        if (validAction){
            // Waktu hanya ditambahkan bila action yang dilakukan valid
            currentTime = NextMinute(currentTime);
            
            // Mengurangi waktu di delivery list dan inventory
            decrementNDel(&deliveryList, 1);
            decrementNExp(&Inventory(sim), 1);
        }

        // Tetap bisa dilakukan meski ValidAction = false (contohnya menggunakan WAIT)
        // Mengeluarkan dari Delivery List, memasukan ke inventory (bila sampai)
        if (!IsEmptyQueue(deliveryList)){
            while ((!TGT(dlvMkn(InfoHead(deliveryList)), boundariesTime)) && (NBElmt(deliveryList) > 1)){
                Dequeue(&deliveryList, &dumpMkn);
                // Mengurangi waktu kadaluarsa sesuai dengan sisa pada delivery
                int remainder = TIMEtoint(dlvMkn(dumpMkn));
                TIME newExpiry = inttoTIME(TIMEtoint(expMkn(dumpMkn)) + remainder);
                expMkn(dumpMkn) = newExpiry;
                EnqueueInventory(&Inventory(sim), dumpMkn);
            }
            if (!TGT(dlvMkn(InfoHead(deliveryList)), boundariesTime)){
                Dequeue(&deliveryList, &dumpMkn);
                // Mengurangi waktu kadaluarsa sesuai dengan sisa pada delivery
                int remainder = TIMEtoint(dlvMkn(dumpMkn));
                TIME newExpiry = inttoTIME(TIMEtoint(expMkn(dumpMkn)) + remainder);
                expMkn(dumpMkn) = newExpiry;
                EnqueueInventory(&Inventory(sim), dumpMkn);
            }
        }

        // Mengeluarkan dari Process List, memasukan ke inventory (bila selesai process)
        if (!IsEmptyQueue(processList)){
            while ((!TGT(dlvMkn(InfoHead(processList)), boundariesTime)) && (NBElmt(processList) > 1)){
                Dequeue(&processList, &dumpMkn);
                // Mengurangi waktu kadaluarsa sesuai dengan sisa pada process time
                int remainder = TIMEtoint(dlvMkn(dumpMkn));
                TIME newExpiry = inttoTIME(TIMEtoint(expMkn(dumpMkn)) + remainder);
                expMkn(dumpMkn) = newExpiry;
                EnqueueInventory(&Inventory(sim), dumpMkn);
            }
            if (!TGT(dlvMkn(InfoHead(processList)), boundariesTime)){
                Dequeue(&processList, &dumpMkn);
                // Mengurangi waktu kadaluarsa sesuai dengan sisa pada process time
                int remainder = TIMEtoint(dlvMkn(dumpMkn));
                TIME newExpiry = inttoTIME(TIMEtoint(expMkn(dumpMkn)) + remainder);
                expMkn(dumpMkn) = newExpiry;
                EnqueueInventory(&Inventory(sim), dumpMkn);
            }
        }

        // Mengeluarkan dari inventory ( bila kadaluarsa)
        if (!IsEmptyQueue(Inventory(sim))){
            // Menghapus sampai bersisa 1
            while ((!TGT(expMkn(InfoHead(Inventory(sim))), boundariesTime)) && (NBElmt(Inventory(sim)) > 1)){
                Dequeue(&Inventory(sim), &dumpMkn);
            }
            // Menghapus makanan terakhir bila bersisa 1
            if (!TGT(expMkn(InfoHead(Inventory(sim))), boundariesTime)){
                Dequeue(&Inventory(sim), &dumpMkn);
            }
        }
    }
    return 0;
}