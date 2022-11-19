#include <stdio.h>
#include "parser.c"
#include "../ADT/Simulator/simulator.c"
#include "../ADT/Stack/stack.c"
#include "../ADT/Kulkas/kulkas.c"

#define MAX_COMMAND 30

void getInput(char* string){
/* Digunakan untuk meminta input dari user. Input dari user akan dimasukan kedalam string*/
    // Fungsi untuk meminta input oleh user
    fgets(string, MAX_COMMAND, stdin);
    upper(string);
    // Procedure giveMark dilakukan karena diujung string ada '\n' dan perlu diberikan '.' sebagai MARK.
    giveMark(string);
}

void getHelp(){
/* Menampilkan segala command valid yang dapat dilakukan selama program dijalankan */
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
    printf("PROCESS         - Membuka tampilan list makanan yang sedang diproses\n");
    printf("WAIT (x) (y)    - Mempercepat time selama x jam dan y menit\n");
    printf("UNDO            - Mengembalikan kondisi sebelum terlaksananya action terakhir\n");
    printf("REDO            - Melakukan kembali action yang telah di-undo\n");
    printf("FRIDGE SHOW     - Menampilkan isi kulkas\n");
    printf("FRIDGE TAKE     - Mengambil makanan dari kulkas\n");
    printf("FRIDGE PUT      - Menaruh makanan pada kulkas\n");
}

int countAndPrintAvailableFood(ListStatik foodList, int foodListLength, char* action){
/* Menampilkan dan menghitung banyaknya makanan yang didapatkan melalui action tertentu*/
    printf("List Bahan Makanan yang Bisa Dibuat: \n");
    int count = 0;
    int i;
    for (i=0; i < foodListLength; i++){
        if (isWordStringEqual(actMkn(ELMTLIST(foodList,i)), action)){
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
    return count;
}

void printListCatalog (ListStatik foodList, int foodListLength){
/* Melakukan print semua makanan yang telah dibaca pada file konfigurasi dan dimasukan kedalam list statik*/
    int i;
    printf("List Makanan");
    printf("\n");
    printf("(Nama Makanan - Durasi Kadaluarsa - Aksi yang Diperlukan - Delivery atau Process Time)");
    printf("\n");
    for (i = 0; i < foodListLength; i++){
        printf("%d. ",i+1);
        printCatalog(ELMTLIST(foodList, i));
        printf("\n");
    }
}

void getInvalidRespond(){
/*Menampilkan respon apabila user memasukkan command yang invalid*/
    printf("====================================================\n");
    printf("===============     INVALID INPUT    ===============\n");
    printf("====================================================\n");
    printf("Input tidak valid. Silahkan inputkan command yang valid.\n");
}

void initState(state *st, Simulator S, TIME T){
    st->sub1 = S;
    st->sub2 = T;
}

POINT getKulkasCoordinate(){
/* Mengembalikan point tempat makanan akan ditaruh atau diambil */
    char command[MAX_COMMAND] = "\0";
    int idx;
    int xResult;
    int yResult;
    POINT pResult;
    getInput(command);
    STARTWORD(command,&idx);

    if (isWordAllIntegers(currentWord)){
        xResult = WordToInt(currentWord);
        
        ADVWORD(command, &idx);
        if (isWordAllIntegers(currentWord)){
            yResult = WordToInt(currentWord);

            Absis(pResult) = xResult;
            Ordinat(pResult) = yResult;
            return pResult;

        } else {
            yResult = -1;
        }
    } else {
        xResult = -1;
    }

}