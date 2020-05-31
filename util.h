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
void readWord(char ** buffer_ptr, char word[], int word_size);
int isEmoji(char *word);
int newWord(char * dictionary[], int dict_length, char* word);
int compareWords(char* word1, char* word2);
void printDict(char ** dictionary, int* occurences, int tail);



#endif