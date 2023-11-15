#include <stdio.h>

// fait la somme des entrées de l'utilisateur jusqu'à ce que l'entéee soit négative
void main(){
    int n;
    int s;

    scanf("%d", &n);
    while(n>=0){
        s += n;
        scanf("%d", &n);
    } 
    printf("%d\n", s);
}