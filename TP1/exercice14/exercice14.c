#include <stdio.h>

void main(){
    int x,y;

    printf("Entrez x: ");
    scanf("%d", &x);

    printf("Entrez y: ");
    scanf("%d", &y);

    if (x < y){
        printf("oui\n");
    }else{
        printf("non\n");
    }
}