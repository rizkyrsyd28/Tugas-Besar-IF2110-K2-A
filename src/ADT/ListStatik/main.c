#include <stdio.h>
#include "liststatik.c"

int main() {

    ListStatik a;
    CreateListStatik(&a);
    Makanan uwa = {19, {"MyFood", 6}, {23, 21, 9}, {"MyAction", 8}, {1,1}, {23, 21, 9}};

    if (isEmpty(a)) {
        printf("This is empty\n");
    }

    insertFirst(&a, uwa);
    printf("%d\n", listLength(a));

    return 0;
}