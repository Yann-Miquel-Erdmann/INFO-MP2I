#include <stdio.h>
#include <time.h>


long int limite_N = 10000000;
long int liste[10000000] = {0}; // l'allocation de mémoire n'est pas dynamique
long int N;
long int plus_long_vol();



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

    if (x <= N){
        if(liste[x-1]>=0){
            return liste[x-1];

        }
    }

    long int rep = 1 + temps_de_vol(suivant(x));
    
    if (x <= N){
        liste[x-1] = rep;
    }

    return rep;
    
    
}

// trouve le plus long vol entre 1 et k
long int plus_long_vol(long int k){
    N = k;

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

    // initialisation de la liste
    for(long int i = 1; i<limite_N;i++){
        liste[i] = -1;
    }

    printf("%ld\n", plus_long_vol(10));
    printf("%ld\n", plus_long_vol(100));
    printf("%ld\n", plus_long_vol(1000));
    printf("%ld\n", plus_long_vol(10000));
    printf("%ld\n", plus_long_vol(100000));
    printf("%ld\n", plus_long_vol(1000000));
    printf("%ld\n", plus_long_vol(10000000));

}