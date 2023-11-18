#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


// renvoie la moyenne des valeurs des voisins de l'élément à l'indice i,j dans la matrice m de taille n,m 
float moy(int ** g, int n, int m, int i, int j){
    int sum = 0;
    int count = 0;
    int offset[3] = {-1, 0, 1};
    for (int a = 0; a<3;a++){
        for (int b = 0; b<3;b++){
            if ((0<=j+offset[a] && j+offset[a]<m) && (0<=i+offset[b] && i+offset[b]<n) && (a != 1 || b != 1)){
                sum += g[j+offset[a]][i+offset[b]];
                count++;
            }
        } 
    } 
    

    if (count == 0){
        return 0;
    }
    

    return (float)sum/count;
}


// affiche les indices des éléments pour lesquels le résultat par la fonction moy est minimal
void min_moy( int ** g, int n, int m){
    int count = 0; 
    int * x_index = malloc(n * m * sizeof(int));
    int * y_index = malloc(n * m * sizeof(int));

    float moy_top = moy(g, n, m, 0,0);
    for (int j = 0; j<m ; j++){
        for (int i = 0; i<n;i++){
            float moyenne = moy(g, n, m, i,j);
            if (moyenne < moy_top){
                moy_top = moyenne;
                count = 0;
                x_index[count] = i;
                y_index[count] = j;
                count ++;

            }else{
                if (moyenne == moy_top){
                    x_index[count] = i;
                    y_index[count] = j;
                    count ++;

                }
            }
        }
    }
    printf("Indices avec la plus petite moyenne\n");
    for (int i = 0; i < count; i++){
        printf("(%d, %d)    ", x_index[i], y_index[i]);
    }
    printf("\n");

    free(x_index);
    free(y_index);
}

void main(){
    int n = 3,m = 3;
    int ** matrice = malloc(n * sizeof(int*));
    matrice[0] = malloc(n * sizeof(int));
    matrice[1] = malloc(n * sizeof(int));
    matrice[2] = malloc(3 * sizeof(int));
    
    matrice[0][0] = 4;
    matrice[0][1] = 4;
    matrice[0][2] = 4;
    matrice[1][0] = 4;
    matrice[1][1] = 4;
    matrice[1][2] = 4;
    matrice[2][0] = 4;
    matrice[2][1] = 4;
    matrice[2][2] = 4;


    min_moy(matrice, 3,2);
    for (int i =0; i<m; i++){
        free(matrice[i]);
    }
    free(matrice);
}

