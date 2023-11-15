#include <stdio.h>
#include <assert.h>
#include <stdbool.h>



bool egaux(int * t1,int* t2, int n){
    for (int i = 0; i<n; i++){
        if (t1[i] != t2[i]){
            return false;
        }
    }
    return true;
}


void main(){
    int test1[5] = {0,1,2,3,4};
    int test2[5] = {0,1,2,3,4};
    int test3[5] = {0,1,2,3,5};
    int test4[5] = {-1,1,2,3,5};
    int test5[5] = {0,-1,-2,-3,-4};
    int test6[5] = {0,-1,-2,-3,-4};

    assert(egaux(test1,test2, 5));
    assert(egaux(test1,test3, 5) == false);
    assert(egaux(test1,test4, 5) == false);
    assert(egaux(test5,test6, 5));
}