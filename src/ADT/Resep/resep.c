#include "resep.h"

boolean canFry(PrioQueueTime pq){
    for(int i = 0; i <= NBElmt(pq); i++){
        printMakanan(Elmt(pq,i));printf("\n");
        if (isWordStringEqual(nameMkn(Elmt(pq,i)),"Minyak Goreng")){
            return true;
        }
    }
    printf("\nMINYAKKKKKKK...\n");
    return false;
}

boolean canMake(Cookbook cb, Makanan m, PrioQueueTime pq){
    PrintPrioQueueTimeInventory(pq);
    int idx;
    for (int i = 0; i < NResep(cb); i++){
        if (Parent(Resep(cb, i)) == idMkn(m)){
            idx = i;
        }
    }
    printf("\n(%d)\n", Parent(Resep(cb, idx)));
    boolean status = true;
    for (int j = 0; j < NChild(Resep(cb, idx)); j++){
        boolean cek = false;
        for (int k = Head(pq); k <= Tail(pq); k++){
            printf("(%d === %d)", Parent(Child(Resep(cb,idx), j)), idMkn(Elmt(pq, k)));
            if (Parent(Child(Resep(cb,idx),j)) == idMkn(Elmt(pq,k))){
                cek = true;
            }
        }

        status = cek;
    }
    
    return status;
}
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