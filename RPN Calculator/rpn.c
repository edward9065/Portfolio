#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

//struct representing a vector
typedef struct {
    int size;
    int capacity;
    int* array; 
} vector;

//initializes the stack as a vector, with capacity as parameter.
vector stackInit(int capacity) {
    vector stack;
    stack.size = 0; //points to next empty spot
    stack.capacity = capacity;
    stack.array = calloc(capacity, sizeof(int));
    return stack; //stack is pointer to array, free this later
}

//expands the vector by a factor of two. Note: this does not zero out the extra memory.
void expand(vector* list) {
    list -> capacity = (list -> capacity)*2;
    list -> array = realloc(list -> array, (list -> capacity) * sizeof(int));
    //careful, not calloced.
}

//Prints the vector out to stdout. Code originally created by Professor Tychonievich, slightly modified by me.
void printArray(vector list){
    char b4='[';
    for(int i=0; i<list.size; i+=1) { printf("%c %d", b4, list.array[i]); b4=','; }
    puts(" ]");
}

//Adds value to the end of the vector and prints the state of the vector.
void push(vector* list, int num) {
    int size = list -> size;
    int capacity = list -> capacity;

    if(size >= capacity) expand(list);

    list -> array[size] = num;
    list -> size++; 
    printArray(*list);
}

//Removes value from the end of the vector and returns it.
int pop(vector* list) {
    int size = list -> size;
    int capacity = list -> capacity;

    list -> size--;
    if(!size) exit(0); //exits program if no ints can be popped
    else return list -> array[size-1];
}

/* Parses the string given.
- When encountering integers, it pushes them to the stack
- When encountering operations, pops two ints from the stack and performs the operation on them.
- If it encounters anything else, ends the program.
*/
void parse(vector *list, const char *buffer) {
    char* str = strdup(buffer);
    //free the original pointer once complete
    char* freeMe = str;

    char* token; 
    char** endptr;

    int first, second, x;
    //seperate the tokens by spaces, then determine what kind of token it is and do appropriate action
    do {
        token = strsep(&str, " \n");

        if(!(strcmp(token, "+"))) {
            x = pop(list) + pop(list);
            push(list, x);
        }
        else if(!(strcmp(token, "-"))) {
            second = pop(list); 
            first = pop(list);
            x = first - second;
            push(list, x);
        }
        else if(!(strcmp(token, "*"))) {
            x = pop(list) * pop(list);
            push(list, x);
        }
        else if(!(strcmp(token, "/"))) {
            second = pop(list); 
            first = pop(list);
            x = first / second;
            push(list, x);
        }
        else if(strcmp(token, "")) { //not an empty string 
            //it's not an operation and not an integer, exit the program.
            if( (token[0]!=45 || (token[1] < 48 || token[1] > 57)) &&  (token[0] < 48 || token[0] > 57)) {
                exit(0);
                //stop the program
            }
            //it's an integer, push it to the stack.
            else{
            int num = atoi(token);
            push(list, num);   
            }
        }
    } while(str);

    free(freeMe);
}

// void resizeBuffer

int main() {    
    vector stack = stackInit(10);
    long size = 10;
    long oriSize = size;

    char* buffer = calloc(size, sizeof(char));
    int nextChar;
    int count = 1;
    int boole = 0;

    while( (nextChar = fgetc(stdin)) != EOF) {
        
        //the next character is a newline
        if(nextChar == 10) {
            parse(&stack, buffer);
            size  = oriSize;
            count = 1;
            buffer = realloc(buffer, size);
            memset(buffer, 0, size);
            boole = 1;
        }
        else {
            boole = 0;
            count++;
            if(count >= size) {
                size *= 2;
                buffer = realloc(buffer, size);
                //printf("size: %ld", size);
            }
            char symbol[2];
            symbol[0] = nextChar;
            symbol[1] = '\0';
            buffer = strncat(buffer, symbol, 1);       

        }
    }
    if(!boole) {
        parse(&stack, buffer);
    }
  
    free(buffer);

    return 0;
}