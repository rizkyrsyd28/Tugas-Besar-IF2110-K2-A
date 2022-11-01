#ifndef RESEP_H
#define RESEP_H

#include "../boolean.h"
#include "../Tree/nTree.c"
#include "../ListStatik/liststatik.c"
#include "../piroqueue/piroqueue.c"

typedef struct {
    int NResep;
    NTree * Resep;
} Cookbook;

/*** SELEKTOR ***/
#define NResep(c) (c).NResep /* selektor jumlah resep */
#define Buku(c) (c).Resep  /* selektor list resep */
#define Resep(c,i) (c).Resep[i] /* selektor element list resep */

boolean canMake(Makanan mkn, PrioQueueTime pq);
/* Mengirim True jika semua bahan yang diperlukan untuk membuat suatu resep tersedia di inventory*/

Makanan getMakanan(ID Id, ListStatik foods);
/* mengembalikan makanan dengan input Id dari cookbook*/

void printResep(Cookbook cb, ListStatik foods);
/* mencetak resep */
/* I.S. cookbook terdefinisi */
/* F.S. Mencetak semua resep yang ada di cook book dengan konfig <ACTION> - <BAHAN> - <BAHAN> - ... */

#endif