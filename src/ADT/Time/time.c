#include <stdio.h>
#include "time.h"

/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */

/* *** Konstruktor: Membentuk sebuah TIME dari komponen-komponennya *** */
void CreateTime (TIME * T, int DD, int HH, int MM) {
/* Membentuk sebuah TIME dari komponen-komponennya yang valid */
/* Prekondisi : HH, MM, SS valid untuk membentuk TIME */
	Day(*T) = DD;
	Hour(*T) = HH;
	Minute(*T) = MM;
}


/* ***************************************************************** */
/* FUngsi - Fungsi Lain                                             */
/* ***************************************************************** */
boolean IsTIMEValid (int DD,int HH,int MM){
/* Mengirim true jika H,M,S dapat membentuk T yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah Jam */
	return ((DD>= 0) && (HH >= 0 && HH <= 23) && (MM >= 0 && MM <= 59));
}

void BacaTIME (TIME * T) {
/*Proses pembacaan time yang terdiri atas DD,HH dan MM Kalo gak valid di ulangi sampai valid yang terdiri dari 
DD,HH,MM digunain buat nunjukin kadaluarsa dari suatu makanan*/
	int HH, MM, DD;
	do {
		scanf("%d %d %d", &DD, &HH, &MM);
	} while (!IsTIMEValid(DD,HH,MM) && printf("Jam tidak valid\n"));
	CreateTime(T, DD, HH, MM);
}


void TulisTIMEDelivery (TIME T)
/* I.S. : T sembarang */
/* Proses : menulis nilai setiap komponen T ke layar dalam format ("HH.MM")
   tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.*/ 
{
	printf("(%d.%d)",Hour(T),Minute(T));
}

void TulisTIME(TIME T)
/* Menulis TIME dalam format <DD,HH,MM>*/
{
	printf("< Day %d | %d:%d >\n",Day(T), Hour(T), Minute(T));
}

void TulisTIMEString(TIME T)
/* Menulis TIME dalam format DD hari HH jam MM menit*/
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
/* Mengirim 1 menit setelah T dalam bentuk TIME */
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
/* Mengirim N menit setelah T dalam bentuk TIME */
	int i; TIME t;
	t = T;
	for (i = 0; i < N; i++) {
		t = NextMinute(t);
	}
	return t;
}


TIME PrevMinute (TIME T) {
/* Mengirim 1 menit sebelum T dalam bentuk TIME */
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


TIME PrevNMinute(TIME T, int N) {
/* Mengirim N menit sebelum T dalam bentuk TIME */
	int i; TIME t;
	t = T;
	for (i = 0; i < N; i++) {
		t = PrevMinute(t);
	}
	return t;
}

/* *** Kelompok Operator Aritmetika *** */
boolean TEQ (TIME T1, TIME T2) {
/* Mengirimkan true jika T1=T2, false jika tidak */
	return ((Day(T1) == Day(T2)) && (Minute(T1) == Minute(T2)) && (Hour(T1) == Hour(T2)));
}


boolean TNEQ (TIME T1, TIME T2) {
/* Mengirimkan true jika T1 tidak sama dengan T2 */
	return !TEQ(T1,T2);
}


boolean TLT (TIME T1, TIME T2) {
/* Mengirimkan true jika T1<T2, false jika tidak */
	return ((Day(T1) < Day(T2)) || (Day(T1) == Day(T2) && Hour(T1) < Hour(T2)) || (Day(T1) == Day(T2) && Hour(T1) == Hour(T2) && Minute(T1) < Minute(T2)));
}


boolean TGT (TIME T1, TIME T2) {
/* Mengirimkan true jika T1>T2, false jika tidak */
	return (TNEQ(T1,T2) && !TLT(T1,T2));
}

/* *** Operator aritmatika TIME *** */

TIME roundToEvenHours(TIME T) {
/* Membulatkan TIME ke jam genap terdekat */
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

int TIMEtoint (TIME T){
/* Mengubah dari TIME ke bentuk int menit*/
	int result = 0;
	result += Day(T)*24*60 + Hour(T)*60 + Minute(T);
	return result;
}

TIME inttoTIME (int n){
/* Mengubah dari int menit ke bentuk TIME*/
	TIME result;
	Day(result) = (n - (n % (24*60)))/24*60;
	Hour(result) = (( n %(24*60)) - (n % (24*60) % 60))/60;
	Minute(result) = (n % (24*60) % 60);
	return result;
}