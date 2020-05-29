#include "util.h"


// void countOccurences(char *line){
//     // returns a list of hash values for each respective word in the line.
//     // TODO: Handle emojis
//     printf("new message\n");
//     char buffer[16];
//     int bidx = 0;
//     int idx  = 0;
//     unsigned long hs;
//     while(line[idx] != '\0'){
//         // printf("%d\n", line[idx]);
//         if(line[idx] == ' '){
//             buffer[bidx] = '\0';
//             printf("word: %s\n", buffer);
//             bidx = 0;
//         }else{
//             buffer[bidx] = tolower(line[idx]); // copy value into buffer
//             bidx++;
//         }
//         idx++;
//     }
// }
// 


int countWords(FILE* fptr){
    // Counts the number of words in the the file
    int buffer_length = 256;
    char line[buffer_length];
    char *line_ptr;
    int sender;
    int count = 0;
    while(fgets(line, buffer_length, fptr) != NULL){
        line_ptr = line;
        if(isNewMessage(line_ptr) == 1){
            sender = who(line_ptr);        // who sent the message?            
            line_ptr += separator(sender); // separate timestamp from message
        }

        if(line_ptr[0] == '<'){ // do not count <message deleted>
            continue;
        }else{
            count += countWordsLine(line_ptr);
        }
    }
    return count;
}

int countWordsLine(char* line){
    int idx  = 0;
    int count = 0;
    int isEmoji = 1; // bool to check if a word is an emoji 
    while(line[idx] != '\0'){
        if(line[idx] == ' ' || line[idx] == '\n'){
            if(isEmoji == 0){
                count++;
                isEmoji = 1;
            }
        }else{
            // if a real character is found we count it as a word
            if(line[idx] >= 0){
                isEmoji = 0;
            }
        }
        idx++;
    }
    return count;
}

int separator(int who){
    // returns the index of the first char of the message. To separate timestamp.
    return 26 + who*2;
}

int who(char *line){
    // Who send the message? 0 == Verena, 1 == Adam
    if (line[SENDERIDX] - 'V' == 0){
        return 0;
    }else{
        return 1;
    }
}

int isNewMessage(char *line){
    // Is the newly read line a new message?
    // We do pattern matching for this: DD.MM.YY, hh:mm - Adam ❤:
    if(line[2] - '.' == 0 && line[5] - '.' == 0 && line[8] - ',' == 0 && line[12] - ':' == 0 && line[16] - '-' == 0){
        return 1;
    } else {
        return 0;
    }
}