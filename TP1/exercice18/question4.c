#include <stdlib.h>
#include <stdio.h>
#include <time.h>


void main(){
    // choix de la seed pour l'aléatoire
    srand(time(NULL));

    int x1,x2,x3;


    x1 = 10 + rand()%11;
    x2 = 10 + rand()%11;
    x3 = 10 + rand()%11;
    
    printf("Voici trois nombres aléatoires entre 10 et 20: %d, %d, %d\n", x1,x2,x3);

}