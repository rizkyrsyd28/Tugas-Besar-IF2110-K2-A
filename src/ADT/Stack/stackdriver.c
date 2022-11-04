#include "stack.c"
#include "../Simulator/simulator.c"
#include "../Point/point.c"
#include "../piroqueue/piroqueue.c"
#include "../MesinKata/wordmachine.c"
#include"../Makanan/makanan.c"
#include <stdio.h>



void initState(state * st, Simulator S, TIME T){
    st->sub1 = S;
    st->sub2 = T;
}

int main()
{
    Stack SUndo, SRedo;
    Simulator S;
    state currentState;
    char in; 

    CreateEmpty(&SRedo);
    CreateEmpty(&SUndo);
    ReadSimulator(&S);

    TIME T;
    Makanan Ayam;
    Makanan Sapi;
    Makanan Minyak;
    Makanan Sayur;
    CreateEmptyMakanan(&Ayam);
    CreateEmptyMakanan(&Sapi);
    CreateEmptyMakanan(&Minyak);
    CreateEmptyMakanan(&Sayur);
    Word namasayur;
    int idx;
    char temp2[100]="\0";
    printf("Masukan kata Sayur : ");
    fgets(temp2, 100, stdin);
    // Mengubah nilai '\n' menjadi '\0' dan menambahkan MARK
    temp2[lengthString(temp2)-1] = '\0';
    appendChar(temp2,'.');

    STARTWORD(temp2,&idx);
    namasayur = currentWord;
    nameMkn(Sayur) = namasayur;
    
    BacaTIME(&T);
    printf("\n");

    initState(&currentState,S,T);
    int totalcommand=0;
    int totalundo = 0;

    boolean found = true;

    while (found){ 
        printf("input = ");
        scanf(" %c", &in);

        if (in == 'b'){
            Push(&SUndo, currentState);
            totalcommand ++;
            OlahMakananInventory(&Inventory(currentState.sub1),5,0,Sayur,Sapi,Minyak,Sayur);
            /*scanf("%d %c", &currentState.sub1.x, &currentState.sub1.c);
            scanf("%d %c", &currentState.sub2.x, &currentState.sub2.c);*/

        }
        else if (in == 'c'){
            Push(&SUndo, currentState);
            totalcommand ++;
            OlahMakananInventory(&Inventory(currentState.sub1),4,0,Sayur,Sapi,Minyak,Sayur);
        }
        else if (in=='g'){
            Push(&SUndo, currentState);
            totalcommand ++;
            GeserLokasi(&currentState.sub1,2);
        }
        else if(in=='t'){
            Push(&SUndo, currentState);
            totalcommand ++;
            currentState.sub2 = NextMinute(currentState.sub2);
        }
        else if (in == 'u'){
            //Undo(&SUndo,&SRedo,&currentState,totalcommand);
            if (totalcommand >0){
                Push(&SRedo, currentState);
                //currentState = InfoTop(SUndo);
                Pop (&SUndo, &currentState);
                printf("undo sukses\n");
            }
            else {
                printf("Tidak bisa undo\n");
            }
            if (totalcommand>0){
                totalcommand --;
                totalundo++;
            }

        }
        else if (in == 'r'){
            Redo(&SUndo,&SRedo,&currentState,totalundo);
            if (totalundo>0){
                totalcommand++;
                totalundo--;
            }
        }
        else {
            found = false;
        }

        DisplaySimulator(currentState.sub1);
        printf("\n");
        DisplayInventory(currentState.sub1);
        printf("\n");
        TulisTIME(currentState.sub2);
        printf("\n");

        printf("---------------------- STACK UNDO-----------------------------\n");
        displayStack(SUndo);
        printf("\n");

        printf("---------------------- STACK REDO-----------------------------\n");
        displayStack(SRedo);
        printf("\n");
        //printf("%d %c == %d %c\n", currentState.sub1.x, currentState.sub1.c, currentState.sub2.x, currentState.sub2.c);
    }
}
