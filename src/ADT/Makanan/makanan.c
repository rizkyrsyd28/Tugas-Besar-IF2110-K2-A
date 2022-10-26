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
boolean isIdentical(Makanan m1, Makanan m2) {
    //Mengirimkan true apabila kedua makanan sama
    return (m1.id == m2.id && m1.action == m2.action && TEQ(m1.delivery, m2.delivery) && TEQ(m1.expired, m2.expired) && (m1.name == m2.name));
}
