#include "stack.c"

void initState(state * st){
    st->sub1.x = 1;
    st->sub2.x = 0;
    st->sub1.c = 'A';
    st->sub2.c = 'B';
}

int main(){
    Stack SUndo, SRedo;
    state currentState; 
    char in;

    CreateEmpty(&SRedo);
    CreateEmpty(&SUndo);

    initState(&currentState);
    int totalcommand=0;
    int totalundo = 0;

    while (true) { 
        printf("input = ");
        scanf("%c", &in);

        if (in == 'i'){
            Push(&SUndo, currentState);
            totalcommand ++;
            scanf("%d %c", &currentState.sub1.x, &currentState.sub1.c);
            scanf("%d %c", &currentState.sub2.x, &currentState.sub2.c);

        }
        else if (in == 'u'){
            Undo(&SUndo,&SRedo,&currentState,totalcommand);
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

        printf("%d %c == %d %c\n", currentState.sub1.x, currentState.sub1.c, currentState.sub2.x, currentState.sub2.c);
    }

    return 0;
}