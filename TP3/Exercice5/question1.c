#include <stdio.h>
#include <assert.h>

void echanger(float *pa, float *pb){
    float temp = *pa;
    *pa = *pb;
    *pb = temp;
}

void incrementer(int *p){
    assert(p != NULL);
    *p = *p +1;
}

int main(){
    int x = 3;
    printf("Avant: %d\n", x);
    incrementer(&x);
    printf("Après: %d\n", x);


    float x = 0.5,y=0.9;
    printf("Avant: x=%f, y=%f\n", x,y);
    echanger(&x,&y);
    printf("Après: x=%f, y=%f\n", x,y);
    
    return 0;
}