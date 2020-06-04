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
        table[tidx].count = 0;
        if(line_ptr[7] == ':'){
            memcpy(table[tidx].unicode, line_ptr, 7);
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
            memcpy(table[tidx].unicode, line_ptr, 6);
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
                printf("| count: %d\n",table[i].count);
                break;
            }else{
                printf("%d ", table[i].ascii[j]);
            }
        }
    }
}

void findAndIncrement(struct Table table[], int table_length, char * seq){
    // find the key in the table and return the index
    // return -1 if key not found
    // printf("%s\n",key);

    int seq_length = strlen(seq);
    int seq_start = 0;
    int seq_offset = 0;
    int key_length;

    // printf("New emoji sequence: %s, len(%d)\n", seq, seq_length);
    for(int i = 0; i < table_length; i++){

        // sliding window of table key on key
        key_length = keylen(table[i].ascii);

        if(key_length > seq_length){
            // printf("Table key len(%d) longer than seq len(%d), continuing...\n", key_length, seq_length);
            continue;
        }
        char window_tmp[key_length];
        int window[key_length];

        for(int j = 0; j < seq_length-key_length +1; j++){
            memcpy(window_tmp, seq + (seq_start + seq_offset), key_length);
            
            //stupid
            for(int k = 0; k < key_length; k++){
                window[k] = (int)window_tmp[k];
            }

            if(cmp(table[i].ascii, window, key_length) == 0){
                // strings are equal!
                // continue with rest of seq
                seq_start += key_length;
                seq_offset = 0;
                // increment counter in table
                table[i].count++;
            }else{
                seq_offset++;
            }
            if(seq_start + seq_offset >= seq_length){
                break;
            }

        }

        if(seq_start >= seq_length){
            // printf("Search done.");
            break;
        }
        // next table key
        seq_offset = 0;
    }
}

int keylen(int key[]){
    int count = 0;
    while(key[count] != 0){
        count++;
    }
    return count;
}

int cmp(int a1[], int a2[], int length){
    for(int i = 0; i < length; i++){
        if(a1[i] - a2[i] != 0){
            return -1;
        }
    }
    return 0;
}

void printIntArray(int *a, int length){
    printf("[ ");
    for(int i = 0; i < length; i++){
        printf("%x ", a[i]);
    }
    printf("]\n");
}