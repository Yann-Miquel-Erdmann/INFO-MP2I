#include <stdio.h>

// affiche un escalier de * de n marches
void main(){
    int n;
    printf("donnez n: ");
    scanf("%d", &n);
    for (int  i = 0; i < n; i++){
        for (int j = 0; j <= i; j++ ){
            printf("*");
        }
        printf("\n");
    }
}