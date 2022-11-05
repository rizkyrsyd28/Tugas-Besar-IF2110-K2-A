#include "resep.h"
#include "../Main/parser.c"

int main(){
    Cookbook c = konfigResep();
    ListStatik foods = konfigMakanan();


    // Liststatik foods = 
    printResep(c, foods);

    return 0;
}