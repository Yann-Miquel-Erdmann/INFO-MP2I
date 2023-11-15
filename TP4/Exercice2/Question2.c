#include <stdio.h>
#include <assert.h>
#include <string.h>


int nb_occurences(char* filename, char* motif){
    FILE* f_in = fopen(filename, "r");	
	assert(f_in != NULL);

    int count = 0;
    char mot[31];
	while (fscanf(f_in, "%s", mot) != EOF){ // on s'arrête à la fin du fichier
        if (strcmp(mot, motif) == 0){
            count ++;
        }
	}
	fclose(f_in);
	return count;

}


int main(){
    char filename[20];
    char motif[31];
	printf("Rentrez un nom de fichier à lire: ");
	scanf("%s", filename);	
	printf("Rentrez un motif à compter: ");
	scanf("%s", motif);	
    printf("%d\n", nb_occurences(filename, motif));
}