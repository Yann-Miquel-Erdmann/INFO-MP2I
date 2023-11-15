#include <stdio.h>

void main(){
    int x;
    printf("entrez un entier: ");
    scanf("%d", &x);
    if (x == 0){
        printf("ce nombre vaut zéro\n");
    }else{
        printf("ce nombre ne vaut pas zéro\n");
    }

}