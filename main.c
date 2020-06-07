#include "util.h"
#include "sort.h"
#include "emojitable.h"


/*
Statistics to collect:
    - Message per person, DONE!
    - Count number of messages over each day DONE!
    - Count occurences of words DONE!
    - Count occurences of emojis DONE!

*/ 

// struct Dictionary {
//     char word[];
//     int count;
// };

void writeMsgPerPerson(int msg_count[]);
void writeWordOccurences(char *dictionary[], int occurence[], int length);
void writeEmojiOccurences(struct Table table[], int length);
void writeMsgPerDay(int count[], int length);

// DD.MM.YY, hh:mm - Verena:
// DD.MM.YY, hh:mm - Adam ❤:
int main(){
    char filename[] = "data.txt";
    char tablename[] = "emoji_encodings.txt";

    FILE *file_ptr = fopen(tablename, "r");
    int table_length = 28;
    struct Table table[table_length];
    readTable(table, table_length, file_ptr);

    fclose(file_ptr);
    file_ptr = fopen(filename, "r");
    int buffer_length = 256;
    char buffer[buffer_length];
    char *buffer_ptr;

    int year_offset = 2018;
    int date_length = (2020-year_offset +1)*31*12;
    int date_array[date_length];
    memset(date_array, 0, date_length*sizeof(int));

    // safeguard for NULL pointer
    if(file_ptr == NULL){
        perror("Error: file could not be read.");
        exit(EXIT_FAILURE);
    }

    int word_count = countWords(file_ptr);
    rewind(file_ptr);
    printf("word count: %d\n", word_count);

    char *dictionary[word_count];
    int word_occurences[word_count];
    int dict_idx;
    int dict_tail = 0; // index of where new words are added
    memset(word_occurences, 0, word_count); // set array to 0

    int msg_count[2] = {0}; // messages per person

    int max_no_read = __INT_MAX__; // debugging
    int read_count = 0; // debugging
    int sender;
    int word_size = 32;
    char word[word_size];
    // read lines in file
    while(fgets(buffer, buffer_length, file_ptr) != NULL){
        buffer_ptr = buffer;
        if(isNewMessage(buffer_ptr) == 1){
            sender = who(buffer_ptr);   // who sent the message?
            msg_count[sender]++;        // count sent messages

            countDate(date_array, year_offset, buffer_ptr);

            buffer_ptr += separator(sender);
        }

        // read words on line
        while(*buffer_ptr != '\0' && *buffer_ptr != '\n'){
            readWord(&buffer_ptr, word, word_size);
            // printf("%s\n", word);
            if(isEmoji(word) < 0){
                // int b = 0;
                // printf("%s\n", word);
                findAndIncrement(table, table_length, word);
                // printf("%ld\n", sizeof(word)/sizeof(char));
            }else{
                // word
                dict_idx = newWord(dictionary, dict_tail, word);
                if(dict_idx == -1){
                    // new word
                    char *new_word;
                    new_word = (char*) malloc(sizeof(char)*word_size);
                    memcpy(new_word, word, word_size);
                    dictionary[dict_tail] = new_word;
                    word_occurences[dict_tail]++;
                    dict_tail++;
                }else{
                    // word found at index dict_idx
                    word_occurences[dict_idx]++;
                }

            }
        }

        // debugging
        read_count++;
        if(read_count > max_no_read){
            printf("Exiting...\n");
            break;
        }
    }

    fclose(file_ptr);

    // sort dictionary by occurences
    // mergeSort(word_occurences, dictionary,0, dict_tail-1);
    // printDict(dictionary, word_occurences, dict_tail);
    // printTable(table, table_length);
    // printIntArray(date_array, date_length);


    // // write to file
    writeMsgPerPerson(msg_count);
    writeWordOccurences(dictionary, word_occurences, dict_tail);
    writeEmojiOccurences(table, table_length);
    writeMsgPerDay(date_array, date_length);

    return 0;
}

void writeMsgPerPerson(int msg_count[]){
    FILE *file_ptr = fopen("msg_per_person.csv", "w");
    fprintf(file_ptr, "Verena,%d\n", msg_count[0]);
    fprintf(file_ptr, "Adam,%d\n", msg_count[1]);
    fclose(file_ptr);
}

void writeWordOccurences(char *dictionary[], int occurence[], int length){
    FILE *file_ptr = fopen("word_occurences.csv", "w");

    for(int i = 0; i < length; i++){
        fprintf(file_ptr, "%s,%d\n", dictionary[i], occurence[i]);
    }
    fclose(file_ptr);
}

void writeEmojiOccurences(struct Table table[], int length){
    FILE *file_ptr = fopen("emoji_occurences.csv", "w");

    for(int i = 0; i < length; i++){
        fprintf(file_ptr, "%s,%d\n", table[i].unicode, table[i].count);
    }

    fclose(file_ptr);
}


void writeMsgPerDay(int count[], int length){
    FILE *file_ptr = fopen("msg_per_day.csv", "w");
    fprintf(file_ptr, "#index,count\n");

    for(int i = 0; i < length; i++){
        fprintf(file_ptr, "%d,%d\n", i, count[i]);
    }
    fclose(file_ptr);
}



