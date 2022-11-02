#include <stdio.h>
#include "time.h"

/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */
boolean IsTIMEValid (int D,int H,int M){
	return ((D>= 0) && (H >= 0 && H <= 23) && (M >= 0 && M <= 59));
}
/* Mengirim true jika H,M,S dapat membentuk T yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah Jam */

/* *** Konstruktor: Membentuk sebuah TIME dari komponen-komponennya *** */
void CreateTime (TIME * T, int DD, int HH, int MM) {
	Day(*T) = DD;
	Hour(*T) = HH;
	Minute(*T) = MM;
}
/* Membentuk sebuah TIME dari komponen-komponennya yang valid */
/* Prekondisi : HH, MM, SS valid untuk membentuk TIME */

/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */
void BacaTIME (TIME * T) {
	int HH, MM, DD;
	do {
		scanf("%d %d %d", &DD, &HH, &MM);
	} while (!IsTIMEValid(DD,HH,MM) && printf("Jam tidak valid\n"));
	CreateTime(T, DD, HH, MM);
}

   
void TulisTIMEKadaluarsa (TIME T) {
	if(Day(T) != 0 && Hour(T) != 0 && Minute(T) != 0)
	{
		printf("%d hari, %d jam, %d menit", Day(T), Hour(T), Minute(T));
	}
	else if(Day(T) == 0 && Hour(T) != 0 && Minute(T) != 0)
	{
		printf("%d jam, %d menit", Hour(T), Minute(T));
	}
	else if(Day(T) == 0 && Hour(T) == 0 && Minute(T) != 0)
	{
		printf("%d menit", Minute(T));
	}
	else if(Day(T) != 0 && Hour(T) == 0 && Minute(T) != 0)
	{
		printf("%d hari,%d menit", Day(T),Minute(T));
	}
	else if(Day(T) == 0 && Hour(T) != 0 && Minute(T) == 0)
	{
		printf("%d jam", Hour(T));
	}
	else if(Day(T) != 0 && Hour(T) == 0 && Minute(T) == 0)
	{
		printf("%d hari", Day(T));
	}
	else if(Day(T) != 0 && Hour(T) != 0 && Minute(T) == 0)
	{
		printf("%d hari, %d jam", Day(T), Hour(T), Minute(T));
	}
	else if(Day(T) == 0 && Hour(T) == 0 && Minute(T) == 0)
	{
		printf("Kadaluarsa");
	}
	
	
}

void TulisTIMEDelivery (TIME T)
{
	printf("(%d.%d)",Hour(T),Minute(T));
}

void TulisTIME(TIME T)
{
	printf("< Day %d | %d:%d >\n",Day(T), Hour(T), Minute(T));
}

void TulisTIMEString(TIME T)
{
	if (Day(T) == 0 && Hour(T) == 0 && Minute(T) == 0){
		printf("[0]");
	} else {
		if (Day(T) != 0){
			printf("%d hari ", Day(T));
		}
		if (Hour(T) != 0){
			printf("%d jam ", Hour(T));
		}
		if (Minute(T) != 0){
			printf("%d menit", Minute(T));
		}
	}

}

TIME NextMinute (TIME T) {
	TIME t;
	t = T;
	Minute(t) += 1;					
	if (Minute(t) > 59) {
		Minute(t) = 0;
		Hour(t) += 1;
		if (Hour(t) > 23) {
			Hour(t) = 0;
			Day(t) += 1;
			}
		}
	return t;
}


TIME NextNMinute (TIME T, int N) {
	int i; TIME t;
	t = T;
	for (i = 0; i < N; i++) {
		t = NextMinute(t);
	}
	return t;
}


TIME PrevMinute (TIME T) {
	TIME t;
	t = T;
	Minute(t) -= 1;
	if (Minute(t) < 0) {
		Minute(t) = 59;
		Hour(t) -= 1;
		if (Hour(t) < 0) {
			Hour(t) = 23;
			Day(t) -= 1;
			//hari tidak akan kurang dari 0 
		}
	}
	return t;
}
/* Mengirim 1 detik sebelum T dalam bentuk TIME */

TIME PrevNMinute(TIME T, int N) {
	int i; TIME t;
	t = T;
	for (i = 0; i < N; i++) {
		t = PrevMinute(t);
	}
	return t;
}
/* Mengirim N detik sebelum T dalam bentuk TIME */
/* *** Kelompok Operator Aritmetika *** */
boolean TEQ (TIME T1, TIME T2) {
	return ((Day(T1) == Day(T2)) && (Minute(T1) == Minute(T2)) && (Hour(T1) == Hour(T2)));
}
/* Mengirimkan true jika T1=T2, false jika tidak */

boolean TNEQ (TIME T1, TIME T2) {
	return !TEQ(T1,T2);
}
/* Mengirimkan true jika T1 tidak sama dengan T2 */

boolean TLT (TIME T1, TIME T2) {
	return ((Day(T1) < Day(T2)) || (Day(T1) == Day(T2) && Hour(T1) < Hour(T2)) || (Day(T1) == Day(T2) && Hour(T1) == Hour(T2) && Minute(T1) < Minute(T2)));
}
/* Mengirimkan true jika T1<T2, false jika tidak */

boolean TGT (TIME T1, TIME T2) {
	return (TNEQ(T1,T2) && !TLT(T1,T2));
}
/* Mengirimkan true jika T1>T2, false jika tidak */
/* *** Operator aritmatika TIME *** */

TIME roundToEvenHours(TIME T) {
	TIME a = T;
	boolean isEven = (Hour(T) % 2 == 0);
	if (Minute(a) == 30) {
		if (!isEven) {
			Hour(a)++;
		}
	} else if (Minute(a) > 30) {
		Hour(a)++;
	}
	Minute(a) = 0;
}
