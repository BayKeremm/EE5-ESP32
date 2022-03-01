#ifndef STACK_H_
#define STACK_H_

typedef struct stack stack_t;
typedef struct stack_element stack_e; 

void stack_free(stack_t ** stack);

stack_t * stack_init();

double stack_get_average(stack_t * stack);

void stack_pop_bottom(stack_t * stack);

void stack_push_top(stack_t * stack,void * value);

int stack_size(stack_t * stack);

#endif
