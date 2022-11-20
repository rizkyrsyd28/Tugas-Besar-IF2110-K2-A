#include "point.h"

int main(){
    // Kamus 
    POINT p1, p2;

    CreatePoint(&p1, 0, 0);

    BacaPOINT(&p2);

    printf("point 1 : "); TulisPOINT(p1);
    printf("point 2 : "); TulisPOINT(p2);

    if (EQ(p1,p2)){
        printf("Equal\n");
    }
    else if (NEQ(p1,p2)){
        printf("Not Equal\n");
    }

    if (IsOrigin(p2)){
        printf("Origin\n");
    }
    else if (IsOnSbX(p2)){
        printf("Sumbu X\n");
    }
    else if (IsOnSbY(p2)){
        printf("Sumbu Y\n");
    }

    printf("Kuadran : %d\n", Kuadran(p2));


    printf("Next X : ");TulisPOINT(NextX(p1));
    printf("Next Y : ");TulisPOINT(NextY(p1));
    printf("BACK X : ");TulisPOINT(BackX(p1));
    printf("BACK Y : ");TulisPOINT(BackY(p1));

    printf("Delta x+1 y+2 : "); TulisPOINT(PlusDelta(p1, 1, 2));

    printf("Mirror p1 : "); TulisPOINT(MirrorOf(p1, true));
    
    Geser(&p1, 1, 2);
    printf("Delta x+1 y+2 : "); TulisPOINT(p1);

    GeserKeSbX(&p1);
    printf("Sumbu X : "); TulisPOINT(p1);

    GeserKeSbY(&p1);
    printf("Sumbu Y : "); TulisPOINT(p1);

    Mirror(&p2, false);
    printf("Mirror p2 : "); TulisPOINT(p2);

    return 0;
}