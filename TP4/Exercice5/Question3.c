#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>


int * zeros_uns(int n, int m){
    int * t = malloc((n+m)*sizeof(int));
    for (int i = 0; i<n; i++){
        t[i] = 0;
    }
    for (int i = n; i<n+m; i++){
        t[i] = 1;
    }
    return t;
}


void main(){
    int * t1 = zeros_uns(5,5);
    for (int i = 0; i<5; i++){
        assert(t1[i] == 0);
    }
    for (int i = 5; i<10; i++){
        assert(t1[i] == 1);
    }
    free(t1);

    t1 = zeros_uns(0,10);
    for (int i = 0; i<0; i++){
        assert(t1[i] == 0);
    }
    for (int i = 0; i<10; i++){
        assert(t1[i] == 1);
    }
    free(t1);

    t1 = zeros_uns(10,0);
    for (int i = 0; i<10; i++){
        assert(t1[i] == 0);
    }
    for (int i = 10; i<10; i++){
        assert(t1[i] == 1);
    }
    free(t1);

    t1 = zeros_uns(0,0);
    for (int i = 0; i<0; i++){
        assert(t1[i] == 0);
    }
    for (int i = 0; i<0; i++){
        assert(t1[i] == 1);
    }
    free(t1);
}