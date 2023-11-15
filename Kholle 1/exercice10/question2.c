#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool isprime(int nombre){
    if (nombre < 2){
        return false;
    }
    if (nombre  == 2){
        return true;
    }
    if (nombre % 2 == 0){
        return false;
    }

    int n = 3;
    float max_n = sqrt(nombre);
    while (n <= max_n){
        if (nombre % n == 0){
            return false;
        }
        n +=2 ;
    }
    return true;
}


int next_prime(int n){
    // invariant: start > n et start - 1 n'est pas premier
    int start = n+1;
    while (! isprime(start)){
        start++;
    }

    return start;
}

void main(){
    int n;
    printf("trouver le prochain nombre premier après N, entrez N: ");
    scanf("%d", &n);
    int next = next_prime(n);
    printf("Le prochain nombre premier après %d est: %d\n", n, next);
}   