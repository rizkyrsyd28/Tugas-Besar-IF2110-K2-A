#include "resep.h"

boolean canFry(PrioQueueTime pq){
/* Mengembalikan nilai True jika terdapat minyak goreng pada inventory*/
    if (Tail(pq) < Head(pq)){
        for(int i = Head(pq); i < MaxEl(pq); i++){
            if (isWordStringEqual(nameMkn(Elmt(pq,i)),"Minyak Goreng")){
                return true;
            }
        }
        for(int i = 0; i <= Tail(pq); i++){
            if (isWordStringEqual(nameMkn(Elmt(pq,i)),"Minyak Goreng")){
                return true;
            }
        }
    }
    else {
        for(int i = Head(pq); i <= Tail(pq); i++){
            if (isWordStringEqual(nameMkn(Elmt(pq,i)),"Minyak Goreng")){
                return true;
            }
        }
    }
    return false;
}

boolean canMake(Cookbook cb, Makanan m, PrioQueueTime pq){
/* Mengirim True jika semua bahan yang diperlukan untuk membuat suatu resep tersedia di inventory*/
    int idx;
    for (int i = 0; i < NResep(cb); i++){
        if (Parent(Resep(cb, i)) == idMkn(m)){
            idx = i;
        }
    }
    boolean status = true;
    for (int j = 0; j < NChild(Resep(cb, idx)); j++){
        boolean cek = false;
        if (Tail(pq) < Head(pq)){
            for (int k = Head(pq); k < MaxEl(pq); k++){
                if (Parent(Child(Resep(cb,idx),j)) == idMkn(Elmt(pq,k))){
                    cek = true;
                }
            }
            for (int l = 0; l <= Tail(pq); l++){                
                if (Parent(Child(Resep(cb,idx),j)) == idMkn(Elmt(pq,l))){
                    cek = true;
                }
            }
        }
        else {
            for (int k = Head(pq); k <= Tail(pq); k++){
                if (Parent(Child(Resep(cb,idx),j)) == idMkn(Elmt(pq,k))){
                    cek = true;
                }
            }
        }
        status = cek;
    }
    
    return status;
}


void printResep(Cookbook cb, ListStatik foods){
/* mencetak resep */
/* I.S. cookbook terdefinisi */
/* F.S. Mencetak semua resep yang ada di cook book dengan konfig <ACTION> - <BAHAN> - <BAHAN> - ... */
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
