#include <stdio.h>



// écrit en console un entier chiffre par chiffe en revenant à la ligne 
void recc(int n){
    if (n != 0){
        printf("O");
        recc(n-1);
    }else{
        printf("\n");
    }
}


void main(){
    recc(5);
}