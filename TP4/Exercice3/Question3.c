#include <stdio.h>
#include <stdlib.h>
#include <assert.h>







void copy(char* in_fn, char* out_fn){
    FILE* f_in = fopen(in_fn, "r");	
	assert(f_in != NULL);

    FILE* f_out = fopen(out_fn, "w");	
	assert(f_out != NULL);

    char mot[31];
	while (fscanf(f_in, "%s", mot) != EOF){ // on s'arrête à la fin du fichier
        fprintf(f_out, "%s", mot);
        
        char espace;
        fscanf(f_in,"%c", &espace);

        if (espace == 32){
            fprintf(f_out," ");
        }
        if (espace == 10){
            fprintf(f_out,"\n");
        }
	}
	fclose(f_in);
	fclose(f_out);

}





int main(int argc, char** argv){
    if (argc <2){
        printf("Vous devez donner un entier comme argument!\n");
        exit(2);
    }
    copy(argv[1],argv[2]);
}