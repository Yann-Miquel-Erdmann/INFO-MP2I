#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


int ma_getline(char **buffer, unsigned long int * n,FILE * f){
    if (*buffer == NULL){
        *n = 30;
        (*buffer) = malloc((*n)*sizeof(char));
    }

    int len = -1;
    char lettre = 0; 
    while (lettre != 10 && fscanf(f,"%c",&lettre) != EOF){
        len ++;
        if ((unsigned) len == *n){
            *buffer = realloc(*buffer, 2*(*n)*sizeof(char));
        }
        (*buffer)[len] = lettre;
    }


    if ((unsigned) len +1 == *n){
            *buffer = realloc(*buffer, 2*(*n)*sizeof(char));
    }
    (*buffer)[len+1] = '\0';
    return len;
}


int main(int argc, char** argv){
    assert(argc > 1);

    FILE* f_in = fopen(argv[1], "r");

    assert(f_in != NULL);

    int count = 1; 
    char * ligne = NULL;
    long unsigned int n = 0;

    while(ma_getline(&ligne, &n, f_in) != -1){
        printf("%d. %s", count,ligne);
        count ++;
        
        free(ligne);
        ligne = NULL;
    }

    free(ligne);


    printf("\n");
    fclose(f_in);


}