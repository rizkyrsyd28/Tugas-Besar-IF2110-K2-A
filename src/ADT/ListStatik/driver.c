#include <stdio.h>
#include "liststatik.c"

int main() {

    ListStatik a;
    CreateListStatik(&a);
    Makanan uwa = {19, {"MyFood", 6}, {23, 21, 9}, {"MyAction", 8}, {2, 2}, {23, 21, 9}};
    Makanan uwb = {19, {"MyFood", 6}, {23, 21, 9}, {"MyAction", 8}, {3, 3}, {23, 21, 9}};
    Makanan trash;

    if (isEmpty(a)) {
        printf("This is empty\n");
    }

    insertFirst(&a, uwa);
    insertLast(&a, uwb);
    insertAt(&a, uwb, 1);
    printf("%d\n", listLength(a));
    deleteFirst(&a, &trash);
    printf("%d\n", listLength(a));
    deleteAt(&a, &trash, 0);
    printf("%d\n", listLength(a));

    return 0;
}