#include <stdio.h>

void main(){
    float x;
    printf("entrez un entier: ");
    scanf("%f", &x);
    if (x < -0.33){
        printf("CAS A\n");
    } 
    if (x >= -0.33 && x <= 7.89){
        printf("CAS B\n");

    }
    if (x > 7.89){

        printf("CAS C\n");

    }


}