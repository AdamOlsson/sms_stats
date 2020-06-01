#ifndef EMOJITABLE_H_
#define EMOJITABLE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct Table {
    int ascii[32];
    char unicode[16];
};

void readTable(struct Table table[], int table_length, FILE* fptr);
void printTable(struct Table table[], int table_length);

#endif