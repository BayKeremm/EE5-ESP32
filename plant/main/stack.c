#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

struct stack_element{
    void * element;
    stack_e * next;
};
struct stack{
    stack_e * head;
};

stack_t *  stack_init(){
    stack_t * stack;
    stack = malloc(sizeof(struct stack));
    stack->head = NULL;
    return stack;
}

void stack_free(stack_t ** stack){
    if(*stack == NULL){
        return;
    }
    stack_e * ptr,*tbfreed;
    ptr = (*stack)->head;
    while(ptr != NULL){
        tbfreed = ptr; 
        ptr = ptr->next;
        free(tbfreed);
    }
    free(*stack);
}

double stack_get_avgerage(stack_t * stack){
    double avg;
    return avg;
}

void stack_pop_bottom(stack_t * stack){

}

void stack_push_top(stack_t * stack, void * value){

}

int stack_size(stack_t * stack){

}
