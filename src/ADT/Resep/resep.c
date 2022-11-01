#include "resep.h"

boolean canMake(Makanan mkn, PrioQueueTime pq);
/* Mengirim True jika semua bahan yang diperlukan untuk membuat suatu resep tersedia di inventory*/


void printResep(Cookbook cb, ListStatik foods);
/* mencetak resep */
/* I.S. cookbook terdefinisi */
/* F.S. Mencetak semua resep yang ada di cook book dengan konfig <ACTION> - <BAHAN> - <BAHAN> - ... */