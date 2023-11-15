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

int next_prime(int start){
    start ++;
    while (! isprime(start)){
        start++;
    }

    return start;
}

void decompose(int n){
    int prime = 2;
    while (n != 1){
        while (n % prime == 0){
            printf("%d ", prime);
            n /= prime;
        }   
        prime = next_prime(prime);
        
    }

    printf("\n");
}

void main(){
    int n;
    printf("entrez l'entier à décomposer: ");
    scanf("%d", &n);
    printf("la décomposition en nombre premiers de %d est: ",n);
    decompose(n);
}   