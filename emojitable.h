#ifndef EMOJITABLE_H_
#define EMOJITABLE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct Table {
    int ascii[32];
    char unicode[16];
    int count;
};

void readTable(struct Table table[], int table_length, FILE* fptr);
void printTable(struct Table table[], int table_length);
void findAndIncrement(struct Table table[], int table_length, char * key);
int keylen(int key[]);
int cmp(int a1[], int a2[], int length);
void printIntArray(int *a, int length);

#endif