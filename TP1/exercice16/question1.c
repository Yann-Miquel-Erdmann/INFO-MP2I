#include <stdio.h>

void main(){
    float x,y,z;
    printf("Entrez des valeurs pour x, y et z:\n");
    scanf("%f %f %f", &x,&y,&z);

    if ((x <= y && y <= z) || (z <= y && y <= x)){
        printf("%f\n", y);
        return;
    }

    if ((x <= z && z <= y) || (y <= z && z <= x)){
        printf("%f\n", z);
        return;

    }

    if ((y <= x && x <= z) || (z <= x && x <= y)){
        printf("%f\n", x);
        return;

    }
}