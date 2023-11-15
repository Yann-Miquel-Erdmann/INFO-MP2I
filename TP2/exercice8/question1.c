#include <stdio.h>
#include <stdbool.h>


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
    bool rep = verifier(5,10);
}