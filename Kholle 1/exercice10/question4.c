#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

bool isprime(int nombre){
    assert(nombre>0);
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
    assert(n>0);
    if (n == 1){
        printf("1");
    }
    int prime = 2;
    int large_counter = 0;
    int counter;
    while (n != 1){
        counter = 0;
        while (n % prime == 0){
            n /= prime;
            counter++;
        }   
        if (counter != 0){

            if (large_counter){
                printf(" . ");
            }

            printf("%d^%d", prime, counter);

            large_counter++;
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