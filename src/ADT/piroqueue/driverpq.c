#include "piroqueue.c"
#include "../Makanan/makanan.c"
#include "../Liststatik/liststatik.c"

void initMakanan(Makanan * m){
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

int main(){
    PrioQueueTime invent;

    MakeEmptyQueue(&invent, 4);

    Makanan m1, m2, m3;

    initMakanan(&m1);
    initMakanan(&m2);
    initMakanan(&m3);
    printf("debug1");

    Enqueue(&invent, m1);
    Enqueue(&invent, m2);
    
    PrintPrioQueueTime(invent);
    
    Enqueue(&invent, m3);

    printf("debug2");
    return 0;
}