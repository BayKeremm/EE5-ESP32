#ifndef STACK_H_
#define STACK_H_

typedef struct stack_ee5 stack_type;
typedef struct stack_element stack_e; 

void stack_free(stack_type ** stack);

stack_type * stack_init();

double stack_get_average(stack_type * stack);

void stack_pop_bottom(stack_type * stack);

void stack_push_top(stack_type * stack,void * value);

int stack_size(stack_type * stack);

#endif
