#include <stdio.h>
#include "wordmachine.c"

void ASCIIArt()
{
	FILE * fPointer;
	fPointer = fopen("ASCIIArt.txt", "r");
	char singleLine[150];
	
	while(!feof(fPointer))
	{
		fgets(singleLine, 150, fPointer);
		puts(singleLine);
	}
	fclose(fPointer);
}


int main()
{
	//Asumsi setiap pilihan akan diakhiri MARK yaitu "."
	Word choice;
	
	ASCIIArt();
	printf("Hello, what do you want?\n1.START.\n2.EXIT.\nwrite your choice:\n");
	STARTWORD();
	choice = currentWord;
	if(!StringsNotEqual(choice, "START")  || !StringsNotEqual(choice, "EXIT"))
	{
		if(!StringsNotEqual(choice, "START"))
		{
			printf("Langkah lanjutan");
		}
		
		else
		{
			printf("Anda keluar dari program");
		}
	}
	
	else
	{
		//Disini mash error bntar
		char newInput;
		do
		{
			
			printf("wrong choice, try again");
			scanf("%c",&newInput);
		}
		while(!StringsEqualChar(newInput, "START.")  && !StringsEqualChar(newInput, "EXIT."));
		if(StringsEqualChar(newInput, "START.") || StringsEqualChar(newInput, "EXIT."))
		{
			if(StringsEqualChar(newInput, "START"))
			{
				printf("Langkah lanjutan");
			}
			else
			{
				printf("Anda keluar dari program");
			}
		}
	}
	return 0;
}
