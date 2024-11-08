#include <stdio.h>
#include "list.h"
#include "log.h"
#include <stdlib.h>

ListError listCtor(List * list)
{
    if (!list) return LST_NULL_PTR;

    list->log = (LogInfo *)calloc(1, sizeof(LogInfo));
    logInit(fopen("log/log.htm", "w"), list->log);

    printf("%p\n", list->log->logFile);

    list->data = (ElementaryPartOfList *)calloc(initialSize, sizeof(ElementaryPartOfList));
    if (!(list->data)) {
        fprintf(stderr, "Couldn't create data array\n");
        list->error = LST_NULL_DATA_PTR;
        return LST_NULL_DATA_PTR;
    }

    list->data[0].element = poison;
    list->capacity        = initialSize;
    list->data[0].next    = 0;
    list->data[0].prev    = 0;
    list->free            = 1;
    list->actualSize      = 1;

    for (int i = 1; i < initialSize; i++) {
        list->data[i].next = - (i + 1);
        list->data[i].prev = - 1;
    }

    DO_LOG_DUMP(list->log, list);
    printf("%p\n", list->log->logFile);

    return LST_NORMAL;
}

ListError listDtor(List * list)
{
    if (!list) return LST_NULL_PTR;

    free(list->data);
    free(list->log);

    return LST_NORMAL;
}

// FIXME: add
ListError listVerifier(List * list)
{
    if (!list) return LST_NULL_PTR;
    if (!list->data) return LST_NULL_DATA_PTR;

    return LST_NORMAL;
}

ListError addToListFromTail(ListElem_t newElement, List * list)
{
    if (listVerifier(list) != LST_NORMAL) return listVerifier(list);

    int free = list->free;
    int nextFree = - (list->data[free].next);
    int tempTail = list->data[0].prev;

    list->data[tempTail].next = free;
    list->data[free].next     = 0;
    list->data[free].element  = newElement;
    list->data[free].prev     = tempTail;
    list->data[0].prev        = free;

    list->free = nextFree;

    list->actualSize++;

    DO_LOG_DUMP(list->log, list);

    return LST_NORMAL;
}

ListError addToListFromHead(ListElem_t newElement, List * list)
{
    if (listVerifier(list) != LST_NORMAL) return listVerifier(list);

    int free = list->free;
    int nextFree = - (list->data[free].next);
    int tempHead = list->data[0].next;

    list->data[tempHead].prev = free;
    list->data[free].next     = tempHead;
    list->data[free].element  = newElement;
    list->data[free].prev     = 0;
    list->data[0].next        = free;

    list->free                = nextFree;

    list->actualSize++;

    DO_LOG_DUMP(list->log, list);

    return LST_NORMAL;
}

ListError addToListBefore(int index, ListElem_t newElement, List * list)
{
    if (listVerifier(list) != LST_NORMAL) return listVerifier(list);

    int free = list->free;
    int nextFree = - (list->data[free].next);

    list->data[list->data[index].prev].next = free;
    list->data[free].prev     = list->data[index].prev;
    list->data[index].prev    = free;
    list->data[free].next     = index;
    list->data[free].element  = newElement;

    list->free                = nextFree;

    list->actualSize++;

    DO_LOG_DUMP(list->log, list);

    return LST_NORMAL;
}

ListError addToListAfter(int index, ListElem_t newElement, List * list)
{
    if (listVerifier(list) != LST_NORMAL) return listVerifier(list);

    int free = list->free;
    int nextFree = - (list->data[free].next);

    list->data[list->data[index].next].prev = free;
    list->data[free].next     = list->data[index].next;
    list->data[index].next    = free;
    list->data[free].element  = newElement;
    list->data[free].prev     = index;

    list->free                = nextFree;

    list->actualSize++;

    DO_LOG_DUMP(list->log, list);

    return LST_NORMAL;
}



ListError deleteElement(int index, List * list)
{
    if (listVerifier(list) != LST_NORMAL) return listVerifier(list);

    if (index >= list->capacity) {
        fprintf(stderr, "Index out of range\n");
        return LST_OUT_OF_RANGE;
    }
    if (list->data[index].prev == -1) {
        fprintf(stderr, "No element on this index\n");
        return LST_NO_ELEMENT;
    }

    list->data[list->data[index].prev].next = list->data[index].next;
    list->data[list->data[index].next].prev = list->data[index].prev;

    list->data[index].element *= (-1);
    list->data[index].next     = -list->free;
    list->data[index].prev     = -1;

    list->free                 = index;
    list->actualSize--;

    DO_LOG_DUMP(list->log, list);

    return LST_NORMAL;
}

/*void dump(List * list)
{
    int c = list->data[0].next;
    for (int i = 1; i < list->actualSize; i++) {
        printf("%d\n", list->data[c].element);
        c = list->data[c].next;
    }
}*/

