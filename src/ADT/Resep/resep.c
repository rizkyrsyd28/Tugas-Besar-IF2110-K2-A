#include "resep.h"

boolean canMake(ID Id, PrioQueueTime pq);
/* Mengirim True jika semua bahan yang diperlukan untuk membuat suatu resep tersedia di inventory*/

void printResep(Cookbook cb, ListStatik foods){
    Makanan m;
    for (int i = 0; i < NResep(cb); i++){
        m = getMakanan(Parent(Resep(cb, i)), foods);
        printf("%d. ", i+1);
        printWord(nameMkn(m));
        printf("\n\t");
        printWord(actMkn(m));
        Makanan mChild;
        for (int j = 0; j < NChild(Resep(cb,i)); j++){
            printf(" - ");
            mChild = getMakanan(Parent(Child(Resep(cb, i), j)), foods);
            printWord(nameMkn(mChild));
        }
        printf("\n");
    }
}
/* mencetak resep */
/* I.S. cookbook terdefinisi */
/* F.S. Mencetak semua resep yang ada di cook book dengan konfig <ACTION> - <BAHAN> - <BAHAN> - ... */