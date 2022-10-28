
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "parser.c"


int main () {
    char command[] = "\0";
    boolean program = true;
    int idx;

    ASCIIArt();
    printf("Input 'START' untuk melakukan program.\n");
    scanf("%s", &command);
    upper(command);
    appendChar(command, '.');

    // Menggunakan mesin kata untuk membaca
    STARTWORD(command, &idx);
    /* Karena hanya satu kata (hanya menerima 'START'), 
    cukup STARTWORD saja yang dijalankan */

    printf("%s\n", command);

    while (!isStringEqual(str(currentWord), "START")){
        printf("Input selain 'START' tidak diterima.\n");
        scanf("%s", &command);
        upper(command);
        appendChar(command, '.');
        STARTWORD(command, &idx);
    }
    
    while(program){
        printf("Silahkan masukkan command yang ingin dilakukan.\n");
        printf("Command: ");
        scanf("%s", &command);
        upper(command);

        if (isStringEqual(command, "EXIT")){
            printf("====================================================\n");
            printf("===============        EXIT          ===============\n");
            printf("====================================================\n");
            printf("Yahh kok udahan... :(\n");
            program = false;
        }
        else if (isStringEqual(command, "HELP")){
            printf("====================================================\n");
            printf("===============        HELP          ===============\n");
            printf("====================================================\n");
            printf("Berikut adalah command yang dapat dimasukkan:\n");
            printf("MOVE            - Menggerakan simulator\n");
            printf("    -> NORTH    - Pergerakan ke petak sebelah atas\n");
            printf("    -> EAST     - Pergerakan ke petak sebelah kanan\n");
            printf("    -> SOUTH    - Pergerakan ke petak sebelah bawah\n");
            printf("    -> WEST     - Pergerakan ke petak sebelah kiri\n");
            printf("BUY             - Proses pembelian Makanan\n");
            printf("MIX             - Proses pencampuran Makanan\n");
            printf("FRY             - Proses penggorengan Makanan\n");
            printf("CHOP            - Proses pemotongan Makanan\n");
            printf("CATALOG         - Melihat data list makanan yang valid\n");
            printf("COOKBOOK        - Melihat data list resep yang valid\n");
            printf("INVENTORY       - Membuka inventory yang dimiliki oleh simulator\n");
            printf("DELIVERY        - Membuka tampilan list makanan yang sedang dikirim\n");
            printf("WAIT (x) (y)    - Mempercepat time selama x jam dan y menit\n");
        }
    }
}