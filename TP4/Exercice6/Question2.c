#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <stdio.h>

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

// libère la mémoire de ma matrice g de dimention n
void free_mat(int ** g, int n){
    assert(n>=0);
    for (int i = 0; i<n;i++){
        free(g[i]);
    }
    free(g);
}

// affiche le contenu de la matrice g de dimentions n*m
void print_mat(int **g , int n, int m){
    assert(n>=0 && m>=0); // la matrice est invalide
    if (n==0 || m==0){ // il n'y a rien a afficher mais la martice est valide
        return;
    }
    for (int i = 0; i<m ; i++){
        for (int j = 0; j<n;j++){
            printf("%d ", g[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void main(){
    int x = 10,y = 10;
    int ** matrice = zeros(x,y);
    print_mat(matrice, x,y);
    free_mat(matrice, y);
    
    x = 0,y = 10;
    matrice = zeros(x,y);
    print_mat(matrice, x,y);
    free_mat(matrice, y);
    
    x = 10,y = 0;
    matrice = zeros(x,y);
    print_mat(matrice, x,y);
    free_mat(matrice, y);


    x = 10,y = 10;
    int a=0, b= 10;
    matrice = rand_mat(x,y,a,b);
    print_mat(matrice, x,y);
    free_mat(matrice, y);
    
    x = 10,y = 10, a=-10, b= 0;
    matrice = rand_mat(x,y,a,b);
    print_mat(matrice, x,y);
    free_mat(matrice, y);
    
    x = 10,y = 10, a=-5, b= 5;
    matrice = rand_mat(x,y,a,b);
    print_mat(matrice, x,y);
    free_mat(matrice, y);
}