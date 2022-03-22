#include <stdio.h>
#include "stack.h"

int main(void){
    stack_type * stk = stack_init();
    double k = 10;
    int  c = 12;
    printf("%f",k+c);
    stack_push_top(stk,&c);
    stack_push_top(stk,&k);
    double avg = stack_get_average(stk);
    printf("avg is %f",avg);
    stack_free(&stk);
    return 0;
    
}
