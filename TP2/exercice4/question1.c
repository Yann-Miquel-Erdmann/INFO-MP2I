#include <stdio.h>
#include <assert.h>

// calcule la factorielle de n lorsque n > 0 ou n == 0
int factorielle(int n){
    assert(n>=0);
    if (n==0){
        return 1;
    }else{
        return n * factorielle(n-1);
    }
}

void main(){
    int n;
    scanf("%d", &n);
    printf("%d\n", factorielle(n));
}
