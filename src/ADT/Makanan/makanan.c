/* IMPLEMENTASI ADT MAKANAN */

#include <stdio.h>
#include "makanan.h"
#include <stdlib.h>
#include "../String/string.c"


// OPERASI PERBANDINGAN
void isIDGreater(Makanan m1, Makanan m2)
// Mengirimkan true bila ID m1 lebih besar dari ID m2
{
    return (idMkn(m1) > idMkn(m2));
}
void isIDLower(Makanan m1, Makanan m2)
// Mengirimkan true bila ID m1 lebih kecil dari ID m2
{
    return (id_mkn(m1) < id_mkn(m2));
}
void isActionSame(Makanan m1, Makanan m2)
// Mengirimkan true bila action yang dibutuhkan m1 dan m2 sama
{
    return( isStringEqual(actMkn(m1), act_mkn(m2)));
}
void isExpiryGreater(Makanan m1, Makanan m2);
// Mengirimkan true bila expiry m1 lebih besar dari m2
void isExpiryLower(Makanan m1, Makanan m2);
// Mengirimkan true bila expiry m1 lebih kecil dari m2
void isDeliveryGreater(Makanan m1, Makanan m2);
// Mengirimkan true bila delivery m1 lebih besar dari m2
void isDeliveryLower(Makanan m1, Makanan m2);
// Mengirimkan true bila delivery m1 lebih kecil dari m2
