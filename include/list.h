#ifndef LIST_H
#define LIST_H

enum ListError {
    LST_NULL_PTR      = 1 << 1,
    LST_NULL_DATA_PTR = 1 << 2,
    LST_NO_ELEMENT    = 1 << 3,
    LST_OUT_OF_RANGE  = 1 << 4
};

typedef struct
{
    int numberOfOperation;
    FILE * logFile;
} LogInfo;

typedef int ListElem_t;

const int initialSize   = 10;
const ListElem_t poison = 0xDEAD;

typedef struct
{
    ListElem_t element;
    int next;
    int prev;
} ElementaryPartOfList;

typedef struct
{
    ElementaryPartOfList * data;

    size_t actualSize;
    size_t capacity;
    int free;
    ListError error;

    LogInfo * log;
} List;

ListError listCtor(List * list);

ListError listDtor(List * list);

ListError addToListFromHead(ListElem_t newElement, List * list);

ListError addToListFromTail(ListElem_t newElement, List * list);

ListError addToListAfter(int index, ListElem_t newElement, List * list);

ListError addToListBefore(int index, ListElem_t newElement, List * list);

ListError deleteElement(int index, List * list);

#endif // LIST_H
