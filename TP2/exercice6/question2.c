#include <stdio.h>

//  demande un entier n et affiche touts les entiers de affiche 2i+1 fois -  et | à la i emme ligne avec i de 0 à n 
void main(){
    int n;
    printf("entrez un entier n: ");
    scanf("%d", &n);
    for (int i = 0; i<n;i++){
        for (int k = 0; k<2*i+1;k++){
            printf("-");
        }
        printf("|\n");
    }
}