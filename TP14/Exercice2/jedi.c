#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct jedi {
    char* prenom;
    char* nom;
    struct jedi** apprentis;
    int n;  // nombre d'apprentis
};

typedef struct jedi JEDI;

bool est_lignee(JEDI* j, char* prenom, char* nom) {
    if (j == NULL) {
        return false;
    }

    // test du noeud actuel
    // RAPPEL: strcmp(a, b) renvoie 0 si a et b sont égaux, un nombre négatif
    // si a < b dans l'ordre lexicographique, et un nombre positif si a > b
    // Pour plus d'informations: tapez "man strcmp" dans le terminal
    if (strcmp(prenom, j->prenom) == 0 && strcmp(nom, j->nom) == 0) {
        return true;
    }

    // recherche récursive. On n'est pas dans une structure d'ABR donc
    // il faut chercher dans tous les enfants
    for (int i = 0; i < j->n; ++i) {
        if (est_lignee(j->apprentis[i], prenom, nom)) {
            return true;
        }
    }

    return false;
}

JEDI* load_jedi(char* prenom, char* nom) {
    
	
	char* filename = malloc(128 * sizeof(char));
    filename[0] = '\0';
    strcat(filename, "data/");
    strcat(filename, prenom);
    strcat(filename, "_");
    strcat(filename, nom);
    strcat(filename, ".txt");
    FILE* f = fopen(filename, "r");
    
	printf("%s\n", filename);
	
	free(filename);

    JEDI* j = malloc(sizeof(JEDI));
    j->prenom = malloc(128 * sizeof(char));
    j->nom = malloc(128 * sizeof(char));

	fscanf(f,"%s", j->prenom);
	fscanf(f,"%s", j->nom);
    
	j->n = 0;
    fscanf(f, "%d", &(j->n));
    j->apprentis = malloc(j->n * sizeof(JEDI));
    for (int i = 0; i < j->n; i++) {
        char* prenom = malloc(64 * sizeof(char));
        char* nom = malloc(64 * sizeof(char));
        fscanf(f, "%s", prenom);
        fscanf(f, "%s", nom);
		j->apprentis[i] = load_jedi(prenom, nom);
    }


	fclose(f);

	return j;
}

void _print_jedi(JEDI* j, int ind) {
	for (int i = 0 ; i< ind; i++){
		printf("\t");
	}
	printf("%s %s:", j->prenom, j->nom);
	if (j->n == 0){
		printf("[Pas  d'apprenti]");
	}else{
		for (int a = 0; a<j->n; a++){
			_print_jedi(j->apprentis[a], ind+1);
		}
	}
}

void print_jedi(JEDI* j){
	_print_jedi(j, 0);
}



int main(){
	JEDI* j = load_jedi("feria", "lokalis");
	print_jedi(j);
}