#include <stdio.h>
#include <stdbool.h>


// renvoie true si b divise a, flase sinon
bool diviseur(int a, int b){
    if (a%b == 0){
        return true;
    }
    return false;
}

// affiche x et son inverse
float inverse(float x){
    printf("x: %f , 1/x: %f", x, 1/x);
    return 1/x; //pour les cas de test
}

//  calcule 3x+5y-6.25z+t, l'affiche et renvoit son carré
float fonction(float x, float y, float z, float t){
    float res = 3*x+5*y-6.25*z+t;
    printf("%f", res);
    return res*res;
}

// teste les fonctions précédentes
void tester(){
    if (diviseur(10,5) == true){
        printf("pass\n");
    }else{
        printf("error\n");
    }
    if (diviseur(3,5) == false){
        printf("pass\n");
    }else{
        printf("error\n");
    }
    if (diviseur(5,5) == true){
        printf("pass\n");
    }else{
        printf("error\n");
    }


    if (inverse(1) == 1){
        printf("pass\n");
    }else{
        printf("error\n");
    }
    if (inverse(2) == 0.5){
        printf("pass\n");
    }else{
        printf("error\n");
    }
    if (inverse(-0.2) == -5){
        printf("pass\n");
    }else{
        printf("error\n");
    }


    if (fonction(5, 3, 4, -5) == 0){
        printf("pass\n");
    }else{
        printf("error\n");
    }
    if (fonction(0,0,0,0) == 0){
        printf("pass\n");
    }else{
        printf("error\n");
    }
    if (fonction(-5,-3,-4,5) == 0){
        printf("pass\n");
    }else{
        printf("error\n");
    }
}

void main(){
    tester();
}