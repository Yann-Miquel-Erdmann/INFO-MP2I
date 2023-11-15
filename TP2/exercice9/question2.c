#include <stdio.h>

// fonction recursive qui affiche les n premier entier de manière croisssante
void recc(int n){
    if (n<=0){
        return;
    }
    if (n == 1){
        printf("1\n");
    }else{
        recc(n-1);
        printf("%d\n", n);

    }

}

void main(){
    recc(5);
}