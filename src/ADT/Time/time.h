/* File: time.h */
/* Tanggal: 3 September 2022 */
/* Definisi ADT TIME */

#ifndef TIME_H
#define TIME_H
#include "../boolean.h"

/* fungsi ADT TIME
Digunakan untuk menyajikan waktu kadaluarsa suatu makanan
Dan untuk waktu delivery makanan*/

/* *** Definisi TYPE TIME <DD:MM:SS> *** */
/* *** Asumsi waktu kadaluarsa makanan tidak lebih dari 30 hari *** */
typedef struct {
	int DD; /* integer >= 0*/
	int HH; /* integer [0..59] */			
	int MM; /* integer [0..59] */	
} TIME;


/* *** Notasi Akses: selektor TIME *** */
#define Day(T) (T).DD
#define Hour(T) (T).HH
#define Minute(T) (T).MM

boolean IsTIMEValid (int H, int M, int D);
/* Mengirim true jika D,H,M dapat membentuk T yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah type time*/

/* *** Konstruktor: Membentuk sebuah TIME dari komponen-komponennya *** */
void CreateTime (TIME * T, int HH, int MM, int SS);
/* Membentuk sebuah TIME dari komponen-komponennya yang valid */
/* Prekondisi : DD, HH, MM valid untuk membentuk TIME */

void BacaTIME (TIME * T);
/*Proses pembacaan time yang terdiri atas DD,HH dan MM Kalo gak valid di ulangi sampai valid yang terdiri dari 
DD,HH,MM digunain buat nunjukin kadaluarsa dari suatu makanan*/
   
void TulisTIMEKadaluarsa (TIME T);
/* I.S. : T sembarang */
/* Proses : menulis nilai setiap komponen T ke layar dalam format "DD hari, HH jam, MM menit"
   tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.*/ 

void TulisTIMEDelivery (TIME T);
/* I.S. : T sembarang */
/* Proses : menulis nilai setiap komponen T ke layar dalam format ("HH.MM")
   tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.*/ 

void TulisTIME(TIME T);
/* Menulis TIME dalam format <DD,HH,MM>*/

void TulisTIMEString(TIME T);
/* Menulis TIME dalam format DD hari HH jam MM menit*/

/* ***************************************************************** */
/* KELOMPOK KONVERSI TERHADAP TYPE                                   */
/* ***************************************************************** */

TIME NextMinute (TIME T);
/* Mengirim 1 menit setelah T dalam bentuk TIME ini berfungsi untuk proses delivery pada proses ini hari tidak ikut ditampilkan maka*/
/*Diasumsikan ketika h = 0 maka akan kembali ke */
TIME NextNMinute (TIME T, int N);
/* Mengirim N menit setelah T dalam bentuk TIME */
TIME PrevMinute (TIME T);
/* Mengirim 1 menit sebelum T dalam bentuk TIME */
TIME PrevNMinute (TIME T, int N);
/* Mengirim N menit sebelum T dalam bentuk TIME */
/* *** Kelompok Operator Aritmetika *** */
boolean TEQ (TIME T1, TIME T2);
/* Mengirimkan true jika T1=T2, false jika tidak */
boolean TNEQ (TIME T1, TIME T2);
/* Mengirimkan true jika T1 tidak sama dengan T2 */
boolean TLT (TIME T1, TIME T2);
/* Mengirimkan true jika T1<T2, false jika tidak */
boolean TGT (TIME T1, TIME T2);
/* Mengirimkan true jika T1>T2, false jika tidak */
TIME roundToEvenHours(TIME T);
/* Membulatkan TIME ke jam genap terdekat */

int TIMEtoint (TIME T);
/* Mengubah dari TIME ke bentuk int menit*/
TIME inttoTIME (int n);
/* Mengubah dari int menit ke bentuk TIME*/

#endif
