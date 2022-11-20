//#include "../MesinKata/wordmachine.c"
//#include"../Makanan/makanan.c"
//#include "../piroqueue/piroqueue.c"
//#include "../Matrix/matrix.c"
//#include "../Simulator/simulator.c"
#include "../../Main/parser.c"
#include "../Simulator/simulator.c"
#include "stack.c"
#include <stdio.h>


void initState(state * st, Simulator S, TIME T){
    st->sub1 = S;
    st->sub2 = T;
}

void initMakanan1(Makanan * m){
    m->id = 12; 
    m->delivery.DD = 1;
    m->delivery.HH = 1;
    m->delivery.MM = 1;
    m->expired.DD = 1;
    m->expired.HH = 2;
    m->expired.MM = 3;
    m->name.Length = 3;
    m->name.TabWord[0] = 'a';
    m->name.TabWord[1] = 'b';
    m->name.TabWord[2] = 'c';
    m->action.Length = 3;
    m->action.TabWord[0] = 'a';
    m->action.TabWord[1] = 'b';
    m->action.TabWord[2] = 'c';
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

void initMakanan3(Makanan * m){
    m->id = 8; 
    m->delivery.DD = 10;
    m->delivery.HH = 10;
    m->delivery.MM = 10;
    m->expired.DD = 10;
    m->expired.HH = 20;
    m->expired.MM = 30;
    m->name.Length = 3;
    m->name.TabWord[0] = 'd';
    m->name.TabWord[1] = 'e';
    m->name.TabWord[2] = 'f';
    m->action.Length = 3;
    m->action.TabWord[0] = 'd';
    m->action.TabWord[1] = 'e';
    m->action.TabWord[2] = 'f';
}

int main()
{
    boolean validAction;
    Stack SUndo, SRedo;
    Simulator S;
    state currentState;
    char in; 

    int redoaktif=0;

    ReadSimulator(&S);
    CreateEmpty(&SRedo);
    CreateEmpty(&SUndo);

    Makanan xyz,abc,def;
    initMakanan1(&abc);
    initMakanan2(&xyz);
    initMakanan3(&def);
    Makanan X;

    TIME T;
    
    printf("time : ");
    BacaTIME(&T);
    printf("\n");

    initState(&currentState,S,T);
    int totalcommand=0;
    int totalundo = 0;

    boolean found = true;


    while (found){ 
        printf("---------------------- MULAI-----------------------------\n");
        printf("input = ");
        scanf(" %c", &in);
        int gabisaredo = 0;
        if (in == 'b'){//enqueue
            printf("sampe a\n");
            CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q,currentState.sub1.D,currentState.sub1.PL);
            printf("sampe b\n");
            Push(&SUndo, currentState);
            totalcommand ++;
            gabisaredo ++;
            CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q,currentState.sub1.D,currentState.sub1.PL);
            printf("sampe c\n");
            EnqueueInventory(&currentState.sub1.Q, xyz); // misal ini bawang
            validAction = true;
             printf("sampe d\n");

        }
        else if (in == 'c'){//dequeueAt terus Enqueue
            printf("sampe a\n");
            CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q,currentState.sub1.D,currentState.sub1.PL);
            Push(&SUndo, currentState);
            totalcommand ++;
            gabisaredo ++;
            printf("sampe b\n");
            CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q,currentState.sub1.D,currentState.sub1.PL);
            DequeueAt(&currentState.sub1.Q,xyz,&X);
            EnqueueInventory(&currentState.sub1.Q,def);
            printf("sampe c\n");
            validAction = true;
        }
        else if (in=='g'){//geser
            CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q,currentState.sub1.D,currentState.sub1.PL);
            Push(&SUndo, currentState);
            totalcommand ++;
            gabisaredo ++;
            CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q,currentState.sub1.D,currentState.sub1.PL);
            GeserLokasi(&currentState.sub1,2);
            validAction = true;
        }
        else if (in == 'u'){//undo
            CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q,currentState.sub1.D,currentState.sub1.PL);
            POINT srcdummy;
            CreatePoint(&srcdummy,-50,-50);
            Undo(&SUndo,&SRedo,&currentState,totalcommand,srcdummy);
            if (totalcommand>0){
                totalcommand --;
                totalundo++;
                redoaktif ++;
            }
            validAction = false;

        }
        else if (in == 'r'){//redo
            CreateSimulatorUndo(&currentState.sub1,currentState.sub1.Nama,currentState.sub1.P,currentState.sub1.Q,currentState.sub1.D,currentState.sub1.PL);
            POINT srcdummy;
            CreatePoint(&srcdummy,-50,-50);
            Redo(&SUndo,&SRedo,&currentState,totalundo, srcdummy);
            if (totalundo>0){
                totalcommand++;
                totalundo--;
                redoaktif--;
            }
            validAction = false;
        }
        else {
            found = false;
        }
        
        if (gabisaredo>0 && redoaktif!=0){
            for(int i = 0;i<redoaktif;i++){
                state X;
                Pop(&SRedo,&X);
            }
            
        }
        if (validAction){
            // Waktu hanya ditambahkan bila action yang dilakukan valid
            currentState.sub2 = NextMinute(currentState.sub2);
            
            // Mengurangi waktu di delivery list dan inventory
            decrementNDel(&currentState.sub1.D, 1);
            decrementNExp(&Inventory(currentState.sub1), 1);
        }

        DisplaySimulator(currentState.sub1);
        printf("\n");
        DisplayInventory(currentState.sub1);
        printf("\n");
        TulisTIME(currentState.sub2);
        printf("\n");
        PrintPrioQueueTimeDelivery(currentState.sub1.Q);
        printf("\n");

    }
    

}
