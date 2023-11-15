#include <stdio.h>

// fonction recursive qui affiche les n premier entier de manière décroisssante
void recc(int n){
    if (n<=0){
        return;
    }
    if (n == 1){
        printf("1\n");
    }else{
        printf("%d\n", n);
        recc(n-1);
    }

}

void main(){
    recc(5);
}