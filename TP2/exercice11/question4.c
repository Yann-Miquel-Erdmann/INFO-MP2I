#include <stdio.h>

// calcule le terme suivant de x dans la suite de Syracuse  
long int suivant(long int x){
    if (x%2 == 1){
        return 3*x+1;
    }else{
        return x/2;
    }
}

// calcule le n eme terme dans la suite de syracuse en partant de x
long int temps_de_vol(long int x){
    long int n = 0;
    while (x!=1){
        x = suivant(x);
        n++;
    }
    return n;
}

long int plus_long_vol(long int N){
    long int max = 0;
    long int max_N = 1;
    long int temp;
    for(long int i=1; i<=N;i++){
        temp = temps_de_vol(i);
        if (temp> max){
            max = temp;
            max_N = i;
        }
    }
    return max_N;
}

void main(){
    printf("%ld\n", plus_long_vol(10));
    printf("%ld\n", plus_long_vol(100));
    printf("%ld\n", plus_long_vol(1000));
    printf("%ld\n", plus_long_vol(10000));
    printf("%ld\n", plus_long_vol(100000));
    printf("%ld\n", plus_long_vol(1000000));
    printf("%ld\n", plus_long_vol(10000000));
}