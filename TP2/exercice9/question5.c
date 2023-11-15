#include <stdio.h>



// écrit en console pour chacun de ses chiffres O fois le chiffre correspondant en revenant à la ligne après chaque chiffre 
void recc(int n){
    if (n < 0){
        printf("-\n");
        n = -1*n;
    }

    if (n == 0){
        printf("\n");
        return;
    }
    if (n<10){
        printf("O");
        recc(n-1);
        return;
    }

    int rep = n/10;
    recc(rep);
    recc(n-rep*10);

}


void main(){
    recc(-894);
}