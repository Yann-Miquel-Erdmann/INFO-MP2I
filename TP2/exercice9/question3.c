#include <stdio.h>



// écrit en console un entier chiffre par chiffe en revenant à la ligne 
void recc(int n){
    if (n < 0){
        printf("-\n");
        n = -1*n;
    }
    if (n != 0){
        int rep = n/10;
        recc(rep);
        printf("%d\n",n-rep*10);  // n-rep*10 = n-n/10*10--> chiffre le plus à droite (unités)

    }
}


void main(){
    recc(-894);
}