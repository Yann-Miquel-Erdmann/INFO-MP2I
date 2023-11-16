#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


int main(int argc, char** argv){
    assert(argc > 1);

    FILE* f_in = fopen(argv[1], "r");

    assert(f_in != NULL);

    int count = 1; 
    char * ligne = NULL;
    long unsigned int n = 0;

    while(getline(&ligne, &n, f_in) != -1){
        printf("%d. %s", count,ligne);
        count ++;
        
        free(ligne);
        ligne = NULL;
    }

    free(ligne);


    printf("\n");
    fclose(f_in);


}