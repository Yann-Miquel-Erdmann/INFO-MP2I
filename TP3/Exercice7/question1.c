#include <stdio.h>

// calcule la somme des n premiers entiers de t. n doit être <= 100 
int somme(int* tab, int n){
    int res = 0;
    for (int i = 0; i<n;i++){
        res += tab[i];
    }
    return res;
}


int main(){
    int t[6] = {2,3,5,1,-3,3};
    printf("%d\n", somme(t,6));
}