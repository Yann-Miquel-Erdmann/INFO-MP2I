#include <stdio.h>
#include <assert.h>


// lit des entiers dans le fichier filename jusqu'a tomber sur un zéro, renvoie le nombre d'entiers lus
int premier_zero(char* filename){
    FILE* f_in = fopen(filename, "r");	
	assert(f_in != NULL);

    int n;
    int count = 0;
	while (fscanf(f_in, "%d", &n) != EOF){ // on s'arrête à la fin du fichier
		if (n == 0){
            fclose(f_in);
			return count;
		}
		count++;
	}
	fclose(f_in);
	return -1;

}


int main(){
    char filename[20];
	printf("Rentrez un nom de fichier à lire: ");
	scanf("%s", filename);	
    printf("%d\n", premier_zero(filename));
}