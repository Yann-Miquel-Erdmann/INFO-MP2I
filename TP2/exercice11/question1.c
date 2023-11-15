#include <stdio.h>

// calcule le terme suivant de x dans la suite de Syracuse  
int suivant(int x){
    if (x%2 == 1){
        return 3*x+1;
    }else{
        return x/2;
    }
}

void main(){
    printf("%d\n", suivant(16));
}