#include <stdio.h>
#include "list.h"
#include "log.h"

int main()
{
    List lst = {};

    listCtor(&lst);
    addToListFromHead(10, &lst);
    addToListFromHead(20, &lst);
    addToListFromHead(30, &lst);
    addToListFromHead(40, &lst);
    addToListFromHead(50, &lst);

    deleteElement(3, &lst);

    addToListBefore(4, 60, &lst);

    listDtor(&lst);
}
