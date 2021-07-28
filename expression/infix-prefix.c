#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STACK_SIZE 100

struct Stack {
    char *arr;
    int top;
    unsigned int cap;
};

// create stack function
struct Stack *create_stack(unsigned int cap) {
    struct Stack *stack = (struct Stack *) malloc(sizeof(struct Stack));
    if (!stack) {
        return NULL;
    }
    stack->top = -1;
    stack->cap = cap;
    stack->arr = (char *) malloc(cap * sizeof(char));
    if(!stack->arr) {
        return NULL;
    }
    return stack;
}

// stack operation

void push(struct Stack *stack, char val) {
    if (stack->top == stack->cap -1) {
        printf("Stack is full\n");
    }
    else {
        *(stack->arr + ++stack->top) = val;
    }
}

char pop(struct Stack *stack) {
    if(stack->top == -1) {
        printf("Stack is empty\n");
    }
    else {
        return *(stack->arr + stack->top--);
    }
}

char peek(struct Stack *stack) {
    if (stack->top == -1) {
        printf("Stack is empty");
    }
    else {
        return *(stack->arr + stack->top);
    }
}

int is_empty(struct Stack *stack) {
    if(stack->top == -1) {
        return 1;
    }
    return 0;
}

void display(struct Stack *stack) {
    int i=0;
    if (stack->top == -1) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack Elements:\n");
    while(i <= stack->top) {
        printf("%c\n", *(stack->arr + i++));
    }
}

int get_precedence(char c) {
    switch (c) {
        case '+':
        case '-': return 1;
        case '/':
        case '*': return 2;
        case '^': return 3;
    }
    return -1;
}

void strrev(char *s) {
    char c;
    int i = 0, j = 0;
    while(*(s + j) != '\0') {
        j++;
    }
    printf("length of %s -> %i\n", s, j);
    j -= 1;
    while ( i < j) {
        c = *(s+i);
        *(s+i++) = *(s+j);
        *(s+j--) = c;  
    }
}

char *infix_to_prefix(char *exp) {
    char c;
    int i = 0, j = 0;
    struct Stack *stack = create_stack(strlen(exp));
    strrev(exp);
    printf("%s\n", exp);
    while((c = exp[i++]) != '\0') {
        if (c == ')') {
            push(stack, c);
        }
        else if (c == '(') {
            while((c = pop(stack)) != ')') {
                exp[j++] = c;
            }
        }
        else if (get_precedence(c) == -1) {
            exp[j++] = c;
        }
        else {
            while(!is_empty(stack) && get_precedence(c) <= get_precedence(peek(stack))) {
                exp[j++] = pop(stack);
            }
            push(stack, c);
        }
    }
    while(!is_empty(stack)) {
        exp[j++] = pop(stack);
    }
    exp[j++] = '\0';
    strrev(exp);
    printf("prefix expression: %s\n", exp);
}

void main() {
    // (A+(B-C)*D)^E+F, A+B/C*(D-A)^F^H, A*B+C*D
    char arr[STACK_SIZE];
    printf("Enter the infix expression: ");
    scanf("%s", arr);
    printf("Entered infix expression: %s\n", arr);
    infix_to_prefix(arr);
}