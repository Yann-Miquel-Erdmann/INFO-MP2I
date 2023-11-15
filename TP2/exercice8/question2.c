#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// renvoit true si target est égal à guess, false sinon et affiche des indications quant à target par rapport à guess 
bool verifier(int target,int guess){
    if (guess == target){
        printf("égal\n");
        return true;
    }
    if (guess < target){
        printf("plus haut\n");
        return false;
    }
    printf("plus bas\n");
    return false;
}

void main(){
    printf("touvez le nombre entre 0 et 4999\n");
    srand(time(NULL));

    int target = rand()%5000; 
    int guess;
    scanf("%d", &guess);
    while (!verifier(target,guess)){
        scanf("%d", &guess);
    }
    printf("Bravo! Vous avez trouvé!\n");
}   