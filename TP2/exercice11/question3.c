#include <stdio.h>

// calcule le terme suivant de x dans la suite de Syracuse  
int suivant(int x){
    if (x%2 == 1){
        return 3*x+1;
    }else{
        return x/2;
    }
}

// calcule le n eme terme dans la suite de syracuse en partant de x
int temps_de_vol(int x){
    int n = 0;
    while (x!=1){
        x = suivant(x);
        n++;
    }
    return n;
}

void main(){
    printf("%d\n", temps_de_vol(1));
    printf("%d\n", temps_de_vol(26));
    printf("%d\n", temps_de_vol(27));
    printf("%d\n", temps_de_vol(28));
    printf("%d\n", temps_de_vol(77030));
    printf("%d\n", temps_de_vol(77031));
}