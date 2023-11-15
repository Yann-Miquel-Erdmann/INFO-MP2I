#include <stdlib.h>
#include <stdio.h>
#include <time.h>


void main(){
    // choix de la seed pour l'aléatoire
    srand(time(NULL));

    int x = rand();
    int y = rand();

    printf("x: %d, y: %d\n", x, y);

}