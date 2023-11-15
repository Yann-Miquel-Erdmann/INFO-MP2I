#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>


int * zeros(int n){
    int * t = malloc(n*sizeof(int));
    for (int i = 0; i<n; i++){
        t[i] = 0;
    }
    return t;
}


void main(){
    int * t1 = zeros(5);
    for (int i = 0; i<5; i++){
        assert(t1[i] == 0);
    }
    free(t1);

    t1 = zeros(10);
    for (int i = 0; i<10; i++){
        assert(t1[i] == 0);
    }
    free(t1);

    t1 = zeros(0);
    for (int i = 0; i<0; i++){
        assert(t1[i] == 0);
    }
    free(t1);

    t1 = zeros(1);
    for (int i = 0; i<1; i++){
        assert(t1[i] == 0);
    }
    free(t1);
}