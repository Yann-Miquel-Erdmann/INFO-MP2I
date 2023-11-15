#include <stdlib.h>
#include <assert.h>
#include <time.h>

// renvoie une matrice nulle de n colonnes et m lignes
int ** zeros(int n, int m){
    assert(n>=0 && m>=0);

    int ** matrice = malloc(m * sizeof(int*));
    for (int i = 0; i<m; i++){
        matrice[i] = malloc(n*sizeof(int));
        for (int j = 0; j<n;j++){
            matrice[i][j] = 0;
        }
    }
    return matrice;
}

// renvoie une matrice de n colonnes et m lignes avec a<=matrice[m][n]<=b
int ** rand_mat(int n, int m, int a, int b){
    assert(b>=a);
    assert(n>=0 && m>=0);

    srand(time(NULL));

    int ** matrice = malloc(m * sizeof(int*));
    for (int i = 0; i<m; i++){
        matrice[i] = malloc(n*sizeof(int));
        for (int j = 0; j<n;j++){
            matrice[i][j] = rand()%(b-a+1) + a;
        }
    }
    return matrice;
}



void main(){
    int x = 10,y = 10;
    int ** matrice = zeros(x,y);
    for (int i = 0; i<y;i++){
        for (int j = 0;j<x;j++){
            assert(matrice[i][j] == 0);
        }
    }
    for (int i = 0; i<y;i++ ){
        free(matrice[i]);
    }
    free(matrice);

    x = 10,y = 0;
    matrice = zeros(x,y);
    for (int i = 0; i<y;i++){
        for (int j = 0;j<x;j++){
            assert(matrice[i][j] == 0);
        }
    }
    for (int i = 0; i<y;i++ ){
        free(matrice[i]);
    }
    free(matrice);

    x = 0,y = 10;
    matrice = zeros(x,y);
    for (int i = 0; i<y;i++){
        for (int j = 0;j<x;j++){
            assert(matrice[i][j] == 0);
        }
    }
    for (int i = 0; i<y;i++ ){
        free(matrice[i]);
    }
    free(matrice);


    x = 10,y = 10;
    int a=0, b= 10;
    matrice = rand_mat(x,y,a,b);
    for (int i = 0; i<y;i++){
        for (int j = 0;j<x;j++){
            assert(matrice[i][j]>=a && matrice[i][j]<=b);
        }
    }
    for (int i = 0; i<y;i++ ){
        free(matrice[i]);
    }
    free(matrice);

    x = 10,y = 10, a=-10, b= 0;
    matrice = rand_mat(x,y,a,b);
    for (int i = 0; i<y;i++){
        for (int j = 0;j<x;j++){
            assert(matrice[i][j]>=a && matrice[i][j]<=b);
        }
    }
    for (int i = 0; i<y;i++ ){
        free(matrice[i]);
    }
    free(matrice);

    x = 10,y = 10, a=-5, b= 5;
    matrice = rand_mat(x,y,a,b);
    for (int i = 0; i<y;i++){
        for (int j = 0;j<x;j++){
            assert(matrice[i][j]>=a && matrice[i][j]<=b);
        }
    }
    for (int i = 0; i<y;i++ ){
        free(matrice[i]);
    }
    free(matrice);
}