#include <stdio.h>
#include "time.h"
#include "boolean.h"

/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */
boolean IsTIMEValid (int D,int H,int M){
	return ((D>= 0 && D <= 30) && (H >= 0 && H <= 23) && (M >= 0 && M <= 59));
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
			//Diasumsikan hari tidak akan lebih dari 30 karena mengingat ini waktu kadaluarsa suatu makanan
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
			//Diasumsikan juga hari tidak akan kurang dari 0 
		}
	}
	return t;
}
/* Mengirim 1 detik sebelum T dalam bentuk TIME */

TIME PrevNDetik (TIME T, int N) {
	int i; TIME t;
	t = T;
	for (i = 0; i < N; i++) {
		t = PrevMinute(t);
	}
	return t;
}
