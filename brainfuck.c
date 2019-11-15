#include <stdio.h>
#include <stdlib.h>

#define MAX_MEM (2048 * 1024)
#define MIN_MEM 32
#define DEFAULT_MEM 2048

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

    char* ptr = calloc(mem, sizeof(char));
    char* base = ptr;
    char read;
    int pos = 1;
    int status = 1;
    printf("\n");
    while ((read = fgetc(program)) != EOF && status){
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
        }
        pos++;
    }
    free(base);
    printf("\n");
    return 0;
}