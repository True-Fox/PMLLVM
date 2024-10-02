#include "../include/vm.h"
#include "../include/utils.h"

#include <string.h>

char* my_strdup(const char* s){
    char* result = malloc(strlen(s)+1);
    if(result!=NULL){
        strcpy(result, s);
    }
    return result;
}