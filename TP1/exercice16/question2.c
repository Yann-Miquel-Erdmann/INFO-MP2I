#include <stdio.h>

// 
void main(){
    int x;
    printf("Entrez un entier: ");
    scanf("%d", &x);

    if (x % 3 == 0){
        printf("gou");
    }
    if (x%5 == 0){
        printf("ba");    
    }

    if ((x % 3 != 0) && (x % 5 != 0)){
        printf("%d", x);
    }
    printf("\n");
}