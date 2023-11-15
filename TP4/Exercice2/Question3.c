#include <stdio.h>
#include <assert.h>
#include <string.h>

void retourne_mot(char * mot){
    char temp[30];
    int i= 0; 
    while (mot[i]!='\0'){ 
        i++;
    } 
    i--;
    for (int a= 0; a<=i; a++){
        temp[a] = mot[i-a];
    }
    temp[i+1] = '\0';
    strcpy(mot,temp);
}

void retourne_fichier(char* in_fn, char* out_fn){
    FILE* f_in = fopen(in_fn, "r");	
	assert(f_in != NULL);

    FILE* f_out = fopen(out_fn, "w");	
	assert(f_out != NULL);

    char mot[31];
	while (fscanf(f_in, "%s", mot) != EOF){ // on s'arrête à la fin du fichier
        retourne_mot(mot);
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


int main(){
    char fn_out[20];
    char fn_in[20];
	printf("Rentrez un nom de fichier à lire: ");
	scanf("%s", fn_in);	
	printf("Rentrez un nom de fichier où écrire: ");
	scanf("%s", fn_out);	
    retourne_fichier(fn_in, fn_out);
}