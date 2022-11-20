#include "makanan.c"

int main () {

    Makanan m1;
    Makanan m2;
    CreateEmptyMakanan(&m1);
    CreateEmptyMakanan(&m2);

    printMakanan(m1);
    idMkn(m1) = 10;
    idMkn(m2) = 5;
    if (isIDGreater(m1, m2)){
        printf("test\n");
    }

    return 0;
}