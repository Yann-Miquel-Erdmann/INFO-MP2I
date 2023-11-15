#include <stdlib.h>
#include <stdio.h>
#include <time.h>


void main(){
    // choix de la seed pour l'aléatoire
    srand(time(NULL));

    int x = rand();
    
    printf("Voici un nombre aléatoire entre 0 et 99: %d\n", x%100);

}