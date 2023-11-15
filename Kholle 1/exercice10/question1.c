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


void main(){
    int nb;
    printf("Entrez le nombre à tester: ");
    scanf("%d", &nb);

    if (isprime(nb)){
        printf("%d est premier\n", nb);
    }else{
        printf("%d n'est pas premier\n",nb);
    }
}