#include <stdio.h>
#include "time.c"

int main()
{
	TIME T;
	BacaTIME (&T);
	printf("Kadaluarsa Ayam ");
	TulisTIMEKadaluarsa (T);
	printf("\n");
	TulisTIMEDelivery (T);
	printf("\n");
	T = NextMinute (T);
	TulisTIMEDelivery (T);
}

