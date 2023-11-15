#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

/* Mémoire adressable simple

Ce programme permet à l'utilisateur de manier une (fausse) mémoire d'entiers.
Il choisit une taille de mémoire, puis peut lire, écrire et effectuer des
additions. */

#define MAX_SIZE 1024

int size; // taille réelle de la mémoire
int mem_tab[MAX_SIZE]; // tableau des cases mémoires
bool no_value[MAX_SIZE]; // no_value[i] = 1 si une case n'a jamais reçu de valeur

/* Teste si l'indice i est valide pour une lecture,
   i.e. si la case i existe dans la mémoire
   Si ce n'est pas le cas, lève une erreur d'assertion. */
void assert_write(int i){
	assert(0 <= i && i < size);	
}

/* Teste si l'indice i est valide pour une lecture,
   i.e. si la case i existe et contient une vraie valeur.
   Si ce n'est pas le cas, lève une erreur d'assertion. */
void assert_read(int i){
	
}



/* Renvoie l'entier contenu dans la case i de la mémoire, si
   i est une case valide à lire. */
int get(int i){
	assert_read(i);
	return mem_tab[i];
}

/* Pour stocker une valeur */
void set(int i, int x){
	
}


/* Pour l'addition */




int main()
{
	// initialisation
	printf("Choisir la taille de la mémoire: ");
	scanf("%d", &size);

	// au départ, toutes les cases sont invalides à lire
	for (int i = 0; i < size; ++i)
	{
		no_value[i] = true;
	}

	int i, j, k, x; // pour la saisie de l'utilisateur

	// boucle Input/Ouput
	bool quit = false;
	while (!quit){
		int choix;
		printf("Que voulez vous faire\n");
		printf("1. Accéder à une valeur\n");
		printf("2. Stocker une valeur\n");
		printf("3. Faire une addition\n");
		printf("4. Quitter le programme\n");
		printf("Choix :");
		scanf("%d", &choix);

		// traiter le choix

	}

	printf("Au revoir\n");
	return 0;
}