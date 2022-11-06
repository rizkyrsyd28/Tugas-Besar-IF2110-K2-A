#include "../MesinKata/wordmachine.c"
#include"../Makanan/makanan.c"
#include "../piroqueue/piroqueue.c"
#include "../Matrix/matrix.c"
#include "../Simulator/simulator.c"
#include "stack.c"
#include <stdio.h>


/*void initState(state * st, Simulator S, TIME T){
    st->sub1 = S;
    st->sub2 = T;
}

void initMakanan2(Makanan * m){
    m->id = 10; 
    m->delivery.DD = 10;
    m->delivery.HH = 10;
    m->delivery.MM = 10;
    m->expired.DD = 10;
    m->expired.HH = 20;
    m->expired.MM = 30;
    m->name.Length = 3;
    m->name.TabWord[0] = 'x';
    m->name.TabWord[1] = 'y';
    m->name.TabWord[2] = 'z';
    m->action.Length = 3;
    m->action.TabWord[0] = 'x';
    m->action.TabWord[1] = 'y';
    m->action.TabWord[2] = 'z';
}

int main()
{
    Stack SUndo, SRedo;
    Simulator S;
    state currentState;
    PrioQueueTime deliverylist;
    PrioQueueTime processlist;
    char in; 

    ReadSimulator(&S);
    MakeEmptyQueue(&deliverylist,100);
    MakeEmptyQueue(&processlist,100);
    CreateEmpty(&SRedo);
    CreateEmpty(&SUndo);

    Makanan xyz;
    initMakanan2(&xyz);
    EnqueueDelivery(&deliverylist,xyz);
    EnqueueDelivery(&processlist,xyz);

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

    //initState(&currentState,S,T,deliverylist,processlist);
    int totalcommand=0;
    int totalundo = 0;

    boolean found = true;

    while (found){ 
        printf("input = ");
        scanf(" %c", &in);

        if (in == 'b'){
            CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q);
            Push(&SUndo, currentState);
            totalcommand ++;
            OlahMakananInventory(&Inventory(currentState.sub1),5,0,Sayur,Sapi,Minyak,Sayur);
            /*scanf("%d %c", &currentState.sub1.x, &currentState.sub1.c);
            scanf("%d %c", &currentState.sub2.x, &currentState.sub2.c);*/

        /*}
        else if (in == 'c'){
            CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q);
            Push(&SUndo, currentState);
            totalcommand ++;
            OlahMakananInventory(&Inventory(currentState.sub1),4,0,Sayur,Sapi,Minyak,Sayur);
        }
        else if (in=='g'){
            CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q);
            Push(&SUndo, currentState);
            totalcommand ++;
            GeserLokasi(&currentState.sub1,2);
        }
        else if(in=='t'){
            CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q);
            Push(&SUndo, currentState);
            totalcommand ++;
            currentState.sub2 = NextMinute(currentState.sub2);
        }
        else if (in == 'u'){
            CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q);
            POINT srcdummy;
            CreatePoint(&srcdummy,-50,-50);
            Undo(&SUndo,&SRedo,&currentState,totalcommand,srcdummy);
            if (totalcommand>0){
                totalcommand --;
                totalundo++;
            }

        }
        else if (in == 'r'){
            CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q);
            POINT srcdummy;
            CreatePoint(&srcdummy,-50,-50);
            Redo(&SUndo,&SRedo,&currentState,totalundo, srcdummy);
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
        PrintPrioQueueTimeDelivery(currentState.sub3);
        printf("\n");

        printf("---------------------- STACK UNDO-----------------------------\n");
        displayStack(SUndo);
        printf("\n");

        printf("---------------------- STACK REDO-----------------------------\n");
        displayStack(SRedo);
        printf("\n");
        //printf("%d %c == %d %c\n", currentState.sub1.x, currentState.sub1.c, currentState.sub2.x, currentState.sub2.c);
    }
}*/
