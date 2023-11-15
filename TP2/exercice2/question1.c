#include <stdio.h>
#include <stdbool.h>


void main(){
    bool a = true,b=true;
    bool and = a&&b;
    bool or = a||b;
    printf("%d %d\n", a,b);
    printf("and: %d , or: %d\n", and,or);
}