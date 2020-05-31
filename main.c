#include "util.h"
#include "sort.h"


/*
Statistics to collect:
    - Message per person, DONE!
    - Plot of number of messages over each day
    - Count occurences of words
    - Count occurences of emojis

*/ 

// struct Dictionary {
//     char word[];
//     int count;
// };

// DD.MM.YY, hh:mm - Verena:
// DD.MM.YY, hh:mm - Adam ❤:
int main(){

    char filename[] = "data.txt";

    FILE *file_ptr = fopen(filename, "r");
    int buffer_length = 256;
    char buffer[buffer_length];
    char *buffer_ptr;


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

            buffer_ptr += separator(sender);
        }

        // read words on line
        while(*buffer_ptr != '\0' && *buffer_ptr != '\n'){
            readWord(&buffer_ptr, word, word_size);
            if(isEmoji(word) < 0){
                // emoji
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

    mergeSort(word_occurences, dictionary,0, dict_tail-1);
    printDict(dictionary, word_occurences, dict_tail);


    // // write to file
    // file_ptr = fopen("statistics.txt", "w");
    // fprintf(file_ptr, "messages sent: %d (Verena) %d (Adam)", msg_count[0], msg_count[1]);
    // fclose(file_ptr);

    return 0;
}








