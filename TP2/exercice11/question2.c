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
int syracuse(int x, int n){
    for(int i; i<n;i++){
        x = suivant(x);
    } 
    return x;
}

void main(){
    printf("%d\n", syracuse(9,6));
    printf("%d\n", syracuse(77,128));
    printf("%d\n", syracuse(1023,729));
    printf("%d\n", syracuse(1234567,52397));
}