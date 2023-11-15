#include <stdio.h>

//  demande un entier n et affiche touts les entiers de 1 à n
void main(){
    int n;
    printf("entrez un entier n: ");
    scanf("%d", &n);
    for (int i = 0; i<=n;i++){
        printf("%d\n", i);
    }
}