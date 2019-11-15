#include <stdio.h>
#include <stdlib.h>

#define MAX_MEM (2048 * 1024)
#define MIN_MEM 32
#define DEFAULT_MEM 2048

int isCorrectFormat(FILE* program, char* allowedChars);
int isPresent(char check, char* list);
int main(int argc, char** argv){
    if (!(argc == 2 || argc == 3)){
        printf("\nCan't do that! Specify the program file name as follows -\n\tbrainfuck <program-to-execute> [mem_size]\nPlease try again!\n");
        return 0;
    }

    char* allowedChars = "+-[]<>,.";

    FILE* program = fopen(argv[1], "r");
    int mem = DEFAULT_MEM;
    if (argc == 3){
        mem = atoi(argv[2]);
        if (mem > MAX_MEM || mem < MIN_MEM){
            mem = DEFAULT_MEM;
        }
    }
    if (!program){
        printf("\nUnable to open the given code!\n");
        return 0;
    }

    if (!isCorrectFormat(program, allowedChars)){
        printf("\nInvalid format!\n");
        return 0;
    }

    char* ptr = calloc(mem, sizeof(char));
    char read;
    int pos = 1;
    int status = 1;
    printf("\n");
    while ((read = fgetc(program)) != EOF && status){
        if (read == '\n'){
            continue;
        }
        switch (read){
            case '+':
                *ptr += 1;
                break;
            case '-':
                *ptr -= 1;
                break;
            case '<':
                ptr--;
                break;
            case '>':
                ptr++;
                break;
            case '.':
                putc(*ptr, stdout);
                break;
            case ',':
                *ptr = getc(stdout);
                break;
            case '[':
                if (*ptr == 0){
                    while ((read = fgetc(program)) != ']')
                        continue;
                }
                break;
            case ']':
                if (*ptr != 0){
                    fseek(program, -1, SEEK_CUR);
                    while (read != '['){
                        read = fgetc(program);
                        fseek(program, -2, SEEK_CUR);
                    }
                    fseek(program, 2, SEEK_CUR);
                }
                break;
            default:
                printf("Invalid code character '%c' at position - %d\n", read, pos);
                status = 0;
        }
        pos++;
    }
    printf("\n");
    return 0;
}

int isCorrectFormat(FILE* program, char* allowedChars){
    char read;
    while ((read = fgetc(program)) != EOF){
        if (!(isPresent(read, allowedChars) || read == '\n'))
            return 0;
    }
    fseek(program, 0, SEEK_SET);
    return 1;
}

int isPresent(char check, char* list){
    while (*list){
        if (*list == check)
            return 1;
        list++;
    }
    return 0;
}