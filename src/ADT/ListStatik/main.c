#include <stdio.h>
#include "liststatik.h"

int main() {

    ListStatik a;
    CreateListStatik(&a);
    Makanan uwa = {19, {"MyFood", 6}, {23, 21, 9}, {"MyAction", 8}, {23, 21, 9}};
    Makanan uwb = {19, {"MyFood", 6}, {23, 21, 9}, {"MyAction", 8}, {23, 21, 9}};
    Makanan trash;

    if (isEmpty(a)) {
        printf("This is empty\n");
    }

    insertFirst(&a, uwa);
    insertFirst(&a, uwb);
    printf("%d\n", listLength(a));
    deleteFirst(&a, &trash);
    printf("%d\n", listLength(a));

    return 0;
}