#include <stdio.h>
#include "time.c"

int main()
{
	TIME T1,T2;
	long simpan1,simpan2;
	BacaTIME (&T1);
	BacaTIME (&T2);
	printf("T1 adalah :\n");
	TulisTIME (T1);
	printf("\n");
	printf("T2 adalah :\n");
	TulisTIME (T2);
	printf("\n");
	printf("T1 dalam detik adalah : \n");
	printf("%d\n",TIMEToDetik (T1));
	printf("T2 dalam detik adalah : \n");
	printf("%d\n",TIMEToDetik (T2));
	simpan1 = TIMEToDetik (T1);
	simpan2 = TIMEToDetik (T2);
	printf("Konversi T1 ke detik di ubah ke jam lagi\n");
	TulisTIME ( DetikToTIME (simpan1));
	printf("\n");
	printf("Konversi T2 ke detik di ubah ke jam lagi\n");
	TulisTIME ( DetikToTIME (simpan2));
	printf("\n");
	printf("Apakah nilainya sama:\n");
	if(TEQ (T1, T2) == 0)
	{
		printf("Tidak\n");
	}	
	else
	{
		printf("Ya\n");
	}
	printf("Apakah nilai T1 lebih kecil dari T2:\n");
	if(TLT (T1, T2) == 0)
	{
		printf("Tidak\n");
	}	
	else
	{
		printf("Ya\n");
	}
	printf("T1 setelah ditambah sedetik:\n");
	TulisTIME (NextDetik (T1));
	printf("\n");
	printf("T2 setelah ditambah limadetik:\n");
	TulisTIME (NextNDetik (T2, 5));
	printf("\n");
	printf("T1 setelah dikurang sedetik:\n");
	TulisTIME (PrevDetik (T1));
	printf("\n");
	printf("T2 setelah dikurang limadetik:\n");
	TulisTIME (PrevNDetik (T2, 5));
	printf("\n");
	printf("Durasi antara T1 dan T2:\n");
	printf("%lu\n",Durasi (T1, T2));
	return 0;
}
