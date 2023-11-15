#include <stdio.h>
#include <math.h>
#include <assert.h>

// renvoit le nombre de solution du polynome du seconde degré et stocke les solutions aux adresses x1 et x2
int quadratic_solve(float a,float b, float c, float * x1, float * x2){
    assert(x1 != NULL);
    assert(x2 != NULL);
    int delta = b*b-4*a*c ;// calcul du discriminant
    if(delta<0){ //discriminant négatif pas de sols réelles
        return 0;
    }
    if (delta ==0) { //discriminant nul donc 1 sol réelle
        *x1 = -b/(2*a);
        return 1;
    }else{ //discriminant >0 donc 2 sols réelles
        *x1 = (-b + sqrt(delta))/(2*a);
        *x2 = (-b - sqrt(delta))/(2*a);
        return 2;
    }
}   
    

int main(){
    float a,b,c;
    float res1, res2;
    printf("entrez les coéfficients du polynome du second degré: a b c pour aX² + bX + c = 0 \n");
    scanf("%f %f %f", &a,&b,&c);
    int sols = quadratic_solve(a,b,c,&res1,&res2);
    printf("Il y a %d solutions", sols);
    if (sols == 1){
        printf(": %f", res1);
    }
    if (sols == 2){
        printf(": %f et %f", res1, res2);
    }
    printf("\n");
}