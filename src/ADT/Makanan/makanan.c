/* IMPLEMENTASI ADT MAKANAN */

#include <stdio.h>
#include "makanan.h"
#include <stdlib.h>
#include "../String/string.c"


// OPERASI PERBANDINGAN
void isIDGreater(Makanan m1, Makanan m2)
// Mengirimkan true bila ID m1 lebih besar dari ID m2
{
    return (m1.id > m2.id);
}
void isIDLower(Makanan m1, Makanan m2)
// Mengirimkan true bila ID m1 lebih kecil dari ID m2
{
    return (m1.id < m2.id);
}
