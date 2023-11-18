#include <stdio.h>
#include <stdlib.h>

// affiche le carré de l'entier donné en paramètres
int main(int argc, char** argv){
    if (argc == 1){
        printf("Vous devez donner un entier comme argument!\n");
        exit(2);
    }
    int nombre = atoi(argv[1]);
    printf("%d\n", nombre*nombre);
}