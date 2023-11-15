#include <stdio.h>
#include <stdbool.h>
#include <assert.h>


/* Lit un entier dans le terminal.
- Si la lecture réussit, alors la fonction renvoie true et stocke l'entier lu 
  dans res. 
- Si la lecture est infructueuse, alors la fonction renvoie false. 
Dans les deux cas, l'entrée du terminal est ensuite vidée de tout caractère 
additionnel */
bool read_int_and_flush(int* res){
	char c;
	bool succes = scanf("%d",res);  // succes est vrai s'il était possible de lire un entier faux sinon 
	do {   // on vide l'entrée du terminal
		scanf("%c", &c);
	} while (c != '\n');
	return succes;
}





int main(){
	int x = 1;
	do
	{
		printf("Rentrez un entier (0 pour finir): ");
		bool b = read_int_and_flush(&x);
		if (b){
			printf("Entier lu: %d\n", x);			
		} else {
			printf("Erreur de lecture\n");
		}
	} while (x != 0);
}