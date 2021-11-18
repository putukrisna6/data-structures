#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct stackNode_t {
    char data;
    struct stackNode_t *next;
} StackNode;

typedef struct stack_t {
    StackNode *_top;
    unsigned _size;
} Stack;

bool stack_isEmpty(Stack *stack) {
    return (stack->_top == NULL);
}

void stack_push(Stack *stack, char value) {
    StackNode *newNode = (StackNode*) malloc(sizeof(StackNode));
    if (newNode) {
        stack->_size++;
        newNode->data = value;
        
        if (stack_isEmpty(stack)) newNode->next = NULL;
        else newNode->next = stack->_top;

        stack->_top = newNode;
    }
}

void stack_pop(Stack *stack) {
    if (!stack_isEmpty(stack)) {
        StackNode *temp = stack->_top;
        stack->_top = stack->_top->next;
        free(temp);
        stack->_size--;
    }
}

char stack_peek(Stack *stack) {
    if (!stack_isEmpty(stack)) 
        return stack->_top->data;
    return 0;
}

unsigned stack_size(Stack *stack) {
    return stack->_size;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        Stack myStack;
        myStack._size = 0;
        myStack._top = NULL;

        char s[1000];
        scanf("%s", s);

        unsigned int len = strlen(s);
        bool flag = false;

        for (int j = 0; j < len; j++) {
            if (s[j] == '{' || s[j] == '(' || s[j] == '[') {
                stack_push(&myStack, s[j]);
            } 
            else {
                if (s[j] == '}') {
                    if (stack_peek(&myStack) == '{') {
                        stack_pop(&myStack);
                    }
                    else {
                        flag = true;
                        break;
                    }
                }
                else if (s[j] == ')') {
                    if (stack_peek(&myStack) == '(') {
                        stack_pop(&myStack);
                    }
                    else {
                        flag = true;
                        break;
                    }
                }
                else if (s[j] == ']') {
                    if (stack_peek(&myStack) == '[') {
                        stack_pop(&myStack);
                    }
                    else {
                        flag = true;
                        break;
                    }
                }
            }
        }

        if (!flag && stack_isEmpty(&myStack)) {
            puts("YES");
        } 
        else {
            puts("NO");
        }
    }

    return 0;
}
