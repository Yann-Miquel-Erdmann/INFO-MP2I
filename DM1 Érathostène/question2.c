#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool *eratosthene(int N){
    bool *t = malloc((N+1)*sizeof(bool));
    for (int i = 0; i<=N; i++){
        t[i] = true;
    }


    t[0] = false;
    t[1] = false;
    int i = 2;
    while(i<=N){
        if (t[i]){
            int j = 2;
            while( j* i <= N){
                t[j*i] = false;
                j++;
            }
        }
        
        i++;
    }

    return t;
} 


int main(){
    int nb;

    printf("Entrez le nombre jusqu'à où chercher: ");
    scanf("%d", &nb);
    bool *T = eratosthene(nb);
    for (int i = 0; i<=nb; i++){
        printf("%d\n", T[i]);
    }

    return 0;
}