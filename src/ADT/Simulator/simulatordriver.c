#include "simulator.c"
#include "../boolean.h"
//#include "../piroqueue/piroqueue.c"
#include "../Point/point.c"
#include "../MesinKata/wordmachine.c"
#include "../Stack/stack.c"
#include "../Time/time.c"
#include <stdio.h>

int main ()
{

    Simulator S;
    ReadSimulator(&S);
    DisplaySimulator(S);
    printf("\n");
    DisplayNama(S);
    printf("\n");
    DisplayLokasi(S);
    printf("\n");

}