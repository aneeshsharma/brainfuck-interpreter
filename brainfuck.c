#include <stdio.h>
#include <stdlib.h>

#define MAX_MEM (2048 * 1024)
#define MIN_MEM 32
#define DEFAULT_MEM 2048

void display(char* array, int size, char* current);
void showProgram(FILE* program);
char* getProgram(FILE* program, char* allowedChars, int* length);
int contains(char check, char* allowed);

typedef struct Node {
    struct Node* next;
    int value;
} Node;

void push(Node** head, int data){
    Node* new = malloc(sizeof(Node));
    new->value = data;
    new->next = *head;
    *head = new;
}

int pop(Node** head){
    if (*head == NULL)
        return -1;
    Node* trash = *head;
    int res = trash->value;
    *head = (*head)->next;
    free(trash);
    return res;
}

int main(int argc, char** argv){
    if (!(argc == 2 || argc == 3)){
        printf("\nCan't do that! Specify the program file name as follows -\n\tbrainfuck <program-to-execute> [mem_size]\nPlease try again!\n");
        return 0;
    }

    char* allowedChars = "+-[]<>,.\0";

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
    int size, count;
    char* code = getProgram(program, allowedChars, &size);
    char read;
    Node* stack;
    int pos = 0;
    #ifdef DEBUG
        printf("\nSize : %d, Code: %s", size, code);
    #endif
    printf("\n");
    for (pos = 0; pos < size; pos++){
        read = code[pos];
        if (read == '\n') continue;
        #ifdef DEBUG
            printf("inst : %c | pos : %d | ", read, pos);
            display(base, 10, ptr);
        #endif
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
                #if defined(DEBUG) || defined(NUMBER)
                    printf("%d\n", *ptr);
                #else
                    putc(*ptr, stdout);
                #endif
                break;
            case ',':
                *ptr = getc(stdout);
                break;
            case '[':
                if (*ptr == 0){
                    count = 1;
                    while (count != 0){
                        pos++;
                        if (code[pos] == '[')
                            count++;
                        else if (code[pos] == ']')
                            count--;
                    }
                }
                else {
                    push(&stack, pos);
                }
                break;
            case ']':
                if (*ptr != 0){
                    pos = pop(&stack);
                    pos--;
                }
                else {
                    pop(&stack);
                }
                break;
        }
    }
    free(base);
    printf("\n");
    return 0;
}

char* getProgram(FILE* program, char* allowedChars, int* length){
    int size = 0;
    char read;
    while ((read = fgetc(program)) != EOF){
        if (contains(read, allowedChars)){
            size++;
        }
    }
        
    if (size == 0)
        return NULL;
    *length = size;
    char* res = calloc(size, sizeof(char));
    int i = 0;
    fseek(program, 0, SEEK_SET);
    while ((read = fgetc(program)) != EOF){
        if (contains(read, allowedChars)){
            res[i] = read;
            i++;
        }
    }
    return res;
}

int contains(char check, char* allowed){
    while (*allowed != '\0'){
        if (*allowed == check)
            return 1;
        allowed++;
    }
    return 0;
}

void showProgram(FILE* program){
    char str[100];
    fscanf(program, "%s", str);
    printf("%s\n", str);
}

void display(char* array, int size, char* current){
    printf("{");
    for(int i = 0; i < size - 1; i++){
        if (&array[i] == current)
            printf("|%d|, ", array[i]);
        else
            printf("%d, ", array[i]);
    }
    printf("%d}\n", array[size - 1]);
}