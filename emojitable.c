#include "emojitable.h"

void readTable(struct Table table[], int table_length, FILE* fptr){
    // Read the emoji table from file
    // ugly but does its work
    int buffer_length = 256;
    char buffer[buffer_length];
    int bidx = 0;
    int tidx = 0;
    char *line_ptr;

    while(fgets(buffer, buffer_length, fptr) != NULL){
        line_ptr = buffer;
        memset(table[tidx].ascii, 0, 32);
        if(line_ptr[7] == ':'){
            memcpy(table[tidx].unicode, line_ptr, 6);
            table[tidx].unicode[7] = '\0';
            line_ptr += 8;
            for(int i = 0; i < 4; i++){
                char dummy[16];
                memcpy(dummy, line_ptr, 8);
                dummy[8] = '\0';
                table[tidx].ascii[i] = (int)strtol(dummy, NULL, 16);
                line_ptr += 9;
            }
            tidx++;
        }else if(line_ptr[6] == ':'){
            memcpy(table[tidx].unicode, line_ptr, 5);
            table[tidx].unicode[6] = '\0';
            line_ptr += 7;
            for(int i = 0; i < 6; i++){
                char dummy[16];
                memcpy(dummy, line_ptr, 8);
                dummy[8] = '\0';
                table[tidx].ascii[i] = (int)strtol(dummy, NULL, 16);
                line_ptr += 9;
            }
            tidx++;
        }
        
        continue;
    }
}

void printTable(struct Table table[], int table_length){
    for(int i = 0; i < table_length; i++){
        printf("unicode: %s | ascii: ", table[i].unicode);
        for(int j = 0; j < 32; j++){
            if(table[i].ascii[j] == 0){
                printf("\n");
                break;
            }else{
                printf("%d ", table[i].ascii[j]);
            }
        }
    }
}