#ifndef UTIL_H_
#define UTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SENDERIDX 18


int who(char *line);
int isNewMessage(char *line);
int countWords(FILE* fptr);
int countWordsLine(char* line);
void countOccurences(char *line);
int separator(int who);

#endif