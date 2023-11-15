#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

float moy(int ** g, int n, int m, int i, int j){
    int sum = 0;
    int count = 0;
    int offset[3] = {-1, 0, 1};
    for (int a = 0; a<3;a++){
        for (int b = 0; b<3;b++){
            if ((0<=i+offset[a] && i+offset[a]<m) && (0<=j+offset[b] && j+offset[b]<n) && (a != 1 || b != 1)){
                sum += g[i+offset[a]][j+offset[b]];
                count++;
            }
        } 
    } 
    

    if (count == 0){
        return 0;
    }
    

    return (float)sum/count;
}

void min_moy( int ** g, int n, int m){
    
    for (int i = 0; i<m ; i++){
        for (int j = 0; j<n;j++){
            
        }
    }
}

void main(){
    int ** matrice = malloc(3 * sizeof(int*));
    matrice[0] = malloc(3 * sizeof(int));
    matrice[1] = malloc(3 * sizeof(int));
    matrice[2] = malloc(3 * sizeof(int));
    matrice[0][0] = 2;
    matrice[0][1] = 1;
    matrice[0][2] = 3;
    matrice[1][0] = 6;
    matrice[1][1] = 0;
    matrice[1][2] = 1;
    matrice[2][0] = 2;
    matrice[2][1] = 3;
    matrice[2][2] = 6;


    printf("%f\n",moy(matrice,3,3,2,2));

}

