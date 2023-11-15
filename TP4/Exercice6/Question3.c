#include <stdlib.h>
#include <assert.h>

int ** somme_mat(int **g1, int **g2, int n, int m){
    assert(n>=0 && m>=0);

    int ** resultat = malloc(m * sizeof(int*));
    for(int i = 0; i<m; i++){
        resultat[i] = malloc(n*sizeof(int));
        for (int j = 0; j<n;j++){
            resultat[i][j] = g1[i][j] + g2[i][j];
        }
    }

    return resultat;
}

