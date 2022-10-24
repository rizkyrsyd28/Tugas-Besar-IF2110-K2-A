//Nama : Shelma Salsabila
//NIM : 1352115
//Tanggal : 06-09-2022
//Deskripsi : Implementasi time.c

#include <stdio.h>
#include "time.h"

boolean IsTIMEValid (int H, int M, int S){
    return (0<=H) && (H<24) && (0<=M) && (M<60) && (0<=S) && (S<60);
}
void CreateTime (TIME * T, int HH, int MM, int SS)
{

    Hour(*T)=HH;
    Minute(*T)=MM;
    Second(*T)=SS;
    
}

void BacaTIME (TIME * T){
    boolean benar=false;
    int j,m,d;
    while(benar == false){
        scanf("%d %d %d", &j,&m,&d);
        benar=IsTIMEValid(j,m,d);
        if (benar == false){
            printf("Jam tidak Valid\n");
        }
    }
    CreateTime(T,j,m,d);
}

void TulisTIME (TIME T){
   printf("%02d:%02d:%02d", Hour(T), Minute(T), Second(T));
}

long TIMEToDetik (TIME T){
    return (3600*Hour(T)+ 60*Minute(T) + Second(T));
}

TIME DetikToTIME (long N){
	int detik; 
	TIME T;

	if (N>=86400) {
		detik = N % 86400;
	} else {
		detik = N;
	}

	Hour(T) = detik/3600;
	Minute(T) = (detik % 3600)/60 ; 
	Second(T) = (detik % 3600)%60;
	return T;
}

boolean TEQ (TIME T1, TIME T2){
    return (Hour(T1)==Hour(T2)) && (Minute(T1)==Minute(T2)) && (Second(T1)==Second(T2));
}

boolean TNEQ (TIME T1, TIME T2){
    return!((Hour(T1) == Hour(T2)) && (Minute(T1) == Minute(T2)) && (Second(T1) == Second(T2)));
}

boolean TLT (TIME T1, TIME T2){
    return TIMEToDetik(T1)<TIMEToDetik(T2);
}

boolean TGT (TIME T1, TIME T2){
    return TIMEToDetik(T1)>TIMEToDetik(T2);
}

TIME NextDetik (TIME T){
    long detik;
    detik = TIMEToDetik(T);
    detik = detik+1 ;
    return DetikToTIME(detik);
}

TIME NextNDetik (TIME T, int N){
    long detik;
    detik = TIMEToDetik(T);
    detik = detik + N;
    return DetikToTIME(detik);
}

TIME PrevDetik (TIME T){
    long detik;
    detik = TIMEToDetik(T);
    detik = detik-1 ;
    return DetikToTIME(detik);
}

TIME PrevNDetik (TIME T, int N){
    long detik;
    detik = TIMEToDetik(T);
    detik = detik-N ;
    return DetikToTIME(detik);
}

long Durasi (TIME TAw, TIME TAkh){
    long selisih = TIMEToDetik(TAkh) - TIMEToDetik(TAw);
    if (selisih < 0) {
        selisih += 86400;
    }
    return selisih;
}
