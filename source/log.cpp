#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"
#include "list.h"

void logInit(FILE * logFile, LogInfo * log)
{
    if (!logFile) {
        fprintf(stderr, "NULL PTR TO FILE\n");
        return;
    }

    log->logFile           = logFile;
    log->numberOfOperation = 0;

    fprintf(logFile, "<pre><span style=\"font-size: 16px\">\n\n");
}

void logDump(LogInfo * log, const char * func, List * list)
{
    char dotFile[sizeOfBuf] = {};
    char pngFile[sizeOfBuf] = {};

    snprintf(dotFile, sizeOfBuf, "log/%d.dot", log->numberOfOperation);
    snprintf(pngFile, sizeOfBuf, "log/%d.png", log->numberOfOperation);

    log->numberOfOperation++;

    fprintf(log->logFile, "Done %s\n\n", func);
    dump(list, dotFile);

    char cmd[sizeOfBuf] = "dot -Tpng -o ";
    strcat(cmd, pngFile);
    strcat(cmd, " ");
    strcat(cmd, dotFile);

    printf("%s\n", cmd);

    system(cmd);

    printf("1\n");

    fprintf(log->logFile, "<img src=\"%s\">\n", pngFile + 4);
}

void dump(List * list, char * pathToDot)
{
    FILE * dotFile = fopen(pathToDot, "w");
    if (!dotFile) return;
    fprintf(dotFile, "digraph G{\n\trankdir=LR;\n\tnode[shape=rect,style=rounded];\n\t");

    for (int i = 0; i < list->capacity; i++) {
        fprintf(dotFile, "id%d [shape=record,label=\"{ id:%d } | data:%d | next:%d | prev:%d }\"]\n\t", i, i, list->data[i].element, list->data[i].next, list->data[i].prev);
    }

    int c = 0;
    int next = list->data[c].next;
    for (int i = 0; i < list->actualSize; i++) {
        fprintf(dotFile, "id%d -> id%d;\n\t", c, next);
        c = next;
        next = list->data[c].next;
    }

    c = list->free;
    next = - list->data[c].next;
    for (int i = 1; i < list->capacity - list->actualSize; i++) {
        fprintf(dotFile, "id%d -> id%d;\n\t", c, next);
        c = next;
        next = - list->data[c].next;
    }

    fprintf(dotFile, "}\n");

    fclose(dotFile);
}

void logClose(LogInfo * log)
{
    fclose(log->logFile);
}

