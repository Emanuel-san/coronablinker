#include"date.h"
#include<stdio.h>

#define TEST_CASE(name) printf("RUNNING CASE: %s\n", name)
#define VERIFY(cond, msg)             \
    if (cond)                         \
        printf("SUCCESS: %s\n", msg); \
    else                              \
        printf("FAIL: %s\n", msg);

int main(void){
    date date1;

    
    return 0;
}