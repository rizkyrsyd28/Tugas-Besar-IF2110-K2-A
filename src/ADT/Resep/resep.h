#ifndef RESEP_H
#define RESEP_H

#include "../boolean.h"
#include "../Tree/nTree.c"
#include "../ListStatik/liststatik.c"
#include "../piroqueue/piroqueue.h"

typedef struct {
    int NResep;
    NTree * Resep;
} Cookbook;

/*** SELEKTOR ***/
#define NResep(c) (c).NResep /* selektor jumlah resep */
#define Resep(c) (c).Resep  /* selektor list resep */

boolean canMake(Makanan mkn, PrioQueueTime pq);
/* Mengirim True jika semua bahan yang diperlukan untuk membuat suatu resep tersedia di inventory*/

void printResep(Cookbook cb, ListStatik foods);
/* mencetak resep */
/* I.S. cookbook terdefinisi */
/* F.S. Mencetak semua resep yang ada di cook book dengan konfig <ACTION> - <BAHAN> - <BAHAN> - ... */

#endif