#include <stdio.h>
#include <string.h>

#define STACK_SIZE 100

int get_precedence(char);
void infix_to_postfix(char *, char *);

char stack[STACK_SIZE];
int top = -1;

int get_precedence(char c) {
    switch (c) {
        case '^': return 3;
        case '/':
        case '*': return 2;
        case '+':
        case '-': return 1;
    }
    return -1;
}

void push(char c) {
    if (top == STACK_SIZE - 1 ) {
        printf("Stack is full\n");
        return;
    }
    stack[++top] = c;
}

char pop() {
    if (top == -1) {
        printf("Stack is empty\n");
    }
    else {
        return stack[top--];
    }
}

char peek() {
    if ( top == -1){
        printf("Stack is empty\n");
    }
    return stack[top];
}

int is_empty() {
    return top == -1;
}

void infix_to_postfix(char *arr, char *postfix) {
    char c;
    while(*arr != '\0') {
        c = *arr++;
        if (c == '(') {
            push(c);
        }
        else if (c == ')') {
            while( (c = pop(c)) != '('){
                *postfix++ = c;
            }
        }
        else if (get_precedence(c) == -1) {
            *postfix++ = c;
        }
        else {
            while (!is_empty() && get_precedence(c) <= get_precedence(peek())){
                *postfix++ = pop();
            }
            push(c);
        }
    }
    while(!is_empty()) {
        printf("ok2\n");
        *postfix++ = pop();
    }
}

void main() {
    // (A+(B-C)*D)^E+F, A+B/C*(D-A)^F^H, A*B+C*D
    
    char arr[STACK_SIZE];
    char postfix[STACK_SIZE];
    printf("Input the infix expression: ");
    scanf("%s", arr);
    printf("Entered expression: %s\n", arr);
    infix_to_postfix(arr, postfix);
    printf("Postfix: %s\n", postfix);
}