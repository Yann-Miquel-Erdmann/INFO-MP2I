#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

// lit n flotants dans le fichier f et les stocke dans un tableau puis renvoie le tableau 
float * lire_flottants(FILE *f,int*n){
    float * flottants = malloc(*n*sizeof(float));

    int count = 0;
    float read;
    while (fscanf(f,"%f",&read) != EOF && count <(*n)){
        flottants[count] = read;
        count+=1;
    }
    if (count < (*n)){
        *n = count;
    }
    return flottants;
}


void main(){
    int n = 5;
    FILE* f = fopen("flottants_cas1.txt", "r");
    assert(f != NULL);

    float * flottants = lire_flottants(f,&n);
    assert( n == 5);
    float liste[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
    for (int i = 0; i<5;i++){
        assert(flottants[i] == liste[i]);
    }
    fclose(f);
    free(flottants);


    n = 5;
    f = fopen("flottants_cas2.txt", "r");
    assert(f != NULL);
    flottants = lire_flottants(f,&n);
    assert( n == 3);
    float liste2[3] = {1.1, 2.2, 3.3};
    for (int i = 0; i<3;i++){
        assert(flottants[i] == liste2[i]);
    }
    fclose(f);
    free(flottants);


    n = 5;
    f = fopen("flottants_cas3.txt", "r");
    assert(f != NULL);
    flottants = lire_flottants(f,&n);
    assert( n == 5);
    float liste3[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
    for (int i = 0; i<5;i++){
        assert(flottants[i] == liste3[i]);
    }
    fclose(f);
    free(flottants);

}