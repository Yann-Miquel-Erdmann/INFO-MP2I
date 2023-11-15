#include <stdio.h>
#include <assert.h>

int main(){
	char filename_in[20], filename_out[20];
	printf("Rentrez un nom de fichier à lire: ");
	scanf("%s", filename_in);	
	printf("Rentrez un nom de fichier pour écrire la somme: ");
	scanf("%s", filename_out);
	
	// ouverture du fichier d'entrée: mode lecture
	FILE* f_in = fopen(filename_in, "r");	
	assert(f_in != NULL);	
	
	int sum = 0, n = 0;
	while (fscanf(f_in, "%d", &n) != EOF){ // on s'arrête à la fin du fichier
		sum += n;
	}
	fclose(f_in);

	// écrire la somme dans le fichier de sortie: mode écriture
	FILE* f_out = fopen(filename_out, "w");	
	assert(f_out != NULL);
	fprintf(f_out, "%d\n", sum);
	fclose(f_out);

	return 0;	
}
