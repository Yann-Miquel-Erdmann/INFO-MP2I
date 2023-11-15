#include <stdio.h>

// affiche les n premières cases d'un tableau d'entiers
void affiche(int* tab, int n){
    for (int i = 0; i<n;i++){
        printf("%d\n", tab[i]);        
    }
}


int main(){
    int t[6] = {2,3,5,1,-3,3};
    affiche(t,6);
}