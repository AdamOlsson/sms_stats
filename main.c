#include "util.h"


/*
Statistics to collect:
    - Message per person, DONE!
    - Plot of number of messages over each day
    - Count occurences of words
    - Count occurences of emojis

*/ 
void readWord(char ** buffer_ptr, char word[], int word_size);

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

    char *found_words[word_count];
    int word_occurences[word_count];
    memset(word_occurences, 0, word_count); // set array to 0

    int msg_count[2] = {0}; // messages per person

    int max_no_read = 4;//__INT_MAX__; // debugging
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
            // Do something
            printf("%s\n", word);
        }
        printf("-------------------\n");

        // debugging
        read_count++;
        if(read_count > max_no_read){
            printf("Exiting...");
            break;
        }
    }

    fclose(file_ptr);

    // // write to file
    // file_ptr = fopen("statistics.txt", "w");
    // fprintf(file_ptr, "messages sent: %d (Verena) %d (Adam)", msg_count[0], msg_count[1]);
    // fclose(file_ptr);

    return 0;
}

void readWord(char ** buffer_ptr, char word[], int word_size){
    // Reads the next word from the buffer and increments the ptr

    char *val;
    for(int i = 0; i < word_size; i++){
        val = *buffer_ptr;
        *buffer_ptr += 1;

        if(*val == ' ' || *val == '\0' || *val == '\n'){ // end of word
            word[i] = '\0';
            return;
        }
        word[i] = tolower(*val);
    }
}






