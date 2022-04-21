#include "parser.h"
int parse_day_response(char * data){
    int i1;
    if (1 == sscanf(s,"%*[^0123456789]%d", &i1)){
        if(i1 == 1){
            return 1;
        }else{
            return 0;
        }
    }
} 

float * parse_ideal_params(char * data){

}
