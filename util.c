#include "util.h"


void printDict(char ** dictionary, int *occurences, int tail){
    for(int i = 0; i < tail; i++){
        printf("%s | %d \n", dictionary[i], occurences[i]);
    }
}

int newWord(char ** dictionary, int dict_length, char* word){
    // checks if the given word has been found before,
    // returns the index of where the word is stored
    // return -1 if the word is not found
    int char_idx = 0;
    for(int i = 0; i < dict_length; i++){
        if(NULL == dictionary[i]){
            return -1;
        }

        if(compareWords(word, dictionary[i]) == 1){
            // words are equal
            return i; // return index of word
        }
    }
    return -1;
}

int compareWords(char* word1, char* word2){
    // compare two words against each other
    // return 1 if equal, 0 otherwise
    // NOTE: Assumes that both words are null terminated
    int equal = 1;
    int char_idx = 0;
    while(1){
        if((word1[char_idx]) != word2[char_idx]){
            equal = 0;
            break;
        }else{
            if((word1[char_idx]) == '\0' && word2[char_idx] == '\0'){ // end of word
                break;
            }
            char_idx++;
        }
    }
    return equal;
}

int isEmoji(char* word){
    // evaluates if the giver char[] is an emoji
    // value > 0 is word
    // value < 0 is emoji
    // value == 0 you fucked
    int sum = 0;
    int idx = 0;
    char c = word[idx];
    while(c != '\0'){
        sum += c;
        c = word[++idx];
    }
    return sum;
}

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

void readWord(char ** buffer_ptr, char word[], int word_size){
    // Reads the next word from the buffer and increments the ptr
    // Emojis will be returned as word. Note sequences of emojies will
    // be returned as a single word.
    char *val;
    // keep track if char sequence starts with negative or positive val,
    // negative value is start of emoji sequence
    int is_word = **buffer_ptr < 0 ? -1 : 1;

    for(int i = 0; i < word_size; i++){
        val = *buffer_ptr;
        *buffer_ptr += 1;

        if(is_word * (*val) < 0 || *val == ' ' || *val == '\0' || *val == '\n'){ // end of word
            if(word[i-1] == '.' || word[i-1] == '!'|| word[i-1] == '?'|| word[i-1] == ','){
                word[i-1] = '\0';
            }else{
                word[i] = '\0';
            }
            return;
        }
        word[i] = tolower(*val);
    }
}

void countDate(int date_array[], int year_offset, char *word){
    char DD[3];
    char MM[3];
    char YY[3];
    char hh[3];
    char mm[3];
    int DDint, MMint, YYint, hhint, mmint;
    // 02.12.18, 22:41
    memcpy(DD, word, 2);
    memcpy(MM, word+3, 2);
    memcpy(YY, word+6, 2);
    memcpy(hh, word+10, 2);
    memcpy(mm, word+13, 2);
    DD[2] = '\0';
    MM[2] = '\0';
    YY[2] = '\0';
    hh[2] = '\0';
    mm[2] = '\0';
    // printf("%s.%s.%s %s:%s \n", YY, MM, DD, hh, mm);
    DDint = atoi(DD);
    MMint = atoi(MM);
    YYint = atoi(YY);
    hhint = atoi(hh);
    mmint = atoi(mm);
    // printf("%d.%d.%d %d:%d \n", YYint, MMint, DDint, hhint, mmint);
    // printf("%d\n", (DDint-1) + (MMint-1)*31 + (YYint-18)*31*12);
    date_array[(DDint-1) + (MMint-1)*31 + (YYint-18)*31*12]++;
}
