#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
//#include "config.h"

struct stack_element{
    void * value;
    stack_e * next;
};
struct stack_ee5{
    stack_e * head;
    stack_e * tail;
    void (*element_add)(void *sum, void *value);
};

stack_type *  stack_init(){
    stack_type * stack;
    stack = malloc(sizeof(struct stack_ee5));
    stack->head = NULL;
    stack->tail = NULL;
    return stack;
}

void stack_free(stack_type ** stack){
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

double stack_get_average(stack_type * stack){
    if(stack == NULL)return 0;
    float avg = 0;
    stack_e * ptr = stack->head;
    int size = 0;
    while(ptr != NULL){
        float * val = ptr->value;
        element_add(&avg,)
        ptr = ptr->next;
        size++;
    }
    return avg/size;
}

void stack_pop_bottom(stack_type * stack){
    stack_e * ptr = stack->head;
    stack->head = stack->head->next;
    free(ptr);
    return;

}

void stack_push_top(stack_type * stack, void * value){
    
    if(stack == NULL)return;
    stack_e * element = malloc(sizeof(struct stack_element));
    element->value = value;
    // empty stack insertion
    if(stack->head == NULL){
        stack->head=element;
        stack->tail = element;
    }
    // stack with element(s) insertion
    else{
        stack->tail->next = element;
        stack->tail = element;
    }
    if(stack_size(stack)>5)
    stack_pop_bottom(stack);
    return;

}

int stack_size(stack_type * stack){
    if(stack == NULL){
        return 0;
    }
    stack_e * ptr;
    ptr = stack->head;
    int size = 0;
    while(ptr != NULL){
        ptr = ptr->next;
        size++;
    }
    return size;
    

}
void stack_print(stack){
}
