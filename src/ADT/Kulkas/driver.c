#include <stdio.h>
#include "kulkas.c"


int main () {
    Kulkas k;
    CreateKulkas(&k);
    DisplayKulkas(k);

    return 0;
}